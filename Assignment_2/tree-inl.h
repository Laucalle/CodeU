#include "tree.h"

#include <queue>
#include <stdexcept>

template <class T>
TBinaryTree<T>::TBinaryTree(const T& key, unsigned depth, TBinaryTree<T>* left, TBinaryTree<T>* right)
    : Key(key)
    , Depth(depth)
    , Left(left)
    , Right(right)
{
    if (Left) {
        if (Left->Parent)
            throw std::invalid_argument("The tree given by left child pointer is already a subtree of some another tree.");
        Left->Parent = this;
    }
    if(Right) {
        if (Right->Parent)
            throw std::invalid_argument("The tree given by right child pointer is already a subtree of some another tree.");
        Right->Parent = this;
    }
}

template <class T>
TBinaryTree<T>::TBinaryTree(const T& key, TBinaryTree<T>* left, TBinaryTree<T>* right)
    : TBinaryTree(key, 0, left, right)
{
    if (Left)
        Left->ComputeDepths(1);
    if(Right)
        Right->ComputeDepths(1);
}

template <class T>
T TBinaryTree<T>::GetKey() {
    return Key;
}

template <class T>
unsigned TBinaryTree<T>::GetDepth() {
    return Depth;
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::GetLeft() {
    return Left;
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::GetRight() {
    return Right;
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::BuildFullBinaryTree(const std::vector<T>& values) {
    // Tree cannot be empty.
    if (values.size() < 1)
        throw std::invalid_argument("Vector should have at least one item.");

    return new TBinaryTree(values[0], 0, BuildTree(values, 1, 1), BuildTree(values, 2, 1));
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::BuildTree(const std::vector<T>& values, int idxRoot, unsigned depth) {
    // Leaf nodes have nullptrs children.
    if (idxRoot >= values.size())
        return nullptr;

    int idxLeft = 2 * idxRoot + 1;
    int idxRight = idxLeft + 1;
    return new TBinaryTree(values[idxRoot], depth, BuildTree(values, idxLeft, depth + 1),
                           BuildTree(values, idxRight, depth + 1));
}

template <class T>
void TBinaryTree<T>::Print(std::ostream &out, std::string levelGap) {
    if (!Parent)
        out << "Root ";
    else
        out << levelGap << Parent->Key << " -> ";
    out << Key << "(" << Depth << ")" << std::endl;

    if (Left)
        Left->Print(out, levelGap + levelGap);
    if (Right)
        Right->Print(out, levelGap + levelGap);
}

template <class T>
TBinaryTree<T>::~TBinaryTree() {
    if (Left)
        delete Left;
    if(Right)
        delete Right;
}

template <class T>
void TBinaryTree<T>::ComputeDepths(unsigned depth) {
    Depth = depth;
    if (Left)
        Left->ComputeDepths(depth + 1);
    if (Right)
        Right->ComputeDepths(depth + 1);
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::SetLeft(TBinaryTree<T>* left) {
    if (left && left->Parent)
        throw std::invalid_argument("The tree given by left child pointer is already a subtree of some another tree.");

    if (Left)
        delete Left;

    if (left) {
        Left = left;
        Left->Parent = this;
        Left->ComputeDepths(Depth + 1);
    } else {
        Left = nullptr;
    }

    return this;
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::SetRight(TBinaryTree<T>* right) {
    if (right && right->Parent)
        throw std::invalid_argument("The tree given by right child pointer is already a subtree of some another tree.");

    if (Right)
        delete Right;

    if (right) {
        Right = right;
        Right->Parent = this;
        Right->ComputeDepths(Depth + 1);
    } else {
        Right = nullptr;
    }

    return this;
}

template <class T>
bool TBinaryTree<T>::PrintAncestors(const T &key, std::ostream &out) {
    // Firsly we find a node with the given tree
    TBinaryTree* node = FindKey(key);
    // after we just go from the node to root by Parent links
    if (node) {
        out << "All ancestors of the node " << key << ":";
        node = node->Parent;
        while (node) {
            out << " " << node->Key;
            node = node->Parent;
        }
        out << std::endl;

        return true;
    }

    return false;
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::FindKey(const T& key) {
    if (Key == key)
        return this;

    for (const auto& child : {Left, Right}) {
        if (child) {
            TBinaryTree* inChild = child->FindKey(key);
            if (inChild)
                return inChild;
        }
    }
    return nullptr;
}

template <class T>
TBinaryTree<T>* TBinaryTree<T>::LeastCommonAncestor(TBinaryTree<T>* first, TBinaryTree<T>* second) {
    // Validate arguments
    if (!first || !second)
        throw std::invalid_argument("Expected pointers for subtrees but nullptrs were given.");

    // The idea is to go from bottom to up by both first and second pointers.
    // So firsly we should put pointers for the same depth in the tree because
    // in another way we cannot move both of them.
    // After we move them while they are not equal.
    unsigned commonDepth = std::min(first->Depth, second->Depth);
    while (first->Depth > commonDepth)
        first = first->Parent;
    while (second->Depth > commonDepth)
        second = second->Parent;

    while (first != second) {
        first = first->Parent;
        second = second->Parent;
    }

    // Since they start from the same level in the tree, they reach the root
    // in the same time. If they are from different trees, each of them skips
    // the root node and will be set in nullptr.
    if (!first)
        throw std::invalid_argument("Given nodes are from different trees.");
    return first;
}
