﻿#include "Queue.hpp"
#include <cstring>
using namespace std;

Queue::Queue(const Queue& b) {
    delete[] data;
    data = new Guest[size = b.size];
    head = b.head; tail = b.tail;
    memcpy(data, b.data, size * sizeof(Guest));
}

Guest& Queue::front() {
    if (isempty()) throw QueueException("The Queue has already been empty");
    else if (head == size - 1) return data[0];
    else return data[head + 1];
}

Guest& Queue::back() {
    if (isempty()) throw QueueException("The Queue has already been empty");
    else if (tail == 0) return data[size - 1];
    else return data[tail - 1];
}

void Queue::push(const Guest& x) {
    if (tail == size - 1) {
        if (head == 0) {
            try {
                Guest* tmp = new Guest[2 * size];
                memcpy(tmp, data, size * sizeof(Guest));
                delete[] data;
                data = tmp;
                data[tail++] = x;
                size *= 2;
            }
            catch (std::bad_alloc) {
                throw QueueException("Failed to expand the Queue!");
            }
        }
        else {
            data[tail] = x;
            tail = 0;
        }
    }
    else if (tail == head) {
        try {
            Guest* tmp = new Guest[2 * size];
            memcpy(tmp, data + head, (size - head) * sizeof(Guest));
            memcpy(tmp + size - head, data, tail * sizeof(Guest));
            delete[] data;
            tail = size; head = 0;
            size *= 2; data = tmp;
            data[tail++] = x;
        }
        catch (const std::exception&) {
            throw QueueException("Failed to expand the Queue!");
        }
    }
    else data[tail++] = x;
}

void Queue::pop() {
    if (isempty()) throw QueueException("The Queue has already been empty");
    else if (head == size - 1) head = 0;
    else ++head;
}

const bool Queue::is_full() {
    return head == tail || (head == 0 && tail == size - 1);
}

const bool Queue::isempty() {
    return tail == head + 1 || (tail == 0 && head == size - 1);
}

const size_t Queue::length() {
    if (tail > head) return tail - head - 1;
    else return tail + size - head - 1;
}
