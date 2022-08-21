#ifndef A3_AVL_TREE_H
#define A3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree: public BinarySearchTree
{
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    //The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    // Pointer to the root node of the tree.
    Node* root_;
    Node* unbalancedAncestor;

    // Number of nodes in the tree.
    unsigned int size_;
    int height(Node* root);


    int heightDifference(Node* root);

    static void rotate_left(Node* n);
    static void rotate_right(Node* n);
    void left_right(Node* n);
    void right_left(Node* n);
    void check_for_unbalanced(Node* n);
};

#endif //SYDE223_A3_AVL_TREE_H
