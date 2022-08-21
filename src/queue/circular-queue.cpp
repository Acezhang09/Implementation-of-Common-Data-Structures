#include "circular-queue.h"
#include <string>
#include <iostream>
using namespace std;
const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -99999;


CircularQueue::CircularQueue() {
    items_ = new QueueItem[16];
    head_ = 0;
    tail_ = 0;
    capacity_ = 16;
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    items_ = new QueueItem[capacity];
    head_ = 0;
    tail_ = 0;
    capacity_ = capacity;
    size_ = 0;
}

CircularQueue::~CircularQueue() {
    delete []items_;
    items_ = NULL;
}

bool CircularQueue::empty() const {
    if (size_ == 0){
        return true;
    }
    else {
        return false;
    }
}

bool CircularQueue::full() const {
    if (size_ == capacity_){
        return true;
    }
    else{
        return false;
    }
}

int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    if (size_ == capacity_){
        return false;
    }
    else {
        items_[tail_] = value;
        tail_ += 1;
        if (tail_ >= capacity_) {
            tail_ = 0;
        }
        size_ += 1;
        return true;
    }

}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if (size_ == 0){
        return EMPTY_QUEUE;
    }
    else{
        QueueItem return_value = items_[head_];
        items_[head_] = NULL;
        head_ += 1;
        if(head_ >= capacity_){
            head_ = 0;
        }
        size_ -= 1;
        return return_value;
    }
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0){
        return EMPTY_QUEUE;
    }
    else{
        return items_[head_];
    }
}

void CircularQueue::print() const {
    for (int i = 0; i < size_; i++) {
        cout << to_string(items_[i]) << endl;
    }
}

