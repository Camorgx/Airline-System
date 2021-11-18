#ifndef PriorityList_hpp
#define PriorityList_hpp

#include <utility>

#include "Guest.hpp"

class PriorityList {
public:
	struct Node {
		Guest data;
		Node* prev = nullptr, * next = nullptr;
        Node() = default;
        explicit Node(Guest g) { data = std::move(g); }
	};
    size_t size = 0;
	Node* head = new Node(), * tail = new Node();
	
    PriorityList() {
        head->next = tail;
        tail->prev = head;
    }
    PriorityList(const PriorityList& b);
    ~PriorityList();

    bool is_empty() const;
    //在优先链表中查找指定的元素，返回指向第一个匹配元素的指针或空指针
	Node* find(const Guest& x) const;
	//向优先链表中插入指定的元素
	void insert(Guest& x);
	//从优先链表中删除指定的元素
	void remove(Node* x);
	//从优先链表中查找x并删除遇到的第一个x
	void remove(const Guest& x);
    //从优先链表中删除所有的x
    void remove_all(const Guest& x);
};

#endif /* PriorityList_hpp */
