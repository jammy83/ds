//
//  stringSearching.cpp
//  
//
//  Created by Janani Natarajan on 12/19/14.
//
//

#include iostream

//Group strings that are anagrams: given an array of strings
//Sort every string and put it in a hash table. Since the string is sorted,
//anagrams will hash to the same value and will be chained together.

//How to sort a given string. if assuming only ascii chars are involved, keep a char count walking the string.
//Then walk the count array adding chars in order

//How to check if one string is a anagram of another - check one is a permutation of the other - solved already



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
        // pattern has a smaller char compared to mid point
        return searchStrings(arr, start, mid-1, pattern);
    } else {
        return searchStrings(arr, mid+1, end, pattern);
    }
}


