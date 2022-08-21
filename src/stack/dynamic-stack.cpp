
#include "dynamic-stack.h"
#include <string>
#include <iostream>
const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -99999;

using namespace std;

DynamicStack::DynamicStack() {
    items_ = new StackItem[16];
    capacity_ = 16;
    size_ = 0;
    init_capacity_ = 16;
}

DynamicStack::DynamicStack(unsigned int capacity) {
    items_ = new StackItem[capacity];
    capacity_ = capacity;
    size_ = 0;
    init_capacity_ = capacity;
}

DynamicStack::~DynamicStack() {
    delete []items_;
    items_ = NULL;
}

bool DynamicStack::empty() const {
    if (size_ == 0){
        return true;
    }
    else {
        return false;
    }
}

int DynamicStack::size() const {
    return size_;
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_) {
        capacity_ *= 2;
    }
    items_[size_] = value;
    size_ += 1;
}

DynamicStack::StackItem DynamicStack::pop() {
    if (empty()) {
        return EMPTY_STACK;
    }
    StackItem return_value = items_[size_-1];
    items_[size_-1] = NULL;
    size_ -= 1;
    if(size_ <= capacity_ / 4){
        if(capacity_ / 2 < init_capacity_){
            ;
        }
        else {
            capacity_ /= 2;
        }
    }
    return return_value;
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size_ == 0){
        return EMPTY_STACK;
    }
    else {
        return items_[size_-1];
    }

}

void DynamicStack::print() const {
    for (int i = 0; i < size_; i++) {
        cout << to_string(items_[i]) << endl;
    }
}