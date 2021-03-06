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

//1
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

// 2: find if str2 is a permutation of str1
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

//3
bool isPermutation(string s1, string s2)
{
    if (s1.empty() || s2.empty() || s1.length() != s2.length()) {
        return false;
    }
    map<char, int> hashMaps1;
    map<char, int>::const_iterator itr;
    for (int i = 0; i < s1.length(); i++) {
        if ((itr = hashMaps1.find(s1[i])) != hashMaps1.end()) {
            itr->second++;
        } else {
            hashMaps1[s1[i]] = 1;
        }
    }
    for (int i = 0; i < s2.length(); i++) {
       itr = hashMaps1.find([s2[i]]);
       if (itr == hashMaps1.end() || --itr->second < 0) {
           return false;
       }
    }
    return true;
}

// 4: Replace space with %20
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

// 5: Compute run length and compress the given string
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
            itr->second++;
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

// 6
bool isRotation(string s1, string s2)
{
    if (s1.empty() || s2.empty() || s1.length() != s2.length()) {
        return false;
    }
    return ((s2+s2).find(s1) != string::npos);
}

//7
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

//8
void reverseIntArray(int* arr, int start, int end)
{
    for (int i = start, j = end; i < j, i++, j--) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// 9: rotate elements to the right
void rotate(vector<int>& nums, int k) {
    if (k < 0 || nums.empty()) {
        return;
    }
    int r = nums.size() < k ? k % nums.size() : k;
    for (int i = 0; i < r; i++) {
        int j = nums.size()-1;
        int temp = nums[j];
        for (; j >= 0; j--) {
            nums[j] = nums[j-1];                
        }
        nums[0] = temp;
    }
}

void rotateArray(int* arr, int size, int d)
{
    if (arr == nullptr || size == 0) {
        return;
    }
    // reverse the array
    reverseIntArray(arr, 0, d-1);
    reverseIntArray(arr, d, size-1);
    reverseIntArray(arr, 0, size-1);
    // juggling .. using gcd(size, d)
}

// 10: Remove all instance of a value in a given array and return the new length; order change is fine.
// Sort and remove instances and compact
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[j++] = nums[i];
            }
        }
        return j;
    }
};

// 11: Remove duplicates from a sorted array in-place and return the new length
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int wIndex = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[wIndex - 1]) {
                nums[wIndex++] = nums[i];    
            }
        }
        return wIndex;
    }
};

// 12: Min size contiguous sub-array sum with only positive integers >= to a target value
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int sum = 0, len = INT_MAX, start = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum > s) {
                while (sum > s && start < i) {
                    sum -= nums[start++];
                }
                if (sum < s) {
                    sum += nums[--start];
                }
            }
            if (sum >= s) {
                len = min(len, i-start);
            }
        }
        return len == INT_MAX ? 0 : len+1;
    }
};

// 13: Maximum contiguous sub-array sum
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int start = 0, maxSum = nums[0], runningSum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] >= runningSum + nums[i]) {
                start = i;
                runningSum = nums[i];
            } else {
                runningSum += nums[i];
            }
            if (runningSum > maxSum) {
                maxSum = runningSum;
            }
        }
        return maxSum;
    }
};

// 14: Maximum contiguous sub-array product
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int localMin = nums[0], localMax = nums[0], maxProduct = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > 0) {
                localMin = min(localMin*nums[i], nums[i]);
                localMax = max(localMax*nums[i], nums[i]);
            } else {
                int temp = localMax;
                localMax = max(localMin*nums[i], nums[i]);
                localMin = min(temp*nums[i], nums[i]);
            }
            if (localMax > maxProduct) {
                maxProduct = localMax;
            }
        }
        return maxProduct;
    }
};

// 15: move zeros in a given array to the end maintaining the relative order of the non-zero elements
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return;
        }
        int len = nums.size(), j = 0;
        for (int i = 0; i < len; i++) {
            if (nums[i] == 0) {
                while (i < len && nums[++i] == 0) { }
                if (i < len) {
                    nums[j++] = nums[i]; continue;
                } else {
                    if (nums[0] == 0) return;
                }
                break;
            } else {
                if (i != j) {
                    nums[j] = nums[i];
                }
                ++j;
            }
        }
        while (j < len) {
            nums[j++] = 0;
        }
    }
};

// 16: find the first unique element in a sorted array
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return nums[0];
        }
        for (int i = 0; i < len-1; ) {
            if (nums[i] == nums[i+1]) {
                int dup = nums[i];
                while (++i < len && nums[i] == dup) { }
                if (i == len) {
                    return -1;    
                } else if (i == len-1) {
                    return nums[i];
                }
            } else {
                return nums[i];
            }
        }
        return -1;
    }
};

/*
 * 17: Given an array of integers nums, write a method that returns the "pivot" index of this array.
 * We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.
 * If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index. 
 */
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int len = nums.size();
        if (len == 0 || len == 1) {
            return -1;
        }
        vector<int> fSum; fSum.reserve(nums.size());
        vector<int> rSum; rSum.reserve(nums.size());
        fSum[0] = nums[0];
        rSum[len-1] = nums[len-1];
        for (int i = 1; i < len; i++) {
            fSum[i] = fSum[i-1] + nums[i];
        }
        for (int j = len-2; j >= 0; j--) {
            rSum[j] = rSum[j+1] + nums[j];
        }
        if (rSum[1] == 0) { //spl index 0
            return 0;
        }
        for (int i = 1; i < len-1; i++) {
            if (fSum[i-1] == rSum[i+1]) {
                return i;
            }    
        }
        if (fSum[len-2] == 0) { //spl index len-2
            return len-1;
        }
        return -1;
    }
};

// 18: Largest Number At Least Twice of Others
class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        if (nums.size() == 1) {
            return 0;
        }
        int sMaxIndex = -1;
        int maxIndex = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[maxIndex]) {
                sMaxIndex = maxIndex;
                maxIndex = i;
            } else if (nums[i] < nums[maxIndex]) {
                if (sMaxIndex == -1 || nums[i] > nums[sMaxIndex]) {
                    sMaxIndex = i;
                }
            }
        }
        if (sMaxIndex != -1 &&
            nums[maxIndex] >= 2*nums[sMaxIndex]) {
            return maxIndex;
        }
        return -1;
    }
};

// 19: Plus one
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        if (digits.empty()) {
            return digits;
        }
        int len = digits.size();
        if (digits[len-1] != 9) {
            digits[len-1]++;
            return digits;
        }
        int i;
        for (i = len-1; i >= 0 && digits[i] == 9; i--) {
            digits[i] = 0;
        }
        if (i >= 0) {
            digits[i]++;
        } else {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

// 20: In a sorted array find a pair of nos that adds up to a certain target value.
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int mid = (numbers.size() - 1) / 2;
        if (numbers[mid] > target) {
            numbers.resize(mid+1);
            return twoSum(numbers, target);
        }
        vector<int> result;
        for (int start = 0, end = numbers.size() - 1; start < end;) {
            int val = numbers[start] + numbers[end];
            if (val > target) {
                end--;
            } else if (val < target) {
                start++;
            } else {
                result.push_back(start+1);
                result.push_back(end+1);
                break;
            }
        }
        return result;
    }
};

// 21: Gn a sorted array and value X, find a pair whose sum is closest to X
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
        int len = numbers.size();
        if (numbers.empty() || len == 1) {
            return result;
        }
        int lastDiff = INT_MAX;
        for (int start = 0, end = len - 1; start < end; ) {
            int sum = numbers[end]+numbers[start];
            int diff = abs(target-sum);
            if (diff < lastDiff) {
                result.clear();
                result.push_back(start+1);
                result.push_back(end+1);
                lastDiff = diff;
            }
            if (sum == target) {
                return result;
            } else if (sum > target) {
                end--;
            } else {
                start++;
            }
        }
        return result;
    }
};

// 22: Merge 2 sorted arrays
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (nums1.capacity() < m+n) {
            return;
        }
        vector<int>::iterator itr;
        int i = 0, j = 0, inserts = 0;
        while (i < m+inserts && j < n) {
            if (nums1[i] <= nums2[j]) {
                i++;
            } else {
                itr = nums1.begin() + i;
                nums1.insert(itr, nums2[j]);
                i++; j++; inserts++;
            }
        }
        while (j < n) {
            itr = nums1.begin() + i;
            nums1.insert(itr, nums2[j]);
            j++; i++;
        }
        nums1.resize(m+n);
    }
};

// 23: Intersection of 2 arrays. The result should only include unique elements.
// Need to filter duplicates so make use of the set but need not be sorted.
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        unordered_set<int> hashMap;
        for (int num : nums1) {
            hashMap.insert(num);
        }
        unordered_set<int> hashMap1;
        pair<unordered_set<int>::iterator, bool> insertRet;
        for (int num : nums2) {
            insertRet = hashMap1.insert(num);
            if (insertRet.second != false &&
                hashMap.find(num) != hashMap.end()) {
                result.push_back(num);
            }
        }
        return result;
    }
};

/*
 * 24: Intersection of 2 arrays - the result need not contain unique elements.
 * What if the given array is already sorted? How would you optimize your algorithm?
 * What if nums1's size is small compared to nums2's size? Which algorithm is better?
 * What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
 * If nums1 is small, hash it and read as much as possible from disk of nums2 and lookup and create the result
 * If both nums1 and nums2 can't be fully loaded into memory, external sort both separately and load and compare since they are both sorted now.
 */
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size(); ) {
            if (nums1[i] < nums2[j]) {
                i++;
            } else if (nums1[i] > nums2[j]) {
                j++;
            } else if (nums1[i] == nums2[j]) {
                result.push_back(nums1[i]);
                i++; j++;
            }
        }
        return result;
    }
};

// 25: Binary search of sorted array looking for a target value
class Solution {
public:
    int getMid(int start, int end) {
        return start + (end - start) / 2;
    }
    int BST(vector<int>& nums, int start, int end, int target) {
        if (start > end) {
            return -1;
        }
        int mid = getMid(start, end);
        if (target == nums[mid]) {
            return mid;
        } else if (target < nums[mid]) {
            return BST(nums, start, mid-1);
        } else {
            return BST(nums, mid+1, end);
        }
    }
}

// Find the first occurrence of an element in a sorted array (with duplicates)
class Solution {
public:
    int getMid(int start, int end) {
        return start + (end - start) / 2;
    }
    int searchFirstOfK(const vector<int>& nums, int k) {
        int start = 0, end = nums.size()-1, result = -1;
        while (start <= end) {
            int mid = getMid(start, end);
            if (k < nums[mid]) {
                end = mid - 1;
            } else if (k == nums[mid]) {
                result = mid;
                end = mid - 1;
            } else {
                start = mid + 1;    
            }
        }
        return result;
    }
};

// search a sorted array for the first element greater than given value
class Solution {
public:
    int searchFirstLargerOfK(vector<int>& nums, int k) {
        int start = 0, end = nums.size()-1, result = -1;
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > k) {
                result = mid;
                end = mid - 1;    
            } else {
                start = mid + 1;
            }
        }
        return result;
    }
};

// search a sorted array of distinct integers for an element equal to its index
class Solution {
public:
    int searchEntryEqualToIndex(vector<int>& nums, int k) {
        int start = 0, end = nums.size() - 1, result = -1;
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > mid) {
                end = mid - 1;
            } else if (nums[mid] == mid) {
                return mid;
            } else {
                start = mid + 1;
            }
        }
        return result;
    }
};

// 26: Search for a min element in a sorted rotated array. Elements are distinct.
class Solution {
public:
    int searchSmallest(vector<int>& nums) {
        int start = 0, end = nums.size() - 1, result = -1;
        while (start < end) {
            int mid = start + ((end - start) / 2);
            if (nums[mid] > nums[end]) {
                start = mid + 1; // min element is between mid + 1 and end.
            } else {
                end = mid;
            }
        }
        return start; // start == end
    }
    // solve the above problem with duplicates
    int searchSmallestWithDups(vector<int>& nums) {
        return searchSmallestWithDups(nums, 0, nums.size() - 1);
    }
    int searchSmallestWithDups(vector<int>& nums, int start, int end) {
        if (start == end) {
            return start;
        }
        int mid = start + ((end - start) / 2);
        if (nums[mid] > nums[end]) {
            return searchSmallestWithDups(nums, mid + 1, end);
        } else if (nums[mid] < nums[end]) {
            return searchSmallestWithDups(nums, start, mid);
        } else {
            int left = searchSmallestWithDups(nums, start, mid);
            int right = searchSmallestWithDups(nums, mid + 1, end);
            return nums[end] < nums[start] ? end : start;
        }
    }
};

// 27: Search for an element in a sorted, rotated array with no duplicates
class Solution {
public:
    int getMid(int start, int end) {
        return start + ((end - start) / 2);
    }
    int searchInSortedRotatedArray(vector<int>& nums, int start, int end, int target) {
        if (start > end) {
            return -1;
        }
        int mid = getMid(start, end);
        if (target == nums[mid]) {
            return mid;
        } else if (nums[start] <= nums[mid]) { // sorted half
            if (target >= nums[start] && target < nums[mid]) {
                return searchInSortedRotatedArray(nums, start, mid-1, target);
            }
            return searchInSortedRotatedArray(nums, mid+1, end, target);
        } 
        // nums[mid..end] is sorted
        if (target > nums[mid] && target <= nums[end]) {
            return searchInSortedRotatedArray(nums, mid+1, end, target);
        }
        return searchInSortedRotatedArray(nums, start, mid-1, target);
    }
    int search(vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        } else if (nums.size() == 1) {
            return nums[0] == target ? 0 : -1;
        } else if (nums.size() == 2) {
            if (nums[0] == target) {
                return 0;
            } else if (nums[1] == target) {
                return 1;
            }
            return -1;
        }
        return searchInSortedRotatedArray(nums, 0, nums.size()-1, target);
    }    
};

// 28: Search in sorted rotated array and handle duplicates
class Solution {
public:
    int getMid(int start, int end) {
        return start + ((end - start) / 2);
    }
    bool searchInSortedRotatedArray(vector<int>& nums, int start, int end, int target) {
        if (start > end) {
            return false;
        }
        int mid = getMid(start, end);
        if (target == nums[mid]) {
            return true;
        } else if (nums[start] < nums[mid]) { // nums[start..mid] is sorted
            if (target >= nums[start] && target < nums[mid]) {
                return searchInSortedRotatedArray(nums, start, mid-1, target);
            }
            return searchInSortedRotatedArray(nums, mid+1, end, target);
        } else if (nums[mid] < nums[end]) { // nums[mid..end] is sorted
            if (target > nums[mid] && target <= nums[end]) {
                return searchInSortedRotatedArray(nums, mid+1, end, target);
            }
            return searchInSortedRotatedArray(nums, start, mid-1, target);
        } else {
            if (nums[start] == nums[mid] && nums[mid] != nums[end]) {
                return searchInSortedRotatedArray(nums, mid+1, end, target);
            } else if (nums[mid] == nums[end] && nums[start] != nums[mid]) {
                return searchInSortedRotatedArray(nums, start, mid-1, target);
            }
            return searchInSortedRotatedArray(nums, start+1, end, target);
        }
    }
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) {
            return false;
        } else if (nums.size() == 1) {
            return nums[0] == target;
        } else if (nums.size() == 2) {
            return (nums[0] == target || nums[1] == target);
        }
        return searchInSortedRotatedArray(nums, 0, nums.size()-1, target);
    }    
};

// 29: Best time to buy and sell stock
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 1) {
            return 0;
        }
        int min = prices[0], maxProfit = 0;
        for (int i = 1; i < prices.size(); i++) {
            int diff = prices[i] - min;
            maxProfit = diff > maxProfit ? diff : maxProfit;
            min = prices[i] < min ? prices[i] : min;
        }
        return maxProfit;
    }
};

// 30: Self excluding product without the use of division
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result;
        if (nums.empty()) {
            return result;
        }
        int len = nums.size();
        vector<int> frontPr, backPr;
        frontPr.reserve(len); backPr.reserve(len); result.reserve(len);
        frontPr[0] = nums[0];
        for (int i = 1; i < len; i++) {
            frontPr[i] = frontPr[i-1] * nums[i]; 
        }
        backPr[len-1] = nums[len-1];
        for (int i = len-2; i >= 0; i--) {
            backPr[i] = backPr[i+1] * nums[i];
        }
        result.push_back(backPr[1]);
        for (int i = 1; i < len-1; i++) {
            result.push_back(frontPr[i-1] * backPr[i+1]);
        }
        result.push_back(frontPr[len-2]);
        return result;
    }
};

// same problem with o(1) space without division/2's complement
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> result(len, 1);
        if (len == 0) {
            return result;
        }
        int frontPr = 1, backPr = 1;
        for (int i = 0; i < len; i++) {
            result[i] *= frontPr;
            frontPr *= nums[i];
            result[len-1-i] *= backPr;
            backPr *= nums[len-1-i];
        }
        return result;
    }
};

// square root of the element
class Solution {
public:
    int squareRoot(int k) {
        int start = 0, end = k;
        while (start <= end) {
            long mid = start + (end - start) / 2;
            long midSquared = mid * mid;
            if (midSquared <= k) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return start - 1;
    }
};

// DNF
class Solution {
public:
    void sortColors(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return;
        }
        int len = nums.size(), start = 0, end = len;
        for (int i = 0; i < end; ) {
            if (nums[i] == 2) {
                int temp = nums[--end];
                nums[end] = nums[i];
                nums[i] = temp;
            } else if (nums[i] == 0) {
                if (start == i) {
                    i++; start++;
                    continue;
                }
                int temp = nums[start];
                nums[start++] = nums[i];
                nums[i] = temp;
            } else {
                i++;
            }
        }
    }
    
    void dnf(int pivot_index, vector<int>& nums) {
        if (nums.empty() || pivot_index < 0 || pivot_index >= nums.size()) {
            return;
        }
        int low = 0, high = nums.size()-1, i = 0;
        while (i < high) {
            if (nums[i] < nums[pivot_index]) {
                swap(nums[i++], nums[low++]);
            } else if (nums[i], nums[pivot_index]) {
                swap(nums[i], nums[high--]);   
            } else {
                i++;
            }
        }
    }
};

// valid palindrome in a string
// "A man, a plan, a canal: Panama" - true; "0P" - false
class Solution {
public:
    void processStr(string& s) {
        for (int i = 0; i < s.size(); ) {
            if (!isalnum(s[i])) {
                s.erase(i, 1);
            } else {
                s[i] = tolower(s[i]);
                i++;
            }
        }
    }
    bool isPalindrome(string s) {
        processStr(s);
        for (int i = 0, j = s.size()-1; i <= j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
};

// Pascal's triangle
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> result;
        if (rowIndex == 0) {
            result.push_back(1);
            return result;
        } else if (rowIndex == 1) {
            result.push_back(1);
            result.push_back(1);
            return result;
        }
        result.push_back(1);
        vector<int> prevRow = getRow(rowIndex-1);
        for (int i = 1; i < rowIndex; i++) {
            result.push_back(prevRow[i] + prevRow[i-1]);
        }
        result.push_back(1);
        return result;
    }
};

// Jump game
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return true;
        }
        set<int> visited;
        pair<set<int>::iterator, bool> itr;
        stack<int> toVisit;
        if (nums[0] >= nums.size()-1) {
            return true;
        }
        toVisit.push(0);
        while (!toVisit.empty()) {
            int index = toVisit.top();
            toVisit.pop();
            int steps = nums[index];
            while (steps > 0) {
                int pos = index + steps;
                if (pos >= nums.size()-1) {
                    return true;
                }
                itr = visited.insert(pos);
                if (itr.second) {
                    toVisit.push(pos);
                }
                --steps;
            }
        }
        return false;
    }
};

// Jump game: O(n) solution
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return true;
        }
        int maxIndexReached = 0;
        for (int i = 0; i <= maxIndexReached && maxIndexReached < nums.size()-1; i++) {
            maxIndexReached = max(maxIndexReached, i + nums[i]);
        }
        return maxIndexReached >= nums.size()-1;
    }
};

// Permute the elements of the array based on the permutation array
// invovles doing a cyclic permutation 
class Solution {
public:
    void doCP(vector<int>& nums, vector<int>& P) {
        for (int j = 0; j < nums.size(); j++) {
            int i = j, val = nums[i];
            while (P[i] >= 0) {
                int index = P[i];
                int tmp = nums[P[i]];
                nums[P[i]] = val; P[i] -= nums.size();
                i = index; val = tmp;
            }
            // restore permutation array
            for (int e : P) {
                e += nums.size();    
            }
        }
    }
};

// Find next permutation - can involve duplicate elements
class Solution {
public:
    /*
     * 1. First find the longest decreasing sequence
     * 2. Swap the index before the longest sequence with the next
          highest from the longest sequence.
     * 3. Reverse the longest decreasing sequence
    */
    void nextPermutation(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return;
        }
        int i = nums.size()-1;
        for ( ; i > 0 && nums[i] <= nums[i-1]; i--) { }
        if (i == 0) {
            reverse(nums.begin(), nums.end());
            return;
        }
        i--; // go the index before longest decreasing sequence
        for (int j = nums.size() - 1; j > i; j--) {
            if (nums[j] > nums[i]) {
                swap(nums[i], nums[j]);
                break;
            }
        }
        reverse(nums.begin()+i+1, nums.end());
    }
};

// Sample offline data - O(n) space and time complexity and O(k) to generate the samples
class Solution {
    void randomSampling(vector<int>& nums, int k) {
        default_random_engine seed;
        for (int i = 0; i < k; i++) {
            swap(nums[i], nums[uniform_int_distribution<int>{i, 
                                       static_cast<int>(nums.size())-1}(seed)]);
        }
    }
};

// Sample online data - O(k) time and space complexity
class Solution {
    vector<int> onlineRandomSampling(istringstream* sin, int k) {
        vector<int> running_sample;
        int x;
        for (int i = 0; i < k && *sin >> x; i++) {
            running_sample.emplace_back(x);
        }
        default_random_engine seed;
        int count = k;
        while (*sin >> x) {
            ++count;
            /*
             * find a random num between 0 and count-1. If the number is within
             * 0 and k-1, then replace it with x. Otherwise incoming x is ignored
             */
            int index = uniform_int_distribution{0, count-1}(seed);
            if (index < k) {
                running_sample[index] = x;
            }
        }
        return running_sample;
    }
};

// random perumation with elements [0,..n-1]
class Solution {
    vector<int> computeRandomPermutation(int n)
    {
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 0);
        randomSampling(permutation, n);
        return permutation;
    }
};

// create a random subset of n elements. we can make use of the random
// sampling to create the random subset but it will take O(n) space and time
// complexity to create the elements. And then O(k) to compute the random
// subset. Use hash table to reduce the space and time complexity to O(k) when
// k << n.

/* we can avoid building the array before hand since
 * we can take advantage of that fact a[i] == i and so just track
 * the change in value in the hash table 
 */
// space and time complexity O(k)
class Solution {
    vector<int> computeRandomSubset(int n, int k) {
        unordered_map<int, int> hashMap;
        default_random_engine seed((random_device())());
        for (int i = 0; i < k; i++) {
            int rIndex = uniform_int_distribution{i, n-1}(seed);
            unordered_map<int,int>::iterator itr1, itr2;
            itr1 = hashMap.find(rIndex);
            itr2 = hahsMap.find(i);
            if (itr1 == hashMap.end() && itr2 == hashMap.end()) {
                hashMap[i] = rIndex;
                hashMap[rIndex] = i;
            } else if (itr1 == hashMap.end() && itr2 != hashMap.end()) {
                hashMap[rIndex] = itr2->second;
                itr2->second = rIndex;
            } else if (itr1 != hashMap.end() && itr2 == hashMap.end()) {
                hashMap[i] = itr1->second;
                itr1->second = i;
            } else {
                int temp = itr2->second;
                hashMap[i] = itr1->second;
                hashMap[rIndex] = temp;
            }
        }
        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.emplace_back(hashMap[i]);    
        }
        return result;
    }
};

///////////////////////////////////////////////////////////////////////////////////////

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

//https://github.com/checkcheckzz/coding-questions#array
//1. Given two arrays, find elements that are in the first array but not in the second
//2. Detect cycle in an array
//3. Length of the first sub-array that sums to zero
//4. Given n points on a two-dimensional plane, find the closest (euclidean distance) k points
//to the point (0, 0).
