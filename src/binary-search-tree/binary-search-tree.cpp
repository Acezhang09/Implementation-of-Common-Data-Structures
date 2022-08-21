#include "binary-search-tree.h"
#include <string>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if(n == nullptr)
        return -1;
    else {
        return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
    }
}

BinarySearchTree::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    if (root_ == nullptr){}
    else {
        queue<Node *> Q;
        Q.push(root_);
        Node *toDelete = nullptr;
        while (!Q.empty()) {
            toDelete = Q.front();
            Q.pop();
            if (toDelete->left != nullptr) {
                Q.push(toDelete->left);
            }
            if (toDelete->right != nullptr) {
                Q.push(toDelete->right);
            }
            delete toDelete;
        }
        root_ = nullptr;
    }
}

unsigned int BinarySearchTree::size() const
{
    unsigned int size = 0;
    if (root_ == nullptr){
        return 0;
    }
    else {
        size = 1;
    }
    queue<Node*> Q;
    Q.push(root_);
    while (!Q.empty()){
        int levelNodeCount = int(Q.size());
        for (int i = levelNodeCount; i > 0; i--){
            Node *temp = Q.front();
            Q.pop();
            if (temp->left != nullptr){
                Q.push(temp->left);
            }
            if (temp->right != nullptr){
                Q.push(temp->right);
            }
        }
        size += int(Q.size());
    }
    return size;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
    Node* current = root_;
    while (current->right != nullptr) {
        current = current-> right;
    }
    return current->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const
{
    Node* current = root_;
    while (current->left != nullptr) {
        current = current-> left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const
{
    if (root_ == nullptr){
        return 0;
    }
    queue<Node*> Q;
    unsigned int depth_count = 0;
    Q.push(root_);
    while (!Q.empty()){
        depth_count += 1;
        int levelNodeCount = int(Q.size());
        for (int i = levelNodeCount; i > 0; i--){
            Node *temp = Q.front();
            Q.pop();
            if (temp->left != nullptr){
                Q.push(temp->left);
            }
            if (temp->right != nullptr){
                Q.push(temp->right);
            }
        }
    }
    return depth_count - 1;
}

void BinarySearchTree::print() const
{
    if (root_ == nullptr){
        cout << "Tree is empty" << endl;
        return;
    }
    queue<Node*> Q;
    Q.push(root_);
    while(!Q.empty()){
        Node *temp = Q.front();
        Q.pop();
        cout << int(temp->val) << ",";
        if (temp->left != nullptr){
            Q.push(temp->left);
        }
        if (temp->right != nullptr){
            Q.push(temp->right);
        }
    }
    cout << endl;
}

bool BinarySearchTree::exists(DataType val) const
{
    Node* current = root_;
    while (current != nullptr){
        if (current->val == val){
            return true;
        }
        else if (current->val > val){
            current = current->left;
        }
        else if (current->val < val){
            current = current->right;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    Node* NewNode = new Node(val);
    Node* current = root_;
    Node* prev = nullptr;
    while (current != nullptr){
        prev = current;
        if (val < current->val){
            current = current->left;
        }
        else if (val > current->val){
            current = current->right;
        }
    }
    if (prev == nullptr){
        root_ = NewNode;
        size_+=1;
        updateNodeBalance(root_);
        return true;
    }
    else if (val < prev->val){
        prev->left = NewNode;
        size_+=1;
        updateNodeBalance(root_);
        return true;
    }
    else if (val > prev->val){
        prev->right = NewNode;
        size_+=1;
        updateNodeBalance(root_);
        return true;
    }
    else {
        return false;
    }
}

bool BinarySearchTree::remove(DataType val)
{
    Node* current = root_;
    Node* prev = nullptr;
    bool val_exists = false;
    bool isLeftChild = false;
    while (current != nullptr){
        if (current->val == val){
            val_exists = true;
            break;
        }
        else if (current->val > val){
            prev = current;
            current = current->left;
            isLeftChild = true;
        }
        else if (current->val < val){
            prev = current;
            current = current->right;
            isLeftChild = false;
        }
    }
    if (!val_exists){
        return false;
    }

    // CASE 1
    if (current->left == nullptr && current->right == nullptr){
        if (current == root_){
            delete root_;
            root_ = nullptr;
            size_--;
            return true;
        }
        else{
            delete current;
            current = nullptr;
            if (isLeftChild){
                prev->left = nullptr;
            }
            else {
                prev->right = nullptr;
            }
            size_--;
            return true;
        }
    }

    // CASE 2
    if (current->left != nullptr && current->right == nullptr){
        if (isLeftChild){
            prev->left = current->left;
        }
        else {
            prev->right = current->left;
        }
        delete current;
        size_--;
        return true;
    }
    else if (current->left == nullptr && current->right != nullptr){
        if (isLeftChild){
            prev->left = current->right;
        }
        else {
            prev->right = current->right;
        }
        delete current;
        size_--;
        return true;
    }

    // CASE 3
    if (current->left != nullptr && current->right != nullptr) {
        Node* predecessor = current->left;
        bool isRightChild = false;
        Node* predecessor_prev = nullptr;
        if (predecessor->right == nullptr){
            predecessor_prev = current;
        }
        while (predecessor->right != nullptr){
            predecessor_prev = predecessor;
            predecessor = predecessor->right;
            isRightChild = true;
        }
        current->val = predecessor->val;
        if (predecessor->left == nullptr){
            if (isRightChild){
                predecessor_prev->right = nullptr;
            }
            else {
                predecessor_prev->left = nullptr;
            }
        }
        else {
            if (isRightChild){
                predecessor_prev->right = predecessor->left;
            }
            else {
                predecessor_prev->left = predecessor->left;
            }
        }
        delete predecessor;
        size_--;
        return true;
    }
}

void BinarySearchTree::updateNodeBalance(Node *n) {
    if(n == nullptr)
        return;
    n->avlBalance = getNodeDepth(n->left)-getNodeDepth(n->right);
    updateNodeBalance(n->left);
    updateNodeBalance(n->right);
}