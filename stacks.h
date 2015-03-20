//
//  stacks.h
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#ifndef _stacks_h
#define _stacks_h

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
        head->_next = NULL;
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
        res->_next = NULL; //unlink it
        _top = _top->_next;
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

#endif
