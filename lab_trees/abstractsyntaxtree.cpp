#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(this->getRoot());
}

// Helper function
double AbstractSyntaxTree::eval(typename BinaryTree<std::string>::Node * subRoot) const {
    
    if (subRoot == NULL) return 0;
    
    std::string curr = subRoot->elem;
    if (curr.compare("+") == 0) return eval(subRoot->left) + eval(subRoot->right);
    if (curr.compare("-") == 0) return eval(subRoot->left) - eval(subRoot->right);
    if (curr.compare("*") == 0) return eval(subRoot->left) * eval(subRoot->right);
    if (curr.compare("/") == 0) return eval(subRoot->left) / eval(subRoot->right);
    return (double) std::stod(curr);
}