//
//  stringSearching.cpp
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#include <iostream>

using namespace std;

//Group strings that are anagrams: given an array of strings
//Sort every string and put it in a hash table. Since the string is sorted,
//anagrams will hash to the same value and will be chained together.

//How to sort a given string? if assuming only ascii chars are involved, all
//comparisons can be performed like integers and so can use any of the sorting algos
//3way string quicksort is the solution -- Robert Sedgewick

//How to check if one string is a anagram of another -
//check one is a permutation of the other - solved already

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

// Replaces space with "%20"
//in-place replacement with the assumption that the input string
//is wide enough to hold the size after replacement
void replaceSpaces(char* str, int size)
{
    if (str == NULL) {
        return;
    }
    //walk the string to find the no. of occurrences of replace char
    int count = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) { // or until char *pStr = str; *pStr != '\0' or *pStr
        if (str[i] == ' ') {
            count++;
        }
    }
    int j = len + count * 2 + 1; // new length of the string including a null char
    if (size < j) {
        cout << "Can't replace spaces. Insufficient space\n";
        return;
    }
    str[--j] = '\0'; //--j is the new index
    for (int i = len; i >= 0; i--, j--) {
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

//String in-place replacement
//replace all the occurrences of a given pattern(="abc") to 'X' and note that contiguous
//occurrence should be replaced only once
//Going from 3 chars to one. So can start replacing from the beginning since it won't
//over-write characters
bool isMatch(char* str, const char* pattern) {
    while (*str && *pattern) {
        if (*str++ != *pattern++) {
            return false;
        }
    }
    if (*pattern) {
        return false;
    }
    return true;
}
void replace(char* str, const char* pattern)
{
    if (str == NULL || pattern == NULL) {
        return;
    }
    char *pSlow = str, *pFast = str;
    int pLen = strlen(pattern);
    
    while (*pFast != '\0') {
        bool matched = false;
        while (isMatch(pFast, pattern)) {
            pFast += pLen;
            matched = true;
        }
        if (matched) {
            *pSlow++ = 'X';
        } else if (*pFast != '\0') {
            *pSlow++ = *pFast++;
        }
    }
    
    *pSlow = '\0'; // terminate with a null char
}

//remove all spaces in a given string
void removeSpace(char* str)
{
    if (str == NULL || !*str) {
        return;
    }
    char *p1 = str, *p2 = str;
    while (*p2) {
        while (*p2 == ' ') {
            p2++;
        }
        *p1++ = *p2++;
    }
}

//find a given pattern within a string
int strstr(char* haystack, char* needle)
{
    if (needle == NULL) { //null string
        return NULL;
    }
    if (!*needle) { //empty string
        return haystack;
    }
    char *p1 = haystack;
    while (*p1) {
        char *p1Begin = p1, *p2 = needle;
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (!*p2) {
            return p1Begin;
        }
        p1 = p1Begin + 1;
    }
    return NULL;
}

//KMP - pattern matching
//construct the prefix function
//lps - longest prefix of the pattern which is also a valid suffix of itself
//lps[i] represents the no. of chars in the suffix that map to a valid prefix

void computePrefixFunction(char* pattern, int size, int* lps)
{
    if (pattern == NULL || size == 0 || lps == NULL) {
        return;
    }
    lps[0] = 0; // no prefix to match before
    // i -- suffix pointer; starts at second char
    // j -- prefix pointer; start at zero. 'lps' is count of no. of
    // prefix chars matched so far
    for (int i = 1, j = 0; i < size; ) {
        if (pattern[i] == pattern[j]) {
            lps[i++] = ++j;
        } else {
            if (j == 0) { //no chars matched so far
                lps[i++] = 0;
            } else {
                j = lps[j-1];
                // for e.g) AAACAAAA, to compute lps[7], slide along in the pattern and
                // compare pattern[7] with pattern[lps[j-1]] to basically find out if there
                // is any overlap which would set lps[7] to non-zero.
            }
        }
    }
}

//search for the pattern
void KMPSearch(char* txt, char* pattern)
{
    if (txt == NULL || pattern == NULL) {
        return;
    }
    int n = strlen(txt);
    int m = strlen(pattern);
    int* lps = new int[m];
    if (lps == NULL) {
        return;
    }
    computePrefixFunction(pattern, m, lps);
    //i - txt pointer; j - pattern pointer
    for (int i = 0, j = 0; i < n; ) {
        if (txt[i] == pattern[j]) {
            i++; j++;
            if (j == m) {
                cout << "Found pattern at index: " << i-j << endl;
                j = lps[j-1];
            }
        } else {
            if (j == 0) {
                i++;
            } else {
                j = lps[j-1];
            }
        }
    }
    delete[] lps;
}

//Given an array of strings that is sorted which contains some empty strings as well,
//serach for a given string
int searchStrings(std::string* arr, int start, int end, string pattern)
{
    if (arr == NULL || size == 0 || pattern.empty()) {
        return -1;
    }
    int mid = start + (end-start) / 2; // avoids overflow
    if (arr[mid].empty()) {
        // try to find a non-empty element
        for (int i = mid-1, j = mid+1; i >= start && j <= end; i--, j++) {
            if (!arr[i].empty()) {
                mid = i;
                break;
            } else if (!arr[j].empty()) {
                mid = j;
                break;
            }
        }
    }
    if (arr[mid].compare(pattern) == 0) {
        return mid;
    } else if (arr[mid].compare(pattern) < 0) { //arr[mid] - compared str and pattern is comparing str
        // arr[mid] has a smaller char compared to pattern
        return searchStrings(arr, mid+1, end, pattern);
    } else {
        return searchStrings(arr, start, mid-1, pattern);
    }
}

void reverseString(char* str, int start, int end)
{
    for (int i = start, j = end; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

//Reverse words in a string
void reverseWords(char* str)
{
    int len = strlen(str);
    //reverse the entire string
    reverseString(str, 0, len-1);
    
    for (int i = 0; i < len; ++i) {
        int start, end;
        start = end = i;
        while (str[i] != ' ' && i < len) {
            i++;
        }
        end = i - 1;
        reverseString(str, start, end);
    }
}

//Check if 2 strings are isomorphic abb --> xyy and not yxy or yyx
bool isomorphic(char* str1, char* str2)
{
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    int size = 256; // ascii characters(lower and upper case)
    int a1[size];
    int a2[size];
    int len = strlen(str1);
    int encode1[len];
    int encode2[len];

    for (int i = 0; i < size; i++) {
        a1[i] = a2[i] = -1;
    }

    //associate an index value with each alphabet and look at the encoding
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (a1[str1[i]] == -1) {
            a1[str1[i]] = index++;
        }
        encode1[i] = a1[str1[i]];
    }
    index = 0;
    for (int i = 0; i < len; i++) {
        if (a2[str2[i]] == -1) {
            a2[str2[i]] = index++;
        }
        encode2[i] = a2[str2[i]];
    }
    
    for (int i = 0; i < len; i++) {
        if (encode1[i] != encode2[i]) {
            return false;
        }
    }
    return true;
}

int wordCount(char* str)
{
    if (str == NULL || !*str) {
        return 0;
    }
    char *p = str;
    while (*p) {
        while (*p != ' ' && isalpha(*p)) {
            p++;
        }
        count++; p++;
    }
    return count;
}

//tokenzier
//    std::string s = "scott>=tiger";
//    std::string delim = ">=";
void splitString(string line, string delim) {
    size_t start = 0U;
    size_t end = s.find(delim);
    while (end != std::string::npos) {
        std::cout << s.substr(start, end - start) << std::endl;
        start = end + delim.length();
        end = s.find(delim, start);
    }
    std::cout << s.substr(start, end);
}




