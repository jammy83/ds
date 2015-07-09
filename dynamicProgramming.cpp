//
//  dynamicProgramming.cpp
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#include <stdio.h>
#include <iostream>

/*DP: technique of dynamic programming, which is the following very simple idea: start with a recursive algorithm for the problem, which may be inefficient because it calls itself repeatedly on a small number of subproblems. Simply remember the solution to each subproblem the first time you compute it, then after that look it up instead of recomputing it. The overall time bound then becomes (typically) proportional to the number of distinct subproblems rather than the larger number of recursive calls. 
 */

//longest increasing subsequence
//subsequence means the values need not be consecutive but maintain the relative order
//O(n^2) solution
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

//Notes: using an array to cache intermediate results reduces the complexity
//from O(3^N) exponential to O(n).
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
    int mid = start+ (end-start)/2;
    if (arr[mid] == mid) {
        return mid;
    } else if (arr[mid] < mid) { //another idea was arr[mid] >= end or 'n', discard everything to the right
        //search right of mid
        return magicIndex(arr, mid+1, end);
    } else {
        return magicIndex(arr, start, mid-1);
    }
}

//longest palindromic substring not *subsequence*
//This can be easily modified to work with integers
int longestPalindromeSubstring(char* str)
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

//Coin change
//C(N,m) = C(N,m-1)+C(N-Sm, m)
//complexity is O(nm) if memoziation is used as well..
int coinChange(int n, int denom)
{
    int next_denom = 0;
    switch (denom) {
        case 25:
            next_denom = 10;
            break;
        case 10:
            next_denom = 5;
            break;
        case 5:
            next_denom = 1;
            break;
        case 1:
            return 1;
    }
    int ways = 0;
    for (int i = 0; i * denom <= n; ++i) {
        ways += coinChange(n - i * denom, next_denom);
    }
    return ways;
}

//longest common subsequence
//L(X[0...n-1], Y[0...m-1]) = 1 + L(X[0..n-2], Y[0..m-2]) if X[n-1] == Y[m-1] else
//                            max(L(X[0..n-1], Y[0..m-2]), L(X[0..n-2], Y[0..m-1]))
//complexity (time + space): O(mn)
/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(char* X, char* Y, int m, int n )
{
    int L[m+1][n+1] = {};

    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
     that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    /*******NOTE********/
    //This is iterative (because it uses nested loops instead of recursion) or bottom up (because the
    //order we fill in the array is from smaller simpler subproblems to bigger more complicate ones).
    /*******************/
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } else if (X[i-1] == Y[j-1]) {
                L[i][j] = L[i-1][j-1] + 1;
            } else {
                L[i][j] = max(L[i-1][j], L[i][j-1]);
            }
        }
    }
    /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
    return L[m][n];
}

//Longest prefix match: Radix tree or trie (used by routers)
//Given a dictionary of words and an input string, find the longest prefix of the
//string which is also a word in dictionary.


//Find all permutations of a string
//Recurrence : f(n) = f(n-1) + a(sub)n <-- inserted in all positions from results of f(n-1)
//Complexity: O(n!) since there are that many permutations
void findPermutations(string str, vector<string>& perms)
{
    if (str.empty()) {
        return;
    }
    findPermutations(str.substr(1, str.length()-1), perms);
    for (vector<string>::iterator itr = perms.begin(); itr != perms.end(); ++itr) {
        for (int i = 0; i < (*itr).length(); ++i) {
            perms.push_back(insertCharAt((*itr), str.at(0), i));
        }
    }
}
string insertCharAt(string s, char c, int pos)
{
    string start = s.substr(0, pos);
    string end = s.substr(pos, s.length() - pos);
    return start + c + end;
}

int main()
{
    return 0;
}
