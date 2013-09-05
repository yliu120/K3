{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE PatternGuards #-}
{-# LANGUAGE QuasiQuotes #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE ViewPatterns #-}

-- TODO:
-- Sends
-- HList record labels
-- Record data types for annotated collections
-- Top-level type declarations for globals
-- Determine if purify expression and annotations are needed

-- | K3-to-Haskell code generation.
module Language.K3.Codegen.Haskell where

import Control.Arrow
import Control.Applicative
import Control.Concurrent.MVar
import Control.Monad.State
import Control.Monad.Trans.Either

import Data.List

import Language.K3.Core.Annotation
import Language.K3.Core.Annotation.Codegen
import Language.K3.Core.Common
import Language.K3.Core.Declaration
import Language.K3.Core.Expression
import Language.K3.Core.Type

import qualified Language.Haskell.Exts.Build  as HB
import qualified Language.Haskell.Exts.SrcLoc as HL
import qualified Language.Haskell.Exts.Syntax as HS

import Language.Haskell.Exts.QQ (hs,dec,ty)

data CodeGenerationError = CodeGenerationError String

type SymbolCounters = [(Identifier, Int)]
type RecordLabels   = [Identifier]
type RecordSpec     = [(Identifier, HS.Type, HS.Exp)] -- TODO: separate lifted vs regular attrs.
type RecordSpecs    = [(Identifier, RecordSpec)]

data AnnotationState = AnnotationState { annotationSpecs  :: RecordSpecs
                                       , compositionSpecs :: RecordSpecs }

type CGState = (SymbolCounters, RecordLabels, AnnotationState)

-- | The code generation monad. This supports CG errors, and stateful operation
--   for symbol generation and type-directed declarations (e.g., record and collection types)
type CodeGeneration = EitherT CodeGenerationError (State CGState)

data HaskellEmbedding
    = HProgram      HS.Module
    | HModule       [HS.Decl]
    | HDeclaration  HS.Decl
    | HExpression   HS.Exp
    | HType         HS.Type
    | HNoRepr
    deriving (Eq, Show)

-- | Runs the code generation monad, yielding a possibly erroneous result, and a final state.
runCodeGeneration :: CGState -> CodeGeneration a -> (Either CodeGenerationError a, CGState)
runCodeGeneration s = flip runState s . runEitherT

{- Code generation state accessors -}
getSymbolCounters :: CGState -> SymbolCounters
getSymbolCounters (x,_,_) = x

modifySymbolCounters :: (SymbolCounters -> (a, SymbolCounters)) -> CGState -> (a, CGState)
modifySymbolCounters f (x,y,z) = (r, (nx, y, z))
  where (r,nx) = f x

getRecordLabels :: CGState -> RecordLabels
getRecordLabels (_,x,_) = x

modifyRecordLabels :: (RecordLabels -> RecordLabels) -> CGState -> CGState 
modifyRecordLabels f (x,y,z) = (x, f y, z)

getAnnotationState :: CGState -> AnnotationState
getAnnotationState (_,_,x) = x

modifyAnnotationState :: (AnnotationState -> AnnotationState) -> CGState -> CGState
modifyAnnotationState f (x,y,z) = (x, y, f z)


{- Code generator monad methods -}

throwCG :: CodeGenerationError -> CodeGeneration a
throwCG = Control.Monad.Trans.Either.left

gensymCG :: Identifier -> CodeGeneration Identifier
gensymCG n = state $ modifySymbolCounters $ \c -> modifyAssoc c n incrSym
  where incrSym Nothing  = (n ++ show (0::Int), 1)
        incrSym (Just i) = (n ++ show i, i+1)

addLabel :: Identifier -> CodeGeneration ()
addLabel n = modify $ modifyRecordLabels $ nub . (n:)

getAnnotationSpec :: Identifier -> CodeGeneration (Maybe RecordSpec)
getAnnotationSpec n = get >>= return . lookup n . annotationSpecs . getAnnotationState

getCompositionSpec :: Identifier -> CodeGeneration (Maybe RecordSpec)
getCompositionSpec n = get >>= return . lookup n . compositionSpecs . getAnnotationState

modifyAnnotationSpecs :: (RecordSpecs -> RecordSpecs) -> CodeGeneration ()
modifyAnnotationSpecs f =
  modify $ modifyAnnotationState (\s -> AnnotationState (f $ annotationSpecs s) (compositionSpecs s))

modifyCompositionSpecs :: (RecordSpecs -> RecordSpecs) -> CodeGeneration ()
modifyCompositionSpecs f =
  modify $ modifyAnnotationState (\s -> AnnotationState (annotationSpecs s) (f $ compositionSpecs s))


{- Symbols and identifiers -}

-- TODO: remove, including call sites
gensym :: Identifier -> Identifier
gensym = id

-- TODO: duplicate of interpreter. Move into common utils.
annotationNamesT :: [Annotation Type] -> [Identifier]
annotationNamesT anns = map extractId $ filter isTAnnotation anns
  where extractId (TAnnotation n) = n
        extractId _ = error "Invalid named annotation"

annotationNamesE :: [Annotation Expression] -> [Identifier]
annotationNamesE anns = map extractId $ filter isEAnnotation anns
  where extractId (EAnnotation n) = n
        extractId _ = error "Invalid named annotation"

annotationComboId :: [Identifier] -> Identifier
annotationComboId annIds = intercalate "_" annIds

annotationComboIdT :: [Annotation Type] -> Maybe Identifier
annotationComboIdT (annotationNamesT -> [])  = Nothing
annotationComboIdT (annotationNamesT -> ids) = Just $ annotationComboId ids

annotationComboIdE :: [Annotation Expression] -> Maybe Identifier
annotationComboIdE (annotationNamesE -> [])  = Nothing
annotationComboIdE (annotationNamesE -> ids) = Just $ annotationComboId ids


{- Code generation annotations -}

isStructure :: Annotation Expression -> Bool
isStructure (EEmbedding (IOStructure _)) = True
isStructure _ = False

isLoad :: Annotation Expression -> Bool
isLoad (EEmbedding IOLoad) = True
isLoad _ = False

isStore :: Annotation Expression -> Bool
isStore (EEmbedding IOStore) = True
isStore _ = False


-- | Purity annotation extraction
structureQualifier :: PStructure -> PQualifier
structureQualifier = \case
    PLeaf q      -> q
    PSingle q _  -> q
    PComplex q _ -> q

qualifier :: [Annotation Expression] -> Maybe PQualifier
qualifier anns = case filter isStructure anns of
  []  -> Nothing
  [EEmbedding (IOStructure s)] -> Just $ structureQualifier s
  _   -> error "Ambiguous qualifier"

structure :: [Annotation Expression] -> Maybe PStructure
structure anns = case filter isStructure anns of
  [] -> Nothing
  [EEmbedding (IOStructure s)] -> Just s
  _ -> error "Ambiguous structure"

singleStructure :: [Annotation Expression] -> Maybe PStructure
singleStructure anns = case structure anns of
    Nothing -> Nothing
    Just (PSingle _ optS) -> Just optS
    _ -> error "Invalid single structure"

complexStructure :: [Annotation Expression] -> Maybe [PStructure]
complexStructure anns = case structure anns of
    Nothing -> Nothing
    Just (PComplex _ complexS) -> Just complexS
    _ -> error "Invalid complex structure"


load :: [Annotation Expression] -> Bool
load anns = not . null $ filter isLoad anns

store :: [Annotation Expression] -> Bool
store anns = not . null $ filter isStore anns


qualLoadError :: a
qualLoadError = error "Invalid structure qualifier and load combination" 

qualStoreError :: a
qualStoreError = error "Invalid structure qualifier and store combination" 

blockError :: a
blockError = error "Invalid do expression" 

seqDoError :: a
seqDoError = error "Invalid do-expression arguments"


{- Type embedding -}

namedType :: Identifier -> HS.Type
namedType n = HS.TyCon . HS.UnQual $ HB.name n

tyApp :: Identifier -> HS.Type -> HS.Type
tyApp n t = HS.TyApp (namedType n) t

unitType :: HS.Type
unitType = HS.TyCon $ HS.Special HS.UnitCon

maybeType :: HS.Type -> HS.Type
maybeType t = tyApp "Maybe" t

tupleType :: [HS.Type] -> HS.Type
tupleType = HS.TyTuple HS.Boxed

indirectionType :: HS.Type -> HS.Type
indirectionType t = tyApp "MVar" t

funType :: HS.Type -> HS.Type -> HS.Type
funType a r = HS.TyFun a r

listType :: HS.Type -> HS.Type
listType = HS.TyList 

ioType :: HS.Type -> HS.Type
ioType t = tyApp "IO" t

-- TODO: convert identifier to named type signature either here, or at call sites.
collectionType :: Identifier -> HS.Type
collectionType tCon = HS.TyCon $ HS.UnQual $ HB.name tCon

typ :: K3 Type -> CodeGeneration HaskellEmbedding
typ t = typ' t >>= return . HType

typ' :: K3 Type -> CodeGeneration HS.Type
typ' (tag -> TBool)       = return [ty| Bool    |]
typ' (tag -> TByte)       = return [ty| Word8   |]
typ' (tag -> TInt)        = return [ty| Int     |]
typ' (tag -> TReal)       = return [ty| Double  |]
typ' (tag -> TString)     = return [ty| String  |]
typ' (tag -> TAddress)    = return [ty| Address |]

typ' (tag &&& children -> (TOption,[x])) = typ' x >>= return . maybeType
typ' (tag -> TOption)                    = throwCG $ CodeGenerationError "Invalid option type"

typ' (tag &&& children -> (TTuple, ch)) = mapM typ' ch >>= return . tupleType

typ' (tag &&& children -> (TIndirection, [x])) = typ' x >>= return . indirectionType
typ' (tag -> TIndirection)                     = throwCG $ CodeGenerationError "Invalid indirection type"

typ' (tag &&& children -> (TFunction, [a,r])) = mapM typ' [a,r] >>= \chT -> return $ funType (head chT) (last chT)
typ' (tag -> TFunction)                       = throwCG $ CodeGenerationError "Invalid function type"

typ' (tag &&& children -> (TSink, [x])) = typ' x >>= return . flip funType unitType
typ' (tag -> TSink)                     = throwCG $ CodeGenerationError "Invalid sink type"

typ' (tag &&& children -> (TTrigger, [x])) = typ' x >>= return . flip funType unitType
typ' (tag -> TTrigger)                     = throwCG $ CodeGenerationError "Invalid trigger type"

-- TODO
typ' (tag &&& children -> (TRecord ids, ch)) = throwCG $ CodeGenerationError "Records types not implemented"

-- TODO: use collectionType above on annotation composition identifier
typ' (tag &&& children -> (TCollection, [x])) = throwCG $ CodeGenerationError "Collection types not implemented"
typ' (tag -> TCollection)                     = throwCG $ CodeGenerationError "Invalid collection type"

typ' _                    = undefined

{- Analysis -}

-- | Attaches purity annotations to a K3 expression tree.
purifyExpression :: K3 Expression -> K3 Expression
purifyExpression = undefined


{- Load-store wrappers -}

doStoreE :: HS.Exp -> HS.Exp
doStoreE e = [hs| newMVar ( $e ) |]

doBindE :: Identifier -> HS.Exp -> HS.Exp
doBindE n e = [hs| do
                      ((nN)) <- return $e
                      $nE |]
  where (nN, nE) = (HB.name n, HB.var $ HB.name n)

doLoadE :: Identifier -> HS.Exp -> HS.Exp
doLoadE n e = [hs| do
                      ((nN)) <- readMVar ( $e )
                      $nE |]
  where (nN, nE) = (HB.name n, HB.var $ HB.name n)

doLoadNameE :: Identifier -> HS.Exp
doLoadNameE n = HB.doE [bindE, HB.qualStmt rE]
  where r = gensym n
        nE = HB.var $ HB.name n
        rE = HB.var $ HB.name r
        bindE = HB.genStmt HL.noLoc (HB.pvar $ HB.name r) [hs| readMVar $nE |]

loadNameE :: [Annotation Expression] -> Identifier -> HS.Exp
loadNameE anns n = case (qualifier anns, load anns) of
  (Nothing, False)         -> varE
  (Just PImmutable, False) -> varE
  (Just PMutable, True)    -> doLoadNameE n
  _ -> qualLoadError
  where varE = HB.var $ HB.name n

storeE :: [Annotation Expression] -> HS.Exp -> HS.Exp
storeE anns e = case (qualifier anns, store anns) of
  (Nothing, False)         -> e
  (Just PImmutable, False) -> e
  (Just PMutable, True)    -> doStoreE e
  _ -> qualStoreError


{- Do-expression manipulation -}

-- | Extracts variable pattern bindings from a do-expression.
extractVarBindingsE :: HS.Exp -> [HS.Name]
extractVarBindingsE (HS.Do stmts) = concatMap extract stmts
  where extract (HS.Generator _ (HS.PVar n) _) = [n]
        extract _ = []

extractVarBindingsE _ = []

-- | Extracts a return value and a context from an expression. For do-expressions this
--   is the qualifier expression and the context is the remainder of the stmts.
--   For any other expression, the context is empty.
extractReturnE :: HS.Exp -> ([HS.Stmt], HS.Exp)
extractReturnE (HS.Do []) = blockError

extractReturnE (HS.Do stmts) = case (init stmts, last stmts) of
  ([], HS.Qualifier e) -> ([], e)
  (c, HS.Qualifier e)  -> (c, e)
  _ -> blockError

extractReturnE e = ([], e)

-- | Prepends a sequence of do-block statements to an expression.
prefixDoE :: [HS.Stmt] -> HS.Exp -> HS.Exp
prefixDoE [] e = e
prefixDoE context (HS.Do stmts) = HB.doE $ context ++ stmts
prefixDoE context e = HB.doE $ context ++ [HB.qualStmt e]

chainReturnE :: HS.Exp -> (HS.Exp -> HS.Exp) -> HS.Exp
chainReturnE e chainF = case extractReturnE e of
  ([], e')   -> chainF e'
  (ctxt, e') -> prefixDoE ctxt $ chainF e'

seqDoE :: HS.Exp -> HS.Exp -> HS.Exp
seqDoE e e2 = 
  let (eStmts, eRetE)   = extractReturnE e
      (e2Stmts, e2RetE) = extractReturnE e2
  in 
  case (eStmts, e2Stmts) of
    ([],[]) -> e2RetE
    _ -> HB.doE $ eStmts ++ e2Stmts ++ [HB.qualStmt e2RetE]

-- | Operator and data constructors applied to evaluated children.
--   TODO: alpha renaming for conflicting binding names during merge
applyE :: ([HS.Exp] -> HS.Exp) -> [HS.Exp] -> HS.Exp
applyE f subE = prefixDoE (concat contexts) $ f args
  where (contexts, args) = unzip $ map extractReturnE subE

unwrapE :: K3 Expression -> (Expression, [Annotation Expression], [K3 Expression])
unwrapE ((tag &&& annotations) &&& children -> ((e, anns), ch)) = (e, anns, ch)


-- | Default values for specific types
defaultValue :: K3 Type -> CodeGeneration HaskellEmbedding
defaultValue t = defaultValue' t >>= return . HExpression

defaultValue' :: K3 Type -> CodeGeneration HS.Exp
defaultValue' (tag -> TBool)       = return [hs| False |]
defaultValue' (tag -> TByte)       = return [hs| (0 :: Word8) |]
defaultValue' (tag -> TInt)        = return [hs| (0 :: Int) |]
defaultValue' (tag -> TReal)       = return [hs| (0 :: Double) |]
defaultValue' (tag -> TString)     = return [hs| "" |]
defaultValue' (tag -> TAddress)    = return [hs| defaultAddress |]

defaultValue' (tag &&& children -> (TOption, [x])) = defaultValue' x >>= \xD -> return [hs| Just $xD |]
defaultValue' (tag -> TOption)                     = throwCG $ CodeGenerationError "Invalid option type"

defaultValue' (tag &&& children -> (TTuple, ch)) = mapM defaultValue' ch >>= return . HB.tuple 

defaultValue' (tag &&& children -> (TIndirection, [x])) = defaultValue' x >>= \xD -> return [hs| newMVar $xD |]
defaultValue' (tag -> TIndirection)                     = throwCG $ CodeGenerationError "Invalid indirection type"

-- TODO
defaultValue' (tag &&& children -> (TRecord ids, ch))   = throwCG $ CodeGenerationError "Default records not implemented"
defaultValue' (tag &&& children -> (TCollection, [x]))  = throwCG $ CodeGenerationError "Default collections not implemented"

defaultValue' (tag -> TFunction) = throwCG $ CodeGenerationError "No default available for a function"
defaultValue' (tag -> TTrigger)  = throwCG $ CodeGenerationError "No default available for a trigger"
defaultValue' (tag -> TSink)     = throwCG $ CodeGenerationError "No default available for a sink"
defaultValue' (tag -> TSource)   = throwCG $ CodeGenerationError "No default available for a source"


{- Expression code generation -}

unary :: Operator -> K3 Expression -> CodeGeneration HS.Exp
unary op e = do
  e' <- expression' e
  return $ case op of
    ONeg -> chainReturnE e' HS.NegApp 
    ONot -> chainReturnE e' $ HB.app (HB.function "not")
    _ -> error "Invalid unary operator"

binary :: Operator -> K3 Expression -> K3 Expression -> CodeGeneration HS.Exp
binary op e e' = do
  eE  <- expression' e
  eE' <- expression' e'
  return $ case op of 
    OAdd -> doBinary True "+"  [eE, eE']
    OSub -> doBinary True "-"  [eE, eE']
    OMul -> doBinary True "*"  [eE, eE']
    ODiv -> doBinary True "/"  [eE, eE']
    OAnd -> doBinary True "&&" [eE, eE']
    OOr  -> doBinary True "||" [eE, eE']
    OEqu -> doBinary True "==" [eE, eE']
    ONeq -> doBinary True "/=" [eE, eE']
    OLth -> doBinary True "<"  [eE, eE']
    OLeq -> doBinary True "<=" [eE, eE']
    OGth -> doBinary True ">"  [eE, eE']
    OGeq -> doBinary True ">=" [eE, eE']
    OApp -> applyE applyFn     [eE, eE']
    OSnd -> undefined -- TODO: invoke engine's send function
    OSeq -> doBinary True ">>" [eE, eE']
    _    -> error "Invalid binary operator"

  where doBinary infx opStr args = applyE (doOpF infx opStr) args
        doOpF infx opStr = if infx then infixBinary opStr else appBinary $ HB.function opStr 

        infixBinary op [a,b] = HB.infixApp a (HB.op $ HB.sym op) b
        infixBinary _ _      = error "Invalid binary operator arguments"

        appBinary f [a,b] = HB.appFun f [a,b]
        appBinary _ _     = error "Invalid binary function app arguments"

        applyFn [a,b] = HB.appFun a [b]
        applyFn _ = error "Invalid function application"


-- | Record embedding
buildRecordE :: [Identifier] -> [HS.Exp] -> HS.Exp
buildRecordE names subE =
  HB.tuple [HB.listE namedLblE, foldl concatRecField [hs| emptyRecord |] recFieldE]
  where
    (_, namedLblE, recFieldE) = accumulateLabelAndFieldE names subE

    accumulateLabelAndFieldE names subE = 
      foldl buildRecordFieldE ([hs| firstLabel |], [], []) $ zip names subE

    buildRecordFieldE (keyE, nlblAcc, recAcc) (n,cE) =
      let namedKeyE = applyE HB.tuple [HB.strE n, keyE]
          fieldE    = [hs| $keyE .=. $cE |]
      in ([hs| nextLabel $keyE |], nlblAcc++[namedKeyE], recAcc++[fieldE])

    concatRecField a b = [hs| $b .*. $a |]

recordFieldLookupE :: HS.Exp -> Identifier -> HS.Exp -> HS.Exp
recordFieldLookupE fE n rE = [hs| maybe (error "Record lookup") $fE $ lookup $(HB.strE n) $rE |]


-- | Compiles an expression, yielding a combination of a do-expression of 
--   monadic action bindings, and a residual expression.
expression' :: K3 Expression -> CodeGeneration HS.Exp

-- | Constants
expression' (tag &&& annotations -> (EConstant c, anns)) =
  return $ constantE c anns
  where 
    constantE (CBool b)   _ = if b then [hs| True |] else [hs| False |]
    constantE (CInt i)    _ = HB.intE $ toInteger i
    constantE (CByte w)   _ = HS.Lit $ HS.PrimWord $ toInteger w
    constantE (CReal r)   _ = HS.Lit $ HS.PrimDouble $ toRational r
    constantE (CString s) _ = HB.strE s
    constantE (CNone _)   _ = [hs| Nothing |]
    constantE (CEmpty _) as = HB.eList -- TODO: annotations

-- | Variables
expression' (tag &&& annotations -> (EVariable i, anns)) = return $ loadNameE anns i

-- | Unary option constructor
expression' (tag &&& children -> (ESome, [x])) = do
  x' <- expression' x
  return $ chainReturnE x' $ \e -> [hs| Just $e |]

expression' (tag -> ESome) = throwCG $ CodeGenerationError "Invalid option expression"

-- | Indirection constructor
expression' (tag &&& children -> (EIndirect, [x])) = do
  x' <- expression' x
  return $ chainReturnE x' $ \e -> [hs| newMVar ( $e ) |]

expression' (tag -> EIndirect) = throwCG $ CodeGenerationError "Invalid indirection expression"

-- | Tuple constructor
expression' (tag &&& children -> (ETuple, cs)) = do
  cs' <- mapM expression' cs
  return $ applyE HB.tuple cs'

-- | Record constructor
-- TODO: records need heterogeneous lists. Find another encoding (e.g., Dynamic/HList).
-- TODO: record labels used in ad-hoc records
expression' (tag &&& children -> (ERecord is, cs)) = do
  cs' <- mapM expression' cs
  return $ applyE (buildRecordE is) cs'

-- | Functions
expression' (tag &&& children -> (ELambda i,[b])) = do
  b' <- expression' b
  return $ [hs| \((ni)) -> $b' |]
  where ni = HB.name i

expression' (tag -> ELambda _) = throwCG $ CodeGenerationError "Invalid lambda expression"

-- | Operations
expression' (tag &&& children -> (EOperate otag, cs))
    | otag `elem` [ONeg, ONot], [a] <- cs = unary otag a
    | otherwise, [a, b] <- cs             = binary otag a b
    | otherwise                           = throwCG $ CodeGenerationError "Invalid operator expression"

-- | Projections
-- TODO: records need heterogeneous lists. Find another encoding.
-- TODO: chainReturnE?
expression' (tag &&& children -> (EProject i, [r])) = do
  r' <- expression' r
  return $ recordFieldLookupE (HB.function "id") i r'

expression' (tag -> EProject _) = throwCG $ CodeGenerationError "Invalid record projection"

-- | Let-in expressions
expression' (tag &&& children -> (ELetIn i, [e, b])) = do
  b'       <- expression' b
  e'       <- expression' e
  subE     <- return $ storeE (annotations e) e'
  letDecls <- return [HB.nameBind HL.noLoc (HB.name i) subE]
  return $ HB.letE letDecls b'

expression' (tag -> ELetIn _) = throwCG $ CodeGenerationError "Invalid let expression"

-- | Assignments
-- TODO: optimize if expression 'e' does a lookup of variable 'i'
-- TODO: chainReturnE for e?
expression' (tag &&& children -> (EAssign i, [e])) = do
  e' <- expression' e
  return $ [hs| modifyMVar_ $iE (const $e') |]
  where iE = HB.var $ HB.name i

expression' (tag -> EAssign _) = throwCG $ CodeGenerationError "Invalid assignment"

-- | Case-of expressions
-- TODO: chainReturnE for e?
expression' (tag &&& children -> (ECaseOf i, [e, s, n])) = do
  e' <- expression' e
  s' <- expression' s
  n' <- expression' n

  case maybe PImmutable structureQualifier $ singleStructure $ annotations e of
    PImmutable -> return $ immutableCase e' s' n'
    PMutable   -> gensymCG i >>= return . mutableCase e' s' n' . HB.name

  where ni = HB.name i

        immutableCase eE sE nE = [hs| case $eE of
                                        Just ((ni)) -> $sE
                                        Nothing -> $nE |]

        mutableCase eE sE nE nj = [hs| case $eE of
                                         Just ((nj)) -> let __i__ = newMVar $(HB.var nj) in ( $sE )
                                         Nothing -> $nE |]


expression' (tag -> ECaseOf _) = throwCG $ CodeGenerationError "Invalid case expression"

-- | Bind-as expressions
expression' (tag &&& children -> (EBindAs b, [e, f])) = case b of
    BIndirection i -> do
      e' <- expression' e
      f' <- expression' f
      return $ case maybe PImmutable structureQualifier $ singleStructure eAnns of
        PImmutable -> chainReturnE (doLoadE i e') $ const f'
        PMutable   -> chainReturnE (doBindE i e') $ const f'

    BTuple ts   -> bindTupleFields ts
    BRecord ids -> bindRecordFields ids

  where 
    eAnns = annotations e
    defaultStructure l = map (const PImmutable) l
    eStructure l = maybe (defaultStructure l) (map structureQualifier) $ complexStructure eAnns

    bindTupleFields ids = do
      e'         <- expression' e
      f'         <- expression' f
      tNames     <- mapM renameBinding $ zip ids $ eStructure ids
      mutNames   <- return $ filter (uncurry (/=)) tNames
      mutPat     <- return $ HB.pvarTuple $ map (HB.name . fst) mutNames
      mutVars    <- return $ HB.tuple $ map (\(_,x) -> [hs| newMVar ( $(HB.var $ HB.name x) ) |]) mutNames
      tupPat     <- return $ HB.pvarTuple $ map (HB.name . snd) tNames      
      return $ 
        chainReturnE e'  $ \eE -> 
          flip seqDoE f' $
            HB.doE $   [ HB.genStmt HL.noLoc tupPat [hs| return $eE |] ]
                    ++ (if not $ null mutNames then 
                       [HB.genStmt HL.noLoc mutPat [hs| return $mutVars |] ] else [])
                    ++ [HB.qualStmt $(HB.varTuple $ map (HB.name . fst) $ tNames)]

    renameBinding (n, PImmutable) = return (n, n)
    renameBinding (n, PMutable)   = gensymCG n >>= return . (n,)

    bindRecordFields namePairs = do
      e'              <- expression' e
      f'              <- expression' f
      rNamedStructure <- return $ zip namePairs $ eStructure namePairs
      rBindings       <- foldM bindRecordField (doBindE recordId e') rNamedStructure
      return $ seqDoE rBindings f'

    bindRecordField acc ((a,b), q) = return $ seqDoE acc $ doBindE a $ recordField q b

    recordField PImmutable x  = recordFieldLookupE (HB.function "id") x recordVarE
    recordField PMutable x    = recordFieldLookupE (HB.function "newMVar") x recordVarE
    (recordId, recordVarE)    = let x = "__record" in (x, HB.var $ HB.name x)

expression' (tag -> EBindAs _) = throwCG $ CodeGenerationError "Invalid bind expression"

expression' (tag &&& children -> (EIfThenElse, [p, t, e])) = do
  p' <- expression' p
  t' <- expression' t
  e' <- expression' e
  return $ chainReturnE p' $ \predE -> [hs| if ( $predE ) then ( $t' ) else ( $e' ) |]

expression' (tag &&& children -> (EAddress, [h, p])) = do
  h' <- expression' h
  p' <- expression' p
  return $ applyE HB.tuple [h', p']

expression' (tag -> ESelf) = undefined

expression' _ = throwCG $ CodeGenerationError "Invalid expression"


expression :: K3 Expression -> CodeGeneration HaskellEmbedding
expression e = expression' e >>= return . HExpression

mkNamedDecl :: Identifier -> HS.Exp -> CodeGeneration HaskellEmbedding
mkNamedDecl n initE = return . HDeclaration $ HB.nameBind HL.noLoc (HB.name n) initE

mkTypedDecl :: Identifier -> HS.Type -> HS.Exp -> CodeGeneration HaskellEmbedding
mkTypedDecl n nType nInit = return . HDeclaration $ 
  HS.PatBind HL.noLoc (HB.pvar $ HB.name n) (Just nType) (HS.UnGuardedRhs nInit) HB.noBinds

mkGlobalDecl :: Identifier -> [Annotation Type] -> HS.Type -> HS.Exp -> CodeGeneration HaskellEmbedding
mkGlobalDecl n anns nType nInit = case filter isTQualified anns of
  []           -> mkTypedDecl n nType nInit
  
  [TMutable]   -> mkTypedDecl n (indirectionType nType) [hs| Just ( $nInit ) |]
    -- assumes no IO actions are present in the initializer.
  
  [TImmutable] -> mkTypedDecl n nType nInit
  _            -> throwCG $ CodeGenerationError "Ambiguous global declaration qualifier"

globalWithDefault :: Identifier -> [Annotation Type] -> HS.Type -> Maybe (K3 Expression) -> CodeGeneration HS.Exp
                     -> CodeGeneration HaskellEmbedding
globalWithDefault n anns t eOpt defaultE = do
  e' <- case eOpt of
          Nothing -> defaultE
          Just e  -> expression' e
  mkGlobalDecl n anns t e'

global :: Identifier -> K3 Type -> Maybe (K3 Expression) -> CodeGeneration HaskellEmbedding
global _ (tag -> TSource) _ = return HNoRepr

-- TODO: create composition record types
-- TODO: two-level namespaces.
-- TODO: cyclic scoping
global n t@(tag -> TCollection) eOpt =
  case composedName of
    Nothing      -> return HNoRepr
    Just comboId -> testAndAddComposition comboId $ flip initializeCollection eOpt

  where anns            = annotations t
        annotationNames = annotationNamesT anns
        composedName    = annotationComboIdT anns

        testAndAddComposition comboId f = 
          getCompositionSpec comboId >>= \case 
            Nothing   -> composeAnnotations comboId >>= \spec -> modifyCompositionSpecs (spec:) >> f spec
            Just spec -> f (comboId, spec)

        composeAnnotations comboId = mapM lookupAnnotation annotationNames >>= composeSpec comboId
        lookupAnnotation n = getAnnotationSpec n >>= maybe (invalidAnnotation n) return

        composeSpec comboId annSpecs = 
          let cSpec  = concat annSpecs
              cNames = concat $ map (map (\(x,y,z) -> x)) annSpecs
          in
          if length cSpec == (length $ nub cNames)
          then return (comboId, cSpec)
          else compositionError n

        -- TODO: implement combo id <-> record constructor mapping
        initializeCollection (comboId,_) eOpt = 
          globalWithDefault n anns (collectionType comboId) eOpt (defaultValue' t)
        
        compositionError n  = throwCG . CodeGenerationError $ "Overlapping attribute names in collection " ++ n
        invalidAnnotation n = throwCG . CodeGenerationError $ "Invalid annotation " ++ n

global n t eOpt = typ' t >>= \t' -> globalWithDefault n (annotations t) t' eOpt (defaultValue' t)

trigger :: Identifier -> K3 Type -> K3 Expression -> CodeGeneration HaskellEmbedding
trigger n t e = expression' e >>= mkNamedDecl n

annotation :: Identifier -> [AnnMemDecl] -> CodeGeneration ()
annotation n memberDecls =
  foldM (initializeMember n) [] memberDecls >>= modifyAnnotationSpecs . (:) . (n,)
  where initializeMember annId acc m = annotationMember annId m >>= return . (acc++) . (:[])

-- TODO: distinguish lifted and regular attributes
annotationMember :: Identifier -> AnnMemDecl -> CodeGeneration (Identifier, HS.Type, HS.Exp)
annotationMember annId = \case
  Lifted    Provides n t (Just e) uid -> memberSpec n t e
  Attribute Provides n t (Just e) uid -> memberSpec n t e
  Lifted    Provides n t Nothing  uid -> builtinLiftedAttribute annId n t uid
  Attribute Provides n t Nothing  uid -> builtinAttribute annId n t uid
  where memberSpec n t e = typ' t >>= (\t' -> expression' e >>= return . (n, t',))

builtinLiftedAttribute :: Identifier -> Identifier -> K3 Type -> UID -> CodeGeneration (Identifier, HS.Type, HS.Exp)
builtinLiftedAttribute annId n t uid = throwCG $ CodeGenerationError "Builtin lifted attributes not implemented"

builtinAttribute :: Identifier -> Identifier -> K3 Type -> UID -> CodeGeneration (Identifier, HS.Type, HS.Exp)
builtinAttribute annId n t uid = throwCG $ CodeGenerationError "Builtin attributes not implemented"

declaration :: K3 Declaration -> CodeGeneration HaskellEmbedding
declaration decl = case (tag &&& children) decl of
  (DGlobal n t eO, ch) -> do 
    d    <- global n t eO
    subM <- mapM declaration ch
    return . HModule $ concatMap extractDeclarations $ [d] ++ subM
  
  (DTrigger n t e, cs) -> do
    HDeclaration d <- expression' e >>= mkNamedDecl n
    subM           <- mapM declaration cs
    return . HModule $ [d] ++ concatMap extractDeclarations subM
  
  (DRole r, ch) -> do
    subM <- mapM declaration ch
    return . HModule $ concatMap extractDeclarations subM
      -- TODO: qualify names?

  (DAnnotation n members, []) -> annotation n members >> return HNoRepr

  _ -> throwCG $ CodeGenerationError "Invalid declaration"

  where extractDeclarations (HModule decls)  = decls
        extractDeclarations (HDeclaration d) = [d]
        extractDeclarations HNoRepr          = []
        extractDeclarations _ = error "Invalid declaration"

generateCollectionCompositions :: CodeGeneration [HS.Decl]
generateCollectionCompositions =
  get >>= mapM generateComposition . compositionSpecs . getAnnotationState >>= return . concat
  where
    -- TODO: self
    generateComposition (comboId, spec) =
      let n            = comboId -- TODO: name manipulation as necessary (e.g., shortening)

          dataId       = "data"  -- TODO: make this a keyword

          contentTyId  = "a"
          contentTyVar = HS.TyVar $ HB.name contentTyId

          reprId       = "C"++n++"_Repr"
          reprDeriving = [(HS.UnQual $ HB.name "Eq", [])]
          reprTyVars   = [HS.UnkindedVar $ HB.name contentTyId]
          recFields    = map generateRecFieldTy spec ++ [([HB.name dataId], HS.UnBangedTy $ listType contentTyVar)]
          reprRecDecl  = HS.RecDecl (HB.name reprId) $ recFields
          reprConDecl  = [HS.QualConDecl HL.noLoc [] [] reprRecDecl]
          reprDecl     = HS.DataDecl HL.noLoc HS.DataType [] (HB.name reprId) reprTyVars reprConDecl reprDeriving
    
          typeId       = "C"++n
          typeDecl     = HS.TypeDecl HL.noLoc (HB.name typeId) [] $ indirectionType (namedType reprId)
          typeExpr     = tyApp typeId contentTyVar

          dataFieldExpr varE       = [hs| $(HB.var $ HB.name dataId) $varE |]
          implFields  fieldF       = mapM fieldF spec
          implConExpr dataE fieldF = implFields fieldF >>= return . (++[dataE]) >>= return . HB.appFun (HS.Con $ HS.UnQual $ HB.name reprId)
          implExpr    dataE fieldF = implConExpr dataE fieldF >>= \fieldsE -> return [hs| newMVar ( $fieldsE ) |]

          initConId    = "c"++n
          initArg      = "l"
          initVar      = HB.var $ HB.name initArg
          initPvar     = HB.pvar $ HB.name initArg
          initCon      = implExpr initVar generateRecConFieldExpr >>= \implE -> return $
                         [ typeSig initConId $ funType (listType contentTyVar) $ ioType typeExpr
                         , simpleFun initConId initArg implE ]

          emptyConId   = "empty"++n
          emptyCon     = implExpr HB.eList generateRecConFieldExpr >>= \implE -> return $
                         [ typeSig emptyConId $ ioType typeExpr
                         , HB.nameBind HL.noLoc (HB.name emptyConId) implE ]

          copyConId    = "copy"++n
          copyArg      = "c"
          copyVar      = HB.var $ HB.name copyArg
          copyCon      = implExpr (dataFieldExpr copyVar) (copyFieldExpr copyVar) >>= \implE -> return $
                         [ typeSig copyConId $ funType typeExpr $ ioType typeExpr
                         , simpleFun copyConId copyArg implE ]

          constructorDecls = (\x y z -> x ++ y ++ z) <$> initCon <*> emptyCon <*> copyCon

      in ([reprDecl, typeDecl] ++) <$> constructorDecls

    generateRecFieldTy (n, ty, _)     = ([HB.name n], HS.UnBangedTy ty)
    generateRecConFieldExpr (_, _, e) = return e
    copyFieldExpr varE (n,_,_)        = return [hs| $(HB.var $ HB.name n) $varE |] 
    
    typeSig n t     = HS.TypeSig HL.noLoc [HB.name n] t
    simpleFun n a e = HB.simpleFun HL.noLoc (HB.name n) (HB.name a) e
      

-- | Top-level code generation function, returning a Haskell module.
-- TODO: record label, type and default constructor generation
generate :: String -> K3 Declaration -> CodeGeneration HaskellEmbedding
generate progName p = declaration p >>= mkProgram
  where 
        mkProgram (HModule decls) = programDecls decls
          >>= return . HProgram . HS.Module HL.noLoc (HS.ModuleName progName) pragmas warning exps mkImports
        
        mkProgram _ = throwCG $ CodeGenerationError "Invalid program"

        mkImports = []
        pragmas   = []
        warning   = Nothing
        exps      = Nothing
        
        programDecls decls = generateCollectionCompositions >>= return . (++ decls)

compile :: CodeGeneration HaskellEmbedding -> String
compile _ = error "NYI"
