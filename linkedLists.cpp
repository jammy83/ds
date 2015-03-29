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
    node* next;

    node(int val) : key(val), next(NULL) {}
    ~node() {
        next = NULL;
    }
};

class nodeDLL {
 public:
    int key;
    nodeDLL* prev;
    nodeDLL* next;

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
    bool insertInOrder(int val);
    void removeAll(int val);
    void remove(int val);
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

 private:
    void insert(node** head, node* newItem);
    void removeAllUtil(node** head, int val);
    void removeUtil(node** head, int val);
    void reverseList(node** head);
    void reverseListPairwise(node** head);
    int getLength(LinkedList& l);
};

LinkedList::~LinkedList()
{
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::printList()
{
    node* curr = head;
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
void LinkedList::removeAll(int val)
{
    return removeAllUtil(&head, val);
}
void LinkedList::removeAllUtil(node**head, int val)
{
    if ((*head) == NULL) {
        return;
    }
    //head is the item to be removed
    while ((*head) != NULL && (*head)->key == val) {
        node* nextNode = (*head)->next;
        (*head)->next = NULL;
        delete *head;
        *head = nextNode;
    }
    //if the element to be removed is somewhere in
    //the middle of the list
    node* curr = *head;
    while (curr->next != NULL) {
        if (curr->next->key == val) {
            node* nextNode = curr->next;
            curr->next = nextNode->next;
            nextNode->next = NULL;
            delete nextNode;
        } else {
            curr = curr->next;
        }
    }
}

//remove an element of a given value
void LinkedList::remove(int val)
{
    return removeUtil(&head, val);
}
void LinkedList::removeUtil(node** head, int val)
{
    if (*head == NULL) {
        return;
    }
    //head is the item to be removed
    if ((*head)->key == val) {
        node* nextNode = (*head)->next;
        (*head)->next = NULL;
        delete *head;
        *head = nextNode;
        return;
    }
    //if the element to be removed is in the middle
    node* curr = *head;
    while (curr->next != NULL) {
        if (curr->next->key == val) {
            node* nextNode = curr->next;
            curr->next = nextNode->next;
            nextNode->next = NULL;
            delete nextNode;
            return;
        }
        curr = curr->next;
    }
}

void LinkedList::removeDups()
{
    if (head == NULL) {
        return;
    }
    HashTable hashT = new HashTable();
    node* start = head;
    node* prev = NULL;
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

//reverse the linked list
//keep moving the elements to the head
void LinkedList::reverseList()
{
    return reverseList(&head);
}
void LinkedList::reverseList(node** head)
{
    if (*head == NULL) {
        return;
    }
    node* curr = *head;
    while (curr->next != NULL) {
        node* nextNode = curr->next;
        curr->next = nextNode->next;
        nextNode->next = *head;
        *head = nextNode;
    }
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
    while (p != null) {
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
    int d = abs(len1-len2);
    node *p1 = l1.head, *p2 = l2.head;

    if (len2 > len1) {
        p2 = l1.head; p1 = l2.head;
        int temp = len1; len1 = len2; len2 = temp;
    }
    //invariant: l1 >= l2 and p1,len1 points to the longer list
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
        if (prev->key > curr->key && (curr->key > val || val > prev->key) break;
    } while (curr != (*aNode));
    //handles only one item in the list as well
    item->next = curr;
    prev->next = item;
    return true;
}

int main()
{
    LinkedList test;
    test.insert(2);
    test.insert(2);
    test.insert(8);
    test.insert(9);
    test.insert(7);
    test.insert(2);
    test.insert(2);
    test.insert(6);
    test.insert(2);
    test.insert(2);
    test.removeAll(2);
    test.printList();
    test.reverseList();
    cout << endl << endl;
    test.printList();
    cout << test.findKtoLastElement(3) << endl;
    /*
     LinkedList test;
     test.insert(8);
     test.insert(9);
     test.insert(7);
     test.insert(6);
     test.insert(2);
     LinkedList test1;
     test1.insert(8);
     test1.insert(9);
     test1.insert(3);
     node* res = test.getIntersectionPoint(test, test1);
     if (res) {
        cout << res->key << endl;
     }
     */
    return 0;
}


