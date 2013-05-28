{-# LANGUAGE TypeFamilies #-}

-- | Expressions in K3.
module Language.K3.Core.Expression where

import Data.Word (Word8)

import Language.K3.Core.Annotation
import Language.K3.Core.Type

-- | Expression tags. Every expression can be qualified with a mutability annotation.
data Expression
    = EConstant   Constant
    | EVariable   Identifier
    | ESome
    | EIndirect
    | ETuple
    | ERecord     [Identifier]
    | ELambda     Identifier
    | EOperate    Operator
    | EProject    Identifier
    | ELetIn      Identifier
    | EAssign     Identifier
    | ECaseOf     Identifier
    | EBindAs     Binder
    | EIfThenElse 
  deriving (Eq, Read, Show)

-- | Constant expression values.
data Constant
    = CBool   Bool
    | CInt    Int
    | CByte   Word8
    | CFloat  Float
    | CString String
    | CNone
    | CEmpty
  deriving (Eq, Read, Show)

-- | Operators (unary and binary).
data Operator
    = OAdd
    | OSub
    | OMul
    | ODiv
    | ONeg
    | OEqu
    | ONeq
    | OLth
    | OLeq
    | OGth
    | OGeq
    | OAnd
    | OOr
    | ONot
    | OSeq
    | OApp
    | OSnd
  deriving (Eq, Read, Show)

-- | Binding Forms.
data Binder
    = BIndirection Identifier
    | BTuple [Identifier]
    | BRecord [(Identifier, Identifier)]
  deriving (Eq, Read, Show)

-- | Annotations on expressions are mutability qualifiers.
instance Annotatable Expression where
    data Annotation Expression
        = EMutable
        | EImmutable
        | EType (K3 Type)
        | EPos Position
      deriving (Eq, Read, Show)
