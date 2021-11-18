#include "PriorityList.hpp"

PriorityList::~PriorityList() {
    auto p = head;
    while (p) {
        auto tmp = p;
        p = p->next;
        delete tmp;
    }
}

PriorityList::PriorityList(const PriorityList& b) {
    head->next = tail; tail->prev = head;
    size = b.size;
    Node* p = b.head->next;
    while (p != b.tail) {
        insert(p->data);
        p = p->next;
    }
}

void PriorityList::insert(Guest& x) {
    ++size;
    Node* p = head;
    while (p->next != tail && p->next->data < x) p = p->next;
    if (p->next == tail) {
        p->next = new Node(x);
        p->next->prev = p;
        tail->prev = p->next;
        p->next->next = tail;
    }
    else {
        Node* tmp = new Node(x);
        tmp->next = p->next;
        tmp->prev = p;
        p->next->prev = tmp;
        p->next = tmp;
    }
}

PriorityList::Node* PriorityList::find(const Guest& x) const {
    if (is_empty()) return nullptr;
    Node* p = head->next;
    while (p->next != tail && p->data != x) p = p->next;
    if (p->data == x) return p;
	return nullptr;
}

void PriorityList::remove(Node* x) {
    if (!x) return;
    if (x == head || x == tail) return;
    else {
        --size;
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete x;
    }
}

void PriorityList::remove(const Guest& x) {
    --size;
    Node* p = find(x);
    remove(p);
}

void PriorityList::remove_all(const Guest &x) {
    Node* p;
    while ((p = find(x))) {
        --size;
        remove(p);
    }
}

bool PriorityList::is_empty() const {
    return size == 0;
}
