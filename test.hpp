#ifndef test_h
#define test_h

#include "QueueList.hpp"
#include <iostream>

void TestQueueList() {
    QueueList q;
    q.push(Guest("1")); std::cout << q.back().name << std::endl;
    q.push(Guest("2")); std::cout << q.back().name << std::endl;
    q.push(Guest("3")); std::cout << q.back().name << std::endl;
    q.push(Guest("4")); std::cout << q.back().name << std::endl;
    q.push(Guest("5")); std::cout << q.back().name << std::endl;
    q.push(Guest("6")); std::cout << q.back().name << std::endl;
    QueueList qq(q);
    std::cout << qq.back().name <<std::endl;
    for (int i = 0; i < 6; ++i) {
        std::cout << q.front().name << ' ' << q.size << std::endl;
        q.pop();
    }
    try {
        q.pop();
    }
    catch (const QueueListException& e)  {
        std::cout << "Fine\n" << e.what() << std::endl;
    }
    try {
        auto i = q.front();
    }
    catch (const QueueListException& e) {
        std::cout << "Fine\n" << e.what() << std::endl;
    }
    try {
        auto i = q.back();
    }
    catch (const QueueListException& e) {
        std::cout << "Fine\n" << e.what() << std::endl;
    }
}

#include <vector>
#include "PriorityList.hpp"

void TestPriorityList() {
    std::vector<Guest> v = {Guest("0"), Guest("1"), Guest("2"), Guest("3")};
    PriorityList a;

    a.insert(v[3]);
    PriorityList::Node* p = a.head->next;
    while(p != a.tail) {
        std::cout << p->data.name << std::endl;
        p = p->next;
    }
    std::cout << std::endl;

    a.insert(v[1]);
    p = a.head->next;
    while(p != a.tail) {
        std::cout << p->data.name << std::endl;
        p = p->next;
    }
    std::cout << std::endl;

    a.insert(v[3]);
    p = a.head->next;
    while(p!= a.tail) {
        std::cout << p->data.name << std::endl;
        p = p->next;
    }
    std::cout << std::endl;

    a.remove_all(v[3]);
    p = a.head->next;
    while(p != a.tail) {
        std::cout << p->data.name << std::endl;
        p = p->next;
    }
    std::cout << std::endl;

    PriorityList b(a);
    p = b.head->next;
    while (p != b.tail) {
        std::cout << p->data.name << std::endl;
        p = p->next;
    }
    std::cout << std::endl;
}

#include "Vector.hpp"

void TestVector() {
    Vector<int> vec = {1, 2, 3, 4, 45, 6};
    for (const auto& i : vec) std::cout << i << ' ';
    std::cout << std::endl;
    vec.push_back(19);
    std::cout << vec.size() << std::endl;
    for (const auto& i : vec) std::cout << i << ' ';
    std::cout << std::endl;
    for (const auto& i : vec) std::cout << i << ' ';
    std::cout << std::endl;
    for(unsigned i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << ' ';
    std::cout << std::endl;
    auto vec_copy_construct(vec);
    vec.pop_back();
    vec.pop_back();
    auto vec_move_construct(std::move(vec));
    Vector<int> vec_copy_equal, vec_move_equal;
    vec_copy_equal = vec_copy_construct;
    vec_move_equal = move(vec_copy_construct);
    for (const auto& i : vec) std::cout << i << ' ';
    std::cout << std::endl;
    for (const auto& i : vec_move_construct) std::cout << i << ' ';
    std::cout << std::endl;
    for (const auto& i : vec_copy_equal) std::cout << i << ' ';
    std::cout << std::endl;
    for (const auto& i : vec_move_equal) std::cout << i << ' ';
    std::cout << std::endl;
    std::cout << (vec_copy_equal == vec_move_construct) << std::endl;
    std::cout << (vec_move_equal == vec_copy_equal) << std::endl;
}

#endif /* test_h */
