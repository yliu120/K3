{-# LANGUAGE LambdaCase #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE ViewPatterns #-}

module Language.K3.Codegen.CPP.Expression where

import Control.Arrow ((&&&))
import Control.Monad.State

import Data.Functor
import Data.List (nub, sortBy, (\\))
import Data.Maybe
import Data.Ord (comparing)

import Language.K3.Core.Annotation
import Language.K3.Core.Common
import Language.K3.Core.Expression
import Language.K3.Core.Type

import Language.K3.Codegen.Common
import Language.K3.Codegen.CPP.Primitives
import Language.K3.Codegen.CPP.Types

import qualified Language.K3.Codegen.CPP.Representation as R

-- | The reification context passed to an expression determines how the result of that expression
-- will be stored in the generated code.
data RContext

    -- | Indicates that the calling context will ignore the callee's result.
    = RForget

    -- | Indicates that the calling context is a C++ function, in which case the result may be
    -- 'returned' from the callee.
    | RReturn

    -- | Indicates that the calling context requires the callee's result to be stored in a variable
    -- of a pre-specified name.
    | RName Identifier

    -- | A free-form reification context, for special cases.
    | RSplice ([CPPGenR] -> CPPGenR)

instance Show RContext where
    show RForget = "RForget"
    show RReturn = "RReturn"
    show (RName i) = "RName \"" ++ i ++ "\""
    show (RSplice _) = "RSplice <opaque>"

attachTemplateVars :: Identifier -> K3 Expression -> [(Identifier, K3 Type)] -> CPPGenM R.Name
attachTemplateVars v e g
    | isJust (lookup v g) && isJust (functionType e)
        = do
            signatureType <- case fromJust (lookup v g) of
                                  t@(tag -> TFunction) -> return t
                                  (tag &&& children -> (TForall _, [t'])) -> return t'
                                  _ -> throwE $ CPPGenE "Unreachable Error."
            let ts = snd . unzip . dedup $ matchTrees signatureType (fromJust $ functionType e)
            cts <- mapM genCType ts
            return $ if null cts
               then R.Name v
               else R.Specialized cts $ R.Name v
    | otherwise = return $ R.Name v

dedup :: [(Identifier, a)] -> [(Identifier, a)]
dedup = foldl (\ds (t, u) -> if isJust (lookup t ds) then ds else ds ++ [(t, u)]) []

matchTrees :: K3 Type -> K3 Type -> [(Identifier, K3 Type)]
matchTrees (tag -> TDeclaredVar i) u = [(i, u)]
matchTrees (children -> ts) (children -> us) = concat $ zipWith matchTrees ts us

functionType :: K3 Expression -> Maybe (K3 Type)
functionType e = case e @~ \case { EType _ -> True; _ -> False } of
    Just (EType t@(tag -> TFunction)) -> Just t
    _ -> Nothing

-- | Realization of unary operators.
unarySymbol :: Operator -> CPPGenM Identifier
unarySymbol ONot = return "!"
unarySymbol ONeg = return "-"
unarySymbol u = throwE $ CPPGenE $ "Invalid Unary Operator " ++ show u

-- | Realization of binary operators.
binarySymbol :: Operator -> CPPGenM Identifier
binarySymbol OAdd = return "+"
binarySymbol OSub = return "-"
binarySymbol OMul = return "*"
binarySymbol ODiv = return "/"
binarySymbol OMod = return "%" -- TODO: type based selection of % vs fmod
binarySymbol OEqu = return "=="
binarySymbol ONeq = return "!="
binarySymbol OLth = return "<"
binarySymbol OLeq = return "<="
binarySymbol OGth = return ">"
binarySymbol OGeq = return ">="
binarySymbol OAnd = return "&&"
binarySymbol OOr = return "||"
binarySymbol b = throwE $ CPPGenE $ "Invalid Binary Operator " ++ show b

-- | Realization of constants.
constant :: Constant -> CPPGenM R.Literal
constant (CBool True) = return $ R.LBool True
constant (CBool False) = return $ R.LBool False
constant (CInt i) = return $ R.LInt i
constant (CReal d) = return $ R.LDouble d
constant (CString s) = return $ R.LString s
constant (CNone _) = return R.LNullptr
constant c = throwE $ CPPGenE $ "Invalid Constant Form " ++ show c

cDecl :: K3 Type -> Identifier -> CPPGenM [R.Statement]
cDecl (tag &&& children -> (TFunction, [ta, tr])) i = do
    ctr <- genCType tr
    cta <- genCType ta
    return [R.Forward $ R.FunctionDecl (R.Name i) [cta] ctr]
cDecl t i = do
    when (tag t == TCollection) $ addComposite (namedTAnnotations $ annotations t)
    ct <- genCType t
    return [R.Forward $ R.ScalarDecl (R.Name i) ct Nothing]

inline :: K3 Expression -> CPPGenM ([R.Statement], R.Expression)
inline e@(tag &&& annotations -> (EConstant (CEmpty t), as)) = case annotationComboIdE as of
    Nothing -> throwE $ CPPGenE $ "No Viable Annotation Combination for Empty " ++ show e
    Just ac -> do
        ct <- genCType t
        addComposite (namedEAnnotations as)
        return ([], R.Initialization (R.Collection ac ct) [])

inline (tag -> EConstant c) = constant c >>= \c' -> return ([], R.Literal c')

-- If a variable was declared as mutable it's been reified as a shared_ptr, and must be
-- dereferenced.
inline e@(tag -> EVariable v)
    | isJust $ e @~ (\case { EMutable -> True; _ -> False }) = return ([], R.Dereference (R.Variable $ R.Name v))
    | otherwise = globals <$> get >>= attachTemplateVars v e >>= \n -> return ([], R.Variable n)

inline (tag &&& children -> (t', [c])) | t' == ESome || t' == EIndirect = do
    (e, v) <- inline c
    ct <- getKType c
    t <- genCType ct
    return (e, R.Call (R.Variable $ R.Specialized [t] (R.Name "make_shared")) [v])

inline (tag &&& children -> (ETuple, [])) = return ([], R.Initialization R.Unit [])

inline (tag &&& children -> (ETuple, cs)) = do
    (es, vs) <- unzip <$> mapM inline cs
    return (concat es, R.Call (R.Variable $ R.Name "make_tuple") vs)

inline e@(tag &&& children -> (ERecord is, cs)) = do
    (es, vs) <- unzip <$> mapM inline cs
    let vs' = snd . unzip . sortBy (comparing fst) $ zip is vs
    t <- getKType e
    case t of
        (tag &&& children -> (TRecord _, _)) -> do
            sig <- genCType t
            return (concat es, R.Initialization sig vs')
        _ -> throwE $ CPPGenE $ "Invalid Record Type " ++ show t

inline (tag &&& children -> (EOperate uop, [c])) = do
    (ce, cv) <- inline c
    usym <- unarySymbol uop
    return (ce, R.Unary usym cv)

inline (tag &&& children -> (EOperate OSeq, [a, b])) = do
    ae <- reify RForget a
    (be, bv) <- inline b
    return (ae ++ be, bv)

inline e@(tag &&& children -> (ELambda arg, [body])) = do
    (ta, tr) <- getKType e >>= \case
        (tag &&& children -> (TFunction, [ta, tr])) -> do
            ta' <- genCInferredType ta
            tr' <- genCInferredType tr

            return (ta', tr')
        _ -> throwE $ CPPGenE "Invalid Function Form"
    exc <- fst . unzip . globals <$> get
    let fvs = nub $ filter (/= arg) $ freeVariables body
    body' <- reify RReturn body
    -- TODO: Handle `mutable' arguments.
    return ([], R.Lambda [(i', R.Variable $ R.Name i') | i' <- fvs \\ exc] [(arg, ta)] (Just tr) body')

inline (tag &&& children -> (EOperate OApp, [f, a])) = do
    -- Inline both function and argument for call.
    (fe, fv) <- inline f
    (ae, av) <- inline a

    return (fe ++ ae, R.Call fv [av])

inline (tag &&& children -> (EOperate OSnd, [tag &&& children -> (ETuple, [trig@(tag -> EVariable tName), addr]), val])) = do
    (te, tv)  <- inline trig
    (ae, av)  <- inline addr
    (ve, vv)  <- inline val
    trigList  <- triggers <$> get
    trigTypes <- getKType val >>= genCType
    let className = R.Specialized [trigTypes] (R.Qualified "K3" $ R.Name "ValDispatcher")
        classInst = R.Forward $ R.ScalarDecl (R.Name "d") R.Inferred
                      (Just $ R.Call (R.Variable $ R.Specialized [R.Named className]
                                           (R.Qualified "std" $ R.Name "make_shared")) [tv, vv])
        (_, trigId) = fromMaybe (error $ "Failed to find trigger " ++ tName ++ " in trigger list") $
                         tName `lookup` trigList
    return (concat [te, ae, ve]
                 ++ [ classInst
                    , R.Ignore $ R.Call (R.Project (R.Variable $ R.Name "engine") (R.Name "send")) [
                                    av, R.Variable (R.Name $ show trigId), R.Variable (R.Name "d")
                                   ]
                    ]
             , R.Initialization R.Unit [])

inline (tag &&& children -> (EOperate bop, [a, b])) = do
    (ae, av) <- inline a
    (be, bv) <- inline b
    bsym <- binarySymbol bop
    return (ae ++ be, R.Binary bsym av bv)

inline e@(tag &&& children -> (EProject v, [k])) = do
    (ke, kv) <- inline k
    vv <- globals <$> get >>= attachTemplateVars v e
    return (ke, R.Project kv vv)

inline (tag &&& children -> (EAssign x, [e])) = reify (RName x) e >>= \a -> return (a, R.Initialization R.Unit [])

inline (tag &&& children -> (EAddress, [h, p])) = do
    (he, hv) <- inline h
    (pe, pv) <- inline p
    return (he ++ pe, R.Call (R.Variable $ R.Name "make_address") [hv, pv])

inline e = do
    k <- genSym
    ct <- getKType e
    decl <- cDecl ct k
    effects <- reify (RName k) e
    return (decl ++ effects, R.Variable $ R.Name k)

-- | The generic function to generate code for an expression whose result is to be reified. The
-- method of reification is indicated by the @RContext@ argument.
reify :: RContext -> K3 Expression -> CPPGenM [R.Statement]

-- TODO: Is this the fix we need for the unnecessary reification issues?
reify RForget e@(tag -> EOperate OApp) = do
    (ee, ev) <- inline e
    return $ ee ++ [R.Ignore ev]

reify r (tag &&& children -> (EOperate OSeq, [a, b])) = do
    ae <- reify RForget a
    be <- reify r b
    return $ ae ++ be

reify r (tag &&& children -> (ELetIn x, [e, b])) = do
    ct <- getKType e
    d <- cDecl ct x
    ee <- reify (RName x) e
    be <- reify r b
    return [R.Block $ d ++ ee ++ be]

-- case `e' of { some `x' -> `s' } { none -> `n' }
reify r (tag &&& children -> (ECaseOf x, [e, s, n])) = do
    ct <- getKType e
    d <- cDecl (head $ children ct) x
    g <- genSym
    p <- cDecl ct g
    ee <- reify (RName g) e
    se <- reify r s
    ne <- reify r n
    let someAssignment = [R.Assignment (R.Variable $ R.Name x) (R.Dereference (R.Variable $ R.Name g))]
    return $ p ++ ee ++ [R.IfThenElse (R.Variable $ R.Name g) (d ++ someAssignment ++ se) ne]

reify r (tag &&& children -> (EBindAs b, [a, e])) = do
    (ae, g) <- case a of
        (tag -> EVariable _) -> inline a
        _ -> do
            g' <- genSym
            ae' <- reify (RName g') a
            return (ae', R.Variable $ R.Name g')

    ta <- getKType a

    bindInit <- case b of
            BIndirection i -> do
                let (tag &&& children -> (TIndirection, [ti])) = ta
                di <- cDecl ti i
                return $ di ++ [R.Assignment (R.Variable $ R.Name i) (R.Dereference g)]
            BTuple is -> do
                let (tag &&& children -> (TTuple, ts)) = ta
                ds <- zipWithM cDecl ts is
                let bindVars = [R.Variable (R.Name i) | i <- is]
                let tieCall = R.Call (R.Variable $ R.Qualified "std" (R.Name "tie")) bindVars
                return $ concat ds ++ [R.Assignment tieCall g]
            BRecord iis -> return [R.Assignment (R.Variable $ R.Name v) (R.Project g (R.Name i)) | (i, v) <- iis]

    let bindWriteback = case b of

            BIndirection i -> [R.Assignment g (R.Call (R.Variable (R.Name "make_shared")) [R.Variable $ R.Name i])]
            BTuple is -> zipWith (genTupleAssign g) [0..] is
            BRecord iis -> map (uncurry $ genRecordAssign g) iis

    (bindBody, k) <- case r of
        RReturn -> do
            g' <- genSym
            te <- getKType e
            de <- cDecl te g'
            re <- reify (RName g') e
            return (de ++ re, Just g')
        _ -> (,Nothing) <$> reify r e

    let bindCleanUp = maybe [] (\k' -> [R.Return (R.Variable $ R.Name k')]) k

    return $ ae ++ [R.Block $ bindInit ++ bindBody ++ bindWriteback ++ bindCleanUp]
  where
    genTupleAssign :: R.Expression -> Int -> Identifier -> R.Statement
    genTupleAssign g n i =
        R.Assignment (R.Call (R.Variable $ R.Specialized [R.Named $ R.Name (show n)] (R.Name "get")) [g])
                     (R.Variable $ R.Name i)
    genRecordAssign g k v = R.Assignment (R.Project g (R.Name k)) (R.Variable $ R.Name v)

reify r (tag &&& children -> (EIfThenElse, [p, t, e])) = do
    (pe, pv) <- inline p
    te <- reify r t
    ee <- reify r e
    return $ pe ++ [R.IfThenElse pv te ee]

reify r e = do
    (effects, value) <- inline e
    reification <- case r of
        RForget -> return []
        RName k -> return [R.Assignment (R.Variable $ R.Name k) value]
        RReturn -> return [R.Return value]
        RSplice _ -> throwE $ CPPGenE "Unsupported reification by splice."
    return $ effects ++ reification
