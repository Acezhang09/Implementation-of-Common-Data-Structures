#include "avl-tree.h";
#include <iostream>
#include <algorithm>
using namespace std;

void AVLTree::rotate_left(Node *n) {
    Node* temp = new Node(n->val);

    temp->left = n->left;
    temp->right = n->right->left;

    n->val = n->right->val;
    n->left = temp;
    n->right = n->right->right;

}

void AVLTree::rotate_right(Node *n) {
    Node* temp = new Node(n->val);

    temp->right = n->right;
    temp->left = n->left->right;

    n->val = n->left->val;
    n->right = temp;


    n->left = n->left->left;

}

void AVLTree::left_right(Node *n) {
    rotate_left(n->left);
    rotate_right(n);

}

void AVLTree::right_left(Node *n) {
    rotate_right(n->right);
    rotate_left(n);

}
int AVLTree::height(Node *n) {
    int node_height = 0;
    if (n != nullptr) {
        int height_left_child = height(n->left);
        int height_right_child = height(n->right);
        int max_height = std::max(height_left_child, height_right_child);
        node_height = max_height + 1;

    }
    return node_height;
}


int AVLTree::heightDifference(Node *n) {
    int height_left_child = height(n->left);
    int height_right_child = height(n->right);
    int heightDiff = height_left_child - height_right_child;
    return heightDiff;
}


void AVLTree::check_for_unbalanced(Node* n)
{
    if(n == nullptr){
        return;
    }

    else if(n->avlBalance < -1 || n->avlBalance > 1) {
        unbalancedAncestor = n;
    }

    check_for_unbalanced(n->left);
    check_for_unbalanced(n->right);
}

bool AVLTree::insert(DataType val)
{
    if(BinarySearchTree::insert(val) == false) {
        return false;
    }

    unbalancedAncestor = nullptr;
    check_for_unbalanced(getRootNode());
    if(unbalancedAncestor == nullptr){
        return true;
    }


    if(unbalancedAncestor->right != nullptr && unbalancedAncestor->right->right != unbalancedAncestor && unbalancedAncestor->right->right != nullptr) {
        rotate_left(unbalancedAncestor);
        return true;
    }

    else if(unbalancedAncestor->left != nullptr && unbalancedAncestor->left->left != nullptr && unbalancedAncestor->left->left != nullptr){
        rotate_right(unbalancedAncestor);
        return true;

    }
    else if(unbalancedAncestor->left != nullptr && unbalancedAncestor->left->right != nullptr && unbalancedAncestor->left->right != nullptr){
        left_right(unbalancedAncestor);
        return true;
    }


    else if(unbalancedAncestor->right != nullptr && unbalancedAncestor->right->left != nullptr && unbalancedAncestor->right->left != nullptr) {
        right_left(unbalancedAncestor);
        return true;

    }
    return false;

}

bool AVLTree::remove(DataType val)
{

}