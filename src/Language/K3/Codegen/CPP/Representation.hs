{-# LANGUAGE OverloadedStrings #-}

module Language.K3.Codegen.CPP.Representation where

import Data.String

import Text.PrettyPrint.ANSI.Leijen hiding ((<$>))

class Stringifiable a where
    stringify :: a -> Doc

data Name
    = Name Identifier
    | Qualified Identifier Name
    | Specialized [Type] Name
  deriving (Eq, Read, Show)

data Primitive
    = PBool
    | PInt
    | PDouble
    | PString
  deriving (Eq, Read, Show)

data Type
    = Named Name
    | Inferred
    | Parameter Identifier
    | Primitive Primitive
  deriving (Eq, Read, Show)

data Literal
    = LBool Bool
    | LInt Int
    | LDouble Double
    | LString String
  deriving (Eq, Read, Show)

data Expression
    = Binary Identifier Expression Expression
    | Call Expression [Expression]
    | Dereference Expression
    | Initialization Type Expression
    | Lambda [(Identifier, Expression)] [(Identifier, Type)] (Maybe Type) [Statement]
    | Literal Literal
    | Project Expression Identifier
    | Unary Identifier Expression
    | Variable Name
  deriving (Eq, Read, Show)

data Statement
    = Assignment (Maybe Type) Expression Expression
    | Block [Statement]
    | Ignored Expression
    | Return Expression
  deriving (Eq, Read, Show)

