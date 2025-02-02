{-# LANGUAGE PatternGuards #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE TypeOperators #-}

-- | K3 Program constructor
module Language.K3.Parser.ProgramBuilder (
  defaultRoleName,
  processInitsAndRoles,
  endpointMethods,
  bindSource,
  mkRunSourceE,
  mkRunSinkE,
  declareBuiltins,

  resolveFn
) where

import Control.Applicative

import Data.List
import Data.Tree
import Debug.Trace

import Language.K3.Core.Annotation
import Language.K3.Core.Common
import Language.K3.Core.Declaration
import Language.K3.Core.Expression
import Language.K3.Core.Type
import Language.K3.Core.Utils

import qualified Language.K3.Core.Constructor.Type        as TC
import qualified Language.K3.Core.Constructor.Expression  as EC
import qualified Language.K3.Core.Constructor.Declaration as DC

-- | Type synonyms, copied from the parser.
type EndpointInfo = (EndpointSpec, Maybe [Identifier], Identifier, Maybe (K3 Expression))

{- Names -}
defaultRoleName :: Identifier
defaultRoleName = "__global"

myId :: Identifier
myId = "me"

peersId :: Identifier
peersId = "peers"

argsId :: Identifier
argsId = "args"

myAddr :: K3 Expression
myAddr = EC.variable myId

chrName :: Identifier -> Identifier
chrName n = n++"HasRead"

crName :: Identifier -> Identifier
crName n = n++"Read"

chwName :: Identifier -> Identifier
chwName n = n++"HasWrite"

cwName :: Identifier -> Identifier
cwName n = n++"Write"

ciName :: Identifier -> Identifier
ciName n = n++"Init"

csName :: Identifier -> Identifier
csName n = n++"Start"

cpName :: Identifier -> Identifier
cpName n = n++"Process"

ccName :: Identifier -> Identifier
ccName n = n++"Controller"

{- Runtime functions -}
openBuiltinFn :: K3 Expression
openBuiltinFn = EC.variable "openBuiltin"

openFileFn :: K3 Expression
openFileFn = EC.variable "openFile"

openSocketFn :: K3 Expression
openSocketFn = EC.variable "openSocket"

closeFn :: K3 Expression
closeFn = EC.variable "close"

{- -- Unused
registerFileDataTriggerFn :: K3 Expression
registerFileDataTriggerFn = EC.variable "registerFileDataTrigger"

registerFileCloseTriggerFn :: K3 Expression
registerFileCloseTriggerFn = EC.variable "registerFileCloseTrigger"

registerSocketAcceptTriggerFn :: K3 Expression
registerSocketAcceptTriggerFn = EC.variable "registerSocketAcceptTrigger"

registerSocketCloseTriggerFn :: K3 Expression
registerSocketCloseTriggerFn = EC.variable "registerSocketCloseTrigger"
-}

registerSocketDataTriggerFn :: K3 Expression
registerSocketDataTriggerFn = EC.variable "registerSocketDataTrigger"

resolveFn :: K3 Expression
resolveFn = EC.variable "resolve"

{- Top-level functions -}
roleId :: Identifier
roleId = "role"

roleVar :: K3 Expression
roleVar = EC.variable roleId

roleFnId :: Identifier
roleFnId = "processRole"

roleFn :: K3 Expression
roleFn = EC.variable roleFnId


{- Declaration construction -}
builtinGlobal :: Identifier -> K3 Type -> Maybe (K3 Expression) -> K3 Declaration
builtinGlobal n t eOpt = (DC.global n t eOpt) @+ (DSpan $ GeneratedSpan "builtin")

builtinTrigger :: Identifier -> K3 Type -> K3 Expression -> K3 Declaration
builtinTrigger n t e = (DC.trigger n t e) @+ (DSpan $ GeneratedSpan "builtin")

{- Type qualification -}
qualifyT :: K3 Type -> K3 Type
qualifyT t = if null $ filter isTQualified $ annotations t then t @+ TImmutable else t

qualifyE :: K3 Expression -> K3 Expression
qualifyE e = if null $ filter isEQualified $ annotations e then e @+ EImmutable else e

{- Desugaring methods -}
-- TODO: replace with Template Haskell

processInitsAndRoles :: K3 Declaration -> [(Identifier, EndpointInfo)] -> [(Identifier, Identifier)]
                     -> K3 Declaration
processInitsAndRoles (Node t c) endpointBQGs roleDefaults = Node t $ c ++ initializerFns
  where
        (sinkEndpoints, sourceEndpoints) = partition matchSink endpointBQGs
        matchSink (_,(_, Nothing, _, _)) = True
        matchSink _ = False

        initializerFns =
            [ builtinGlobal roleFnId (qualifyT unitFnT)
                $ Just . qualifyE $ mkRoleBody sourceEndpoints sinkEndpoints roleDefaults ]

        sinkInitE acc (_,(_, Nothing, _, Just e)) = acc ++ [e]
        sinkInitE acc _ = acc

        mkRoleBody sources sinks defaults =
          EC.lambda "_" $ EC.block $
            (trace ("Sinks " ++ show sinks) $ foldl sinkInitE [] sinks) ++
            [uncurry (foldl dispatchId) $ defaultAndRestIds sources defaults]

        defaultAndRestIds sources defaults = (defaultE sources $ lookup "" defaults, sources)
        dispatchId elseE (n,(_,_,y,goE))  = EC.ifThenElse (eqRole y) (runE n goE) elseE

        eqRole n = EC.binop OEqu roleVar (EC.constant $ CString n)

        runE _ (Just goE) = goE
        runE n Nothing    = EC.applyMany (EC.variable $ cpName n) [EC.unit]

        defaultE s (Just x) = case find ((x ==) . third . snd) s of
                                Just (n,(_,_,_,goE)) -> runE n goE
                                Nothing              -> EC.unit
        defaultE _ Nothing   = EC.unit

        third (_,_,x,_) = x

        unitFnT = TC.function TC.unit TC.unit


{- Code generation methods-}
-- TODO: replace with Template Haskell

endpointMethods :: Bool -> EndpointSpec -> K3 Expression -> K3 Expression -> Identifier -> K3 Type
                -> (EndpointSpec, Maybe (K3 Expression), [K3 Declaration])
endpointMethods isSource eSpec argE formatE n t =
  if isSource then sourceDecls else sinkDecls
  where
    sourceDecls = (eSpec, Nothing,) $
         (map mkMethod [mkInit, mkStart, mkFinal, sourceHasRead, sourceRead])
      ++ [sourceController]

    sinkDecls = (eSpec, Just sinkImpl, map mkMethod [mkInit, mkFinal, sinkHasWrite, sinkWrite])

    mkMethod (m, argT, retT, eOpt) =
      builtinGlobal (n++m) (qualifyT $ TC.function argT retT)
        $ maybe Nothing (Just . qualifyE) eOpt

    mkInit  = ("Init",  TC.unit, TC.unit, Just $ EC.lambda "_" $ openEndpointE)
    mkStart = ("Start", TC.unit, TC.unit, Just $ EC.lambda "_" $ startE)
    mkFinal = ("Final", TC.unit, TC.unit, Just $ EC.lambda "_" $ EC.applyMany closeFn [sourceId n])

    sourceController = builtinTrigger (ccName n) TC.unit $
      EC.lambda "_"
        (EC.ifThenElse
          (EC.applyMany (EC.variable $ chrName n) [EC.unit])
          (controlE $ EC.applyMany (EC.variable $ cpName n) [EC.unit])
          EC.unit)

    sinkImpl =
      EC.lambda "__msg"
        (EC.ifThenElse
          (EC.applyMany (EC.variable $ chwName n) [EC.unit])
          (EC.applyMany (EC.variable $ cwName n) [EC.variable "__msg"])
          (EC.unit))

    -- External functions
    cleanT        = stripTUIDSpan t
    sourceHasRead = ("HasRead",  TC.unit, TC.bool, Nothing)
    sourceRead    = ("Read",     TC.unit, cleanT,  Nothing)
    sinkHasWrite  = ("HasWrite", TC.unit, TC.bool, Nothing)
    sinkWrite     = ("Write",    cleanT,  TC.unit, Nothing)

    openEndpointE = case eSpec of
      BuiltinEP _ _ -> EC.applyMany openBuiltinFn [sourceId n, argE, formatE]
      FileEP    _ _ -> openFnE openFileFn
      NetworkEP _ _ -> openFnE openSocketFn
      _             -> error "Invalid endpoint argument"

    openFnE openFn = EC.applyMany openFn [sourceId n, argE, formatE, modeE]

    modeE = EC.constant . CString $ if isSource then "r" else "w"

    startE = case eSpec of
      BuiltinEP _ _ -> fileStartE
      FileEP    _ _ -> fileStartE
      NetworkEP _ _ -> EC.applyMany registerSocketDataTriggerFn [sourceId n, EC.variable $ ccName n]
      _             -> error "Invalid endpoint argument"

    fileStartE = EC.send (EC.variable (ccName n)) myAddr EC.unit

    controlE processE = case eSpec of
      BuiltinEP _ _ -> fileControlE processE
      FileEP    _ _ -> fileControlE processE
      NetworkEP _ _ -> processE
      _             -> error "Invalid endpoint argument"

    fileControlE processE =
      EC.block [processE, (EC.send (EC.variable $ ccName n) myAddr EC.unit)]

    sourceId n' = EC.constant $ CString n'

-- | Rewrites a source declaration's process method to access and
--   dispatch the next available event to all its bindings.
bindSource :: [(Identifier, Identifier)] -> K3 Declaration -> (K3 Declaration, [K3 Declaration])
bindSource bindings d
  | DGlobal src t eOpt <- tag d
  , TSource <- tag t
  = (d, [mkProcessFn src eOpt])

  | otherwise = (d, [])

  where
    -- | Constructs a dispatch function declaration for a source.
    mkProcessFn n eOpt =
      builtinGlobal (cpName n) (qualifyT unitFnT) (Just . qualifyE $ body n eOpt)

    body n eOpt = EC.lambda "_" $ EC.applyMany (processFnE n) [nextE n eOpt]

    processFnE n = EC.lambda "next" $ EC.block $
      map (\(_,dest) -> sendNextE dest) $ filter ((n ==) . fst) bindings

    nextE _ (Just e) = stripEUIDSpan e
    nextE n Nothing  = EC.applyMany (EC.variable $ crName n) [EC.unit]
    sendNextE dest   = EC.send (EC.variable dest) myAddr (EC.variable "next")
    unitFnT          = TC.function TC.unit TC.unit

-- | Constructs an "atInit" expression for initializing and starting sources.
mkRunSourceE :: Identifier -> K3 Expression
mkRunSourceE n = EC.block [EC.applyMany (EC.variable $ ciName n) [EC.unit],
                           EC.applyMany (EC.variable $ csName n) [EC.unit]]

-- | Constructs an "atInit" expression for initializing sinks.
mkRunSinkE :: Identifier -> K3 Expression
mkRunSinkE n = EC.applyMany (EC.variable $ ciName n) [EC.unit]


-- TODO: at_exit function body
declareBuiltins :: K3 Declaration -> K3 Declaration
declareBuiltins d
  | DRole n <- tag d, n == defaultRoleName = replaceCh d new_children
  | otherwise = d
  where new_children = runtimeDecls ++ peerDecls ++ (children d)

        runtimeDecls = [
          mkGlobal "registerFileDataTrigger"     (mkCurriedFnT [idT, TC.trigger TC.unit, TC.unit]) Nothing,
          mkGlobal "registerFileCloseTrigger"    (mkCurriedFnT [idT, TC.trigger TC.unit, TC.unit]) Nothing,
          mkGlobal "registerSocketAcceptTrigger" (mkCurriedFnT [idT, TC.trigger TC.unit, TC.unit]) Nothing,
          mkGlobal "registerSocketDataTrigger"   (mkCurriedFnT [idT, TC.trigger TC.unit, TC.unit]) Nothing,
          mkGlobal "registerSocketCloseTrigger"  (mkCurriedFnT [idT, TC.trigger TC.unit, TC.unit]) Nothing ]

        peerDecls = [
          mkGlobal myId    TC.address Nothing,
          mkGlobal peersId peersT     Nothing,
          mkGlobal argsId  progArgT   Nothing,
          mkGlobal roleId  TC.string  Nothing]

        idT      = TC.string
        progArgT = TC.tuple [qualifyT argT, qualifyT paramsT]
        peersT   = mkCollection [("addr", TC.address)]
        argT     = mkCollection [("arg", TC.string)]
        paramsT  = mkCollection [("key", TC.string), ("value", TC.string)]

        mkGlobal n t eOpt = builtinGlobal n (qualifyT t) $ maybe Nothing (Just . qualifyE) eOpt

        mkCurriedFnT tl = foldr1 TC.function tl

        --mkAUnitFnT at = TC.function at TC.unit
        --mkRUnitFnT rt = TC.function TC.unit rt
        unitFnT       = TC.function TC.unit TC.unit

        mkCollection fields = (TC.collection $ TC.record $ map (qualifyT <$>) fields) @+ TAnnotation "Collection"
