{-# LANGUAGE TupleSections, TemplateHaskell #-}

module Language.K3.TypeSystem.Utils.K3Tree
( assert0Children
, assert1Child
, assert2Children
, assert3Children
, assert4Children
, assert5Children
, assert6Children
, assert7Children
, assert8Children
) where

import Control.Applicative
import Control.Monad
import Data.Map as Map
import Data.Set as Set
import Language.Haskell.TH

import Language.K3.Core.Annotation
import Language.K3.Core.Common
import Language.K3.Core.Expression
import Language.K3.Core.Type as K3T
import Language.K3.Core.Utils
import Language.K3.TypeSystem.Data
import Language.K3.TypeSystem.Error
import Language.K3.TypeSystem.Monad.Iface.TypeError
import Language.K3.TypeSystem.Utils.TemplateHaskell

-- * Generated routines

class ErrorForWrongChildren a where
  childCountError :: K3 a -> InternalTypeError
instance ErrorForWrongChildren Expression where
  childCountError = InvalidExpressionChildCount
instance ErrorForWrongChildren K3T.Type where
  childCountError = InvalidTypeExpressionChildCount
$(
  let f = mkAssertChildren
            (\tpn tt -> ForallT [PlainTV tpn] [] <$>
                        [t| ( Monad m, TypeErrorI m
                            , ErrorForWrongChildren $(varT tpn))
                           => K3 $(varT tpn) -> m $(tt) |])
            (\treeExp -> [| internalTypeError $ childCountError $(treeExp) |])
            (\tupleExp -> [| return $(tupleExp) |])
  in
  concat <$> mapM f [0::Int .. 8]
 )
