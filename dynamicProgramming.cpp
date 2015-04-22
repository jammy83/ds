//
//  dynamicProgramming.cpp
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#include <stdio.h>
#include <iostream>

//longest increasing subsequence
//subsequence means the values need not be consecutive but maintain the relative order
int LIS(int* arr, int size)
{
    //lis will store the length of the longest increasing subsequence ending at 'i'
    int lis[size] = {};
    //initialize to 1
    for (int i = 0; i < size; i++) {
        lis[i] = 1;
    }
    int max = 1;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j]+1) {
                lis[i] = lis[j] + 1;
            }
        }
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

//maximum sum subarray
int maxSumSubarray(int* arr, int size)
{
    int maxSum = 0;
    int runningSum = 0;
    for (int i = 0; i < size; i++) {
        runningSum += a[i];
        if (runningSum < a[i]) {
            runningSum = a[i];
        }
        if (maxSum < runningSum) {
            maxSum = runningSum;
        }
    }
    return maxSum;
}

//given an array of + and -ve integers, find the subarray
//with the maximum product {12, 2, -3, 7, -5, 8, -6, 2}
int maxProductSubarray(int* arr, int size)
{
    if (arr == NULL || size == 0) {
        return 0;
    }
    int max = 1, min = 1, maxProduct = 1;
    // idea is to maintain the positive and negative product since
    // 2 -ves turn positive.
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            max = max * arr[i];
            min = (min > 0) ? 1 : min * arr[i];
        } else if (arr[i] == 0) {
            min = max = 1;
        } else {
            int prevMax = max;
            max = (min < 0) ? min * arr[i] : 1;
            min = prevMax * arr[i];
        }
        if (maxProduct < max) {
            maxProduct = max;
        }
    }
    return maxProduct;
}

// hops 1/2/3 in a staircase
// how many possible ways to run up the stairs
// if instead of storing intermediate results, we compute the result, its exponential
// since each function call branches out to 3 more calls.
int computeHops(int n, int* arr, int size)
{
    // initialize the elements of arr to -1 on first invocation of this function
    if (n < 0 || n > size) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (arr[n] != -1) {
        return arr[n];
    } else {
        arr[n] = computeHops(n-1, arr, size) +
                 computeHops(n-2, arr, size) +
                 computeHops(n-3, arr, size);
        return arr[n];
    }
}

//magic index is the one where a[i] = i
//Given a sorted array of *distinct* integers, find the magic index if one exists
int magicIndex(int* arr, int start, int end)
{
    if (end < start || start < 0) {
        return -1;
    }
    int mid = (start+end)/2;
    if (arr[mid] == mid) {
        return mid;
    } else if (arr[mid] < mid) { //another idea was arr[mid] > end+1 or 'n', discard everything to the right
        //search right of mid
        magicIndex(arr, mid+1, end);
    } else {
        magicIndex(arr, start, mid-1);
    }
}

//longest palindromic substring not *subsequence*
//This can be easily modified to work with integers
int longestPalindromeSubstring(char* str) // int* str, int len
{
    if (str == NULL) {
        return 0;
    }
    int len = strlen(str);
    bool table[len][len]; // records if str[i..j] is palindrome or not
    memset(table, 0, sizeof(table));
    int maxLength = 1; // length of the palindrome identified so far
    int start = 0; // starting index where the palindrome begins

    for (int i = 0; i < len; ++i) {
        table[i][i] = true;
        if (i < len - 1 && str[i] == str[i+1]) {
            table[i][i+1] = true;
            start = i; // records the last instance of the palindrome occurrence
            maxLength = 2;
        }
    }

    for (int k = 3; k < len; ++k) {
        for (int i = 0; i < len-k; ++i) {
            int j = i+k-1;
            if (table[i+1][j-1] && str[i] == str[j]) {
                table[i][j] = true;
                if (k > maxLength) { // this means it will record the first occurrence of the palindrome for a given length
                    start = i;
                    maxLength = k;
                }
            }
        }
    }
    //just print the starting index and walk in a for loop if working with integers
    cout << "Palindromic Substring: " << std::string(str).substr(start, maxLength) << endl;
    return maxLength;
}

//longest common subsequence

//Longest prefix match: Radix tree or trie (used by routers)
//Given a dictionary of words and an input string, find the longest prefix of the
//string which is also a word in dictionary.

int main()
{
    return 0;
}
