#ifndef Queue_hpp
#define Queue_hpp

#include "Guest.hpp"
#include <stdexcept>
#include <cstring>
#include <utility>

class QueueException : public std::runtime_error {
public:
    explicit QueueException(const std::string& information) : runtime_error(information) {}
    const char* what() const noexcept override { return runtime_error::what(); }
};

class QueueList {
    struct Node {
        Guest data;
        Node* prev = nullptr, * next = nullptr;
        Node() = default;
        explicit Node(Guest g) { data = std::move(g); }
    };
    size_t size = 0;
public:
    Node* head = new Node(), * tail = new Node();

    QueueList() {
        head->next = tail;
        tail->prev = head;
    }
    QueueList(const QueueList& b) noexcept;
    ~QueueList();
    Guest& front();
    Guest& back();
    void push(const Guest& x);
    void pop();
    bool is_empty() const;
    size_t length();
    Node* find(const Guest& x) const;
    void remove(Node* x);
    void remove(const Guest& x);
};

#endif /* Queue_hpp */
