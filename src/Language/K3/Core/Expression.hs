{-# LANGUAGE DeriveDataTypeable #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE ViewPatterns #-}

-- | Expressions in K3.
module Language.K3.Core.Expression where

import Data.List
import Data.Tree
import Data.Typeable
import Data.Word (Word8)

import Language.K3.Core.Annotation
import Language.K3.Core.Annotation.Analysis
import Language.K3.Core.Annotation.Codegen
import Language.K3.Core.Annotation.Syntax
import Language.K3.Core.Common
import Language.K3.Core.Type
import Language.K3.Core.Literal
import Language.K3.Analysis.Effects.Core

import Language.K3.Transform.Hints

import Language.K3.Analysis.HMTypes.DataTypes
import Language.K3.Utils.Pretty

-- | Cycle-breaking import for metaprogramming
import {-# SOURCE #-} Language.K3.Core.Metaprogram ( SpliceEnv )

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
    | EAddress
    | ESelf
    | EImperative ImperativeExpression
  deriving (Eq, Ord, Read, Show, Typeable)

data ImperativeExpression
    = EWhile
  deriving (Eq, Ord, Read, Show, Typeable)

-- | Constant expression values.
data Constant
    = CBool    Bool
    | CInt     Int
    | CByte    Word8
    | CReal    Double
    | CString  String
    | CNone    NoneMutability
    | CEmpty   (K3 Type)
  deriving (Eq, Ord, Read, Show, Typeable)

-- | Operators (unary and binary).
data Operator
    = OAdd
    | OSub
    | OMul
    | ODiv
    | OMod
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
    | OConcat
    | OSeq
    | OApp
    | OSnd
  deriving (Eq, Ord, Read, Show, Typeable)

-- | Binding Forms.
data Binder
    = BIndirection Identifier
    | BTuple       [Identifier]
    | BRecord      [(Identifier, Identifier)]
  deriving (Eq, Ord, Read, Show, Typeable)

-- | Annotations on expressions.
data instance Annotation Expression
    = ESpan Span
    | EUID UID
    | EMutable
    | EImmutable

    | EAnnotation Identifier
    | EProperty   Identifier (Maybe (K3 Literal))
    | EApplyGen   Bool Identifier SpliceEnv
        -- ^ Apply a K3 generator, with a bool indicating a control annotation generator (vs a data annotation),
        --   a generator name, and a splice environment.

    | ESyntax     SyntaxAnnotation
    | EAnalysis   AnalysisAnnotation

    -- TODO: the remainder of these should be pushed into
    -- an annotation category (e.g., EType, EAnalysis, etc)
    | EEffect     (K3 Effect)
    | ESymbol     (K3 Symbol)
    | EOpt        OptHint
    | EType       (K3 Type)
    | EQType      (K3 QType)
    | ETypeLB     (K3 Type)
    | ETypeUB     (K3 Type)
    | EPType      (K3 Type)  -- Annotation embedding for pattern types
    | EEmbedding EmbeddingAnnotation
  deriving (Eq, Ord, Read, Show)

instance HasUID (Annotation Expression) where
  getUID (EUID u) = Just u
  getUID _        = Nothing

instance HasSpan (Annotation Expression) where
  getSpan (ESpan s) = Just s
  getSpan _         = Nothing

-- | Data Conflicts
--   TODO: move to Language.K3.Core.Annotation.Analysis
data Conflict
    = RW [(Annotation Expression)] (Annotation Expression)
    | WR (Annotation Expression) [(Annotation Expression)]
    | WW (Annotation Expression) (Annotation Expression)
  deriving (Eq, Ord, Read, Show)

instance Pretty (K3 Expression) where
    prettyLines (Node (ETuple :@: as) []) =
      let (annStr, pAnnStrs) = drawExprAnnotations as
      in ["EUnit" ++ annStr] ++ (shift "`- " "   " pAnnStrs)

    prettyLines (Node (EConstant (CEmpty t) :@: as) []) =
      let (annStr, pAnnStrs) = drawExprAnnotations as
      in ["EConstant CEmpty" ++ annStr] ++ (shift "+- " "|  " pAnnStrs) ++ ["|"] ++ terminalShift t

    prettyLines (Node (t :@: as) es) =
      let (annStr, pAnnStrs) = drawExprAnnotations as
          shiftedTAnns       = if null es then (shift "`- " "   " pAnnStrs)
                                          else (shift "+- " "|  " pAnnStrs)
      in
      [show t ++ annStr] ++ shiftedTAnns ++ drawSubTrees es

drawExprAnnotations :: [Annotation Expression] -> (String, [String])
drawExprAnnotations as =
  let (typeAnns, anns)    = partition (\a -> isETypeOrBound a || isEQType a || isEPType a) as
      (effectAnns, anns') = partition (\a -> isEEffect a || isESymbol a) anns
      prettyTypeAnns = case typeAnns of
                         []         -> []
                         [EType t]  -> drawETypeAnnotation $ EType t
                         [EQType t] -> drawETypeAnnotation $ EQType t
                         [EPType t] -> drawETypeAnnotation $ EPType t
                         [t, l, u]  -> drawETypeAnnotation t
                                        %+ indent 2 (drawETypeAnnotation l
                                        %+ indent 2 (drawETypeAnnotation u))
                         _     -> error "Invalid type bound annotations"

      prettyTypeAnnsPrefixed =
        if null prettyTypeAnns then []
        else head prettyTypeAnns : map (\(_:t) -> '|':t) (tail prettyTypeAnns)

      prettyEffectAnnsL = map drawEEffectAnnotations effectAnns

      prettyEffectAnnsConcat  = foldl (\a b -> a %$ ["|"] %$ b) [] prettyEffectAnnsL
      prettyEffectAnnsShifted =
        if null prettyEffectAnnsL then []
        else    (concatMap (\e -> (shift "+- " "|  " e) ++ ["|"]) $ init prettyEffectAnnsL)
             ++ (shift "`- " "   " $ last prettyEffectAnnsL)

      prettyAnns = if null prettyTypeAnns || null prettyEffectAnnsL
                     then prettyTypeAnns ++ prettyEffectAnnsConcat
                     else prettyTypeAnnsPrefixed ++ ["|"] ++ prettyEffectAnnsShifted

  in (drawAnnotations anns', prettyAnns)

  where drawETypeAnnotation (ETypeLB t) = ["ETypeLB "] %+ prettyLines t
        drawETypeAnnotation (ETypeUB t) = ["ETypeUB "] %+ prettyLines t
        drawETypeAnnotation (EType   t) = ["EType   "] %+ prettyLines t
        drawETypeAnnotation (EQType  t) = ["EQType  "] %+ prettyLines t
        drawETypeAnnotation (EPType  t) = ["EPType  "] %+ prettyLines t
        drawETypeAnnotation _ = error "Invalid argument to drawETypeAnnotation"

        drawEEffectAnnotations (EEffect e) = ["EEffect "] %+ prettyLines e
        drawEEffectAnnotations (ESymbol s) = ["ESymbol "] %+ prettyLines s
        drawEEffectAnnotations _ = error "Invalid effect annotation"


{- Expression annotation predicates -}

isESpan :: Annotation Expression -> Bool
isESpan (ESpan _) = True
isESpan _         = False

isEQualified :: Annotation Expression -> Bool
isEQualified EImmutable = True
isEQualified EMutable   = True
isEQualified _          = False

isEUID :: Annotation Expression -> Bool
isEUID (EUID _) = True
isEUID _        = False

isEAnnotation :: Annotation Expression -> Bool
isEAnnotation (EAnnotation _) = True
isEAnnotation _               = False

isEProperty :: Annotation Expression -> Bool
isEProperty (EProperty _ _) = True
isEProperty _               = False

isEApplyGen :: Annotation Expression -> Bool
isEApplyGen (EApplyGen _ _ _) = True
isEApplyGen _ = False

isEType :: Annotation Expression -> Bool
isEType (EType   _) = True
isEType _           = False

isETypeOrBound :: Annotation Expression -> Bool
isETypeOrBound (EType   _) = True
isETypeOrBound (ETypeLB _) = True
isETypeOrBound (ETypeUB _) = True
isETypeOrBound _           = False

isEQType :: Annotation Expression -> Bool
isEQType (EQType _) = True
isEQType _          = False

isEPType :: Annotation Expression -> Bool
isEPType (EPType _) = True
isEPType _          = False

isEEffect :: Annotation Expression -> Bool
isEEffect (EEffect _) = True
isEEffect _           = False

isESymbol :: Annotation Expression -> Bool
isESymbol (ESymbol _) = True
isESymbol _           = False

namedEAnnotations :: [Annotation Expression] -> [Identifier]
namedEAnnotations anns = map extractId $ filter isEAnnotation anns
  where extractId (EAnnotation n) = n
        extractId _ = error "Invalid named annotation"
