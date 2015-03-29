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

//implements a stack using a linked list by pushing and popping off
//elements at the head of the linked list
template <class T>
class MyStack {
    element<T> *_top;
    int _count;
    MyStack<T> _minStack;

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
    T getMin() const;
};

template <class T>
void MyStack<T>::push(T item)
{
    element<T> *newE = new element<T>(item);
    if (newE) {
        push(&_top, newE);
        _count++;
    }
    if (_minStack.isEmpty() || item <= _minStack.peek()) {
        _minStack.push(item);
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
        if (_minStack.peek() == _top->_data) {
            _minStack.pop();
        }
        res = _top->_data;
        element<T>* head = _top;
        _top = _top->_next;
        head->_next = NULL;
        delete head;
        _count--;
    }
    if (_minStack.isEmpty() && !isEmpty()) {
        //walk the original stack and find the new minimum
        element<T>* curr = _top;
        T min = curr->_data;
        while (curr) {
            if (curr->_data < min) {
                min = curr->_data;
            }
            curr = curr->_next;
        }
        _minStack.push(min);
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

//http://articles.leetcode.com/2010/11/stack-that-supports-push-pop-and-getmin.html
template <class T>
T MyStack<T>::getMin()
{
    T res;
    if (!_minStack.isEmpty()) {
        res = _minStack.pop();
    }
    return res;
}

#endif
