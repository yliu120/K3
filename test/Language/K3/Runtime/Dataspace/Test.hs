{-# LANGUAGE DoAndIfThenElse #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE RankNTypes #-}

module Language.K3.Runtime.Dataspace.Test (tests) where

import Control.Monad
import Control.Monad.Trans.Either
import Data.List
import Data.Maybe

import Test.HUnit hiding (Test)
import Test.Framework.Providers.API
import Test.Framework.Providers.HUnit

import Language.K3.Interpreter
import Language.K3.Runtime.Dataspace
import Language.K3.Runtime.Engine
import Language.K3.Runtime.FileDataspace

-- Duplicated from Interpreter.hs
vunit = VTuple []

compareDataspaceToList :: (Monad m, Dataspace m ds Value) => ds -> [Value] -> m Bool
compareDataspaceToList ds l = do
  result <- foldM findAndRemoveElement (Just ds) l
  case result of
    Nothing -> return False
    Just ds -> do
      s <- sizeDS ds
      return $ if s == 0 then True else False
  where
    findAndRemoveElement :: (Monad m, Dataspace m ds Value) => Maybe ds -> Value -> m (Maybe ds)
    findAndRemoveElement maybeTuple cur_val = do
      case maybeTuple of
        Nothing -> return Nothing
        Just ds -> do
          contains <- containsDS ds cur_val
          if contains
            then do
              removed <- deleteDS cur_val ds
              return $ Just removed
          else
            return Nothing

emptyPeek :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
emptyPeek dataspace _ = do
  d <- newDS dataspace
  result <- peekDS d
  return (isNothing result)

testEmptyFold :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testEmptyFold dataspace _ = do
  d <- newDS dataspace
  counter <- foldDS innerFold 0 d
  return (counter == 0 )
  where
    innerFold :: Int -> Value -> Interpretation Int
    innerFold cnt _ = return $ cnt + 1

test_lst = [VInt 1, VInt 2, VInt 3, VInt 4, VInt 4, VInt 100]

testPeek :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testPeek dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  peekResult <- peekDS test_ds
  case peekResult of
    Nothing -> return False
    Just v -> containsDS test_ds v
  

testInsert :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testInsert dataspace _ = do
  test_ds <- newDS ([]::[Value])
  test_ds <- foldM (\ds val -> insertDS ds val) test_ds test_lst
  compareDataspaceToList test_ds test_lst

testDelete :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testDelete dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  deleted <- deleteDS (VInt 3) test_ds
  deleted <- deleteDS (VInt 4) deleted
  compareDataspaceToList deleted [VInt 1, VInt 2, VInt 4, VInt 100]

testMissingDelete :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testMissingDelete dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  deleted <- deleteDS (VInt 5) test_ds
  compareDataspaceToList deleted test_lst

testUpdate :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testUpdate dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  updated <- updateDS (VInt 1) (VInt 4) test_ds
  compareDataspaceToList updated [VInt 4, VInt 2, VInt 3, VInt 4, VInt 4, VInt 100]

testUpdateMultiple :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testUpdateMultiple dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  updated <- updateDS (VInt 4) (VInt 5) test_ds
  compareDataspaceToList updated [VInt 1, VInt 2, VInt 3, VInt 5, VInt 4, VInt 100]

testUpdateMissing :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testUpdateMissing dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  updated <- updateDS (VInt 40) (VInt 5) test_ds
  compareDataspaceToList updated ( test_lst ++ [VInt 5] )

testFold :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testFold dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  test_sum <- foldDS innerFold 0 test_ds
  return $ test_sum == 114
  where
    innerFold :: Int -> Value -> Interpretation Int
    innerFold acc value =
      return $ case value of
        VInt v -> acc + v
        otherwise -> -1 -- TODO throw real error

vintAdd :: Int -> Value -> Value
vintAdd c val =
  case val of
    VInt v -> VInt (v + c)
    otherwise -> VInt (-1) -- TODO throw real error

testMap :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testMap dataspace _ = do
  test_ds <- initialDS test_lst dataspace
  mapped_ds <- mapDS (return . (vintAdd 5)) test_ds
  compareDataspaceToList mapped_ds [VInt 6, VInt 7, VInt 8, VInt 9, VInt 9, VInt 105]

testCombine :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testCombine dataspace _ = do
  left' <- initialDS test_lst dataspace
  right' <- initialDS test_lst dataspace
  combined <- combineDS left' right'
  compareDataspaceToList combined (test_lst ++ test_lst)

sizeDS :: (Monad m, Dataspace m ds Value) => ds -> m Int
sizeDS ds = do
  foldDS innerFold 0 ds
  where
    innerFold :: (Monad m) => Int -> Value -> m Int
    innerFold cnt _ = return $ cnt + 1
-- depends on combine working
testSplit :: (Dataspace Interpretation ds Value) => ds -> () -> Interpretation Bool
testSplit dataspace _ = do
  -- split doesn't do anything if one of the collections contains less than 10 elements
  let long_lst = test_lst ++ test_lst
  first_ds <- initialDS long_lst dataspace
  (left', right') <- splitDS first_ds
  leftLen <- sizeDS left'
  rightLen <- sizeDS right'
  if leftLen >= length long_lst || rightLen >= length long_lst || leftLen + rightLen > length long_lst
    then
      return False
    else do
      remainders <- foldM findAndRemoveElement (Just (left', right')) long_lst
      case remainders of
        Nothing -> return False
        Just (l, r) -> do
          lLen <- sizeDS l
          rLen <- sizeDS r
          if lLen == 0 && rLen == 0
            then
              return True
            else
              return False
  where
    findAndRemoveElement :: (Dataspace Interpretation ds Value) => Maybe (ds, ds) -> Value -> Interpretation (Maybe (ds, ds))
    findAndRemoveElement maybeTuple cur_val =
      case maybeTuple of
        Nothing -> return Nothing
        Just (left, right) -> do
          leftContains <- foldDS (\fnd cur -> return $ fnd || cur == cur_val) False left
          if leftContains
            then do
              removed_left <- deleteDS cur_val left
              return $ Just (removed_left, right)
          else do
            rightContains <- containsDS right cur_val
            if rightContains
              then do
                removed_right <- deleteDS cur_val right
                return $ Just (left, removed_right)
              else
                return Nothing

containsDS :: (Monad m, Dataspace m ds Value) => ds -> Value -> m Bool
containsDS ds val =
  foldDS (\fnd cur -> if cur == val then return True else return fnd) False ds

callTest testFunc = do
  engine <- simulationEngine [] syntaxValueWD
  interpResult <- runInterpretation engine emptyState (testFunc ())
  success <- either (const $ return False) (either (const $ return False) (return . id) . getResultVal) interpResult
  unless success (assertFailure "Dataspace test failed")

makeTestGroup :: (Dataspace Interpretation dataspace Value) => String -> dataspace -> Test
makeTestGroup name ds =
  testGroup name [
        testCase "EmptyPeek" $ callTest $ emptyPeek ds,
        testCase "Fold on Empty List Test" $ callTest $ testEmptyFold ds,
        testCase "Peek Test" $ callTest $ testPeek ds,
        testCase "Insert Test" $ callTest $ testInsert ds,
        testCase "Delete Test" $ callTest $ testDelete ds,
        testCase "Delete of missing element Test" $ callTest $ testMissingDelete ds,
        testCase "Update Test" $ callTest $ testUpdate ds,
        testCase "Update Multiple Test" $ callTest $ testUpdateMultiple ds,
        testCase "Update missing element Test" $ callTest $ testUpdateMissing ds,
        testCase "Fold Test" $ callTest $ testFold ds,
        testCase "Map Test" $ callTest $ testMap ds,
        testCase "Combine Test" $ callTest $ testCombine ds,
        testCase "Split Test" $ callTest $ testSplit ds
    ]

tests :: [Test]
tests = [
    makeTestGroup "List Dataspace" ([] :: (Dataspace Interpretation [Value] Value) => [Value]),
    makeTestGroup "File Dataspace" (FileDataspace "tmp" :: FileDataspace Value)
  ]
