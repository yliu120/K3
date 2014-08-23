{-# LANGUAGE OverloadedStrings #-}

module Language.K3.Codegen.CPP.Representation where

import Data.String

import Text.PrettyPrint.ANSI.Leijen hiding ((<$>))

import Language.K3.Core.Common

class Stringifiable a where
    stringify :: a -> Doc

-- Pretty-Printing Utility Functions

commaSep :: [Doc] -> Doc
commaSep = fillSep . punctuate comma

data Name
    = Name Identifier
    | Qualified Identifier Name
    | Specialized [Type] Name
  deriving (Eq, Read, Show)

instance Stringifiable Name where
    stringify (Name i) = text i
    stringify (Qualified i n) = text i <> "::" <> stringify n
    stringify (Specialized ts n) = stringify n <> angles (commaSep $ map stringify ts)

data Primitive
    = PBool
    | PInt
    | PDouble
    | PString
  deriving (Eq, Read, Show)

instance Stringifiable Primitive where
    stringify PBool = "bool"
    stringify PInt = "int"
    stringify PDouble = "double"
    stringify PString = "string"

data Type
    = Named Name
    | Inferred
    | Parameter Identifier
    | Primitive Primitive
  deriving (Eq, Read, Show)

instance Stringifiable Type where
    stringify (Named n) = stringify n
    stringify Inferred = "auto"
    stringify (Parameter i) = fromString i
    stringify (Primitive p) = stringify p

data Literal
    = LBool Bool
    | LInt Int
    | LDouble Double
    | LString String
  deriving (Eq, Read, Show)

instance Stringifiable Literal where
    stringify (LBool b) = if b then "true" else "false"
    stringify (LInt i) = int i
    stringify (LDouble d) = double d
    stringify (LString s) = dquotes $ string s

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

instance Stringifiable Expression where
    stringify (Binary op a b) = parens (stringify a) <+> fromString op <+> parens (stringify b)
    stringify (Call e as) = stringify e <> parens (commaSep $ map stringify as)
    stringify (Dereference e) = fromString "*" <> parens (stringify e)
    stringify (Initialization t e) = stringify t <+> braces (stringify e)
    stringify (Lambda cs as rt bd) = cs' <+> as' <+> rt' <+> bd'
      where
        cs' = brackets $ commaSep [fromString i <+> equals <+> stringify t | (i, t) <- cs]
        as' = parens $ commaSep [stringify t <+> fromString i | (i, t) <- as]
        rt' = maybe empty (\rt'' -> "->" <+> stringify rt'') rt
        bd' = braces $ vsep $ map stringify bd
    stringify (Literal lt) = stringify lt
    stringify (Project pt i) = parens (stringify pt) <> dot <> fromString i
    stringify (Unary op e) = fromString op <> parens (stringify e)
    stringify (Variable n) = stringify n

data Statement
    = Assignment (Maybe Type) Expression Expression
    | Block [Statement]
    | Ignored Expression
    | Return Expression
  deriving (Eq, Read, Show)

instance Stringifiable Statement where
    stringify (Assignment mt a e) = maybe empty stringify mt <+> stringify a <+> equals <+> stringify e <> semi
    stringify (Block ss) = braces (vsep [stringify s <> semi | s <- ss])
    stringify (Ignored e) = stringify e <> semi
    stringify (Return e) = "return" <+> stringify e <> semi

data Declaration
    = Class Name [Type] [Declaration] [Declaration] [Declaration]
    | Function Type Name [(Identifier, Type)] [Statement]
    | Global Statement
    | Templated [(Identifier, Maybe Type)] Declaration
  deriving (Eq, Read, Show)

instance Stringifiable Declaration where
    stringify (Class cn ps publics privates protecteds) =
        "class" <+> stringify cn <> colon <+> stringifyParents ps
                    <+> braces (publics' <$$> privates' <$$> protecteds') <> semi
      where
        stringifyParents parents = commaSep ["public" <+> stringify t | t <- parents]
        publics' = "public" <> colon <$$> vsep (map stringify publics)
        privates' = "protected" <> colon <$$> vsep (map stringify protecteds)
        protecteds' = "private" <> colon <$$> vsep (map stringify privates)
    stringify (Function rt fn as bd) = rt' <+> fn' <> as' <+> bd'
      where
        rt' = stringify rt
        fn' = stringify fn
        as' = parens (commaSep [fromString i <+> stringify t | (i, t) <- as])
        bd' = braces (vsep $ map stringify bd)
    stringify (Global s) = stringify s
    stringify (Templated ts d) = "template" <+> angles (commaSep $ map parameterize ts) <$$> stringify d
      where
        parameterize (i, Nothing) = "class" <+> fromString i
        parameterize (i, Just t) = stringify t <+> fromString i
