#ifndef Queue_hpp
#define Queue_hpp

#include "Guest.hpp"
#include <stdexcept>
#include <cstring>

class QueueException : public std::runtime_error {
public:
    QueueException(std::string information) : runtime_error(information) {}
    const char* what() const noexcept { return runtime_error::what(); }
};

//data[head + 1] points to the first element in the queue, 
//data[tail - 1] points to the last element in the queue.
class Queue {
    Guest* data = new Guest[5];
    unsigned head = 0, tail = 1;
    unsigned size = 5;
public:
    Queue() = default;
    Queue(const Queue& b);
    Queue& operator=(const Queue& b);
    ~Queue() { delete[] data; }
    Guest& front();
    Guest& back();
    void push(const Guest& x);
    void pop();
    bool is_full();
    bool is_empty() const;
    size_t length();
    Guest* begin();
    Guest* end();
};

#endif /* Queue_hpp */
