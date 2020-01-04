/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t = tmp;
    // update the height
    t->left->height = 1 + std::max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right));
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * tmp = t->left;
    // if (tmp == NULL) {
    //     std::cout << "tmp is NULL !!" << std::endl;
    // }
    t->left = tmp->right;
    tmp->right = t;
    t = tmp;
    // update the height
    t->right->height = 1 + std::max(heightOrNeg1(t->right->left), heightOrNeg1(t->right->right));
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    // calculate the balance factor
    int b1 = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (std::abs(b1) <= 1) {
        return;
    }
    if (b1 < 0) {
        int b2 = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (b1 - b2 == -1) {
            // rotate right
            rotateRight(subtree);
        } else {
            // rotate left-right
            rotateLeftRight(subtree);
        }
    } else {
        int b2 = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (b1 - b2 == 1) {
            // rotate left
            rotateLeft(subtree);
        } else {
            // rotate right-left
            rotateRightLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    if (key == subtree->key) {
        subtree->value = value;
        return;
    }

    if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else {
        insert(subtree->right, key, value);
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * left = subtree->left;
            // The right most node in the left subtree should be the new subtree
            Node * rightMost = left;
            // Find the in inorder predecessor
            while (rightMost->right != NULL) {
                rightMost = rightMost->right;
            }
            subtree->key = rightMost->key;
            subtree->value = rightMost->value;
            remove(subtree->left, rightMost->key);
        } else {
            /* one-child remove */
            // your code here
            Node * child = (subtree->left == NULL) ? subtree->right : subtree->left;
            delete subtree;
            subtree = child;
        }
        // your code here
    }
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
