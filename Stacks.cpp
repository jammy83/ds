//
//  Stacks.cpp
//  
//
//  Created by Janani Natarajan on 11/27/14.
//
//

#include iostream

template <class T>
class element {
 public:
    T _data;
    element<T> *_next;

    element(T val) : _data(val), _next(NULL) {}
    ~element() { _next = NULL; }
};

template <class T>
class MyStack {
    element<T> *_top;
    int _count;
    MyStack _min; //min stack

    void push(element<T> **head, element<T> *item);
    element<T>* pop();

 public:
    MyStack() : _top(NULL), _count(0) {}
    MyStack(element<T>* item) : _top(item), _count(1) {}
    ~MyStack() {
        // delete all the items in the stack starting at the top
        while (_top != NULL) {
            element<T> *nextE = _top->next;
            delete _top;
            _top = nextE;
        }
    }
    void push(T item);
    T pop();
    int size() const { return _count; }
    bool isEmpty() const { return (count == 0); }
    T peek() const {
        T res;
        if (_top) {
            res = _top->_data;
        }
        return res;
    }
    T min() const;
};

template <class T>
void MyStack<T>::push(T item)
{
    element<T> *newE = new element<T>(item);
    if (newE) {
        push(&_top, newE);
        _count++;
    }
    element<T> *newMin = new element<T>(item);
    if (newMin) {
        if (_min.isEmpty() || _min.peek() > item) {
            push(&_min._top, newMin);
            _min._count++;
        } else {
            // find the right position for this element
            int popped = 0;
            while (!_min.isEmpty() && _min.peek() > item) {
                element<T>* first = _min.popElement();
                popped++;
                push(&_top, first);
            }
            if (popped) {
                push(&_min._top, newMin);
                _min._count++;
                while (popped) {
                    element<T>* front = popElement();
                    push(&_min._top, front);
                    popped--;
                }
            }
        }
    }
}
template <class T>
void MyStack<T>::push(element<T> **head, element<T> *item)
{
    item->_next = *head;
    *head = item;
}

template <class T>
T MyStack<T>::pop()
{
    T res;
    if (_top) {
        res = _top->_data;
        element<T>* head = _top;
        _top = _top->_next;
        delete head;
        _count--;
    }
    return res;
}

template <class T>
element<T>* MyStack::popElement()
{
    if (_top) {
        element<T>* res = _top;
        _top = _top->_next;
        res->_next = NULL; //unlink it
        _count--;
        return res;
    }
    return NULL;
}

template <class T>
T MyStack<T>::min()
{
    T res;
    if (!_min.isEmpty()) {
        res = _min.pop();
    }
    return res;
}

// Vector operations
// push_back(), pop_back(), back(), front(), empty(), at(), capacity(), erase(index)
vector<MyStack> stacks = new vector<MyStack>();
MyStack newStack = new MyStack();
stacks.push_back(newStack);

getLastStack() // stacks.back();
noOfStacks() // stacks.capacity();

popAtIndex(int index)
{
    leftShit(index, true);
}

int leftShift(int index, bool removeTop)
{
    int res = 0;
    if (!stacks.empty()) {
        Mystack topStack = stacks.at(index);
        if (removeTop) {
            res = topStack.pop();
        } else {
            res = topStack.popEnd(); // need to maintain the head and tail of underlying linked list impl of the stack
        }
        if (topStack.empty()) {
            stacks.erase(index);
        } else if (stacks.capacity() > index + 1) {
            int v = leftShift(index+1, false);
            topStack.push(v);
        }
    }
    return res;
}


// create a queue using 2 stacks
// pop() -- pop all the elements from s1 onto s2 and return the top. When empty,
// pop more elements from s1 onto s2.
// when you have to push() to s1, simply push onto s1

//Queue implemetation using linked lists will maintain a head and tail pointer


