//
//  arrays.cpp
//  
//
//  Created by Janani Natarajan on 11/20/14.
//
//

#include <iostream>
#include <string.h>

using namespace std;

bool hasUniqueCharacters(char* str)
{
    // Assuming ASCII characters alone are used in the given
    // string. There are 128 ascii chars including lower and upper case
    // alphabets, decimal [0-9], special characters (@,$, space char...),
    // arithmetic operators.
    if (str == NULL || strlen(str) > 128) {
        return false;
    }
    // strlen(str) returns the length of the string excluding the null char
    int alpha[256] = {}; // bool alpha[256] = {} .. initializes to false
    for (int i = 0; i < strlen(str); i++) {
        alpha[str[i]]++; // you need to first increment and then check
        if (alpha[str[i]] > 1) {
            return false;
        }
        /* if the array just stores whether the char was seen before or not
        if (alpha[str[i]]) {
            return false;
        }
        alpha[str[i]] = true;
        */
        
    }
    return true;
}

// Reveres a given string
void reverse(char* str)
{
    if (str == NULL) {
        return;
    }
    for (int i = 0, j = strlen(str)-1; i < j; i++, j--) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    cout << "String reversed: " << str << endl;
}

// find if str2 is a permutation of str1
// Same logic can be used to check if str2 is an anagram of str1
// anagrams are meanigful words formed by using the same chars from str1
// and this means its a permutation of the str1 that's also a dict word
bool isPermutation(char* str1, char* str2)
{
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    // 1. Sort both the strings and compare. They should match exactly
    // 2. Compare chars from str1 against str2 - O(n^2).
    // 3. Build a hash table with the chars from str1 as keys
    // Lookup the chars from str2 and all the lookups should succeed.
    /*
    for (int i = 0; i < strlen(str1); i++) {
        hashTable.insert(str1[i]);
    }
    for int i = 0; i < strlen(str2); i++) {
        if (hashTable.lookup(str2[i]) == false) {
            cout << str2 << "is not a permutation of str1" << endl;
            return false;
        }
    }*/
    // 4. Check if the 2 strings have identical char counts
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    int counts[256] = {};
    for (int i = 0; i < strlen(str1); i++) {
        counts[str1[i]]++;
    }
    for (int i = 0; i < strlen(str2); i++) {
        if (--counts[str2[i]] < 0) {
            return false;
        }
    }
    return true;
}

// Replaces space with "%20"
void replaceSpaces(char* str, int size)
{
    if (str == NULL) {
        return;
    }
    //walk the string to find the no. of occurrences of replace char
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            count++;
        }
    }
    int j = strlen(str) + count * 2 + 1; // new length of the string including a null char
    if (size < j) {
        cout << "Can't replace spaces. Insufficient space\n";
        return;
    }
    str[--j] = '\0'; //--j is the new index
    for (int i = strlen(str); i >= 0; i--, j--) {
        if (i == j) {
            break;
        }
        if (str[i] == ' ') {
            str[j--] = '0';
            str[j--] = '2';
            str[j] = '%';
        } else {
            str[j] = str[i];
        }
    }
}

// Compute run length and compress the given string
int computeCompressedLength(char* str)
{
    if (str == NULL) {
        return 0;
    }
    char last = str[0];
    int count = 1;
    int size = 0;
    for (int i = 1; i < strlen(str); i++) {
        if (str[i] == last) {
            count++;
        } else {
            char tmp[65];
            snprintf(tmp, sizeof(tmp), "%d", count);
            size += 1 + strlen(tmp);
            count = 1;
            last = str[i];
        }
    }
    char tmp[65];
    snprintf(tmp, sizeof(tmp), "%d", count);
    size += 1 + strlen(tmp);
    return size;
}

char* runLength(char* str)
{
    if (str == NULL) {
        return NULL;
    }
    int newlen = computeCompressedLength(str);
    if (newlen == 0) {
        return NULL;
    } /* else if (newlen >= strlen(str)) {
        return str;
    }*/
    cout << "The length of the compressed string would be " << newlen << endl;
    char* cstr = new char[newlen];
    if (cstr == NULL) {
        return NULL;
    }
    char last = str[0];
    int count = 1;
    for (int i = 1; i < strlen(str); i++) {
        if (last == str[i]) {
            count++;
        } else {
            snprintf(cstr+strlen(cstr), newlen, "%c%d", last, count);
            count = 1;
            last = str[i];
        }
    }
    snprintf(cstr+strlen(cstr), newlen, "%c%d", last, count);
    cstr[newlen] = '\0';

    return cstr;
}

bool isRotation(char* str1, char* str2)
{
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    string s2(str2);
    size_t found = (s2+s2).find(str1);
    if (found != string::npos) {
        return true;
    }
    return false;
}

void zeroing2DMatrix(int** matrix, int n, int m)
{
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (matrix[i][j] = 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        if (matrix[0][i] == 0) {
            for (int j = 0; j < n; j++) {
                matrix[j][i] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (matrix[i][0] == 0) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = 0;
            }
        }
    }
}

void rotateByChars(int* arr, int size, int d)
{
    int i = 0, j = d;
    while (i < size - (d%size)) { // "d" elements are going to get displaced and get placed at the back
        int temp = arr[i];
        arr[i++] = a[j];
        a[j++] = temp;
    }
}

int max(int a, int b)
{
    return (a >= b) ? a : b;
}
int min(int a, int b)
{
    return ( a <= b) ? a : b;
}
int getMedian(int* arr, int size)
{
    if (arr == NULL) {
        return 0;
    }
    return (size%2 == 0) ? (arr[n/2-1]+arr[n/2])/2 : arr[n/2];
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
    // have even no. of elements. Median is the avg of middle and the next element.
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
    int last_l, last_r, last_diff;
    last_l = last_r = last_diff = -1;
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
    last_l = last_r = last_diff = -1;
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
    int mid = (start+end)/2;
    if (arr[mid] == n) {
        return mid;
    }
    if (n < arr[mid]) {
        binarySearch(arr, start, mid-1, n);
    } else {
        binarySearch(arr, mid+1, end, n);
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
    
    int mid = start+end/2;
    if (arr[mid] == n) {
        return mid;
    }
    if (arr[start] <= arr[mid-1]) {
        // sorted half
        if (arr[start] >= n && n <= arr[mid-1]) {
            // search in this half
            return binarySearch(arr, start, mid-1, n);
        } else {
            return searchInSortedRotatedArray(arr, mid+1, end, n);
        }
    } else if (arr[mid+1] <= arr[end]) {
        // sorted half
        if (arr[mid+1] >= n && n <= arr[end]) {
            return binarySearch(arr, mid+1, end, n);
        } else {
            return searchInSortedRotatedArray(arr, start, mid-1, n);
        }
    } else if (arr[start] == arr[mid]) { // handles duplicates with the left half containing the same elements
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
}

int factorial(int n)
{
    if (n == 0) {
        return 1;
    }
    return factorial(n-1)*n;
    
    //iterative
    int result = 1;
    while (n >=1) {
        result *= n;
        n--;
    }
    return result;
}

//check if a number is a palindrome
bool isNumPalindrome(int x)
{
    //reverse the no and find the diff between the original no and reveresed
    int rev = 0;
    int num = x;
    while (num > 0) {
        rev = rev*10 + num%10;
        num = num/10;
    }
    return ((x-rev) == 0) ? true : false;
}

int strToInt(char* arr, int size)
{
    bool isNeg = false;
    if (arr[0] == '-') {
        isNeg = true;
    }
    int num = 0;
    for (int i = 1; i < size; i++) {
        num = num*10;
        num += (arr[i]-'0');
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
    do {
        temp[i++] = (num%10) + '0';
        num = num/10;
    } while (num);
    if (isNeg) temp[i++] = '-';
    
    int j = 0;
    while (i > 0) {
        str[j++] = temp[--i];
    }
    str[j] = '\0';
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
    int product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = product/i;
    }
}

double powerOf(double b, int a)
{
    
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

