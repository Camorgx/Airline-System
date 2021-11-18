#ifndef PriorityList_hpp
#define PriorityList_hpp

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
	PriorityList(PriorityList&& b) = default;
	PriorityList& operator=(const PriorityList& b);
    ~PriorityList();

    bool is_empty() const;
    //If not find, return nullptr.
	Node* find(const Guest& x) const;
	void insert(Guest& x);
	void remove(Node* x);
	//Delete the first x met in the list.
	void remove(const Guest& x);
    void remove_all(const Guest& x);
};

#endif /* PriorityList_hpp */
