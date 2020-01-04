/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Mirror helper
 * */
template<typename T>
void BinaryTree<T>::mirror(Node * subRoot) {
    if (subRoot == NULL) {
        return;
    }
    Node * tmp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = tmp;
    mirror(subRoot->left);
    mirror(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> * traversal = new InorderTraversal<T>(root);
    typename TreeTraversal<T>::Iterator iter = traversal->begin();
    BinaryTree<T>::Node * prev = *iter;
    ++iter;
    for (; iter != traversal->end(); ++iter) {
        if (prev->elem > (*iter)->elem) {
            return false;
        }
        prev = *iter;
    }
    return true;
}

// Helper function 1 mostRight, return the mostRight node in the left subtree
template<typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::mostRight(BinaryTree<T>::Node * subRoot) const {
    if (subRoot == NULL) {
        return NULL;
    }

    if (subRoot->right == NULL) {
        return subRoot;
    }

    return subRoot->right;
}

// Helper function 2 mostLeft, return the mostLeft node in the right subtree
template<typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::mostLeft(BinaryTree<T>::Node * subRoot) const {
    if (subRoot == NULL) {
        return NULL;
    }

    if (subRoot->left == NULL) {
        return subRoot;
    }

    return subRoot->left;
}

// Helper function 3 
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const BinaryTree<T>::Node * subRoot) const
{
    // your code here
    if (subRoot == NULL) {
        return true;
    }

    BinaryTree<T>::Node * mostRight = BinaryTree<T>::mostRight(subRoot->left);
    BinaryTree<T>::Node * mostLeft = BinaryTree<T>::mostLeft(subRoot->right);
    if (mostRight != NULL && mostRight->elem > subRoot->elem) {
        return false;
    }

    if (mostLeft != NULL && mostLeft->elem < subRoot->elem) {
        return false;
    }

    return isOrderedRecursive(subRoot->left) && isOrderedRecursive(subRoot->right);
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{

    // your code here
    paths.resize(1);
    getPaths(paths, root, height(root));
    // for (unsigned i = 0; i < paths.size(); i++) {
    //     for (unsigned j = 0; j < paths[i].size(); j++) {
    //         std::cout << paths[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

// Helper function getPath
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths, const BinaryTree<T>::Node * subRoot, int h) const {

    if (subRoot == NULL) {
        return;
    }

    paths.back().push_back(subRoot->elem);
    getPaths(paths, subRoot->left, h);
    
    
    if (subRoot->right != NULL) {
        //std::vector<T>::const_iterator start = paths.back().begin();
        //std::vector<T>::const_iterator end = paths.back().begin() + height(subRoot) + 1;
        if (subRoot->left != NULL) {
            std::vector<T> newPath(paths.back().begin(), paths.back().begin() + (h - height(subRoot)) + 1);
            paths.push_back(newPath);
        }
    }

    getPaths(paths, subRoot->right, h);
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistances(root, 0, height(root));
}

// helper
template <typename T>
int BinaryTree<T>::sumDistances(BinaryTree<T>::Node * subRoot, int sum, int h) const {
    if (subRoot == NULL) {
        return 0;
    }

    sum += (h - height(subRoot));
    // sumDistances(subRoot->left, sum, h);
    // sumDistances(subRoot->right, sum, h);
    // return sum;
    return sum + sumDistances(subRoot->left, 0, h) + sumDistances(subRoot->right, 0, h);
}