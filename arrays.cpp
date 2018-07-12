//
//  arrays.cpp
//  
//
//  Created by Janani Natarajan on 11/20/14.
//
//

//http://kartikkukreja.wordpress.com
//http://noteworthyalgorithms.blogspot.com

#include <iostream>
#include <string.h>
#include <deque>
using namespace std;

bool hasUniqueCharacters(char *str)
{
    // Assuming ASCII characters alone are used in the given
    // string. There are 128 ascii chars including lower and upper case
    // alphabets, decimal [0-9], special characters (@,$, space char...),
    // arithmetic operators.
    if (str == NULL || strlen(str) > 128) {
        return false;
    }
    bool *charSeen = new bool[128](); 
    for (int i = 0; i < strlen(str); i++) {
        if (charSeen[str[i]]) {
            return false;
        }
        charSeen[str[i]] = true;
    }
    return true;
}

// find if str2 is a permutation of str1
// Same logic can be used to check if str2 is an anagram of str1
// anagrams are meanigful words formed by using the same chars from str1
// and this means its a permutation of the str1 that's also a dict word
bool isPermutation(string s1, string s2)
{
    if (s1.empty() || s2.empty() || s1.length() != s2.length()) {
        return false;
    }
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return (s1 == s2);
}

bool isPermutation(string s1, string s2)
{
    if (s1.empty() || s2.empty() || s1.length() != s2.length()) {
        return false;
    }
    map<char, int> hashMaps1;
    map<char, int>::const_iterator itr;
    for (int i = 0; i < s1.length(); i++) {
        if ((itr = hashMaps1.find(s1[i])) != hashMaps1.end()) {
            itr.second++;
        } else {
            hashMaps1[s1[i]] = 1;
        }
    }
    for (int i = 0; i < s2.length(); i++) {
       itr = hashMaps1.find([s2[i]]);
       if (itr == hashMaps1.end() || --itr.second < 0) {
           return false;
       }
    }
    return true;
}

// Replace space with %20
void replace(string s)
{
    if (s.empty()) {
        return;
    }
    //make sure size() >= length() + spaces * 2
    for (int end = s.size()-1, last = s.length()-1; last >= 0; end--, last--) {
        if (s[last] != " ") {
            s[end] = s[last];
        } else {
            s[end--] = "0"; s[end--] = "2"; s[end] = "%";
        }
    }
}

// Compute run length and compress the given string
string compressStr(string s)
{
    if (s.empty()) {
        return "";
    }
    map<char, int> mapL;
    map<char, int>::iterator itr;
    for (int i = 0; i < s.length(); i++) {
        itr = mapL.find(s[i]);
        if (itr != mapL.end()) {
            itr.second++;
            continue;
        }
        mapL[s[i]] = 1;
    }
    string compStr;
    for (map<char, int>::const_reference e : mapL) {
        compStr += e.first + e.second;
    }
    if (compStr.length() > s.length()) {
        return s;
    }
    return compStr;
}

bool isRotation(string s1, string s2)
{
    if (s1.empty() || s2.empty() || s1.length() != s2.length()) {
        return false;
    }
    return ((s2+s2).find(s1) != string::npos);
}

void zeroing2DMatrix(int** matrix, int n, int m)
{
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (matrix[i][j] = 0) {
                matrix[0][j] = 0; // represent cols
                matrix[i][0] = 0; // represent rows
            }
        }
    }
    //nullify cols
    for (int i = 0; i < m; i++) {
        if (matrix[0][i] == 0) {
            for (int j = 0; j < n; j++) {
                matrix[j][i] = 0;
            }
        }
    }
    //nullify rows
    for (int i = 0; i < n; i++) {
        if (matrix[i][0] == 0) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = 0;
            }
        }
    }
}

void reverseIntArray(int* arr, int start, int end)
{
    for (int i = start, j = end; i < j, i++, j--) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void rotateArray(int* arr, int size, int d)
{
    if (arr == nullptr || size == 0) {
        return;
    }
    // left rotate the array 'd' times
    for (int i = 0; i < d; i++) {
        int temp = arr[0];
        for (int i = 0; i < size-1; i++) {
            arr[i] = arr[i+1];
        }
        arr[i] = temp;
    }
    // reverse the array
    reverseIntArray(arr, 0, d-1);
    reverseIntArray(arr, d, size-1);
    reverseIntArray(arr, 0, size-1);
    // juggling .. using gcd(size, d)
}

int max(int a, int b)
{
    return (a >= b) ? a : b;
}
int min(int a, int b)
{
    return ( a <= b) ? a : b;
}
int getMedian(int* arr, int n)
{
    if (arr == NULL) {
        return 0;
    }
    return (n%2 == 0) ? (arr[n/2-1]+arr[n/2])/2 : arr[n/2]; //which is basically the mid, mid+1
}
// median of 2 sorted arrays; both of size n
int mergedMedian(int* arr1, int* arr2, int n)
{
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return (arr1[0]+arr2[0])/2;
    }
    if (n == 2) {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1]))/2;
    }
    int m1 = getMedian(arr1, n);
    int m2 = getMedian(arr2, n);
    if (m1 == m2) {
        return m1;
    }
    // have even no. of elements. Median is the avg of middle and the one before
    bool even = (n%2 == 0) ? true : false;
    int size = even ? n-n/2+1 : n-n/2;
    int offset = even ? n/2-1 : n/2;
    if (m1 > m2) {
        return mergedMedian(arr1, arr2+offset, size);
    } else {
        return mergedMedian(arr2, arr1+offset, size);
    }
}
//http://aleph.nu/blog/kth-smallest-in-sorted-union.html

// Gn a sorted array and value X, find a pair whose sum is closest to X
void closestPair(int* arr, int size, int val)
{
    if (arr == NULL) {
        return;
    }
    if (size < 2) {
        return;
    }
    // assuming this is a sorted array
    int l = 0;
    int r = size - 1;
    int last_l, last_r;
    last_l = last_r = 0;
    int last_diff = MAX_INT;
    while (l < r) {
        int sum = arr[l] + arr[r];
        int diff = abs(sum - val);
        if (diff < last_diff) {
            // found a better pair
            last_l = l;
            last_r = r;
            last_diff = diff;
        }
        if (sum == val) {
            break; // definitively closest.
            // if you want to continue, advance both the pointers
            // l++; r--;
        }
        if (sum < val) {
            l++;
        } else {
            r--;
        }
    }
    cout <<" The closest pair is " << arr[last_l] << " and " << arr[last_r];
}

// Gn 2 sorted arrays and a value X, find a pair one from each array whose sum is closest to X
void closestPair2Arrays(int* a, int* b, int n1, int n2, int val)
{
    if (a == NULL || b == NULL) {
        return;
    }
    if (n1 <= 0 || n2 <= 0) {
        return;
    }
    if (n1 == 1 && n2 == 1) {
        cout <<" The closest pair is " << a[0] << " and " << b[0];
        return;
    }
    //apply merge sort and call closestPair() on the single array.
    //need to track a given element for its source or pick the elements on the fly
    //as though applying merge sort.
    //Simply apply the same logic as for a single sorted array
    //Loop termination: l<size of arr1, r>=0
    int l = 0;
    int r = n2 - 1;
    int last_l, last_r, last_diff;
    last_l = last_r = 0;
    last_diff = MAX_INT;
    while (l < n1 && r >= 0) {
        int sum = a[l] + b[r];
        int diff = abs(sum - val);
        if (diff < last_diff) {
            // found a better pair
            last_l = l;
            last_r = r;
            last_diff = diff;
        }
        if (sum == val) {
            break; //definitively closest
        }
        if (sum < val) {
            l++;
        } else {
            r--;
        }
    }
    cout <<" The closest pair is " << a[last_l] << " and " << b[last_r];
}

// 3SUM problem - Given a sorted array, find 3 elements whose sum equals to zero
// What if the nos are not sorted - rem a+b = -c and you can look up for "-c" in the hash table
set<vector<int>> 3SUM(int* arr, int size)
{
    // assuming it is a sorted array, insert the elements in a hash table or BST
    // the idea is for elements at i & j, lookup -(arr[i]+arr[j])
    
    set<vector<int>> triplets; // to make sure unique combination of triplets are returned
    for (int i = 0; i < size; i++) {
        int left = i + 1;
        int right = size - 1;
        while (left < right) {
            sum = arr[i] + arr[left] + arr[right];
            if (sum < 0) {
                left++;
            }  else if (sum > 0) {
                right--;
            } else { // sum == 0
                vector<int> triplet = new vector<int>(3);
                triplet.push_back(arr[i]);
                triplet.push_back(arr[left]);
                triplet.push_back(arr[right]);
                triplets.insert(triplet);
                left++; right--;
            }
        }
    }
    return triplets;
}

// find a pair given the difference given a sorted array
void findPairForDifference(int* arr, int size, int n)
{
    for (int i = 0, j = 1; i < size && j < size; ) {
        if (arr[j] - arr[i] < n) {
            j++;
        } else if (arr[j] - arr[i] > n) {
            i++;
        } else if (i != j) {
            cout << "1: " << arr[i] << " 2: " << arr[j];
            return;
        }
    }
}

int binarySearch(int* arr, int start, int end, int n)
{
    int mid = start + (end-start) / 2; //avoids overflow
    if (arr[mid] == n) {
        return mid;
    }
    if (n < arr[mid]) {
        return binarySearch(arr, start, mid-1, n);
    } else {
        return binarySearch(arr, mid+1, end, n);
    }
}

//sorted+rotated array - search for a given element or the smallest element
int searchInSortedRotatedArray(int* arr, int start, int end, int n)
{
    //Note: if the array is sorted around the middle element, the subarrays on either
    //side of it will be sorted as well. So return middle element which is the beginning
    //of the sorted array.
    if (end < start) {
        return -1;
    }

    int mid = start + (end-start) / 2; //avoids overflow
    if (arr[mid] == n) {
        return mid;
    }
    if (arr[start] < arr[mid-1]) {
        // sorted half
        if (arr[start] >= n && n <= arr[mid-1]) {
            // search in this half
            return binarySearch(arr, start, mid-1, n);
        } else {
            return searchInSortedRotatedArray(arr, mid+1, end, n);
        }
    } else if (arr[mid+1] < arr[end]) {
        // sorted half
        if (arr[mid+1] >= n && n <= arr[end]) {
            return binarySearch(arr, mid+1, end, n);
        } else {
            return searchInSortedRotatedArray(arr, start, mid-1, n);
        }
    } else if (arr[start] == arr[mid]) {
        // handles duplicates with the left half containing the same elements
        if (arr[mid] != arr[end]) { // the second half is different
            // search in the second half since we can discard the first as
            // "n" has already been compared with mid
            // e.g {2, 2, 2, 3, 4, 2}
            //duplicates will make this more of a O(n) solution than O(lgn)
            return searchInSortedRotatedArray(arr, mid+1, end, n);
        } else {
            // search both the halves
            int result = searchInSortedRotatedArray(arr, start, mid-1, n);
            if (result == -1) {
                return searchInSortedRotatedArray(arr, mid+1, end, n);
            }
            return result;
        }
    }
    return -1;
}

int gcd(int a, int b)
{
    if (a==0) {
        return b;
    }
    return gcd(b%a, a);
}

int fibonacci(int n)
{
    if (n == 1) {
        return 0;
    } else if (n == 2) {
        return 1;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
    //iterative
    int n1 = 0, n2 = 1;
    if (n >= 1) {
        cout << n1 << endl;
    }
    if (n >= 2) {
        cout << n2 << endl;
    }
    for (int i = 0; i < n-2; i++) {
        next = n1 + n2;
        cout << next << endl;
        n1 = n2;
        n2 = next;
    }
    cout << endl;
    //just return the "nth" fibonacci
    //returns {0,1,1..} for n starting from '0'.
    int n1 = 0, n2 = 1;
    if (n == 0) return n1;
    if (n == 1) return n2;
    for (int i = 2; i < n; i++) {
        int next = n1 + n2;
        n1 = n2;
        n2 = next;
    }
    return (n1+n2);
    //returns {1,1,2..} for n starting from '0'.
    int n1 = n2 = 1;
    if (n == 0 || n == 1) {
        return 1;
    }
    int next = 0;
    for (int i = 2; i <= n; i++) {
        next = n1 + n2;
        n1 = n2;
        n2 = next;
    }
    return next;
}

int factorial(int n)
{
    if (n == 0) {
        return 1;
    }
    return factorial(n-1)*n;
    
    //iterative
    int result = 1;
    while (n) {
        result *= n;
        n--;
    }
    return result;
}

//check if a number is a palindrome
bool isPalindrome(int x)
{
    if (x < 0) return false;

    //in the solution below, be wary of overflows and
    //make use a bigger type like long long
    //reverse the no and find the diff between the original no and reversed
    int rev = 0;
    int num = x;
    while (num != 0) {
        rev = rev*10 + num%10;
        num = num/10;
    }
    return ((x-rev) == 0) ? true : false;

    //alternative soln: with no extra space
    //compare the first and last digits, if same, chop off and compare the ends
    int div = 1;
    while (x/div > 10) {
        div *= 10;
    }
    while (x != 0) {
        int l = x/div;
        int r = x%10;
        if (l != r) return false;
        x = (x % div)/10; //chop off digits from either end
        div /= 100;
    }
    return true;
}

int strToInt(char* arr, int size)
{
    bool isNeg = false;
    if (arr[0] == '-') {
        isNeg = true;
    }
    int num = 0;
    for (int i = (isNeg) ? 1 : 0; i < size; i++) {
        num = num*10 + (arr[i]-'0');
    }
    if (isNeg) {
        num = num * -1;
    }
    return num;
}

void intToStr(int num, char* str)
{
    bool isNeg = false;
    if (num < 0) {
        num *= -1;
        isNeg = true;
    }
    char temp[64+2];
    int i = 0;
    do {
        temp[i++] = (num%10) + '0';
        num = num/10;
    } while (num);
    if (isNeg) temp[i++] = '-';

    int j = 0;
    i = strlen(temp);
    while (i > 0) {
        str[j++] = temp[--i];
    }
    str[j] = '\0';
}

bool isDigit(char d)
{
    return (d >= '0' && d <= '9');
}

bool isNumber(char* str)
{
    
}

//time complexity: O(n log k): k sorted lists with n items in total
void mergeKSortedArrays(vector<int>* arr, int k)
{
    vector<int>::iterator* itr = new vector<int>::iterator[k]; //array of vector iterators
    IndexedMinPQ pq(k);
    
    //insert the first element from all of the arrays into the priority queue
    for (int i = 0, itr[i] = arr[i].begin(); i < k; i++) {
        if (itr[i] != arr[i].end()) {
            pq.insert(i, *itr[i]);
            itr[i]++;
        }
    }
    
    while (!pq.empty()) {
        cout << pq.minKey();
        int index = pq.delMin();
        if (itr[index] != arr[index].end()) {
            pq.insert(index, *itr[index]);
            itr[index]++;
        }
    }
}

/**
 * Implement a method which takes an integer array and returns an integer array (of equal size) in
 * which each element is the product of every number in the input array with the exception of the
 * number at that index.
 *
 * Example:
 *   [3, 1, 4, 2] => [8, 24, 6, 12]
 */

void selfExcludingProduct(int* arr, int size)
{
    int count = 0; //count of no. of zeros
    int product = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            product *= arr[i];
        } else {
            count++;
            if (count == 2) {
                product = 0;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (count == 1) {
            arr[i] = (arr[i] == 0) ? product : 0;
        } else if (count == 0) {
            arr[i] = product/i;
        } else {
            arr[i] = 0;
        }
    }
}

double powerOfUtil(double b, int a)
{
    if (a == 0 || b == 1) {
        return 1;
    }
    if (a == 1 || b == 0) {
        return b;
    }
    double t = powerOfUtil(b, a/2);
    double res = t*t;
    return ((a%2==0) ? res : b*res);
}

double pow(double b, int a)
{
    if (a < 0) {
        return 1/powerOfUtil(b,-a);
    } else if (b < 0) {
        if (a%2 == 0) {
            return powerOfUtil(-b,a);
        } else {
            return -(powerOfUtil(-b,a));
        }
    }
}

//Find the self excluding sum without using the "-" operator
void selfExcludingSum(int* arr, int size)
{
    //maintain 2 arrays of same size one working forward and the other working backward
    //forward[i] = sum(0..i) and reverse[i] = sum(end..i+1)
    //Update arr[i] = sum(forward[i-1] and reverse[i-1])
    
    //To get a negative number -- take 2's complement
    //arr[i] = totalSum+(~arr[i]+1)
    
    //two's complement
    // 8 => 0000 1000
    // ~8 => 1111 0111
    // add 1 => 1111 1000
}


//finding the most repeated element in an array given the size of the array (n) and the range of elements
//{0...k} k <= n

//Solution 1: sort the elements and duplicates will get moved close by. Just count
//the repeats and the return the one with the maximum
//Solution 2: Maintain a indexed max priority queue of size "k+1" and insert all the elements (element, count)
// if contains(i) returns true, invoke increaseKey() or just insert the element
//Call delMax() - returns the index of the element with the max repeats
//Count arr[k] for count[arr[i]]++ - O(k) space
//arr[arr[i]%k] += k, the index with the max value is the most repeated element

// Given a unsorted array of intergers an a range of (1...n), how will you find the
// missing element and a duplicate? What if its sorted?
// Solution: sorted - use BS and unsorted find the sum and the original expected sum.
// The difference is the missing element. Find abs diff and that will tell you the duplicate element.




// Given an array, find the maximum difference between two array elements given the second
// element when finding the difference comes after the first.
// For example: array = [1,2,3,4,5,6,7]
// We can take the difference between 2 and 1 (2-1), but not the different between 1 and 2 (1-2).
// Another example: [1,5,8,7,9,-5,15,21] => maxDiff = 26 {-5, 21}
// Alternative way of asking the same problem: "Best time to buy and sell stock"
// Say you have an array for which the ith element is the price of a given stock on day i.
// If you were only permitted to buy one share of the stock and sell one share of the stock,
// design an algorithm to find the best times to buy and sell.
void findMaxDiff(int* arr, int size, int& min, int& max)
{
    if (arr == NULL || size <= 1) {
        return;
    }
    min = 0; max = 1; // index of the minimum and maximum value seen so far
    int maxDiff = arr[max] - arr[min];
    for (int i = 1; i < size; ++i) {
        int diff = arr[i] - arr[min]
        if (diff > maxDiff) {
            maxDiff = diff;
            max = i;
        }
        if (arr[i] < arr[min]) {
            min = i;
        }
    }
    cout << "Max Diff: " << maxDiff << endl;
}

/* Given a set of n people, find the celebrity.
 * Celebrity is a person who:
 * 1. Knows only himself and no one else
 * 2. Every one else knows this person

 * You are given the following helper function:
 * bool knows(i, j);
 * Returns:
 * True: if i knows j
 * False: otherwise
 */
// Assumption that there is only one celebrity
int findCelebrity(int* arr, int size)
{
    int c = 0;
    // Consider A, B, C
    // if A knows B, A is not celebrity else B is not
    for (int i = 1; i < size; ++i) {
        if (knows(arr[c], arr[i])) {
            if (!knows(arr[i], arr[c])) {
                c = i;
            } else {
                c = ++i; // celebrity is not either A or B; set it to C
            }
        }
    }
    if (c == -1 || c >= size) {
        cout << "No Celebrity" << endl;
        return c;
    }
    // Need to confirm if anyone everyone else knows c and c does not know anyone
    for (int i = 0; i < size; ++i) {
        if (i == c) continue; // since knows(i, i) will be true
        if (!knows(arr[i], arr[c]) || knows(arr[c], arr[i])) {
            c = -1;
            break;
        }
    }
    return c;
}

/*
 Given two strings, return boolean True/False, if they are only one edit apart.
 Edit can be insert/delete/update of only one character in the string.
 Eg: -True
 xyz,xz
 xyz, xyk
 xy, xyz
 -False
 xyz, xyz
 xyz,xzy
 x, xyz
 */
bool edit(string s1, string s2)
{
    if (s2.length() < s1.length()) {
        return edit(s2, s1);
    }
    if (s1.length() + 1 < s2.length()) {
        return false;
    }
    //invariant: s1.size() (one)<= s2.size()
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            if (s1.size() == s2.size()) {
                return s1.substr(i+1) == s2.substr(i+1);
            } else {
                return s1.substr(i) == s2.substr(i+1);
            }
        }
    }
    return s1.length() != s2.length();
}

//Input: A list of points in 2-dimensional space, and an integer k
//Output: The k input points closest to (5, 5), using Euclidean distance
//Solution: Compute the euclidean distance of all the points to (5,5) and insert them
//into the Indexed MIN priority queue. delMin() will return the item with
//the least distance to (5,5).

//Category: DNF: http://en.wikipedia.org/wiki/Dutch_national_flag_problem
//Given an array find an efficient way to sort the list into {high, med, low}
//Maintain a pointer for the high and low position and keep swapping.. middle elements
//will naturally be of mid category
void sortPriority(char* priorities)
{
    int cur = 0, high = 0, low = strlen(priorities)- 1;
    char temp;
    while (cur < low) {
        if (priorities[cur] == 'H') {
            if (cur == high) {
                cur++; high++;
                continue;
            }
            temp = priorities[high];
            priorities[high] = priorities[cur];
            priorities[cur] = temp;
            high++;
        } else if (priorities[cur] == 'L') {
            temp = priorities[low];
            priorities[low] = priorities[cur];
            priorities[cur] = temp;
            low--;
        } else {
            cur++;
        }
    }
}

//Sliding window maximum
//http://articles.leetcode.com/2011/01/sliding-window-maximum.html
//Soln 1: Indexed max priority queue and
//Soln 2: double-ended queue(deque,http://en.wikipedia.org/wiki/Double-ended_queue#Applications)
//Soln 3: Using a regualr queue implementation that supports pop_front(), push_back()
//        and getMax()/getMin() - achieved using 2 queues
//b[i] stores the max value from arr[i..i+w-1]
void slidingWindowMax(int *arr, int size, int w, int* b)
{
    //using indexed max priority queue
    IndexedMaxPQ pq;
    for (int i = 0; i < w; i++) {
        pq.insert(i, arr[i]);
    }
    for (int i = w; i < size; i++) {
        b[i-w] = pq.maxKey();
        pq.delete(i-w);
        pq.insert(i, arr[i]);
    }
    b[size-w] = pq.maxKey();

    //using deque
    //Add the new element onto the back and pop off the element
    //in the left edge from the front
    //challenge: make sure the largest element always is at the front
    deque<int> q; // store the indices
    for (int i = 0; i < w; i++) {
        while (!q.empty() && arr[i] >= arr[q.back()]) {
            //remove redundant elements from the queue
            //q.g [10, 5, 3] and new element is '11'. No need to maintain 10,5,3
            q.pop_back();
        }
        q.push_back(i);
    }
    for (int i = w; i < size; i++) {
        b[i-w] = arr[q.front()];
        while (!q.empty() && arr[i] >= arr[q.back()])
            q.pop_back();
        while (!q.empty() && q.front() <= i-w)
            q.pop_front();
        q.push_back(i);
    }
    b[n-w] = arr[q.front()];
}

//find the intersection of 2 sorted arrays - finding common elements between the 2 sorted arrays
//Time complexity O(n+m)
void intersection(int* a, int m, int* b, int n)
{
    int i = 0; j = 0;
    while (i < m && j < n; ) {
        if (a[i] < b[j]) {
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else {
            cout << a[i] << endl;
            i++; j++;
        }
    }
}

//Running median (incoming stream of data)
//Stratergy is to be able to retrieve the middle element and the one before
//(for even no. of elements) in O(1) time
void insertNumber(int num)
{
    if (maxHeap.isEmpty()) {
        maxHeap.insert(num);
        return;
    }
    if (num <= maxHeap.getMax()) {
        maxHeap.insert(num);
    } else {
        minHeap.insert(num);
    }
    int min = minHeap.size();
    int max = maxHeap.size();
    if (min == max || (max > min && (max-min == 1))) {
        return;
    }
    if (max > min) {
        minHeap.insert(maxHeap.getMax());
        maxHeap.delMax();
    } else {
        maxHeap.insert(minHeap.getMin());
        minHeap.delMin();
    }
}
int getRunningMedian(int* arr, int size)
{
    minPQ minHeap;
    maxPQ maxHeap;
    if (maxHeap.isEmpty()) {
        return 0;
    }
    if (maxHeap.size() == minHeap.size()) {
        return (maxHeap.getMax()+minHeap.getMin())/2;
    } else {
        return maxHeap.getMax();
    }
}

//in-place palindrome check
bool isPalindrome(string s)
{
    if (str.length() <= 1) {
        return true;
    }
    return isPalindromeUtil(s, 0, s.length());
}
bool isPalindromeUtil(string str, int start, int end) {
    
    if (start >= end) {
        return true;
    }
    return (str.at(start) == str.at(end) &&
            isPalindromeUtil(str.substring(start + 1, end - 1), start + 1, end - 1) );
}

//alternate version
bool isPalindrome(char* arr, int size)
{
    if (size == 0 || arr == nullptr) {
        return false;
    }
    for (int i = 0, j = size-1; i < j; i++, j--) {
        if (arr[i] != arr[j]) {
            return false;
        }
    }
    return true;
}

//Reverse polish notation (postfix notation): maintain a stack; as soon as you see an operand,
//pop the top 2 elements off the stack. Think about sqrt() which takes only one operand.


//Prime factorization
void primeFactors(long int num)
{
    vector<int> factors;
    while (num % 2 == 0) {
        factors.push_back(2);
        num /= 2;
    }
    //odd prime factors
    for (int i = 3; i < sqrt(num); i = i + 2) {
        while (num % i == 0) {
            factors.push_back(i);
            num /= i;
        }
    }
    //what if the given num is prime > 2?
    if (num > 2) {
        factors.push_back(num);
    }
}

//Pascal's triangle
void printPascal(int n)
{
    int arr[n][n]; // An auxiliary array to store generated pascal triangle values
    
    // Iterate through every line and print integer(s) in it
    for (int line = 0; line < n; line++) {
        // Every line has number of integers equal to line number
        for (int i = 0; i <= line; i++) {
            // First and last values in every row are 1
            if (line == i || i == 0) {
                arr[line][i] = 1;
            } else {// Other values are sum of values just above and left of above
                arr[line][i] = arr[line-1][i-1] + arr[line-1][i];
            }
            printf("%d ", arr[line][i]);
        }
        printf("\n");
    }
}

//https://github.com/checkcheckzz/coding-questions#array
//1. Given two arrays, find elements that are in the first array but not in the second
//2. Detect cycle in an array
//3. Length of the first sub-array that sums to zero
//4. Given n points on a two-dimensional plane, find the closest (euclidean distance) k points
//to the point (0, 0).

int main(int argc, char* argv[])
{
    char test[] = "healo$erd$@";
    cout << "hasUniqueCharacters returned " << hasUniqueCharacters(test) << endl;

    reverse(test);

    char test2[] = "I am janani ";
    char test3[] = "Iamjanani";
    string res = isPermutation(test2, test3) ? "" : "not ";
    cout << "\"" << test3 << "\"" << " is " << res << "a permutation of " << "\"" << test2 << "\"" << endl;

    char replace[12] = {'I', ' ', 'a', 'm', ' ', 'j', 'a', 'n', 'a', 'n', 'i', '\0'};
    replaceSpaces(replace, sizeof(replace));
    cout << replace << endl;

    char teststring[] = "aaaabfcdeeff";
    cout << "RunLenghth of " << teststring << " : " << runLength(teststring);

    char[] s1 = "waterbottle";
    char[] s2 = "erbottlewat";
    cout << s2 << "is rotation of " << s1 << "? : " << isRotation(s1, s2);

    return 0;
}
