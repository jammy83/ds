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
//3way string quciksort is the solution -- Robert Sedgewick

//How to check if one string is a anagram of another -
//check one is a permutation of the other - solved already

//KMP - pattern matching
//construct the prefix function
// lps - longest prefix of the pattern which is also a valid suffix of itself
// lps[i] represents the no. of chars in the suffix that map to a valid prefix
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
    int mid = (start+end)/2;
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
    int size = 64; // 2*26alphabets(lower and upper case)
    int a1[size];
    int a2[size];
    int len = strlen(str1);
    int encode1[len];
    int encode2[len];

    for (int i = 0; i < size; i++) {
        a1[i] = a2[i] = -1;
    }

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
