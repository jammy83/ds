//
//  stacks.cpp
//  
//
//  Created by Janani Natarajan on 11/27/14.
//
//

#include iostream
#include "stacks.h"

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


