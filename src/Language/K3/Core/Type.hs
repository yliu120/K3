{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE FlexibleInstances #-}

-- | Types in K3.
module Language.K3.Core.Type (
    Type(..),
    TypeBuiltIn(..),
    TypeVarDecl(..),
    TypeVariableOperator(..),
    Annotation(..),
    
    isTSpan,
    isTUID,
    isTQualified,
    isTImmutable,
    isTMutable,
    isTAnnotation,

    namedTAnnotations
) where

import Data.Maybe
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
    | TNumber
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
    | TForall [TypeVarDecl] {- ^Should have one child representing the body. -}
    | TDeclaredVar Identifier {- ^Represents the use of a declared type var. -}
    -- The following constructors are used primarily during type manifestation
    -- after typechecking is complete; they do not necessarily have an
    -- equivalent in the language syntax.
    | TTop
    | TBottom
    | TExternallyBound [TypeVarDecl]
        -- ^Represents an externally chosen type variable binding.
    | TRecordExtension [Identifier] [Identifier]
        -- ^Represents the extension of a record.  The first list of identifiers
        --  names the labels corresponding to the children of this record
        --  extension; the second list names the type variables with which this
        --  record concatenates.
    | TDeclaredVarOp [Identifier] TypeVariableOperator
        -- ^Represents an n-ary operation over declared type variables.  This
        --  type is generated when multiple opaque variables are aligned during
        --  type manifestation, since computing the appropriate bounds is
        --  inconvenient and quite complex.
    | TMu Identifier
        -- ^Represents a mu-recursive binding.  This type is generated when a
        --  self-referential type is encountered.  This type has one child: the
        --  body of the type declaration.

    -- | Implementation Types. These should never be produced by the parser, nor should they be
    -- considered by the typechecker.
    | TImperative ImperativeType
  deriving (Eq, Read, Show)

-- | Types specific to an imperative implementation backend.
data ImperativeType
    -- | A named type synonym, usually for the instantiation of a class. Requires the name of the
    -- class, and the template type parameters to instantiate with.
    = TNamed Identifier [K3 Type]

    -- | An imperative class type. Requires the name of the class, list of superclasses, and the
    -- list of named template variables.
    | TClass Identifier [Identifier] [Identifier]
  deriving (Eq, Read, Show)

-- | The built-in type references.
data TypeBuiltIn
    = TSelf
    | TStructure
    | THorizon
    | TContent
  deriving (Eq, Read, Show)
  
-- | Type variable declarations.  These consist of the identifier for the
--   declared variable and, optionally, a type expression for the lower and
--   upper bounds (respectively).
data TypeVarDecl = TypeVarDecl Identifier (Maybe (K3 Type)) (Maybe (K3 Type))
  deriving (Eq, Read, Show)

-- | The operations which may occur on a collection of opaque variables.
data TypeVariableOperator = TyVarOpUnion | TyVarOpIntersection
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
    prettyLines (TypeVarDecl i mlbtExpr mubtExpr) =
      (if isNothing mlbtExpr then [] else
          prettyLines (fromJust mlbtExpr) %+ ["=<"]) %+
      [i] %+
      (if isNothing mubtExpr then [] else
          ["<="] %+ prettyLines (fromJust mubtExpr))

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

