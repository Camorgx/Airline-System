#include "QueueList.hpp"
#include <cstring>
using namespace std;

QueueList::QueueList(const QueueList& b) noexcept {
    head->next = tail; tail->prev = head;
    size = b.size;
    Node* p = b.head->next;
    while (p != b.tail) {
        push(p->data);
        p = p->next;
    }
}

QueueList::~QueueList() {
    auto p = head;
    while (p) {
        auto tmp = p;
        p = p->next;
        delete tmp;
    }
}

Guest& QueueList::front() {
    return head->next->data;
}

Guest& QueueList::back() {
    return tail->prev->data;
}

void QueueList::push(const Guest& x) {
    Node* tmp = new Node(x);
    tail->prev->next = tmp;
    tmp->prev = tail->prev;
    tmp->next = tail;
    tail->prev = tmp;
    ++size;
}

void QueueList::pop() {
    if (is_empty()) throw QueueException("The QueueList has already been empty");
    auto tmp = tail->prev;
    tmp->prev->next = tail;
    tail->prev = tmp->prev;
    delete tmp;
    --size;
}

bool QueueList::is_empty() const {
    return size == 0;
}

size_t QueueList::length() {
    return size;
}

QueueList::Node* QueueList::find(const Guest& x) const {
    if (is_empty()) return nullptr;
    Node* p = head->next;
    while (p->next != tail && p->data != x) p = p->next;
    if (p->data == x) return p;
    return nullptr;
}

void QueueList::remove(QueueList::Node* x) {
    if (!x) return;
    if (x == head || x == tail) return;
    else {
        --size;
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete x;
    }
}

void QueueList::remove(const Guest& x) {
    --size;
    Node* p = find(x);
    remove(p);
}
