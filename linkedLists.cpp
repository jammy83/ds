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

/*
 * Given a linked list, remove the n-th node from the end of list and return its head.
 * Approach 1: Find the length of the list and return the len-n+1
 * Approach 2: Maintain 2 ptrs that are n nodes apart. When the fast pointer reaches the end,
 * the slow pointer will be pointing to nth node from the last.
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *curr = head, *node = head;
        int count = 0;
        while (curr != nullptr && count++ < n) {
            curr = curr->next;
        }
        if (count != n && curr == nullptr) {
            return nullptr;
        }
        ListNode *prev = nullptr;
        while (curr != nullptr) {
            curr = curr->next;
            prev = node;
            node = node->next;
        }
        if (prev != nullptr) {
            prev->next = node->next;
        } else {
            head = node->next;
        }
        delete node;
        return head;
    }
};

// Delete a node in a linked list given only access to that node.
class Solution {
public:
    void deleteNode(ListNode* node) {
        if (node == nullptr || node->next == nullptr) {
            return;
        }
        ListNode *nextNode = node->next;
        node->val = nextNode->val;
        node->next = nextNode->next;
        nextNode->next = nullptr;
        delete nextNode;
    }
};

/*
 * Given a linked list and a value x, partition it such that all nodes <x come before nodes >=x.
 * You should preserve the original relative order of the nodes in each of the two partitions.
 * Input: head = 1->4->3->2->5->2, x = 3
 * Output: 1->2->2->4->3->5
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *curr = head, *prev = nullptr;
        ListNode *prevItem = nullptr, *beforeItem = nullptr;
        while (curr != nullptr && curr->val < x) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) {
            return head;
        }
        prevItem = prev;
        beforeItem = curr;
        while (curr != nullptr) {
            if (curr->val >= x) {
                prev = curr;
                curr = curr->next;
            } else {
                ListNode *nextNode = curr->next;
                prev->next = nextNode;
                if (prevItem != nullptr) {
                    prevItem->next = curr;
                } else {
                    head = curr;
                }
                curr->next = beforeItem;
                prevItem = curr;
                curr = nextNode;
            }
        }
        return head;
    }
};

// Reverse the linked list
// Approach 1: using a stack
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<int> vals;
        ListNode *curr = head;
        while (curr != nullptr) {
            vals.push(curr->val);
            ListNode *nextNode = curr->next;
            curr->next = nullptr;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
        ListNode* prev = nullptr;
        while (!vals.empty()) {
            if (head == nullptr) {
                head = new ListNode(vals.top());
                vals.pop();
                prev = head;
                continue;
            }
            curr = new ListNode(vals.top());
            vals.pop();
            prev->next = curr;
            prev = curr;
        }
        return head;
    }
};

// Approach 2: Reverse the pointers in one pass
class Solution {
public:
   ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *curr = head->next, *prev = head;
        prev->next = nullptr;
        while (curr != nullptr) {
            ListNode *nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev;
        return head;
    }
};

// Merge 2 sorted lits
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr && l2 == nullptr) {
            return nullptr;
        }
        if (l1 == nullptr) {
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        }
        ListNode *newPrev = nullptr, *newHead = nullptr, *curr = nullptr;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                curr = l1;
                l1 = l1->next;
            } else {
                curr = l2;
                l2 = l2->next;
            }
            if (newHead == nullptr) {
                newHead = curr;
            } else {
                newPrev->next = curr;
            }
            newPrev = curr;
        }
        newPrev->next = l1 != nullptr ? l1 : l2;
        return newHead;
    }
};

// middle element in a linked list
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if (head == nullptr || head-> next == nullptr) {
            return head;
        }
        ListNode *slow = head, *fast = head->next->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->next;
    }
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode *slow = head, *fast = head->next->next;
        while (fast != nullptr && fast->next != nullptr) {
            if (slow == fast) {
                return true;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        ListNode *slow = head, *fast = head, *prev = nullptr;
        ListNode *nextNode = nullptr;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            nextNode = slow->next;
            slow->next = prev;
            prev = slow;
            slow = nextNode; 
        }
        if (fast != nullptr) { // odd no. of elements
            slow = slow->next;
        }
        while (slow != nullptr && prev != nullptr) {
            if (slow->val != prev->val) {
                return false;
            }
            slow = slow->next;
            prev = prev->next;
        }
        return true;
    }
};

//intersection point of two singly linked lists
//Soln: Find the length of the 2 linked list and calculate the diff
//Move the longer list to that point and start comparing the 2 list
//walking until you find the common element
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        int lenA = 0, lenB = 0;
        ListNode *currA = headA, *currB = headB, *lastA, *lastB;
        while (currA != nullptr) {
            lastA = currA;
            currA = currA->next;
            ++lenA;
        }
        while (currB != nullptr) {
            lastB = currB;
            currB = currB->next;
            ++lenB;
        }
        if (lastA != lastB) {
            return nullptr;
        }
        currA = headA;
        currB = headB;
        int move = abs(lenA-lenB);
        if (lenA > lenB) {
            while (move-- > 0) {
                currA = currA->next;
            }
        } else if (lenB > lenA) {
            while (move-- > 0) {
                currB = currB->next;
            }
        }
        while (currA != nullptr && currB != nullptr) {
            if (currA == currB) {
                return currA;
            }
            currA = currA->next;
            currB = currB->next;
        }
        return nullptr;
    }
};

// odd-even linked list
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return head;
        }
        //atleast 3 elements
        ListNode *odd = head, *even = nullptr, *prevOdd = nullptr, *evenHead = head->next;
        while (odd != nullptr) {
            even = odd->next;
            odd->next = even != nullptr ? even->next : nullptr;
            prevOdd = odd;
            odd = odd->next;
            if (even != nullptr) {
                even->next = odd != nullptr ? odd->next : nullptr;
            }
        }
        prevOdd->next = evenHead;
        return head;
    }
};

// sort linked list using insertion sort
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *curr = head->next, *sortedEnd = head;
        while (curr != nullptr) {
            if (curr->val >= sortedEnd->val) {
                sortedEnd = curr;
                curr = curr->next;
                continue;
            }
            ListNode *begin = head, *prev = nullptr;
            while (begin != curr) {
                if (begin->val <= curr->val) {
                    prev = begin;
                    begin = begin->next;
                } else {
                    if (prev != nullptr) {
                        prev->next = curr;
                    } else {
                        head = curr;
                    }
                    sortedEnd->next = curr->next;
                    curr->next = begin;
                    break;
                }
            }
            curr = sortedEnd->next;
        }
        sortedEnd->next = nullptr;
        return head;
    }
};

//reverse a linked list between m & n where  1 <= m <= n
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == nullptr || m == 0 || n == 0 || n <= m) {
            return head;
        }
        int cnt = 1;
        ListNode *curr = head, *prev = nullptr, *start = nullptr, *prevStart = nullptr;
        while (curr != nullptr && cnt <= n) {
            ListNode *nextNode = curr->next;
            if (cnt == m) {
                start = curr;
                prevStart = prev;
            } else if (cnt > m) {
                curr->next = prev;
            }
            prev = curr;
            curr = nextNode; cnt++;
        }
        if (prevStart != nullptr) {
            prevStart->next = prev;
        } else {
            head = prev;
        }
        start->next = curr;
        return head;
    }
};

// Reorder the list
// Given a singly linked list L: L0→L1→…→Ln-1→Ln,
// reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return;
        }
        //atleast 3 elements
        ListNode *slow = head; ListNode *fast = head, *odd = nullptr;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;     
        }
        ListNode *mid = slow;
        if (fast != nullptr) { // odd no. of elements
            odd = slow;
            slow = slow->next;
            odd->next = nullptr;
        }
        stack<ListNode*> s;
        while (slow != nullptr) {
            s.push(slow);
            slow = slow->next;
        }
        ListNode *curr = head, *prev = nullptr;
        while (curr != mid) {
            ListNode *nextNode = curr->next;
            curr->next = s.top(); s.pop();
            if (prev != nullptr) {
                prev->next = curr;
            }
            prev = curr->next;
            curr = nextNode;
        }
        prev->next = odd;
    }
};

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
