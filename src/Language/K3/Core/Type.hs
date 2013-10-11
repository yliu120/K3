{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE FlexibleInstances #-}

-- | Types in K3.
module Language.K3.Core.Type (
    Type(..),
    TypeBuiltIn(..),
    TypeVarDecl(..),
    Annotation(..),
    
    isTSpan,
    isTUID,
    isTQualified,
    isTImmutable,
    isTMutable,
    isTAnnotation,

    namedTAnnotations
) where

import Data.Tree

import Language.K3.Core.Annotation
import Language.K3.Core.Annotation.Syntax
import Language.K3.Core.Common

import Language.K3.Utils.Pretty

-- * Basic types

-- | Tags in the Type Tree. Every type can be qualified with a mutability
--   annotation.  This set of tags is a superset of those which can be parsed
--   by the type expression grammar in the K3 specification because it also
--   represents the (unparseable) types inferred by the type system.
data Type
    = TBool
    | TByte
    | TInt
    | TReal
    | TString
    | TOption
    | TIndirection
    | TTuple
    | TRecord [Identifier]
    | TCollection
    | TFunction
    | TAddress
    | TSource
    | TSink
    | TTrigger
    | TBuiltIn TypeBuiltIn
    | TForall [TypeVarDecl] -- ^Should have one child representing the body.
    | TDeclaredVar Identifier -- ^Represents the use of a declared type var.
  deriving (Eq, Read, Show)

-- | The built-in type references.
data TypeBuiltIn
    = TSelf
    | TStructure
    | THorizon
    | TContent
  deriving (Eq, Read, Show)
  
-- | Type variable declarations.  These consist of the identifier for the
--   declared variable and, optionally, a type expression for the upper bound.
data TypeVarDecl = TypeVarDecl Identifier (Maybe (K3 Type))
  deriving (Eq, Read, Show)

-- | Annotations on types are the mutability qualifiers.
data instance Annotation Type
    = TMutable
    | TImmutable
    | TWitness
    | TSpan Span
    | TUID UID
    | TAnnotation Identifier
    | TSyntax SyntaxAnnotation
  deriving (Eq, Read, Show)

instance Pretty (K3 Type) where
    prettyLines (Node (TTuple :@: as) []) = ["TUnit" ++ drawAnnotations as]
    prettyLines (Node (t :@: as) ts) = (show t ++ drawAnnotations as) : drawSubTrees ts

instance Pretty TypeVarDecl where
    prettyLines (TypeVarDecl i mtExpr) = case mtExpr of
      Nothing -> [i]
      Just tExpr -> [i ++ "<="] %+ prettyLines tExpr

{- Type annotation predicates -}

isTSpan :: Annotation Type -> Bool
isTSpan (TSpan _) = True
isTSpan _ = False

isTUID :: Annotation Type -> Bool
isTUID (TUID _) = True
isTUID _        = False

isTQualified :: Annotation Type -> Bool
isTQualified TImmutable = True
isTQualified TMutable   = True
isTQualified _          = False

isTImmutable :: Annotation Type -> Bool
isTImmutable TImmutable = True
isTImmutable _          = False

isTMutable :: Annotation Type -> Bool
isTMutable TMutable = True
isTMutable _        = False

isTAnnotation :: Annotation Type -> Bool
isTAnnotation (TAnnotation _) = True
isTAnnotation _               = False

namedTAnnotations :: [Annotation Type] -> [Identifier]
namedTAnnotations anns = map extractId $ filter isTAnnotation anns
  where extractId (TAnnotation n) = n
        extractId _ = error "Invalid named annotation"

