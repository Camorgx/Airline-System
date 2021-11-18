#include "QueueList.hpp"
#include <cstring>
using namespace std;

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
