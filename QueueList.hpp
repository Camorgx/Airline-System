#ifndef Queue_hpp
#define Queue_hpp

#include "PriorityList.hpp"
#include <stdexcept>

class QueueException : public std::runtime_error {
public:
    explicit QueueException(const std::string& information) : runtime_error(information) {}
    const char* what() const noexcept override { return runtime_error::what(); }
};

class QueueList : public PriorityList {
public:
    QueueList() : PriorityList() {}
    QueueList(const QueueList& b) : PriorityList(b) {}
    QueueList(QueueList&& b) noexcept : PriorityList(b) {}
    ~QueueList() = default;
    Guest& front();
    Guest& back();
    void push(const Guest& x);
    void pop();
    QueueList& operator=(const QueueList& b) = default;
};

#endif /* Queue_hpp */
