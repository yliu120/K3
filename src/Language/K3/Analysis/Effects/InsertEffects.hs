{-# LANGUAGE DoAndIfThenElse #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE ViewPatterns #-}

-- | Insertion of effects into the expression/declaration tree
--
--   We rely on the fact that we run after typechecking and after
--   the InsertMembers analysis, so that collection annotation effects
--   are present in the expression tree
--
--  TODO: handle cyclic scope properly
--        cyclic scope can create loops
--
--  TODO: handle collection attributes (pass lambda var of self immediate)
--  TODO: handle recursive scope
--  TODO: lambda needs to filter effects for closure/formal args

module Language.K3.Analysis.Effects.InsertEffects (
  EffectEnv(..),
  preprocessBuiltins,
  runAnalysis,
  runAnalysisEnv,
  applyLambda,
  applyLambdaEnv,
  runConsolidatedAnalysis,
  symRWAQuery,
  eE,
  eS,
  expandProgram,
  expandEffDeep,
  expandSymDeep,
  occursEff,
  occursSym,
  symEqual
)
where

import Prelude hiding (read, seq)
import Control.Monad.State.Lazy
import Control.Applicative ((<$>))
import Data.Maybe
import Data.Map(Map)
import qualified Data.Map as Map
import Data.IntMap(IntMap)
import qualified Data.IntMap as IntMap
import Data.List(nub, delete)
import Data.Foldable hiding (and, mapM_, any, all, concatMap, concat, elem)
import Debug.Trace(trace)

import Language.K3.Core.Annotation
import Language.K3.Core.Common
import Language.K3.Core.Expression
import Language.K3.Core.Declaration
import Language.K3.Core.Utils
import Language.K3.Core.Type

import Language.K3.Analysis.Effects.Core
import Language.K3.Analysis.Effects.Constructors
import Language.K3.Utils.Pretty(pretty)

import qualified Language.K3.Analysis.InsertMembers as IM

debugTrace = False

data LocalSym = LocalSym (K3 Symbol) | LambdaLayer (Maybe (K3 Symbol))

getLambdaLayer :: LocalSym -> Maybe(K3 Symbol)
getLambdaLayer (LambdaLayer (Just x)) = Just x
getLambdaLayer _ = Nothing

isLambdaLayer :: LocalSym -> Bool
isLambdaLayer (LambdaLayer _) = True
isLambdaLayer _ = False

type GlobalEnv  = Map Identifier (K3 Symbol)
-- Nothing implies that a lambda layer was created, and needs to be filled in
-- This is done for closure
type LocalEnv   = Map Identifier [LocalSym]
type SymbolMap  = IntMap (K3 Symbol)
type EffectMap  = IntMap (K3 Effect)
-- Mapping of previously assigned ids to new ids
-- This is critical for proper non-destructive mapping
type AssignMap  = [IntMap Int]

data EffectEnv = EffectEnv {
                   count     :: Int,
                   globalEnv :: GlobalEnv,
                   bindEnv   :: LocalEnv,
                   symEnv    :: SymbolMap,
                   effEnv    :: EffectMap,
                   assignMap :: AssignMap -- Locally used for maps
                 }

startEnv :: EffectEnv
startEnv = EffectEnv {
             count     = 1,
             globalEnv = Map.empty,
             bindEnv   = Map.empty,
             symEnv    = IntMap.empty,
             effEnv    = IntMap.empty,
             assignMap = []
           }

insertGlobal :: Identifier -> K3 Symbol -> EffectEnv -> EffectEnv
insertGlobal i s env = env {globalEnv=Map.insert i s $ globalEnv env}

getId :: EffectEnv -> (Int, EffectEnv)
getId env = (count env, env {count = 1 + count env})

insertBind :: Identifier -> K3 Symbol -> EffectEnv -> EffectEnv
insertBind i s env = env {bindEnv=Map.insertWith (++) i [LocalSym s] $ bindEnv env}

-- Fully insert the entire depth of the bind environment for an identifier
insertBindDeep :: Identifier -> [LocalSym] -> EffectEnv -> EffectEnv
insertBindDeep i ss env = env {bindEnv=Map.insert i ss $ bindEnv env}

-- Insert a layer of a lambda into all the locals
-- Add the layer to all the locals
insertLambdaLayer :: EffectEnv -> EffectEnv
insertLambdaLayer env = env {bindEnv=Map.map (LambdaLayer Nothing:) $ bindEnv env}

-- Also removes the introduced variable
removeLambdaLayer :: EffectEnv -> (EffectEnv, [K3 Symbol])
removeLambdaLayer env =
  let syms =  catMaybes $ map (getLambdaLayer . head . snd) $ Map.toList $ bindEnv env
      env' = env {bindEnv=Map.map tailIfLambda $ bindEnv env}
  in (env', syms)
  where
    tailIfLambda xs = if isLambdaLayer $ head xs then tail xs else xs


deleteBind :: Identifier -> EffectEnv -> EffectEnv
deleteBind i env =
  let m  = bindEnv env
      m' = case Map.lookup i m of
             Just []     -> Map.delete i m
             Just [_]    -> Map.delete i m
             Just (_:xs) -> Map.insert i xs m
             Nothing     -> m
  in
  env {bindEnv=m'}

clearBinds :: EffectEnv -> EffectEnv
clearBinds env = env {bindEnv=Map.empty}

emptyClosure :: ClosureInfo
emptyClosure = ([],[],[])

-- Lookup either in the bind environment or the global environment
lookupBindInner :: Identifier -> EffectEnv -> Maybe [LocalSym]
lookupBindInner i env =
  case Map.lookup i $ bindEnv env of
    Nothing           -> liftM (singleton . LocalSym) $ lookupGlobalInner i env
    Just s            -> Just s

lookupGlobalInner :: Identifier -> EffectEnv -> Maybe (K3 Symbol)
lookupGlobalInner i env = Map.lookup i $ globalEnv env

-- Handle lambda layers and creating closure symbols
lookupBindInnerM :: Identifier -> MEnv (Maybe (K3 Symbol))
lookupBindInnerM i = do
  env <- get
  case lookupBindInner i env of
    Just (LocalSym s:_) -> return $ Just s
    -- If we initialized the closure var, return it
    Just ((LambdaLayer (Just s)):_) -> return $ Just s
    -- Otherwise, initialize a closure var
    Just (ss@((LambdaLayer Nothing):_)) -> do
      (syms, s, rest) <- initClosureSyms ss
      insertBindDeepM i $ syms++rest
      return $ Just s
    _                         -> return Nothing
  where
    -- Keep making new closure symbols until we get to a real symbol
    -- Each closure symbol points to the next
    initClosureSyms ((LambdaLayer Nothing):xs) = do
      (n, s, rest)  <- initClosureSyms xs
      s'            <- genSym PClosure True False [s]
      return ((LambdaLayer (Just s')):n, s', rest)
    initClosureSyms ((n@(LocalSym s)):rest)  = return ([n], s, rest)
    initClosureSyms (n@(LambdaLayer (Just s)):rest) = return ([n], s, rest)
    initClosureSyms _ = error "unexpected missing LocalSym"


lookupEffect :: Int -> EffectEnv -> Maybe (K3 Effect)
lookupEffect i env = IntMap.lookup i $ effEnv env

lookupSymbol :: Int -> EffectEnv -> Maybe (K3 Symbol)
lookupSymbol i env = IntMap.lookup i $ symEnv env

insertEffect :: Int -> K3 Effect -> EffectEnv -> EffectEnv
insertEffect i e env = env {effEnv=IntMap.insert i e $ effEnv env}

insertSymbol :: Int -> K3 Symbol -> EffectEnv -> EffectEnv
insertSymbol i s env = env {symEnv=IntMap.insert i s $ symEnv env}


type MEnv = State EffectEnv

insertGlobalM :: Identifier -> K3 Symbol -> MEnv ()
insertGlobalM i s = modify $ insertGlobal i s

insertBindM :: Identifier -> K3 Symbol -> MEnv ()
insertBindM i s = modify $ insertBind i s

insertBindDeepM :: Identifier -> [LocalSym] -> MEnv ()
insertBindDeepM i ss = modify $ insertBindDeep i ss

insertLambdaLayerM :: MEnv ()
insertLambdaLayerM = modify insertLambdaLayer

removeLambdaLayerM :: MEnv [K3 Symbol]
removeLambdaLayerM = do
  env <- get
  let (env', syms) = removeLambdaLayer env
  put env'
  return syms

deleteBindM :: Identifier -> MEnv ()
deleteBindM i = modify $ deleteBind i

clearBindsM :: MEnv ()
clearBindsM = modify clearBinds

lookupBindM :: Identifier -> MEnv (K3 Symbol)
lookupBindM i = do
  s <- lookupBindInnerM i
  let s' = fromMaybe (error $ "failed to find "++i++" in env") s
  return s'

getIdM :: MEnv Int
getIdM = do
  e <- get
  let (i, e') = getId e
  put e'
  return i

lookupEffectM :: Int -> MEnv (Maybe (K3 Effect))
lookupEffectM i = liftM (lookupEffect i) get

lookupSymbolM :: Int -> MEnv (Maybe (K3 Symbol))
lookupSymbolM i = liftM (lookupSymbol i) get

insertEffectM :: Int -> K3 Effect -> MEnv ()
insertEffectM i e = modify $ insertEffect i e

insertSymbolM :: Int -> K3 Symbol -> MEnv ()
insertSymbolM i s = modify $ insertSymbol i s

-- Manipulate the assignment env
-- It's a stack, to keep mapSym/Eff invocations separate
addAssignLevelM :: MEnv ()
addAssignLevelM = modify $ \env -> env {assignMap = IntMap.empty : assignMap env}

removeAssignLevelM :: MEnv ()
removeAssignLevelM = modify $ \env -> env {assignMap = tail $ assignMap env}

insertAssignM :: Int -> Int -> MEnv ()
insertAssignM from to =
  modify $ \env -> env {assignMap = ((IntMap.insert from to $ head $ assignMap env) : (tail $ assignMap env))}

findAssignM :: Int -> MEnv (Maybe Int)
findAssignM i = IntMap.lookup i . head . assignMap <$> get

-- Shallow substitution of symbol/effects id from env
expandEffM :: K3 Effect -> MEnv (K3 Effect)
expandEffM (tag -> FEffId i) = liftM (fromMaybe $ error $ "effect " ++ show i ++ " not in environment") (lookupEffectM i) >>= expandEffM
expandEffM eff               = return eff

expandSymM :: K3 Symbol -> MEnv (K3 Symbol)
expandSymM (tag -> SymId i)  = liftM (fromMaybe $ error $ "symbol " ++ show i ++ " not in environment") (lookupSymbolM i) >>= expandSymM
expandSymM sym               = return sym

expandEff :: EffectEnv -> K3 Effect -> K3 Effect
expandEff env eff = flip evalState env $ expandEffM eff

expandSym :: EffectEnv -> K3 Symbol -> K3 Symbol
expandSym env sym = flip evalState env $ expandSymM sym

expandEffDeep :: EffectEnv -> K3 Effect -> K3 Effect
expandEffDeep env eff = flip evalState env $ expandEffDeepM eff

expandSymDeep :: EffectEnv -> K3 Symbol -> K3 Symbol
expandSymDeep env sym = flip evalState env $ expandSymDeepM sym

expandEffDeepM :: K3 Effect -> MEnv (K3 Effect)
expandEffDeepM eff = do
  eff' <- expandEffM eff
  tg   <- case tag eff' of
             FRead s  -> liftM FRead  $ exSym s
             FWrite s -> liftM FWrite $ exSym s
             FScope ss  -> liftM FScope (exSyms ss)
             FApply s s' -> liftM2 FApply (exSym s) (exSym s')
             x -> return x
  let eff'' = replaceTag eff' tg
  handleCh eff''
  where
    handleCh eff'@(children -> ch) = do
      ch'  <- mapM expandEffDeepM ch
      return $ replaceCh eff' ch'
    exSym  = expandSymDeepM
    exSyms = mapM expandSymDeepM

expandSymDeepM :: K3 Symbol -> MEnv (K3 Symbol)
expandSymDeepM sym = do
  sym' <- expandSymM sym
  tg   <- case tag sym' of
             t@(Symbol {symProv=PLambda e}) -> do
               e' <- expandEffDeepM e
               return $ t {symProv=PLambda e'}
             x -> return x
  let sym'' = replaceTag sym' tg
  handleCh sym''
  where
    handleCh sym'@(children -> ch) = do
      ch'  <- mapM expandSymDeepM ch
      return $ replaceCh sym' ch'

expandProgram :: EffectEnv -> K3 Declaration -> K3 Declaration
expandProgram env p = fst $ runState (expandProg p) env

expandProg :: K3 Declaration -> MEnv (K3 Declaration)
expandProg n =
  -- Apply all lambda expressions
  mapProgram handleDecl mId applyLambdaExprs Nothing n >>=
  mapProgram mId mId expandExprs Nothing

-- go over the tree and apply all lambdas
applyLambdaExprs :: K3 Expression -> MEnv (K3 Expression)
applyLambdaExprs n = modifyTree applyLambdaExpr n

applyLambdaExpr :: K3 Expression -> MEnv (K3 Expression)
applyLambdaExpr n = do
  let mSym = getESymbol n
      mEff = getEEffect n
  mSym' <- case mSym of
              Nothing -> return Nothing
                        -- Make sure to do a non-destructive substitution
              Just s  -> liftM Just $ mapSym False (subEff Nothing) (subSym Nothing) s
  mEff' <- case mEff of
              Nothing -> return Nothing
              Just s  -> liftM Just $ mapEff False (subEff Nothing) (subSym Nothing) s
  return $ addEffSym mEff' mSym' n


expandExprs :: K3 Expression -> MEnv (K3 Expression)
expandExprs n' = modifyTree expandExpr n'
  where
    expandExpr :: K3 Expression -> MEnv (K3 Expression)
    expandExpr n = do
      let e = getEEffect n
          s = getESymbol n
      e' <- case e of
              Nothing  -> return Nothing
              Just eff -> liftM Just $ expandEffDeepM eff
      s' <- case s of
              Nothing  -> return Nothing
              Just sym -> liftM Just $ expandSymDeepM sym
      return $ addEffSym e' s' n

-- Common procedure for adding back the symbols, effects and children
addEffSym :: Maybe (K3 Effect) -> Maybe (K3 Symbol) -> K3 Expression -> K3 Expression
addEffSym eff sym n =
  let n'   = stripAnno (\x -> isEEffect x || isESymbol x) n
      n''  = maybe n'  ((@+) n'  . EEffect) eff
      n''' = maybe n'' ((@+) n'' . ESymbol) sym
  in n'''

addEffSymCh :: Maybe (K3 Effect) -> Maybe (K3 Symbol) -> [K3 Expression] -> K3 Expression -> K3 Expression
addEffSymCh eff sym ch n =
  let n'   = addEffSym eff sym n
  in replaceCh n' ch

-- Shortcuts for expandeffect & expandSym
eE :: EffectEnv -> K3 Effect -> K3 Effect
eE = expandEff

eS :: EffectEnv -> K3 Symbol -> K3 Symbol
eS = expandSym

-- Occurs check
occursEff :: Int -> K3 Effect -> K3 Effect -> MEnv ()
occursEff n occE e | occE `effEqual` e = error $ "Failed occurs check, step "++show n
occursEff n occE (tag -> FEffId i)   = liftM fromJust (lookupEffectM i) >>= occursEff (n+1) occE
occursEff _ _    _                     = return ()

occursSym :: Int -> K3 Symbol -> K3 Symbol -> MEnv ()
occursSym n occS s | occS `symEqual` s = error $ "Failed occurs check, step "++show n
occursSym n occS (tag -> SymId i)    = liftM fromJust (lookupSymbolM i) >>= occursSym (n+1) occS
occursSym _ _    _                     = return ()

-- Update symbols/effects: old, new, whether they're ids or not
updateEffM :: K3 Effect -> K3 Effect -> MEnv (K3 Effect)
updateEffM e@(tag -> FEffId i) e' = insertEffectM i e' >> return e
updateEffM _  e@(tag -> FEffId _) = return e
updateEffM (getFID -> Just i) e' = insertEffectM i (stripAnno isFID e' @+ FID i) >> return (effId i)
updateEffM _ e'@(getFID -> Just i) = insertEffectM i e' >> return (effId i)
updateEffM e e' = error $ "can't do the update: "++show e++"\n and also:"++show e'

updateSymM :: K3 Symbol -> K3 Symbol -> MEnv (K3 Symbol)
updateSymM s@(tag -> SymId i) s' = insertSymbolM i s' >> return s
updateSymM _ s@(tag -> SymId _)  = return s
updateSymM (getSID -> Just i) s' = insertSymbolM i (stripAnno isSID s' @+ SID i) >> return (symId i)
updateSymM _ e'@(getSID -> Just i) = insertSymbolM i e' >> return (symId i)
updateSymM e e' = error $ "can't do the update: "++show e++"\n and also:"++show e'

-- In contrast to updateXM, give a symbol a new id and put it in the environment
duplicateSymM :: K3 Symbol -> MEnv (K3 Symbol)
duplicateSymM s = do
  s2 <- expandSymM s
  let s' = stripAnno isSID s2
  i  <- getIdM
  insertSymbolM i (s' @+ SID i)
  return $ symId i

-- Give an effect a new id and put it in the environment
duplicateEffM :: K3 Effect -> MEnv (K3 Effect)
duplicateEffM e = do
  e2 <- expandEffM e
  let e' = stripAnno isFID e2
  i  <- getIdM
  insertEffectM i (e' @+ FID i)
  return $ effId i

singleton :: a -> [a]
singleton x = [x]

-- Create an effect and add it to the map
genEff :: K3 Effect -> MEnv (K3 Effect)
genEff eff = do
  i <- getIdM
  insertEffectM i $ eff @+ FID i
  return $ effId i

-- Add an id to an effect
addFID :: K3 Effect -> MEnv (K3 Effect)
addFID eff = do
  i <- getIdM
  return $ eff @+ FID i

addSID :: K3 Symbol -> MEnv (K3 Symbol)
addSID sym = do
  i <- getIdM
  return $ sym @+ SID i

getSID :: K3 Symbol -> Maybe Int
getSID sym = liftM extract $ sym @~ isSID
  where extract (SID i) = i

getFID :: K3 Effect -> Maybe Int
getFID sym = liftM extract $ sym @~ isFID
  where extract (FID i) = i

-- Generate a symbol
symbolM :: Identifier -> Provenance -> Bool -> Bool -> [K3 Symbol] -> MEnv (K3 Symbol)
symbolM name prov hasCopy hasWb ch = do
  i <- getIdM
  let s = symbol name prov hasCopy hasWb @+ SID i
  insertSymbolM i $ replaceCh s ch
  return $ symId i

genSym :: Provenance -> Bool -> Bool -> [K3 Symbol] -> MEnv (K3 Symbol)
genSym prov hasCopy hasWb ch = do
   i <- getIdM
   let s = symbol ("sym_"++show i) prov hasCopy hasWb @+ SID i
   insertSymbolM i $ replaceCh s ch
   return $ symId i

genSymTemp :: MEnv (K3 Symbol)
genSymTemp = genSym PTemporary True False []

genSymDerived :: [K3 Symbol] -> MEnv (K3 Symbol)
genSymDerived = genSym PDerived True False

genSymDirect :: K3 Symbol -> MEnv (K3 Symbol)
genSymDirect = genSym PDirect True False . singleton

getEEffect :: K3 Expression -> Maybe (K3 Effect)
getEEffect n = case n @~ isEEffect of
                 Just (EEffect e) -> Just e
                 _                -> Nothing

getESymbol :: K3 Expression -> Maybe (K3 Symbol)
getESymbol n = case n @~ isESymbol of
                 Just (ESymbol e) -> Just e
                 _                -> Nothing

-- If we don't have a symbol, we automatically gensym one
getOrGenSymbol :: K3 Expression -> MEnv (K3 Symbol)
getOrGenSymbol n = case getESymbol n of
                     Nothing -> genSymTemp
                     Just i  -> return i

-- Create a closure of symbols read, written, or applied that are relevant to the current env
createClosure :: Maybe (K3 Effect) -> Maybe (K3 Symbol) -> MEnv ClosureInfo
createClosure mEff mSym = liftM nubTuple $ do
  acc  <- case mSym of
           Nothing  -> return emptyClosure
           Just sym -> addClosureSym emptyClosure sym
  case mEff of
    Nothing  -> return acc
    Just eff -> addClosureEff acc eff
  where
    nubTuple (a,b,c) = (nub a, nub b, nub c)

    addClosureEff :: ClosureInfo -> K3 Effect -> MEnv ClosureInfo
    addClosureEff acc n' = do
      n <- expandEffM n'
      case tag n of
        FRead s -> do
          (a,b,c) <- addClosureSym acc s
          s'      <- getClosureSyms [] s
          return (s' ++ a,b,c)
        FWrite s -> do
          (a,b,c) <- addClosureSym acc s
          s'      <- getClosureSyms [] s
          return (a, s' ++ b, c)
        FApply s s' -> do
          acc'    <- addClosureSym acc  s
          (a,b,c) <- addClosureSym acc' s'
          s''     <- getClosureSyms [] s'
          return (a, b, s'' ++ c)
        FScope ss -> do
          acc' <- foldrM (flip addClosureEff) acc $ children n
          -- Add effects for scope behavior
          foldrM addScopeEff acc' ss
        -- Generic case
        _ -> foldrM (flip addClosureEff) acc $ children n

    -- Add the effect of scope
    addScopeEff :: K3 Symbol -> ClosureInfo -> MEnv ClosureInfo
    addScopeEff n' (r,w,a) = do
      n  <- expandSymM n'
      (r', w') <- case tag n of
                    Symbol {symHasCopy=True, symHasWb=True} -> (\a -> (a, a)) <$> getClosureSyms [] n'
                    Symbol {symHasCopy=True}                -> (,[]) <$> getClosureSyms [] n'
                    Symbol {symHasWb=True}                  -> ([],) <$> getClosureSyms [] n'
                    _                                       -> return ([], [])
      return (r'++r, w'++w, a)


    addClosureSym acc n' = do
      n <- expandSymM n'
      case tag n of
         Symbol {symProv=PLambda eff} -> do
           acc' <- foldrM (flip addClosureSym) acc $ children n
           addClosureEff acc' eff

         _ -> foldrM (flip addClosureSym) acc $ children n

    -- The method for searching for valid symbols
    getClosureSyms acc n' = do
      n <- expandSymM n'
      case tag n of
        SymId _                       -> error "unexpected symId1"
        -- Don't bother with temporaries (for now)
        Symbol {symProv=PGlobal}      -> return acc
        Symbol {symIdent=i}           -> do
          x' <- lookupBindInnerM i
          case x' of
            -- if we haven't found a match, it might be deeper in the symbol tree
            Nothing  -> foldrM (flip getClosureSyms) acc $ children n
            Just x'' -> do
              x  <- expandSymM x''
              case tag x of
                Symbol {symProv=PGlobal}      -> return acc
                _ | n `symEqual` x            -> return $ n':acc
                -- These 2 symbols' children aren't really further provenances
                Symbol {symProv=PLambda _}    -> return acc
                Symbol {symProv=PApply}       -> return acc
                -- If we have copy semantics, abort search
                Symbol {symHasCopy=True}     -> return acc
                -- if we haven't found a match, it might be deeper in the tree
                _ -> foldrM (flip getClosureSyms) acc $ children n

addAllGlobals :: K3 Declaration -> MEnv (K3 Declaration)
addAllGlobals node = mapProgram preHandleDecl mId mId Nothing node
  where
    -- add everything to global environment for cyclic/recursive scope
    -- we'll fix it up the second time through
    preHandleDecl n@(tag -> DGlobal i _ _)  =
      case n @~ isDSymbol of
        Just (DSymbol s) -> addGlobal i s >> return n
        _                -> addGeni i >> return n

    preHandleDecl n@(tag -> DTrigger i _ _) =
      case n @~ isDSymbol of
        Just (DSymbol s) -> addGlobal i s >> return n
        _                -> addGeni i >> return n

    preHandleDecl n = return n

    addGeni i     = symbolM i PGlobal False False []  >>= insertGlobalM i
    addGlobal i s = symbolM i PGlobal False False [s] >>= insertGlobalM i

mId :: Monad m => a -> m a
mId = return

mIdNone :: Monad m => a -> m (Maybe a)
mIdNone _ = return Nothing

symEqual :: K3 Symbol -> K3 Symbol -> Bool
symEqual (getSID -> s) (getSID -> s')    = s == s'

effEqual :: K3 Effect -> K3 Effect -> Bool
effEqual (getFID -> e) (getFID -> e')    = e == e'

-- map over symbols and effects, starting at an effect
-- @inplace: modify the tree in-place. If false, create new symbols/effects for the new parts
-- @functions: return a value if modified, otherwise nothing

type MapExpandF  a = K3 a -> MEnv (K3 a)
type MapChF      a = K3 a -> MEnv (Maybe (K3 a))
type MapProcessF a = K3 a -> Bool -> MEnv (Maybe (K3 a))
type MapUpdateF  a = K3 a -> K3 a -> MEnv (K3 a)
type MapDupF     a = K3 a -> MEnv (K3 a)
type MOptEffF      = K3 Effect -> MEnv (Maybe (K3 Effect))
type MOptSymF      = K3 Symbol -> MEnv (Maybe (K3 Symbol))

-- Generic version of map for both effects and symbols
-- Generic version of map for both effects and symbols
mapGen :: MapExpandF a -> MapChF a -> MapProcessF a -> MapUpdateF a -> MapDupF a
       -> (K3 a -> Int) -> (Int -> K3 a) -> Bool -> K3 a -> MEnv (Maybe (K3 a))
mapGen expandFn chMapFn processFn updateFn duplicateFn getIdFn mkIdFn inPlace n' =
  if inPlace then processNode $ updateFn n'
    else do
      -- Check if we can skip this iteration by using our cache
      t <- findAssignM (getIdFn n')
      case t of
        -- Reuse an old result
        Just targetId -> return $ Just $ mkIdFn targetId
        -- Save the new result
        Nothing       -> processNode $ dupAndSave n'
  where
    processNode handleResult = do
      n2 <- expandFn n'
      (ch, noch) <- getNew chMapFn $ children n2
      let n = replaceCh n2 ch
      mn <- processFn n noch
      case mn of
        Nothing -> return Nothing
        Just n3 -> liftM Just $ handleResult n3

    -- Duplicate the new result and cache it
    dupAndSave oldN newN = do
      n <- duplicateFn newN
      insertAssignM (getIdFn oldN) (getIdFn n)
      return n

-- Apply the function to a list. Return the new result if it exists, or the old result
-- if it doesn't. Also return a boolean of whether any new data was created
getNew :: (K3 a -> MEnv (Maybe (K3 a))) -> [K3 a] -> MEnv ([K3 a], Bool)
getNew f l = do
  ml <- mapM f l
  return (zipWith fromMaybe l ml, all isNothing ml)

-- @inPlace: whether we should do destructive updates (modifying in the tree) or create
-- new duplicated values
mapEff :: Bool -> MOptEffF -> MOptSymF -> K3 Effect -> MEnv (K3 Effect)
mapEff inPlace effFn symFn n = do
  -- Create a unique assignment map for this mapping, if needed
  addAssignLevelM
  mn <- mapEffInner inPlace effFn symFn n
  removeAssignLevelM
  return $ fromMaybe n mn

mapEffInner :: Bool -> MOptEffF -> MOptSymF -> K3 Effect -> MEnv (Maybe (K3 Effect))
mapEffInner inPlace effFn symFn =
  mapGen expandEffM mapEff' processNode updateEffM duplicateEffM (fromJust . getFID) effId inPlace
    where
      mapSym' = mapSymInner inPlace effFn symFn
      mapEff' = mapEffInner inPlace effFn symFn
      processNode n noch =
        case tag n of
          FRead s -> do
            ([s'], nos) <- getNew mapSym' [s]
            let n3 = replaceTag n $ FRead s'
            mn <- effFn n3
            return $ if noch && nos then mn else Just $ fromMaybe n3 mn
          FWrite s -> do
            ([s'], nos) <- getNew mapSym' [s]
            let n3 = replaceTag n $ FWrite s'
            mn <- effFn n3
            return $ if noch && nos then mn else Just $ fromMaybe n3 mn
          FScope ss -> do
            (ss', noss) <- getNew mapSym' ss
            let n3 = replaceTag n $ FScope ss'
            mn <- effFn n3
            return $ if noch && noss then mn else Just $ fromMaybe n3 mn
          FApply sL sA -> do
            ([sL'], nosl) <- getNew mapSym' [sL]
            ([sA'], nosa) <- getNew mapSym' [sA]
            let n3 = replaceTag n $ FApply sL' sA'
            mn <- effFn n3
            return $ if and [noch,nosl,nosa] then mn else Just $ fromMaybe n3 mn
          _ -> do
            mn <- effFn n
            return $ if noch then mn else Just $ fromMaybe n mn

mapSym :: Bool -> MOptEffF -> MOptSymF -> K3 Symbol -> MEnv (K3 Symbol)
mapSym inPlace effFn symFn n = do
  -- Create a unique assignment map for this mapping
  addAssignLevelM
  mn <- mapSymInner inPlace effFn symFn n
  removeAssignLevelM
  return $ fromMaybe n mn

mapSymInner :: Bool -> MOptEffF -> MOptSymF -> K3 Symbol -> MEnv (Maybe (K3 Symbol))
mapSymInner inPlace effFn symFn =
  mapGen expandSymM mapSym' processNode updateSymM duplicateSymM (fromJust . getSID) symId inPlace
  where
      mapSym' = mapSymInner inPlace effFn symFn
      mapEff' = mapEffInner inPlace effFn symFn
      processNode n noch =
        case tag n of
          t@(Symbol {symProv=PLambda e}) -> do
            ([e'], noe) <- getNew mapEff' [e]
            let n3 = replaceTag n $ t {symProv=PLambda e'}
            mn <- symFn n3
            return $ if noch && noe then mn else Just $ fromMaybe n3 mn
          _ -> do
            mn <- symFn n
            return $ if noch then mn else Just $ fromMaybe n mn

-------- Preprocessing phase --------
--
-- Fill in the effect symbols missing in any builtins
-- Number any existing symbols with SIDs and FIDs
-- This must be called before effects are lifted into the expression tree
preprocessBuiltins :: K3 Declaration -> (K3 Declaration, EffectEnv)
preprocessBuiltins prog = flip runState startEnv $ modifyTree addMissingDecl prog
  where
    addMissingDecl :: K3 Declaration -> MEnv (K3 Declaration)
    addMissingDecl n =
      case (tag n, n @~ isDSymbol) of
        (DDataAnnotation i t attrs, _) -> do
          attrs' <- mapM handleAttrs attrs
          return $ replaceTag n $ DDataAnnotation i t attrs'
        -- A global without an effect symbol
        (DGlobal _ t@(tag -> TFunction) Nothing, Nothing) -> handleFunctions t
        (DGlobal _ t@(tag -> TForall _) Nothing, Nothing) -> handleFunctions t
        -- If we have a symbol, number it
        (_, Just (DSymbol s)) -> do
          s' <- liftM (\ns -> DSymbol $ ns @+ SDeclared s) $ numberSyms s
          return $ stripAnno isDSymbol n @+ s'
        _ -> return n
      where handleFunctions t = do
              s <- symOfFunction False t
              return $ n @+ DSymbol s

    -- Handle lifted/unlifted attributes without symbols
    handleAttrs :: AnnMemDecl -> MEnv AnnMemDecl
    handleAttrs (Lifted x y t@(tag -> TFunction) Nothing annos)
      | isNothing (find isDSymbol annos) = do
          s <- symOfFunction True t
          return $ Lifted x y t Nothing $ DSymbol s:annos

    -- If we have a sumbol, number it
    handleAttrs (Lifted x y z u as) = liftM (Lifted x y z u) $ handleAttrsInner as

    handleAttrs (Attribute x y t Nothing annos)
      | isNothing (find isDSymbol annos) = do
          s <- symOfFunction True t
          return $ Attribute x y t Nothing $ DSymbol s:annos

    -- If we have a symbol, number it
    handleAttrs (Attribute x y z u as) = liftM (Attribute x y z u) $ handleAttrsInner as

    handleAttrs a = return a

    -- handle common attribute symbol/effect renumbering functionality
    handleAttrsInner as =
      case find isDSymbol as of
        Just ds@(DSymbol s) -> do
          s' <- liftM (\ns -> DSymbol $ ns @+ SDeclared s) $ numberSyms s
          let as' = delete ds as
          return $ s':as'
        _ -> return as

    -- Number existing symbols/effects
    numberSyms s = do
      s' <- mapSym True addNumEff addNumSym s
      clearBindsM  -- binds are only temporary here
      return s'

    -- For symbols, we only need a very simple binding pattern
    -- We bind variables so that inside the effect, we refer to the same symbols
    addNumSym s@(tag -> Symbol {symIdent=i, symProv=PVar}) = do
      l <- lookupBindInnerM i
      case l of
        Nothing -> do
          s' <- addSID s
          insertBindM i s'
          return $ Just s'
        s' -> return s'
    addNumSym s = liftM Just $ addSID s

    addNumEff = liftM Just . addFID

    -- Create a symbol for a function based on type
    -- If we're an attribute, we need to also write to self
    symOfFunction :: Bool -> K3 Type -> MEnv (K3 Symbol)
    symOfFunction addSelf t = liftM head $ symOfFunction' addSelf t 1

    symOfFunction' :: Bool -> K3 Type -> Int -> MEnv [K3 Symbol]
    symOfFunction' a (tnc -> (TForall _,   [ch])) i = symOfFunction' a ch i
    symOfFunction' addSelf (tnc -> (TFunction, [_, ret])) i = do
      s  <- symOfFunction' addSelf ret $ i + 1
      s' <- createConservativeSym (addSelf && i==1) s $ "__"++show i
      return [s']
    symOfFunction' _ _ _ = return []

    -- Create a default conservative symbol for the function
    -- @addSelf: add a r/w to 'self' (for attributes)
    createConservativeSym addSelf subSym' nm = do
      sym   <- symbolM nm PVar True False []
      r     <- genEff $ read sym
      w     <- genEff $ write sym
      seq'  <- if addSelf then do
                 selfSym <- symbolM "self" PVar False False []
                 rSelf   <- genEff $ read selfSym
                 wSelf   <- genEff $ write selfSym
                 return [Just w, Just r, Just wSelf, Just rSelf]
               else
                 return [Just w, Just r]
      seq'' <- combineEffSeq seq'
      lp    <- genEff $ loop $ fromMaybe (error "createConservativeSym") seq''
      sc    <- genEff $ scope [sym] [lp]
      genSym (PLambda sc) True False subSym'

----- Actual effect insertion ------
-- Requires an environment built up by the preprocess phase

runAnalysis :: K3 Declaration -> (K3 Declaration, EffectEnv)
runAnalysis = runAnalysisEnv startEnv

runConsolidatedAnalysis :: K3 Declaration -> (K3 Declaration, EffectEnv)
runConsolidatedAnalysis d =
  let (p, env) = preprocessBuiltins d in
  runAnalysisEnv env $ IM.runAnalysis p

-- Add all globals and decorate tree
handleDecl :: K3 Declaration -> MEnv (K3 Declaration)
handleDecl n =
  case tag n of
    DGlobal i _ (Just e) -> addE i e
    DTrigger i _ e       -> addE i e
    _                    -> return n
  where
    addE i e = case e @~ isESymbol of
                  Just (ESymbol s)  -> addSym i [s]
                  _                 -> addSym i []

    addSym i ss = do
      sym <- symbolM i PGlobal False False ss
      insertGlobalM i sym
      return $ stripAnno isDSymbol n @+ DSymbol sym

runAnalysisEnv :: EffectEnv -> K3 Declaration -> (K3 Declaration, EffectEnv)
runAnalysisEnv env1 prog = flip runState env1 $ do
  -- for cyclic scope, add temporaries for all globals
  p1 <- addAllGlobals prog
  -- actual modification of AST (no need to decorate declarations here)
  p2 <- mapProgram handleDecl mId handleExprs Nothing p1
  -- apply all lambdas
  if debugTrace then do
    p3 <- mapProgram handleDecl mId applyLambdaExprs Nothing p2
    p4 <- expandProg p3
    trace (pretty p4) $ return p2
    else
      return p2
  where

    handleExprs :: K3 Expression -> MEnv (K3 Expression)
    handleExprs n = mapIn1RebuildTree pre sideways handleExpr n

    extractBindData (BIndirection i) = [(i, PIndirection)]
    extractBindData (BTuple ids)     = zip ids [PTuple j | j <- [0..fromIntegral $ length ids - 1]]
    extractBindData (BRecord ijs)    = map (\(i, j) -> (j, PRecord i)) ijs

    doNothing = return ()

    doNothings n = return $ replicate n doNothing

    pre :: K3 Expression -> K3 Expression -> MEnv ()
    pre _ (tag -> ELambda i) = do
      -- Add to the environment
      sym  <- symbolM i PVar True False []
      -- Insert a lambda layer into the local environment
      insertLambdaLayerM
      -- Only insert the new binding now (so we don't create a lamda layer on it)
      insertBindM i sym

    pre _ _ = doNothing

    sideways :: K3 Expression -> K3 Expression -> MEnv [MEnv ()]

    -- We take the first child's symbol and bind to it
    sideways ch1 (tag -> ELetIn i) = do
      chSym <- getOrGenSymbol ch1
      s     <- symbolM i PLet True False [chSym]
      return [insertBindM i s]

    -- We take the first child's symbol and bind to it
    sideways ch1 (tag -> EBindAs b) = do
      chSym <- getOrGenSymbol ch1
      let iProvs = extractBindData b
      syms <- mapM (\(i, prov) -> liftM (i,) $ symbolM i prov True True [chSym]) iProvs
      return [mapM_ (uncurry insertBindM) syms]

    -- We take the first child's symbol and bind to it
    sideways ch1 (tag -> ECaseOf i) = do
      chSym <- getOrGenSymbol ch1
      s     <- symbolM i PLet True True [chSym]
      return [insertBindM i s, deleteBindM i, insertBindM i s]

    sideways _ (children -> ch) = doNothings (length ch - 1)

    -- A variable access looks up in the environment and generates a read
    -- It also creates a symbol
    handleExpr :: [K3 Expression] -> K3 Expression -> MEnv (K3 Expression)

    handleExpr _ n@(tag -> EVariable i) = do
      sym <- lookupBindM i
      eff <- genEff $ read sym
      return $ addEffSymCh (Just eff) (Just sym) [] n

    -- An assignment generates a write, and no symbol
    handleExpr ch@[e] n@(tag -> EAssign i) = do
      sym    <- lookupBindM i
      w      <- genEff $ write sym
      -- Add the write to any existing child effects
      nEff   <- combineEffSeq [getEEffect e, Just w]
      return $ addEffSymCh nEff Nothing ch n

    -- For ifThenElse be pessimistic: include effects and symbols of both paths
    handleExpr ch@[p,t,f] n@(tag -> EIfThenElse) = do
      tfEff <- combineEffSet [getEEffect t, getEEffect f]
      -- combineEff with predicate effects
      nEff  <- combineEffSeq [getEEffect p, tfEff]
      -- combineEff path symbols into a new symbol
      nSym  <- combineSymSet [getESymbol t, getESymbol f]
      return $ addEffSymCh nEff nSym ch n

    -- ELambda wraps up the child effect and sticks it in a symbol, but has no effect per se
    -- A new scope will be created at application
    handleExpr ch@[e] n@(tag -> ELambda i) = do
      bindSym     <- lookupBindM i
      -- Retrieve the results of the lambda layer
      closureSyms <- removeLambdaLayerM
      let eEff = getEEffect e
          eSym = maybeToList $ getESymbol e
      -- Create a gensym for the lambda, containing the effects of the child, and leading to the symbols
      eScope  <- genEff $ scope (bindSym : closureSyms) $ maybeToList eEff
      deleteBindM i
      lSym    <- genSym (PLambda eScope) True False eSym
      return $ addEffSymCh Nothing (Just lSym) ch n

    -- For collection attributes, we need to create and apply a lambda
    -- containing 'self'
    -- NOTE: We assume that the effect for this function has been inserted locally
    --       on the project

    -- On application, Apply creates a scope and substitutes into it
    -- We only create the effect of apply here
    handleExpr ch@[l,a] n@(tag -> EOperate OApp) = do
      seqE    <- combineEffSeq [getEEffect l, getEEffect a]
      -- Create the effect of application
      aSym    <- getOrGenSymbol a
      case getESymbol l of
        Nothing   -> error $ "failed to find symbol at lambda: " ++ show n
        Just lSym -> do
          -- mapp   <- applyLambda lSym aSym
          -- case mapp of
            -- Nothing -> do
              appE    <- genEff $ apply lSym aSym
              fullEff <- combineEffSeq [seqE, Just appE]
              fullSym <- combineSymApply (Just lSym) (Just aSym)
              return $ addEffSymCh fullEff fullSym ch n
            -- Just (resE, resS) -> do
            --  fullEff <- combineEffSeq [seqE, Just resE]
            --  return $ addEffSymCh fullEff (Just resS) ch n

    -- Bind
    handleExpr ch@[bind,e] n@(tag -> EBindAs b) = do
      let iProvs = extractBindData b
          ids    = map fst iProvs
      -- Get the scope info
      bindSyms <- mapM lookupBindM ids
      -- Remove binds from env
      mapM_ deleteBindM ids
      -- peel off until we get to a scope we know
      fullSym <- symInBind $ getESymbol e
      let eEff = maybe [] singleton $ getEEffect e
      bScope  <- genEff $ scope bindSyms eEff
      fullEff <- combineEffSeq [getEEffect bind, Just bScope]
      return $ addEffSymCh fullEff (Just fullSym) ch n

    -- CaseOf
    handleExpr ch@[e,some,none] n@(tag -> ECaseOf i) = do
      bindSym <- lookupBindM i
      deleteBindM i -- remove bind from env
      -- Wrap some in a scope
      let someEff = maybeToList $ getEEffect some
      scopeEff <- genEff $ scope [bindSym] someEff
      -- Conservative approximation
      setEff   <- combineEffSet [getEEffect none, Just scopeEff]
      combSym  <- combineSymSet [getESymbol some, getESymbol none]
      -- peel off symbols until we get ones in our outer scope
      fullSym  <- symInBind combSym
      fullEff  <- combineEffSeq [getEEffect e, setEff]
      return $ addEffSymCh fullEff (Just fullSym) ch n

    -- LetIn
    handleExpr ch@[l,e] n@(tag -> ELetIn i) = do
      bindSym <- lookupBindM i
      deleteBindM i -- remove bind from env
      let eEff = maybeToList $ getEEffect e
      scopeEff <- genEff $ scope [bindSym] eEff
      fullEff  <- combineEffSeq [getEEffect l, Just scopeEff]
      -- peel off symbols until we get to ones in our outer scope
      fullSym  <- symInBind $ getESymbol e
      return $ addEffSymCh fullEff (Just fullSym) ch n

    -- Projection
    handleExpr ch@[e] n@(tag -> EProject i) =
      -- Check in the type system for a function in a collection
      case (e @~ isEType, n @~ isEType) of
        (Just (EType(tag -> TCollection)), Just (EType(tag -> TFunction))) ->
          case getESymbol n of
            Just nSym -> do
              eSym  <- getOrGenSymbol e
              -- Make sure to substitute self without destructive updates
              -- In essence, we're making fresh copies of the parts we change
              nSym' <- mapSym False mIdNone (subSelf eSym) nSym
              -- for debugging
              -- nSym2 <- expandSymDeepM nSym'
              -- trace (show nSym2) $
              return $ addEffSymCh (getEEffect e) (Just nSym') ch n

            _   -> error $ "Missing symbol for projection of " ++ i

        _ -> do -- not a collection member function
          nSym <- genSym (PProject i) False False $ maybeToList $ getESymbol e
          return $ addEffSymCh (getEEffect e) (Just nSym) ch n
      where
        subSelf s n'@(tag -> Symbol {symIdent="self", symProv=PVar})    = return $ Just $ replaceCh n' [s]
        subSelf s n'@(tag -> Symbol {symIdent="content", symProv=PVar}) = return $ Just $ replaceCh n' [s]
        subSelf _ _                                                     = return Nothing

    -- handle seq (last symbol)
    handleExpr ch n@(tag -> EOperate OSeq) = do
      let chSym = getESymbol $ last ch
      eff   <- combineEffSeq $ map getEEffect ch
      return $ addEffSymCh eff chSym ch n

    handleExpr ch n@(tag -> EOperate OSnd) = do
      eff  <- genEff fio
      eff' <- combineEffSeq $ map getEEffect ch ++ [Just eff]
      return $ addEffSymCh eff' Nothing ch n

    -- Handle all derived expressions
    handleExpr ch n@(tag -> ESome)      = derivedExpr ch n
    handleExpr ch n@(tag -> EIndirect)  = derivedExpr ch n
    handleExpr ch n@(tag -> ETuple)     = derivedExpr ch n
    handleExpr ch n@(tag -> ERecord _)  = derivedExpr ch n
    -- All remaining operates are derivations
    handleExpr ch n@(tag -> EOperate _) = derivedExpr ch n

    handleExpr ch n = genericExpr ch n

    derivedExpr ch n = do
      eff <- combineEffSeq $ map getEEffect ch
      sym <- combineSymDerived $ map getESymbol ch
      return $ addEffSymCh eff sym ch n

    -- Generic case: combineEff effects, ignore symbols
    genericExpr ch n = do
      eff <- combineEffSeq $ map getEEffect ch
      return $ addEffSymCh eff Nothing ch n

------ Utilities ------

-- Data type for symInBind
data Changed a = Changed a | Unchanged a | Deleted

isDeleted :: Changed a -> Bool
isDeleted Deleted = True
isDeleted _ = False

isChanged :: Changed a -> Bool
isChanged (Changed _) = True
isChanged _ = False

isUnchanged :: Changed a -> Bool
isUnchanged (Unchanged _) = True
isUnchanged _ = False

-- Keep only symbol paths that originate in the bind envrionment
symInBind :: Maybe (K3 Symbol) -> MEnv (K3 Symbol)
symInBind Nothing    = genSymTemp
symInBind (Just sym) = do
  s' <- loop sym
  case s' of
    Deleted      -> genSymTemp
    Changed s'   -> genSymDirect s'
    Unchanged s' -> genSymDirect s'
  where
    -- Returns whether the symbol tree led to something in the env
    loop :: K3 Symbol -> MEnv (Changed (K3 Symbol))
    loop n' = do
      n <- expandSymM n'
      let i = symIdent $ tag n
      -- Particular provenances that are ok with deleting children
      let canRemoveCh = symProv (tag n) `elem` [PSet, PChoice, PDerived]
      -- If we don't find the symbol it may be deeper
      s <- lookupBindInnerM i
      if isJust s && fromJust s `symEqual` n then
        -- We found a match
        return $ Unchanged n'
      else do
        -- Search the children
        rs <- mapM loop $ children n
        if all isDeleted rs || null rs then return Deleted    -- Delete this branch
        else if all isUnchanged rs then return $ Unchanged n' -- Keep this branch as is
        else do                                               -- Keep some children
          ch' <- concat <$> mapM (extractOrTemp canRemoveCh) rs
          let n2 = replaceCh n ch'
          -- Save to the environment
          n3 <- duplicateSymM n2
          return $ Changed n3
      where
        extractOrTemp _ (Changed x)   = return [x]
        extractOrTemp _ (Unchanged x) = return [x]
        extractOrTemp True  Deleted   = return []
        extractOrTemp False Deleted   = singleton <$> genSymTemp

---- Utilities to work with effects dynamically

-- combineEff effects if they're present. Otherwise keep whatever we have
combineEff :: ([K3 Effect] -> K3 Effect) -> [Maybe (K3 Effect)] -> MEnv (Maybe (K3 Effect))
combineEff constF es =
  case filter isJust es of
    []  -> return Nothing
    [e] -> return e
    es' -> liftM Just $ genEff $ constF $ map (fromMaybe $ error "combineEff") es'

combineEffSet :: [Maybe (K3 Effect)] -> MEnv (Maybe (K3 Effect))
combineEffSet = combineEff set
combineEffSeq :: [Maybe (K3 Effect)] -> MEnv (Maybe (K3 Effect))
combineEffSeq = combineEff seq

-- combineSym symbols into 1 symbol
combineSym :: Bool -> Provenance -> [Maybe (K3 Symbol)] -> MEnv (Maybe (K3 Symbol))
combineSym okToDelete p ss =
  -- if there's no subsymbol at all, just gensym a temp
  if all (Nothing ==) ss then
    liftM Just genSymTemp
  -- if we have some symbols, we must preserve them
  else do
    ss' <- concat <$> mapM maybeGen ss
    case ss' of
      [s] -> return $ Just s
      _   -> liftM Just $ genSym p False False ss'
    where
      maybeGen (Just s) = return [s]
      maybeGen Nothing  | okToDelete = return []
      maybeGen Nothing  = singleton <$> genSymTemp

combineSymSet :: [Maybe (K3 Symbol)] -> MEnv (Maybe (K3 Symbol))
combineSymSet = combineSym True PSet

combineSymApply :: Maybe (K3 Symbol) -> Maybe (K3 Symbol) -> MEnv (Maybe (K3 Symbol))
combineSymApply l a = combineSym False PApply [l,a]

combineSymDerived :: [Maybe (K3 Symbol)] -> MEnv (Maybe (K3 Symbol))
combineSymDerived = combineSym True PDerived

applyLambdaEnv :: EffectEnv -> K3 Symbol -> K3 Symbol -> Maybe (K3 Effect, K3 Symbol)
applyLambdaEnv env l a = flip evalState env $ applyLambda l a

-- If the symbol is a global, substitute from the global environment
-- Apply (substitute) a symbol into a lambda symbol, generating effects and a new symbol
-- If we return Nothing, we cannot apply yet because of a missing lambda
applyLambda :: K3 Symbol -> K3 Symbol -> MEnv (Maybe (K3 Effect, K3 Symbol))
applyLambda sLam' sArg = do
  env  <- get
  sLam <- expandSymM sLam'
  case tnc sLam of
    (Symbol {symProv=PLambda lamEff@(tag . eE env -> FScope (sOld:_)), symHasCopy=hasCopy}, [chSym]) -> do
      -- Dummy substitute into the argument, in case there's an application there
      -- Any effects won't be substituted in and will be visible outside
      sArg'    <- mapSym False (subEff Nothing) (subSym Nothing) sArg
      -- Substitute into the old effects and symbol
      lamEff'  <- mapEff False (subEff $ Just (sOld, sArg', hasCopy))
                               (subSym $ Just (sOld, sArg', hasCopy)) lamEff
      -- Substitute into the child (result symbol)
      chSym'   <- mapSym False (subEff $ Just (sOld, sArg', hasCopy))
                               (subSym $ Just (sOld, sArg', hasCopy)) chSym
      -- For debugging
      {-
      sLam2 <- expandSymDeepM sLam
      sArg2 <- expandSymDeepM sArg'
      lamEff2 <- expandEffDeepM lamEff''
      chSym2 <- expandSymDeepM chSym'
      trace ("applied lambda: \n"++pretty sLam2++"\nto arg: \n"++pretty sArg2++"\nresult effect: \n"++pretty lamEff2++"\nresult symbol: \n"++pretty chSym2) $ return $ Just (lamEff', chSym')
      -}
      return $ Just (lamEff', chSym')

    (Symbol {symProv=PGlobal}, [ch])  -> applyLambda ch sArg
    (Symbol {symProv=PDirect}, [ch])  -> applyLambda ch sArg

    -- For a set 'lambda', we need to combine results
    (Symbol {symProv=PSet}, ch)      -> do
      xs <- mapM (`applyLambda` sArg) ch
      let (es, ss) = unzip $ catMaybes xs
          (es', ss') = (map Just es, map Just ss)
      sSet <- combineSymSet ss'
      eSet <- combineEffSet es'
      return $ Just (fromMaybe (error "applyLambda: 1st") eSet, fromMaybe (error "applyLambda: 2nd") sSet)

    -- For now, have only 1 choice
    (Symbol {symProv=PChoice}, ch:_) -> applyLambda ch sArg

    _ -> return Nothing

-- Substitute a symbol for another in a symbol: old, new, symbol in which to replace
-- NOTE: We assume the effects and symbols here don't need the environment
subSym :: Maybe (K3 Symbol, K3 Symbol, Bool) -> K3 Symbol -> MEnv (Maybe(K3 Symbol))
subSym (Just (s, s', hasCopy)) n@(tag -> t@(Symbol {symProv=PVar})) | n `symEqual` s =
    return $ Just $ flip replaceTag (t {symHasCopy=hasCopy}) $ replaceCh n [s']
-- Apply: recurse (we already substituted into the children)
subSym _ (tnc -> (Symbol {symProv=PApply}, [sL, sA])) = do
  m <- applyLambda sL sA
  case m of
    Nothing -> return Nothing
    Just m' -> return $ Just $ snd m'
subSym _ _ = return Nothing

-- Substitute one symbol for another in an effect
-- mapSym already handled sL and sA
-- NOTE: We assume the effects and symbols here don't need the environment
subEff :: Maybe (K3 Symbol, K3 Symbol, Bool) -> K3 Effect -> MEnv (Maybe(K3 Effect))
subEff _ (tag -> FApply sL sA) = do
  m <- applyLambda sL sA
  case m of
    Nothing -> return Nothing
    Just m' -> return $ Just $ fst m'
subEff _ _ = return Nothing

-- Query whether certain symbols are read, written, applied
symRWAQuery :: K3 Effect -> [K3 Symbol] -> EffectEnv -> ClosureInfo
symRWAQuery eff syms env = flip evalState env $ do
  clearBindsM
  -- Use the symbols as a bind environment
  mapM_ addToEnv syms
  -- Substitute any lambdas inside
  eff' <- mapEff False (subEff Nothing) (subSym Nothing) eff
  -- Get the general closure
  cl <- createClosure (Just eff') Nothing
  return cl
  where
    -- For superstructure, we add parents
    addToEnv s' = do
      s <- expandSymM s'
      case tag s of
        Symbol {symIdent=i, symProv=PRecord _}   -> insertBindM i s' >> mapM_ addToEnv (children s)
        Symbol {symIdent=i, symProv=PTuple _}    -> insertBindM i s' >> mapM_ addToEnv (children s)
        Symbol {symIdent=i, symProv=PProject _}  -> insertBindM i s' >> mapM_ addToEnv (children s)
        -- Otherwise, we just add the individual symbol
        Symbol {symIdent=i} -> insertBindM i s'
        SymId _                -> error "unexpected symId2"

-- Only reads query
-- Modified-before e1 -> e2 -> [Symbol] -> bool
