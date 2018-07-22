//
//  linkedLists.cpp
//  
//
//  Created by Janani Natarajan on 11/25/14.
//
//

#include <iostream>
#include <cmath>

class node {
 public:
    int key;
    node *next;

    node(int val) : key(val), next(nullptr) {}
    ~node() {
        next = nullptr;
    }
};

class nodeDLL {
 public:
    int key;
    nodeDLL *prev;
    nodeDLL *next;

    nodeDLL(int val) : key(val), prev(nullptr), next(nullptr) {}
    ~nodeDLL() {
        prev = next = nullptr;
    }
};

class LinkedList {
 private:
    node *head;
 
 public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();
    void insert(int val);
    bool insertInOrder(int val);
    void printList();
    void reverseList();
    bool isPalindrome(node* start);
    node* findLoopBeginning(node* start);
    // the lists are numbers represented in reverse
    node* addLists(node* l1, node* l2, int carry);
    node* partitionList(node* start, int val);
    int findKtoLastElement(int k);
    void removeDups();
    void deleteNode(node* item);
    void reverseListPairwise();
    node* getIntersectionPoint(LinkedList& l1, LinkedList& l2);
    bool insertInOrderCyclic(node** aNode, int val);
    void frontBackSplit(node* head, node** first, node** second);

 private:mc v
    void insert(node** head, node* newItem);
    node* removeElements(node *head, int val);
    void reverseList(node** head);
    void reverseListPairwise(node** head);
    int getLength(LinkedList& l);
};

LinkedList::~LinkedList()
{
    while (head != nullptr) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::printList()
{
    node *curr = head;
    while (curr) {
        cout << curr->key << endl;
        curr = curr->next;
    }
}

bool LinkedList::insertInOrder(int val)
{
    node* item = new node(val);
    if (item == NULL) {
        return false;
    }
    if (head == NULL) {
        head = item;
        return true;
    }
    node* prev = NULL;
    node* curr = head;
    while (curr != NULL) {
        if (val < curr->key) {
            item->next = curr;
            if (prev != NULL) {
                prev->next = item;
            } else {
                head = item;
            }
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = item;
    return true;
}

void LinkedList::insert(int val)
{
    node* newItem = new node(val);
    if (newItem) {
        insert(&head, newItem);
    }
}
// If you are updating what the pointer is pointing to, pass in a pointer to pointer
void LinkedList::insert(node** start, node* newItem)
{
    newItem->next = *start;
    *start = newItem;
}

//remove all elements of a given value
node* removeElements(node* head, int val)
{
     node *prev = nullptr, *curr = head;
     while (curr != nullptr) {
         node *nextNode = curr->next;
             if (curr->val == val) {
                if (prev != nullptr) {
                    prev->next = nextNode;
                } else {
                    head = nextNode;
                }
                delete curr;
            } else {
                prev = curr;
            }
            curr = nextNode;
        }
        return head;
    }
}

// delete dups in a sorted list such that each element appear only once
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        } else if (head->next == nullptr) {
            return head;
        }
        ListNode *curr = head->next, *prev = head;
        while (curr != nullptr) {
            ListNode *nextNode = curr->next;
            if (curr->val == prev->val) {
                prev->next = nextNode;
                delete curr;
            } else {
                prev = curr;
            }
            curr = nextNode;
        }
        return head;
    }
};

/*
 * Given a sorted linked list, delete all nodes that have duplicate numbers, 
 * leaving only *distinct* numbers from the original list.
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->5
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        } else if (head->next == nullptr) {
            return head;
        }
        ListNode *curr = head, *prev = nullptr;
        while (curr != nullptr) {
            if (curr->next != nullptr && curr->val == curr->next->val) {
                int dupVal = curr->val;
                while (curr != nullptr && curr->val == dupVal) {
                    ListNode *nextNode = curr->next;
                    if (prev != nullptr) {
                        prev->next = nextNode;
                    } else {
                        head = nextNode;
                    }
                    delete curr;
                    curr = nextNode;
                }
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }
};

// remove duplicates in a unsorted linked list
class Solution {
public:
    void removeDuplicates(ListNode *head) {
        ListNode * curr = head, *prev = nullptr;
        set<int> values;
        pair<set<int>::iterator, bool> result;
        while (curr != nullptr) {
            ListNode *nextNode = curr->next;
            result = values.insert(curr->val);
            if (result.second == false) {
                if (prev != nullptr) {
                    prev->next = nextNode;
                } else {
                    head = nextNode;
                }
                delete curr;
            } else {
                prev = curr;
            }
            curr = nextNode;
        }
    }
};

int LinkedList::findKtoLastElement(int k)
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
    return ((knode) ? knode->key : -1);
}

void LinkedList::deleteNode(node* item)
{
    // don't have access to the prev node
    if (item == NULL || item->next == NULL) {
        return;
    }
    node* nextNode = item->next;
    item->next = nextNode->next;
    item->key = nextNode->key;
    delete nextNode;
}

node* LinkedList::partitionList(node* start, int val)
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
            start->next = valNode; // to handle the case where there are dups
            valNode = start;
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

//reverse the linked list
//keep moving the elements to the head
void LinkedList::reverseList()
{
    return reverseList(&head);
}
void LinkedList::reverseList(node** head)
{
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    //there are atleast 2 items in the linked list
    node* curr = *head, *prev = NULL;
    while (curr) {
        node* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    *head = prev;
}

// the lists are numbers represented in reverse
node* LinkedList::addLists(node* l1, node* l2, int carry)
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

node* LinkedList::findLoopBeginning(node* start)
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

bool LinkedList::isPalindrome(node* start)
{
    //find the middle and reverse the linked list until middle point using a stack
    //Now compare the rest of the list with the reversed items from the stack
    node* fast, *slow;
    fast = slow = start;
    stack<node*> s;

    while (fast != NULL && fast->next != NULL) {
        s.push(slow);
        slow = slow->next;
        fast = fast->next->next;
    }
    // has odd no. of elements; skip the middle and point past it
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
    if (slow || !s.empty()) {
        return false;
    }
    return true;
}

//linked list with a pointer to random item in the list
struct {
    int data;
    RandomListNode* next;
    RandomListNode* random;
} RandomListNode;

//Another solution: is to use a hashMap to store the
//mapping between the random and random'.
//First walk the original list and create a copy list
//walk it again looking up the hashMap for every random
//pointer the corresponding random' and updating the copy list
RandomListNode* copyRandomList(RandomListNode* head)
{
    if (head == NULL) {
        return NULL;
    }
    
    RandomListNode* p = head;
    
    // copy every node and insert to list
    while (p != NULL) {
        RandomListNode* copy = new RandomListNode(p->data);
        copy->next = p->next;
        p->next = copy;
        p = copy->next;
    }
    
    // copy random pointer for each new node
    p = head;
    while (p != NULL) {
        if (p->random != NULL) {
            p->next->random = p->random->next;
        } else {
            p->next->random = NULL;
        }
        p = p->next->next;
    }

    // break list to two
    p = head;
    RandomListNode* newHead = head->next;
    while (p != NULL) {
        RandomListNode* temp = p->next;
        p->next = temp->next;
        if (temp->next != NULL) {
            temp->next = temp->next->next;
        }
        p = p->next;
    }
    
    return newHead;
}

int LinkedList::getLength(LinkedList& l)
{
    node* p = l.head;
    int len = 0;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}
//intersection point of two singly linked lists
//Soln: Find the length of the 2 linked list and calculate the diff
//Move the longer list to that point and start comparing the 2 list
//walking until you find the common element
node* LinkedList::getIntersectionPoint(LinkedList& l1, LinkedList& l2)
{
    if (l1.head == NULL || l2.head == NULL) {
        return NULL;
    }
    int len1 = getLength(l1);
    int len2 = getLength(l2);

    node *p1 = l1.head, *p2 = l2.head;

    if (len2 > len1) {
        p2 = l1.head; p1 = l2.head;
        int temp = len1; len1 = len2; len2 = temp;
    }
    //invariant: l1 >= l2 and p1,len1 points to the longer list
    int d = len1-len2;
    for (int i = 0; i < d && p1 != NULL; ++i) {
        p1 = p1->next;
    }
    node* res = NULL;
    while (p1 && p2) {
        if (p1->key == p2->key) {
            if (res == NULL) {
                res = p1;
            }
        } else if (res) { // keep walking the list to the end to make sure the values are alinged
            return NULL;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return res;
}

//reversing linked lists pair-wise
void LinkedList::reverseListPairwise(node** head)
{
    node* prev = NULL;
    node* curr = *head;
    while (curr && curr->next != NULL) {
        node* nextNode = curr->next;
        node* newCurr = nextNode->next;
        curr->next = nextNode->next;
        nextNode->next = curr;
        if (prev) {
            prev->next = nextNode;
        } else {
            *head = nextNode;
        }
        prev = curr;
        curr = newCurr;
    }
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
void swapPairwise(nodeDLL** head)
{
    nodeDLL* first = *head;
    nodeDLL* prev = first->prev;
    while (first != NULL && first->next != NULL) {
        nodeDLL* second = first->next;
        nodeDLL* third = second->next;
        first->next = third;
        first->prev = second;
        second->next = first;
        second->prev = prev;
        if (prev) {
            prev->next = second;
        } else {
            *head = second;
        }
        prev = first;
        first = third;
    }
}

//insert an item into a cyclic sorted linked list, maintaining the sorted order,
//given a pointer to any node in the list
bool LinkedList::insertInOrderCyclic(node** aNode, int val)
{
    node* item = new node(val);
    if (item == NULL) {
        return false;
    }
    if ((*aNode) == NULL) {
        //the list is empty
        //make the item point back to itself
        item->next = item;
        *aNode = item;
        return true;
    }
    node* prev = NULL;
    node* curr = *aNode;
    do {
        prev = curr;
        curr = curr->next;
        if (val <= curr->key && val >= prev->key) break;
        if (prev->key > curr->key && (curr->key > val || val > prev->key)) break;
    } while (curr != (*aNode));
    //handles only one item in the list as well
    item->next = curr;
    prev->next = item;
    return true;
}

void LinkedList::frontBackSplit(node* head, node** first, node** second)
{
    if (head == NULL) {
        return;
    }
    node *pSlow = head, *pFast = head;
    while (pFast != NULL && pFast->next != NULL) {
        pSlow = pSlow->next;
        pFast = pFast->next->next;
    }
    *first = *head;
    *second = pSlow->next;
    pSlow->next = NULL; //break into 2 lists
}
