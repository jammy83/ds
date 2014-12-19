//
//  dynamicProgramming.cpp
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#include <stdio.h>
#include iostream

//longest increasing subsequence
int LIS(int* arr, int size)
{
    int lis[size] = {};
    //initialize to 1
    for (int i = 0; i < size; i++) {
        lis[i] = 1;
    }
    //lis will store the length of the longest increasing subsequence ending at 'i'
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j]+1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    // find the max
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (max < lis[i]) {
            max = lis[i];
        }
    }
    return max;
}

//Given an array which provides the no. of hops to the next element
//Search if there is a path from start to destination
//example: {1, 2, 0, 1, 0 , 1}
//Construct a adjacency list for the DAG and use BFS to find if there is a route
bool hopArray(int* arr, int size, int start, int end)
{
    int steps = a[start];
    int index = start;
    while (steps > 0) {
        steps--;
        index++;
        if (index == end) {
            return true;
        }
        if (a[index] > steps) {
            steps = a[index];
        }
    }
    return false;
}

int main()
{
    return 0;
}
