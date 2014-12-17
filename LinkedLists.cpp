//
//  LinkedLists.cpp
//  
//
//  Created by Janani Natarajan on 11/25/14.
//
//

#include <iostream>

class node {
 private:
    int key;
    node* next;

 public:
    node(int val) : key(val), next(NULL) {}
    ~node() {
        next = NULL;
    }
};

class nodeDLL {
 private:
    int key;
    nodeDLL* prev;
    nodeDLL* next;

 public:
    nodeDLL(int val) : key(val), prev(NULL), next(NULL) {}
    ~nodeDLL() {
        prev = next = NULL;
    }
};

class LinkedList {
 private:
    node* head;
 
 public:
    LinkedList() : head(NULL) {}
    ~LinkedList();
    void insert(int val);
    void insert(node** head, node* newItem);
    void remove(node** head, node* item);
    bool isPalindrome(node* start);
    node* findLoopBeginning(node* start);
    // the lists are numbers represented in reverse
    node* addLists(node* l1, node* l2, int carry);
    node* reverseList(node* start);
    node* partitionList(node* start, int val);
    node* findKtoLastElement(int k);
    void removeDups();
    void deleteNode(node* item);
};

LinkedList::~LinkedList()
{
    node* start = head;
    while (start != NULL) {
        node* temp = start;
        start = start->next;
        delete temp;
    }
}

void LinkedList::insert(int val)
{
    node* newItem = new node(val);
    if (newItem) {
        insert(&head, newItem);
    }
}
// If you are updating what the pointer is pointing to, pass in a pointer to pointer
// or else just the pointer object
void LinkedList::insert(node** start, node* newItem)
{
    newItem->next = *start;
    *start = newItem;
}

void LinkedList::remove(node** head, node* item)
{
    if (*head == item) {
        // if the element we are deleting is the head of the list
        *head = *head->next;
        delete item;
        return;
    }

    node* start = *head;
    while (start->next != NULL) {
        if (start->next == item) {
            start->next = item->next;
            delete item;
            return;
        }
        start = start->next;
    }
}

void removeDups()
{
    if (head == NULL) {
        return;
    }
    HashTable hashT = new HashTable();
    node* start = head;
    node* prev = start;
    while (start) {
        if (hashT.containsKey(start->key)) {
            prev->next = start->next;
            node* temp = start;
            start = start->next;
            delete temp;
        } else {
            hashT.insert(start->key, start);
            prev = start; // update previous only if this is not a duplicate
            start = start->next;
        }
    }
}

void findKtoLastElement(int k)
{
    node* start = head;
    node* knode = NULL;
    int count = 0;
    while (start != NULL) {
        count++;
        if (count == k) {
            knode = head;
        } else if (count > k) {
            knode = knode->next;
        }
        start = start->next;
    }
    return knode;
}

void deleteNode(node* item)
{
    // don't have access to the node
    if (item == NULL || item->next == NULL) {
        return;
    }
    node* nextNode = item->next;
    item->next = nextNode->next;
    item->key = nextNode->key;
    delete nextNode;
}

node* partitionList(node* start, int val)
{
    if (head == NULL) {
        return;
    }
    // maintain 2 separate lists for storing values <x
    // and one for >x
    node* beforeHead, *beforeTail;
    beforeHead = beforeTail = NULL;
    node* after = NULL;
    node* valNode = NULL;

    while (start != NULL) {
        node* nextNode = start->next;
        if (start->key < val) {
            if (beforeHead == NULL) {
                start->next = beforeHead;
                beforeHead = start;
                beforeTail = beforeHead;
            } else {
                beforeTail->next = start;
                start->next = NULL;
                beforeTail = start;
            }
        } else if (start->key > val) {
            start->next = after;
            after = start;
        } else {
            valNode = start;
            start->next = NULL;
        }
        start = nextNode;
    }
    
    if (beforeHead && beforeTail) {
        beforeTail->next = valNode;
        if (valNode) {
            valNode->next = after;
        }
        start = beforeHead;
    } else if (valNode) {
        valNode->next = after;
        start = valNode;
    } else {
        start = after;
    }
    
    return start;
}

node* reverseList(node* start)
{
    if (start == NULL) {
        return NULL;
    }
    node* prev = start;
    node* curr = start->next;
    while (curr != NULL) {
        node* nextNode = curr->next;
        curr->next = prev;
        if (prev == start) {
            prev->next = NULL;
        }
        prev = curr;
        curr = nextNode;
    }
}

// the lists are numbers represented in reverse
node* addLists(node* l1, node* l2, int carry)
{
    if (l1 == NULL && l2 == NULL && carry == 0) {
        return NULL;
    }
    int val = carry;
    if (l1 != NULL) {
        val += l1->key;
    }
    if (l2 != NULL) {
        val += l2->key;
    }
    node* result = new node(val%10);
    if (l1 != NULL || l2 != NULL) {
        result->next = addLists((l1 ? l1->next : NULL),
                                (l2 ? l2->next : NULL),
                                (val > 10 ? 1 : 0));
    }
    return result;
}

node* findLoopBeginning(node* start)
{
    node* fast, *slow;
    fast = slow = start;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    if (fast == NULL || fast->next == NULL) {
        return NULL; // no loop
    }
    slow = start; // reset to beginning of the list
    while (slow != fast) { // they collide next at the beginning of the loop
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

bool isPalindrome(node* start)
{
    //find the middle and reverse the linked list until middle point using a stack
    //Now compare the rest of the list with the reversed items from the stack
    node* fast, *slow;
    fast = slow = start;
    stack<node*> s;

    while (fast != NULL && fast->next != NUll) {
        s.push(slow);
        slow = slow->next;
        fast = fast->next->next;
    }
    // If there are odd no. of elements, fast won't be NULL
    if (fast != NULL) {
        slow = slow->next;
    }
    while (slow != NULL && !s.empty()) {
        node* item = s.top();
        s.pop();
        if (item->key != slow->key) {
            return false;
        }
        slow = slow->next;
    }
    return true;
}

// delete item from a doubly linked list
nodeDLL* removeFromDLL(nodeDLL* item)
{
    if (head == NULL) {
        return NULL;
    }
    if (head == item) {
        head = item->next;
        head->prev = NULL;
        item->prev = NULL;
        item->next = NULL;
        return item;
    }
    nodeDLL* start = head;
    while (start->next != NULL) {
        if (start->next == item) {
            start->next = item->next;
            (item->next)->prev = start;
            item->prev = NULL;
            item->next = NULL;
            return item;
        }
        start = start->next;
    }
    return NULL;
}

//swap item in a DLL
void swapPairwise(nodeDLL* head)
{
    nodeDLL* first = head;
    while (first != NULL && first->next != NULL) {
        nodeDLL* two = first->next;
        nodeDLL* third = two->next;
        node* prev = first->prev;
        first->next = third;
        first->prev = two;
        two->next = first;
        two->prev = prev;
        first = third;
    }
}

