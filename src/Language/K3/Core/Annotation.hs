{-# LANGUAGE DeriveDataTypeable #-}
{-# LANGUAGE DeriveGeneric #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE TypeOperators #-}

-- | The K3 Annotation System.
module Language.K3.Core.Annotation (
    -- * Basic Infrastructure
    Annotation,
    AContainer(..),
    AConstruct(..),

    -- * K3 Instantiations
    (:@:)(..),
    K3,

    children,
    replaceCh,
    replaceTag,
    replaceAnnos,
    stripAnno,
    details,
    tna,
    tnc
) where

import Control.Arrow ( (&&&) )
import Control.DeepSeq

import Data.List (delete, find)
import Data.Tree
import Data.Typeable

import GHC.Generics (Generic)

-- | Every tag type defines the set of annotations that can be associated with that tag.
data family Annotation t :: *

-- | An annotation container is a generic container which supports a standard set of operations that
-- one might want to perform on a set of annotations. There is, however, nothing annotation-specific
-- about the container's interface.
class AContainer c where
    -- | The sub-component of an annotated value that is actually annotatable.
    type IElement c :: *

    -- | The annotation addition operator. Adds the given annotation to an annotated value.
    (@+) :: Eq (IElement c) => c -> IElement c -> c

    -- | The annotation subtraction operator. Removes the given annotation from an annotated value.
    (@-) :: Eq (IElement c) => c -> IElement c -> c

    -- | The annotation matching operator. Returns the first annotation satisfying the given
    -- predicate.
    (@~) :: c -> (IElement c -> Bool) -> Maybe (IElement c)

infixl 3 @+
infixl 3 @-

-- | An annotation construct is a data structure where each member contains a tag, and a container
-- of the corresponding tag type's annotations.
class AConstruct c where
    -- | The type of the tag.
    type ITag c :: *

    -- | The type of the container.
    type IContainer c :: *

    -- | Retrieve the tag from the construct.
    tag :: c -> ITag c

    -- | Retrieve the annotation container from the construct.
    annotations :: c -> IContainer c

    -- | Replace the annotation container within the construct.
    (@<-) :: c -> IContainer c -> c

-- | A maybe-type is a container of a single annotation.
instance AContainer (Maybe a) where
    type IElement (Maybe a) = a

    -- | Adding an annotation replaces the existing annotation, if there was one.
    _ @+ v' = Just v'

    -- | Removing an annotation only occurs if the exact annotation was already present.
    Just v @- v'
        | v == v' = Nothing
        | otherwise = Just v
    Nothing @- _ = Nothing

    -- | Matching an annotation only occurs if there was an annotation to begin with.
    Just v @~ p
        | p v = Just v
        | otherwise = Nothing
    Nothing @~ _ = Nothing

-- | A list is a container of annotations, quite trivially.
instance AContainer [a] where
    type IElement [a] = a

    vs @+ v = vs++[v]
    vs @- v = delete v vs
    vs @~ p = find p vs

-- | A tree can act as a proxy to the container at its root.
instance AContainer a => AContainer (Tree a) where
    type IElement (Tree a) = IElement a

    Node a cs @+ v = Node (a @+ v) cs
    Node a cs @- v = Node (a @- v) cs
    Node a _ @~ f = a @~ f

-- | A convenience form for attachment, structurally equivalent to tupling.
data a :@: b = a :@: b deriving (Eq, Ord, Read, Show, Typeable, Generic)

instance (NFData a, NFData b) => NFData (a :@: b)

-- | A pair can act as a proxy to the container it contains as its second element.
instance AContainer a => AContainer (b :@: a) where
    type IElement (b :@: a) = IElement a

    (b :@: a) @+ v = b :@: (a @+ v)
    (b :@: a) @- v = b :@: (a @- v)
    (_ :@: a) @~ f = a @~ f

-- | A pair can also act as a construct, where the first element is the tag.
instance AConstruct (b :@: a) where
    type ITag (b :@: a) = b
    type IContainer (b :@: a) = a

    tag (b :@: _) = b

    annotations (_ :@: a) = a

    (b :@: _) @<- a' = b :@: a'

-- | A tree can act as a proxy to the construct at its root.
instance AConstruct a => AConstruct (Tree a) where
    type ITag (Tree a) = ITag a
    type IContainer (Tree a) = IContainer a

    tag (Node a _) = tag a

    annotations (Node a _) = annotations a

    (Node a cs) @<- a' = Node (a @<- a') cs

-- | A K3 source tree contains a tag, along with a list of annotations defined for trees with that
-- tag.
type K3 a = Tree (a :@: [Annotation a])

{- Tree utilities -}

instance (Ord a, Eq (Annotation a), Ord (Annotation a)) => Ord (K3 a) where
  compare a b = compare (flatten a) (flatten b)

-- | Subtree extraction
children :: Tree a -> Forest a
children = subForest

-- | Replace children
replaceCh :: Tree a -> Forest a -> Tree a
replaceCh (Node x _) ch = Node x ch

-- | Replace node type
replaceTag :: K3 a -> a -> K3 a
replaceTag (Node (_ :@: anns) ch) tg = Node (tg :@: anns) ch

replaceAnnos :: K3 a -> [Annotation a] -> K3 a
replaceAnnos (Node (n :@: _) ch) as = Node (n :@: as) ch

-- | Remove all annotations of a certain kind
stripAnno :: (Annotation a -> Bool) -> K3 a -> K3 a
stripAnno f n@(Node (_ :@: as) _) = replaceAnnos n $ filter (not . f) as

-- | Get all elements: tag, children, annotations
details :: K3 a -> (a, [K3 a], [Annotation a])
details (Node (tg :@: anns) ch) = (tg, ch, anns)

tna :: K3 a -> (a, [Annotation a])
tna = tag &&& annotations

tnc :: K3 a -> (a, [K3 a])
tnc = tag &&& children
