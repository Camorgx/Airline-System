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

//data[head + 1]指向队列中的第一个元素, data[tail - 1]指向队列中的最后一个元素。
class Queue {
    Guest* data = new Guest[5];
    unsigned head = 0, tail = 1;  
    //数组的实际大小
    unsigned size = 5;
public:
    Queue() {}
    Queue(const Queue& b);
    ~Queue() { delete[] data; }
    Guest& front();
    Guest& back();
    void push(const Guest& x);
    void pop();
    const bool is_full();
    const bool isempty();
    const size_t length();
};

#endif /* Queue_hpp */
