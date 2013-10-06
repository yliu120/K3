{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE PatternGuards #-}
{-# LANGUAGE ViewPatterns #-}

module Language.K3.Pretty.Syntax (
    program,
    decl,
    expr,
    typ,

    programS,
    declS,
    exprS,
    typeS
) where

import Control.Applicative ( (<*>) )
import qualified Control.Applicative as C ( (<$>) )

import Data.List 

import Language.K3.Core.Common
import Language.K3.Core.Annotation
import Language.K3.Core.Type
import Language.K3.Core.Expression
import Language.K3.Core.Declaration

import Text.PrettyPrint.ANSI.Leijen

data SyntaxError = SyntaxError String deriving (Eq, Show)

-- | A simple syntax printer monad.
type Printer a     = Either SyntaxError a
type SyntaxPrinter = Printer Doc

runSyntaxPrinter :: SyntaxPrinter -> Either String Doc
runSyntaxPrinter p = either (\(SyntaxError s) -> Left s) Right p

throwSP :: String -> SyntaxPrinter
throwSP = Left . SyntaxError

programS :: K3 Declaration -> String
programS = either id show . program

declS :: K3 Declaration -> String
declS = either id show . runSyntaxPrinter . decl

exprS :: K3 Expression -> String
exprS = either id show . runSyntaxPrinter . expr

typeS :: K3 Type -> String
typeS = either id show . runSyntaxPrinter . typ

program :: K3 Declaration -> Either String Doc
program = runSyntaxPrinter . decl

-- | Declaration syntax printing.
decl :: K3 Declaration -> SyntaxPrinter
decl (details -> (DGlobal n t eOpt, cs, _)) =
  return . vsep =<< ((:) C.<$> decl' <*> mapM decl cs)
  where
    decl' = globlDecl C.<$> qualifierAndType t
                        <*> optionalPrinter qualifierAndExpr eOpt
    globlDecl (qualT, t') eqeOpt = 
      flip initializer eqeOpt $ text "declare" <+> text n <+> colon <+> qualT <+> t'

    initializer d Nothing           = d
    initializer d (Just (qualE, e)) = d <+> equals <+> qualE <+> e

decl (details -> (DTrigger n t e, cs, _)) =
  return . vsep =<< ((:) C.<$> decl' <*> mapM decl cs)
  where
    decl' = triggerDecl C.<$> typ t <*> expr e
    triggerDecl t' e' = text "trigger" <+> text n <+> colon <+> t' <+> e'

decl (details -> (DRole n, cs, _)) = 
  mapM decl cs >>= return . roleDecl
  where roleDecl subDecls = text "role" <+> text n <+> braces (indent 2 $ vsep subDecls)

decl (details -> (DAnnotation n tvars mems, cs, _)) =
  return . uncurry annotationDecl =<< ((,) C.<$> mapM memberDecl mems <*> mapM decl cs)
  where
    annotationDecl memDecls subDecls = vsep . (: subDecls) $ 
          text "annotation" <+> text n
      <+> text "given" <+> text "type" <+> cat (punctuate comma $ map text tvars)
      <+> braces (indent 2 . vsep $ memDecls)

    memberDecl (Lifted pol i t eOpt _) =
      attrDecl pol "lifted" i C.<$> qualifierAndType t
                                <*> optionalPrinter qualifierAndExpr eOpt
    
    memberDecl (Attribute pol i t eOpt _) =
      attrDecl pol "" i C.<$> qualifierAndType t
                          <*> optionalPrinter qualifierAndExpr eOpt
    
    memberDecl (MAnnotation pol i _) =
      return $ polarity pol <+> text "annotation" <+> text i

    attrDecl pol kw j (qualT, t') eqeOpt = flip initializer eqeOpt $
      polarity pol <+> (if null kw then text j else text kw <+> text j) <+> colon <+> qualT <+> t'

    polarity Provides = text "provides"
    polarity Requires = text "requires"

    initializer d Nothing            = d
    initializer d (Just (qualE, e')) = d <+> equals <+> qualE <+> e'

decl _ = throwSP "Invalid declaration"

-- | Expression syntax printing.
expr :: K3 Expression -> SyntaxPrinter
expr (details -> (EConstant c, _, anns)) =
  case c of 
    CBool b   -> return . text $ if b then "true" else "false"
    CInt i    -> return $ int i
    CByte w   -> return . integer $ toInteger w
    CReal r   -> return $ double r
    CString s -> return . dquotes $ text s
    CNone q   -> return $ text "None" <+> nQualifier q
    CEmpty t  -> typ t >>= return . emptyCollection (namedEAnnotations anns)

  where
    emptyCollection annIds t =
      text "empty" <+> t <+> text "@" <+> commaBrace (map text annIds)
        
    nQualifier NoneMut   = text "mut"
    nQualifier NoneImmut = text "immut"

expr (tag -> EVariable i) = return $ text i

expr (details -> (ESome, [x], _)) = qualifierAndExpr x >>= return . uncurry someExpr
expr (tag -> ESome)               = exprError "some"

expr (details -> (EIndirect, [x], _)) = qualifierAndExpr x >>= return . uncurry indirectionExpr
expr (tag -> EIndirect)               = exprError "indirection"

expr (details -> (ETuple, cs, _)) = mapM qualifierAndExpr cs >>= return . tupleExpr
expr (tag -> ETuple)              = exprError "tuple"

expr (details -> (ERecord is, cs, _)) = mapM qualifierAndExpr cs >>= return . recordExpr is
expr (tag -> ERecord _)               = exprError "record"

expr (details -> (ELambda i, [b], _)) = expr b >>= return . lambdaExpr i
expr (tag -> ELambda _)               = exprError "lambda"

expr (details -> (EOperate otag, cs, _))
    | otag `elem` [ONeg, ONot], [a] <- cs = expr a >>= unary otag
    | otherwise, [a, b] <- cs             = uncurry (binary otag) =<< ((,) C.<$> expr a <*> expr b)
    | otherwise                           = exprError "operator"

expr (details -> (EProject i, [r], _)) = expr r >>= return . projectExpr i
expr (tag -> EProject _)               = exprError "project"

expr (details -> (ELetIn i, [e, b], _)) = letExpr i C.<$> qualifierAndExpr e <*> expr b
expr (tag -> ELetIn _)                  = exprError "let"

expr (details -> (EAssign i, [e], _)) = expr e >>= return . assignExpr i
expr (tag -> EAssign _)               = exprError "assign"

expr (details -> (ECaseOf i, [e, s, n], _)) = caseExpr i C.<$> expr e <*> expr s <*> expr n
expr (tag -> ECaseOf _)                     = exprError "case-of"

expr (details -> (EBindAs b, [e, f], _)) = bindExpr b C.<$> expr e <*> expr f
expr (tag -> EBindAs _)                  = exprError "bind-as"

expr (details -> (EIfThenElse, [p, t, e], _)) = branchExpr C.<$> expr p <*> expr t <*> expr e
expr (tag -> EIfThenElse)                     = exprError "if-then-else"

expr (details -> (EAddress, [h, p], _)) = addrExpr C.<$> expr h <*> expr p
expr (tag -> EAddress)                  = exprError "address"

expr (tag -> ESelf) = return $ keyword "self"

expr _ = exprError "unknown"

unary :: Operator -> Doc -> SyntaxPrinter
unary ONeg e = return $ text "-" <//> e
unary ONot e = return $ text "not" <+> e
unary op _   = throwSP $ "Invalid unary operator '" ++ show op ++ "'"

binary :: Operator -> Doc -> Doc -> SyntaxPrinter
binary op e e' = 
  case op of 
    OAdd -> infixOp "+" 
    OSub -> infixOp "-" 
    OMul -> infixOp "*" 
    ODiv -> infixOp "/" 
    OAnd -> infixOp "&&"
    OOr  -> infixOp "||"
    OEqu -> infixOp "=="
    ONeq -> infixOp "/="
    OLth -> infixOp "<" 
    OLeq -> infixOp "<="
    OGth -> infixOp ">" 
    OGeq -> infixOp ">="
    OSeq -> return $ e <//> text ";" <+> e'
    OApp -> return $ e <+> e'
    OSnd -> infixOp "<-"
    _    -> throwSP $ "Invalid binary operator '" ++ show op ++ "'"

  where infixOp opStr = return $ e <+> text opStr <+> e'

qualifierAndExpr :: K3 Expression -> Printer (Doc, Doc)
qualifierAndExpr e@(annotations -> anns) = (,) C.<$> eQualifier anns <*> expr e

eQualifier :: [Annotation Expression] -> SyntaxPrinter
eQualifier anns = qualifier isEQualified eqSyntax anns
  where 
    eqSyntax EImmutable = return $ text "immut"
    eqSyntax EMutable   = return $ text "mut"
    eqSyntax _          = throwSP "Invalid expression qualifier"

exprError :: String -> SyntaxPrinter
exprError msg = throwSP $ "Invalid " ++ msg ++ " expression"

-- | Type expression syntax printing.
typ :: K3 Type -> SyntaxPrinter
typ (tag -> TBool)       = return $ text "bool"
typ (tag -> TByte)       = return $ text "byte"
typ (tag -> TInt)        = return $ text "int"
typ (tag -> TReal)       = return $ text "real"
typ (tag -> TString)     = return $ text "string"
typ (tag -> TAddress)    = return $ text "address"

typ (details -> (TOption, [x], _)) = qualifierAndType x >>= return . uncurry optionType
typ (tag -> TOption)               = throwSP "Invalid option type"

typ (details -> (TTuple, ch, _)) = mapM qualifierAndType ch >>= return . tupleType

typ (details -> (TRecord ids, ch, _))
  | length ids == length ch  = mapM qualifierAndType ch >>= return . recordType ids
  | otherwise                = throwSP "Invalid record type"

typ (details -> (TIndirection, [x], _)) = qualifierAndType x >>= return . uncurry indirectionType
typ (tag -> TIndirection)               = throwSP "Invalid indirection type"

typ (details -> (TFunction, [a,r], _)) = mapM typ [a,r] >>= \chT -> return $ funType (head chT) (last chT)
typ (tag -> TFunction)                 = throwSP "Invalid function type"

typ (details -> (TSink, [x], _)) = typ x
typ (tag -> TSink)               = throwSP "Invalid sink type"

typ (details -> (TTrigger, [x], _)) = typ x >>= return . triggerType
typ (tag -> TTrigger)               = throwSP "Invalid trigger type"

typ (details -> (TCollection, [x], anns)) =
  typ x >>= return . collectionType (map text $ namedTAnnotations anns)

typ (tag -> TCollection) = throwSP "Invalid collection type"

typ (tag -> TBuiltIn TSelf)      = return $ keyword "self"
typ (tag -> TBuiltIn TContent)   = return $ keyword "content"
typ (tag -> TBuiltIn THorizon)   = return $ keyword "horizon"
typ (tag -> TBuiltIn TStructure) = return $ keyword "structure"

typ _ = throwSP "Cannot generate type syntax"

qualifierAndType :: K3 Type -> Printer (Doc, Doc)
qualifierAndType t@(annotations -> anns) = (,) C.<$> tQualifier anns <*> typ t

tQualifier :: [Annotation Type] -> SyntaxPrinter
tQualifier anns = qualifier isTQualified tqSyntax anns
  where 
    tqSyntax TImmutable = return $ text "immut"
    tqSyntax TMutable   = return $ text "mut"
    tqSyntax _          = throwSP "Invalid type qualifier"


{- Syntax constructors -}

optionType :: Doc -> Doc -> Doc
optionType qual t = text "option" <+> qual <+> t

indirectionType :: Doc -> Doc -> Doc
indirectionType qual t = text "ind" <+> qual <+> t

tupleType :: [(Doc, Doc)] -> Doc
tupleType qualC = tupled $ map (uncurry (<+>)) qualC

recordType :: [Identifier] -> [(Doc, Doc)] -> Doc
recordType ids qualC =
  commaBrace $ map (\(a,b) -> text a <+> colon <+> b)
             $ zip ids $ map (uncurry (<+>)) qualC

collectionType :: [Doc] -> Doc -> Doc
collectionType namedAnns t =
  text "collection" <+> t <+> text "@" <+> commaBrace namedAnns

funType :: Doc -> Doc -> Doc
funType arg ret = arg <+> text "->" <+> ret

triggerType :: Doc -> Doc
triggerType t = text "trigger" <+> t


someExpr :: Doc -> Doc -> Doc
someExpr qual e = text "Some" <+> qual <+> e

indirectionExpr :: Doc -> Doc -> Doc
indirectionExpr qual e = text "ind" <+> qual <+> e

tupleExpr :: [(Doc, Doc)] -> Doc
tupleExpr qualC = tupled $ map (uncurry (<+>)) qualC

recordExpr :: [Identifier] -> [(Doc, Doc)] -> Doc
recordExpr ids qualC = 
  commaBrace $ map (\(a,b) -> text a <+> colon <+> b)
             $ zip ids $ map (uncurry (<+>)) qualC

lambdaExpr :: Identifier -> Doc -> Doc
lambdaExpr n b = backslash <//> text n <+> text "->" <+> b

projectExpr :: Identifier -> Doc -> Doc
projectExpr n r = r <//> dot <//> text n

letExpr :: Identifier -> (Doc, Doc) -> Doc -> Doc
letExpr n (qual,e) b =
  text "let" <+> text n <+> equals <+> qual <+> e <+> text "in" <+> b

assignExpr :: Identifier -> Doc -> Doc
assignExpr n e = text n <+> equals <+> e

caseExpr :: Identifier -> Doc -> Doc -> Doc -> Doc
caseExpr i e s n = text "case" <+> e <+> text "of" <+> sCase <+> nCase
  where sCase = braces $ text "Some" <+> text i <+> text "->" <+> s
        nCase = braces $ text "None" <+> text "->" <+> n

bindExpr :: Binder -> Doc -> Doc -> Doc
bindExpr b e e' = text "bind" <+> e <+> text "as" <+> binder b <+> text "in" <+> e'
  where
    binder (BIndirection i) = text "ind" <+> text i
    binder (BTuple ids)     = tupled $ map text ids
    binder (BRecord idMap)  = commaBrace $ map (\(s,t) -> text s <+> colon <+> text t) idMap

branchExpr :: Doc -> Doc -> Doc -> Doc
branchExpr p t e = text "if" <+> p <+> text "then" <+> t <+> text "else" <+> e

addrExpr :: Doc -> Doc -> Doc
addrExpr h p = h <//> colon <//> p


{- Helpers -}

keyword :: String -> Doc
keyword s = text s

commaBrace :: [Doc] -> Doc
commaBrace = encloseSep lbrace rbrace comma

details :: K3 a -> (a, [K3 a], [Annotation a])
details n = (tag n, children n, annotations n)

qualifier :: (Eq (Annotation a))
          => (Annotation a -> Bool) -> (Annotation a -> SyntaxPrinter) -> [Annotation a]
          -> SyntaxPrinter
qualifier matchQ syntaxQ anns = case filter matchQ anns of
    []            -> throwSP "No qualifier found"
    [q]           -> syntaxQ q
    l | same l    -> syntaxQ $ head l
      | otherwise -> throwSP "Ambiguous qualifier found"
  where same l = 1 == (length $ nub l)

optionalPrinter :: (a -> Printer b) -> Maybe a -> Printer (Maybe b)
optionalPrinter f opt = maybe (return Nothing) (\x -> f x >>= return . Just) opt
