//
//  stacks.cpp
//  
//
//  Created by Janani Natarajan on 11/27/14.
//
//

#include iostream
#include "stack.h"

//--------------------------------------------------------------------------------------------------------
// Vector operations
// push_back(), pop_back(), back(), front(), empty(), at(), capacity(), size(), erase(index)
vector< MyStack<int> > stacks = new vector< MyStack<int> >();
MyStack<int> newStack = new MyStack<int>();
stacks.push_back(newStack);

getLastStack() // stacks.back();
noOfStacks() // stacks.size() is the the no. elements in the vector and capacity() is the storage capacity

popAtIndex(int index)
{
    leftShit(index, true);
}

int leftShift(int index, bool removeTop)
{
    int res = 0;
    if (!stacks.empty()) {
        if (index < 0 || index >= stacks.size()) {
            return -1; // out of bounds
        }
        Mystack topStack = stacks.at(index);
        if (removeTop) {
            res = topStack.pop();
        } else {
            res = topStack.popEnd();
            // need to maintain the head and tail of underlying linked list impl of the stack
        }
        if (topStack.empty()) {
            stacks.erase(index);
        } else if (stacks.size() > index + 1) {
            int v = leftShift(index+1, false);
            topStack.push(v);
        }
    }
    return res;
}
//--------------------------------------------------------------------------------------------------------

// create a queue using 2 stacks
// pop() -- pop all the elements from s1 onto s2 and return the top. When empty,
// pop more elements from s1 onto s2.
// when you have to push() to s1, simply push onto s1

//Queue implemetation using linked lists will maintain a head and tail pointer: push_back(), pop_front()

//--------------------------------------------------------------------------------------------------------

//Stacks implemented using doubly linked list to return the middle element in O(1) complexity
//Support findMiddle() and delMiddle()
// if count == 1, mid is the first element.
// On push, count%2 == 0, even : mid = mid->prev
// On pop, count%2 == 1, odd : mid = mid->next

//--------------------------------------------------------------------------------------------------------

//Direction of stack growth in an OS
//http://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86/
/*In a Linux (or other Operating System) process when a subroutine is called, the memory for local variables
comes from stack area of the process. Any dynamically allocated memory (using malloc, new, etc.) comes from
the heap area of the process. During recursion local memory is allocated from stack area during function
call and get cleared when the function execution is done.

The memory is being represented with lowest address being at the bottom and highest being at the top.
Here are the steps to find the direction of stack growth in recursion using a quick C code.
*/

void test_stack_growth_direction(recursion_depth) {
    int local_int1;
    printf("%p\n", &local_int1);
    if (recursion_depth < 10) {
        test_stack_growth_direction(recursion_depth + 1);
    }
}

int main () {
    test_stack_growth_direction(0);
    return 0;
}

/*
out put on MAC
0x7fff6e9e19ac
0x7fff6f9e89a8
0x7fff6f9e8988
0x7fff6f9e8968
0x7fff6f9e8948
0x7fff6f9e8928
0x7fff6f9e8908
0x7fff6f9e88e8
0x7fff6f9e88c8
0x7fff6f9e88a8
0x7fff6f9e8888

output on ubuntu
0x7ffffeec790c
0x7ffffeec78dc
0x7ffffeec78ac
0x7ffffeec787c
0x7ffffeec784c
0x7ffffeec781c
0x7ffffeec77ec
0x7ffffeec77bc
0x7ffffeec778c
0x7ffffeec775c
0x7ffffeec772c
 
The stack is growing downwards on these specific setups as memory addresses are reducing.
This depends on the architecture of the system and may have different behavior for other architectures.
*/


//Endianness

#include     "unp.h"

int main(int argc, char **argv)
{
    union {
        short   s;
        char    c[sizeof(short)];
    } un;

    un.s = 0x0102;
    printf("%s: ", CPU_VENDOR_OS);
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unknown\n");
    } else
    printf("sizeof(short) = %d\n", sizeof(short));

    exit(0);
}
//--------------------------------------------------------------------------------------------------------
