#include "doubly-linked-list.h"
#include <string>
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* current = head_;
    while(current){
        Node* after = current->next;
        delete current;
        current = after;
    }
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0) {
        return true;
    }
    else{
        return false;
    }
}

bool DoublyLinkedList::full() const
{
    if (size_ >= CAPACITY){
        return true;
    }
    else {
        return false;
    }
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (empty()){
        return DataType(-999);
    }
    if (index < 0 || index >size_){
        return tail_->value;
    }

    int counter = 0;
    Node* current = head_;
    while(current != NULL){
        if (counter == index){
            return current->value;;
        }
        current = current->next;
        counter += 1;
    }
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    int counter = 0;
    Node* current = head_;
    while(current != NULL){
        if (current->value == value) {
            return counter;
        }
        current = current->next;
        counter += 1;
    }
    return size_;
}

void DoublyLinkedList::print() const
{
    Node* current = head_;
    while(current != NULL){
        cout << to_string(current->value) << "\n" << endl;
        current = current->next;
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    if (empty()){
        return NULL;
    }
    else if (index < 0 || index >= size_){
        return NULL;
    }
    Node* current = head_;
    int counter = 0;
    while(current != NULL){
        if (counter == index - 1){
            return current->next;
        }
        current = current->next;
        counter += 1;
    }
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if (size_ == CAPACITY){
        return false;
    }
    else if (index == 0){
        insert_front(value);
        return true;
    }
    else if (index == size_){
        insert_back(value);
        return true;
    }
    else if (index < 0 || index > size_){
        return false;
    }
    else {
        Node *NewNode = new Node(value);
        Node *current = head_;
        int counter = 0;
        while (current != NULL) {
            if (counter == index - 1) {
                Node *AfterNode = current->next;

                current->next = NewNode;
                NewNode->prev = current;

                AfterNode->prev = NewNode;
                NewNode->next = AfterNode;
                size_ += 1;
                return true;
            }
            current = current->next;
            counter += 1;
        }
        return false;
    }
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if(empty()){
        Node* NewNode = new Node(value);
        head_ = NewNode;
        tail_ = NewNode;
        NewNode->next = NULL;
        NewNode->prev = NULL;
        size_ += 1;
        return true;
    }
    else if (size_ == CAPACITY){
        return false;
    }
    else{
        Node *NewNode = new Node(value);
        Node* OldHead = head_;

        OldHead->prev = NewNode;
        NewNode->prev = NULL;
        NewNode->next = OldHead;
        head_ = NewNode;
        size_ += 1;
        return true;
    }

}

bool DoublyLinkedList::insert_back(DataType value)
{
    if(empty()){
        Node* NewNode = new Node(value);
        head_ = NewNode;
        tail_ = NewNode;
        NewNode->next = NULL;
        NewNode->prev = NULL;
        size_ += 1;
        return true;
    }
    else if (size_ == CAPACITY){
        return false;
    }
    else {
        Node *NewNode = new Node(value);
        Node *OldTail = tail_;

        OldTail->next = NewNode;
        NewNode->prev = OldTail;
        NewNode->next = NULL;
        tail_ = NewNode;
        size_ += 1;
        return true;
    }
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (empty()){
        return false;
    }
    if (index == 0){
        remove_front();
        return true;
    }
    else if (index == size_ - 1){
        remove_back();
        return true;
    }
    else if (index < 0 || index >= size_){
        return false;
    }
    else {
        Node *current = head_;
        int counter = 0;
        while (current != NULL) {
            if (counter == index) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                current = NULL;
                size_ -= 1;
                return true;
            }
            current = current->next;
            counter += 1;
        }
    }
    return false;
}

bool DoublyLinkedList::remove_front()
{
    if (empty()){
        return false;
    }
    else if (size_ == 1){
        Node* current = head_;
        head_ = NULL;
        tail_ = NULL;
        delete current;
        current = NULL;
        size_ -= 1;
        return true;
    }
    else {
        Node* current = head_;
        head_ = head_->next;
        head_->prev = NULL;
        delete current;
        current = NULL;
        size_ -= 1;
        return true;
    }
}

bool DoublyLinkedList::remove_back()
{
    if (empty()){
        return false;
    }
    else if (size_ == 1){
        Node* current = tail_;
        head_ = NULL;
        tail_ = NULL;
        delete current;
        current = NULL;
        size_ -= 1;
        return true;
    }
    else{
        Node* current = tail_;
        tail_ = tail_->prev;
        tail_->next = NULL;
        delete current;
        current = NULL;
        size_ -= 1;
        return true;
    }
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (index < 0 || index >= size_){
        return false;
    }
    else {
        Node *current = head_;
        int count = 0;
        while (current != NULL) {
            if (count == index) {
                current->value = value;
                return true;
            }
            current = current->next;
            count += 1;
        }
    }
    return false;
}

