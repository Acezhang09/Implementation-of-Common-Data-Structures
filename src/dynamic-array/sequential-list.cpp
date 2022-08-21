#include "sequential-list.h"
#include <string>
#include <iostream>

using namespace std;

SequentialList::SequentialList(unsigned int cap)
{
    data_ = new DataType[cap];
    capacity_ = cap;
    size_ = 0;
}

SequentialList::~SequentialList()
{
    delete []data_;
    data_ = NULL;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if (size_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool SequentialList::full() const
{
    if (size_ == capacity_) {
        return true;
    }
    else {
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (size_ == 0){
        return data_[0];
    }
    else if (index < 0 || index >= size_) {
        return data_[size_-1];
    }
    else {
        return data_[index];
    }

}

unsigned int SequentialList::search(DataType val) const
{
    for(int i = 0; i < size_; i++) {
        if (data_[i] == val) {
            return i;
        }
    }
    return size_;
}

void SequentialList::print() const
{
    for(int i = 0; i < size_; i++) {
        cout << to_string(data_[i]) << "\n";
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (full()) {
        return false;
    }
    for(int i = size_; i > index; i--) {
        data_[i] = data_[i-1];
    }
    data_[index] = val;
    size_ += 1;
    return true;
}

bool SequentialList::insert_front(DataType val)
{
    if (full()) {
        return false;
    }
    for(int i = size_; i > 0; i--) {
        data_[i] = data_[i-1];
    }
    data_[0] = val;
    size_ += 1;
    return true;
}

bool SequentialList::insert_back(DataType val)
{
    if (full()) {
        return false;
    }
    data_[size_] = val;
    size_ += 1;
    return true;
}

bool SequentialList::remove(unsigned int index)
{
    if (empty()) {
        return false;
    }
    for(int i = index; i < size_-index; i++) {
        data_[i] = data_[i+1];
    }
    data_[size_-1] = NULL;
    size_ -= 1;
    return true;
}

bool SequentialList::remove_front()
{
    if (empty()) {
        return false;
    }
    for(int i = 0; i < size_; i++) {
        data_[i] = data_[i+1];
    }
    data_[size_-1] = NULL;
    size_ -= 1;
    return true;
}

bool SequentialList::remove_back()
{
    if (empty()) {
        return false;
    }
    data_[size_-1] = NULL;
    size_ -= 1;
    return true;
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    //TODO: make sure index is in bounds
    if (empty()) {
        return false;
    }
    if (data_[index] == NULL){
        return false;
    }
    else {
        data_[index] = val;
    }
}

