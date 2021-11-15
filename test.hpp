//
//  test.hpp
//  航空客运订票系统
//
//  Created by 曹高翔 on 2021/11/15.
//

#ifndef test_h
#define test_h

#include "Queue.hpp"
#include <iostream>

void TestQueue() {
    Queue q;
    q.push(Guest("1")); std::cout << q.back().name << std::endl;
    q.push(Guest("2")); std::cout << q.back().name << std::endl;
    q.push(Guest("3")); std::cout << q.back().name << std::endl;
    q.push(Guest("4")); std::cout << q.back().name << std::endl;
    q.push(Guest("5")); std::cout << q.back().name << std::endl;
    q.push(Guest("6")); std::cout << q.back().name << std::endl;
    Queue qq(q);
    std::cout << qq.back().name <<std::endl;
    for (int i = 0; i < 6; ++i) {
        std::cout << q.front().name << ' ' << q.length() << std::endl;
        q.pop();
    }
    try {
        q.pop();
    }
    catch (const QueueException& e)  {
        std::cout << "Fine\n" << e.what() << std::endl;
    }
    try {
        auto i = q.front();
    }
    catch (const QueueException& e) {
        std::cout << "Fine\n" << e.what() << std::endl;
    }
    try {
        auto i = q.back();
    }
    catch (const QueueException& e) {
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
    
    a.removeall(v[3]);
    p = a.head->next;
    while(p != a.tail) {
        std::cout << p->data.name << std::endl;
        p = p->next;
    }
    std::cout << std::endl;
}

#endif /* test_h */
