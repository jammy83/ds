//Palindromic substrings
class Solution {
public:
    int countSubstrings(string s) {
        if (s.empty())
            return 0;
        int n, count;
        n = count = s.length();
        bool dp[n][n];
        fill_n(*dp, n * n, false);
        // Base case: single letter substrings
        for (int i = 0; i < n; ++i)
            dp[i][i] = true;
        // Base case: double letter substrings
        for (int i = 0; i < n - 1; ++i) {
            dp[i][i + 1] = (s[i] == s[i + 1]);
            count += dp[i][i + 1];
        }
        // All other cases: substrings of length 3 to n
        for (int len = 3; len <= n; ++len)
            for (int i = 0, j = i + len - 1; j < n; ++i, ++j) {
                dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
                count += dp[i][j];
            }
        return count;
    }
};

//Valid Palindrome - II
class Solution {
public:
    bool isPalindrome(string s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
    bool validPalindrome(string s) {
        for (int i = 0, j = s.length()-1; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return (isPalindrome(s, i+1, j) || isPalindrome(s, i, j-1));
            }
        }
        return true;
    }
};

//Valid Palindrome
class Solution {
public:
    bool isPalindrome(string s) {
        for (int i = 0, j = s.length()-1; i < j; i++, j--) {
            while (i < j && !isalnum(s[i]))
                i++;
            while (i < j && !isalnum(s[j]))
                j--;
            if (tolower(s[i]) != tolower(s[j])) {
                return false;
            }
        }
        return true;
    }
};

//Permutation in string - check if permutation of s1 is a substring of s2.
//Use of bitset is a viable option when there are no duplicate characters, otherwise use an array to track the occurrences
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.empty() || s2.empty() || s2.length() < s1.length()) {
            return false;
        }
        vector<int> h1(26,0);
        for (char c : s1) {
            h1[c - 'a']++;
        }
        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            vector<int> h2(26,0);
            for (int j = 0; j < s1.length(); j++) {
                h2[s2[i + j] - 'a']++;
            }
            if (h1 == h2) {
                return true;
            }
        }
        return false;
    }
};
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.empty() || s2.empty() || s2.length() < s1.length()) {
            return false;
        }
        bitset<26> h1, h2;
        for (char c : s1) {
            h1.set(c - 'a');    
        }
        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            h2.reset();
            for (int j = 0; j < s1.length(); j++) {
                h2.set(s2[i + j] - 'a');
            }
            if (h1 == h2) {
                return true;
            }
        }
        return false;
    }
};

//Permutation string - check if one is a permutation of the other
class Solution {
public:
    bool permutation(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false;
        }
        multiset<char> hash; // allows duplicates but orders for faster lookup.
        for (char c : s1) {
            hash.insert(c);
        }
        for (char c : s2) {
            hash.erase(hash.find(c));
        }
        return hash.empty();
    }
    //O(n) space but lookups faster with multiset unlike doing lookups and erase operations in s2
};

//Palindrome permutation - check if a permutation of a string could form a palindrome
class Solution {
public:
    // A permutation of a string can be a palindrome if each of the characters occurs equal no. of times 
    // if the string length is even. If odd, there is only one element that has not occurred again in 's'.
    bool canPermutePalindrome(string s) {
        unordered_set<char> hash;
        pair<unordered_set<char>::iterator, bool> ret;
        for (char c : s) {
            ret = hash.insert(c);
            if (ret.second == false) {
                hash.erase(c);
            }
        }
        return (hash.size() <= 1);
    }
};

//Rotate string - check if rotation of A can result in B
class Solution {
public:
    bool rotateString(string A, string B) {
        if (A.length() != B.length()) {
            return false;
        }
        string t = B + B;
        return (t.find(A) != string::npos) ? true : false;
    }
};

//Set Matrix zeroes
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool rowZ = false, colZ = false;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    if (i == 0)
                        rowZ = true;
                    if (j == 0)
                        colZ = true;
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < matrix.size(); i++) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < matrix[0].size(); j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int j = 1; j < matrix[0].size(); j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < matrix.size(); i++) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (rowZ) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[0][j] = 0;
            }
        }
        if (colZ) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

//Reverse words in a string III
class Solution {
public:
    void reverseString(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseWords(string s) {
        int left = -1;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != ' ' && left == -1) {
                left = i;
            } else if (s[i] == ' ' && left != -1) {
                reverseString(s, left, i-1);
                left = -1;
            }
        }
        if (left != -1) {
            reverseString(s, left, s.length()-1);
        }
        return s;
    }
};

//Reverse words in a string. Handle leading/tailing whitespaces and remove extra whitespaces in between
class Solution {
public:
    void reverseString(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseWords(string s) {
        reverseString(s, 0, s.length()-1);
        int left = -1;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != ' ' && left == -1) {
                left = i;
            } else if (s[i] == ' ' && left != -1) {
                reverseString(s, left, i-1);
                left = -1;
            }
        }
        if (left != -1) {
            reverseString(s, left, s.length()-1);
        }
        reduce(s);
        return s;
    }
    void trim(string& s) { // removes the leading spaces from the string
        const auto strBegin = s.find_first_not_of(" ");
        if (strBegin == string::npos)
            return;
        const auto strEnd = s.find_last_not_of(" ");
        s = s.substr(strBegin, strEnd-strBegin+1);
    }
    void reduce(string& s) {
        trim(s); // remove leading whitespace
        auto begin = s.find_first_of(" ");
        while (begin != string::npos) {
            const auto end = s.find_first_not_of(" ", begin);
            s.replace(begin, end-begin, " ");
            begin = s.find_first_of(" ", begin+1);
        }
    }
};

// Min size subArray sum
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = INT_MAX, total = 0;
        for (int i = 0, left = 0; i < nums.size(); i++) {
            total += nums[i];
            if (total > s) {
                while (total > s && left < i) {
                    total -= nums[left++];
                }
                if (total < s) {
                    total += nums[--left];
                }
            }
            if (total >= s) {
                len = min(len, i-left);
            }
        }
        return len == INT_MAX ? 0: len+1;
    }
};

//Two Sum II - input array is sorted
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
        for (int i = 0, j = numbers.size()-1; i < j; ) {
            int sum = numbers[i] + numbers[j];
            if (sum == target) {
                result.push_back(i+1);
                result.push_back(j+1);
                break;
            }
            if (sum > target) {
                j--;
            } else {
                i++;
            }
        }
        return result;
    }
};

//Array partition - sum of min(a,b) is maximum
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sum = 0, i = 0;
        while (i+1 < nums.size()) {
            sum += min(nums[i], nums[i+1]);
            i += 2;
        }
        return (i < nums.size()) ? sum+nums[i] : sum;
    }
};

//Reverse string
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0, j = s.size()-1; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
};

// Print matrix in spiral order
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> d;
        int mbegin = 0, mend = matrix.size(), nbegin = 0, nend = matrix[0].size(); // m rows, n cols
        do {
            printBoundary(d, matrix, mbegin, mend, nbegin, nend);
            mbegin++; mend--;
            nbegin++; nend--;
        } while (mbegin < mend && nbegin < nend);
        return d;
    }
    void printBoundary(vector<int>& d, vector<vector<int>>& matrix,
                       int mbegin, int mend,
                       int nbegin, int nend) {
        for (int m = mbegin, n = nbegin; n < nend; n++) { //top row
            d.push_back(matrix[m][n]);
        }
        for (int m = mbegin+1, n = nend-1; m < mend; m++) { //rightmost col
            d.push_back(matrix[m][n]);
        }
        for (int m = mend-1, n = nend-2;
             mbegin != mend-1 && n >= nbegin; n--) { //bottom row (r->l)
            d.push_back(matrix[m][n]);
        }
        for (int m = mend-2, n = nbegin;
             nbegin != nend-1 && m > mbegin; m--) { //first col (b->t)
            d.push_back(matrix[m][n]);
        }
    }
};

//Diagonal traversal (reversing direction) of matrix
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if (matrix.empty()) {
            return result;
        }
        int N = matrix.size(), M = matrix[0].size();
        bool up = true;
        for (int i = 0, j = 0; i < N && j < M; ) {
            int r = i, c = j; // gn an index print the diagonal
            while (r >= 0 && r < N && c >= 0 && c < M) {
                result.push_back(matrix[r][c]);
                i = r, j = c;
                if (!up) {
                    r++, c--;
                } else {
                    c++, r--;
                }
            }
            up = !up;
            // matrix[i][j] is the last index pushed
            if (!up) {
                i += (j == M-1) ? 1 : 0;
                j += (j < M-1)  ? 1 : 0;
            } else {
                j += (i == N-1) ? 1 : 0;
                i += (i < N-1)  ? 1 : 0;
            }
            // i,j points to the next head
        }
        return result;
    }
};

//Pascal's triangle
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result(numRows, vector<int>());
        for (int i = 0; i < numRows; i++) {
            result[i].push_back(1);
        }
        for (int i = 1; i < numRows; i++) {
            for (int j = 1; j <= i; j++) {
                if (i == j) {
                    result[i].push_back(1);
                    continue;
                }
                result[i].push_back(result[i-1][j-1] + result[i-1][j]);
            }
        }
        return result;
    }
};

// Find pivot index
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int total = 0, left = 0;
        for (int num: nums) {
            total += num;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (left == total - nums[i] - left) {
                return i;
            }
            left += nums[i];
        }
        return -1;
    }
};

// Largest # atleast twice of others
class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        int max1 = 0, max2 = 1;
        if (nums[max2] > nums[max1])
            swap(max1, max2);
        for (int i = 2; i < nums.size(); i++) {
            if (nums[i] > nums[max1]) {
                max2 = max1;
                max1 = i;
            } else if (nums[i] > nums[max2]) {
                max2 = i;
            }
        }
        if (nums[max2]*2 <= nums[max1]) {
            return max1;
        }
        return -1;
    }
};

// Plus one
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int c = 1, i = digits.size()-1;
        do {
            int val = digits[i] + c;
            c = (val >= 10) ? 1 : 0;
            digits[i--] = val % 10;
        } while (c == 1 && i >= 0);
        if (c == 1) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

// Height checker
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> v = heights;
        sort(v.begin(), v.end());
        int cnt = 0;
        for (auto itr = v.begin(), hItr = heights.begin(); itr != v.end(), hItr != heights.end(); hItr++, itr++) {
            if (*itr != *hItr) {
                cnt++;
            }
        }
        return cnt;
    }
};

//Third max number in an array with dups
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        nums.assign(s.begin(), s.end());
        if (nums.empty()) {
            return -1;
        } else if (nums.size() == 1) {
            return nums[0];
        } else if (nums.size() == 2) {
            return ((nums[0] == nums[1]) ? nums[0] : max(nums[0], nums[1]));
        }
        //return nums[nums.size()-3]; if using a set instead of unordered_set
        int max1 = nums[0], max2 = nums[1], max3 = nums[2];
        if (max2 > max1)
            swap(max1, max2);
        if (max3 > max1)
            swap(max1, max3);
        if (max3 > max2)
            swap(max2, max3);
        for (int i = 3; i < nums.size(); i++) {
            int num = nums[i];
            if (num > max1) {
                max3 = max2;
                max2 = max1;
                max1 = num;
            } else if (num > max2) {
                max3 = max2;
                max2 = num;
            } else if (num > max3) {
                max3 = num;
            }
        }
        return max3;
    }
};

// Find all nos disappeared in an array [1...n]
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        bitset<100000> b;
        for (int num : nums) {
            b.set(num-1);
        }
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++) {
            if (!b.test(i)) {
                ret.push_back(i+1);
            }
        }
        return ret;
    }
};

//squares of sorted array with negative numbers
#include <algorithm>
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> neg;
        for (auto itr = nums.begin(); itr != nums.end(); ) {
            int num = *itr;
            if (num < 0) {
                neg.insert(neg.begin(), num*num);
                nums.erase(itr);
            } else {
                *itr = num*num; ++itr;
            }
        }
        if (!neg.empty()) {
            vector<int> dst;
            std::merge(nums.begin(), nums.end(), neg.begin(), neg.end(), std::back_inserter(dst));
            return dst;
        }
        return nums;
    }
};

//Remove element
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int w = 0;
        for (int r = 0; r < nums.size(); r++) {
            if (nums[r] != val) {
                nums[w++] = nums[r];
            }
        }
        return w;
    }
};

//Remove dups from sorted array
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return nums.size();
        }
        int w = 1; int val = nums[0];
        for (int r = 1; r < nums.size(); r++) {
            if (nums[r] != val) {
                nums[w++] = val = nums[r];
            }
        }
        return w;
    }
};

//sort array by parity
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int odd = -1;
        for (int r = 0; r < A.size(); ++r) {
            if (A[r] %2 != 0) {
                odd = (odd == -1) ? r : odd;
            } else {
                if (odd != -1) {
                    A.insert(A.begin()+odd, A[r]); odd++;
                    if (r+1 < A.size()) {
                        A.erase(A.begin()+r+1);
                    }                    
                }
            }
        }
        return A;
    }
};

//Move zeroes
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int w = 0;
        for (int r = 0; r < nums.size(); r++) {
            if (nums[r] != 0) {
                nums[w++] = nums[r];
            }
        }
        for ( ; w < nums.size(); w++) {
            nums[w] = 0;
        }
    }
};

//Replace elements with the largest number to its right
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        if (arr.empty()) {
            return arr;
        }
        int len = arr.size(), max = arr[len-1];
        arr[len-1] = -1;
        for (int i = len-2; i >=0; i--) {
            int val = arr[i];
            arr[i] = max;
            max = (val > max) ? val : max;
        }
        return arr;
    }
};

//valid mountain array
class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        bool up = false, down = false;
        if (arr.size() < 3) {
            return false;
        }
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i-1] == arr[i]) {
                return false;
            } else if (arr[i-1] < arr[i]) { // strict increase
                if (down == true) {
                    return false;
                }
                up = true;
            } else if (arr[i-1] > arr[i]) { // strict decrease
                if (up != true) {
                    return false;
                }
                down = true;
            }
        }
        return (up && down);
    }
};

//Check if N and its double exists
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        set<int> s;
        for (int num : arr) {
            if (s.find(num*2) != s.end() ||
                (num % 2 == 0 && s.find(num/2) != s.end())) {
                return true;
            }
            s.insert(num);
        }
        return false;
    }
};

//Merge sorted array
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        nums1.resize(m);
        int i = m, j = n; 
        auto itr1 = nums1.begin(), itr2 = nums2.begin();
        for (; itr1 != nums1.end() && itr2 != nums2.end() && i > 0 && j > 0; ) {
            if (*itr1 <= *itr2) {
                ++itr1; --i;
            } else {
                nums1.insert(itr1, *itr2); ++itr1; // move itr1 past the new element.
                ++itr2; --j;
            }
        }
        for (; itr2 != nums2.end() && j > 0; ++itr2) {
            nums1.push_back(*itr2); j--;
        }
    }
};

//Duplicate if zero present
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int dups = 0, len = arr.size()-1;
        for (int i = 0; i <= len-dups; i++) {
            if (arr[i] == 0) {
                if (i == len-dups) {
                    arr[len--] = 0;
                    break;
                }
                ++dups;
            }
        }
        int last = len-dups;
        for (int i = last; i >= 0; i--) {
             if (arr[i] == 0) {
                 arr[i+dups] = 0;
                 dups--;
                 arr[i+dups] = 0;
             } else {
                 arr[i+dups] = arr[i];
             }
        }
    }
};

//Max consecutive ones
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max = 0, count = 0;
        for (int num : nums) {
            if (num == 1) {
                count++;
            } else {
                max = (count > max) ? count : max;
                count = 0;
            }
        }
       return (count > max) ? count : max;
    }
};

//Find no with even no. of digits
#include <math.h>

class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int cnt = 0;
        for (int num : nums) {
            for (int powIndex = 1; powIndex <= 5; ++powIndex) {
                int mod = int(pow(10, powIndex));
                if (num == mod || num % mod == num) {
                    int digits = num == mod ? powIndex+1 : powIndex;
                    if (digits % 2 == 0) {
                        ++cnt;
                    }
                    break;
                }
            }
        }
        return cnt;
    }
};

//Given 2 binary strings, return their as a binary string
class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        char c = '0';
        if (a.empty() || b.empty()) {
            return (a.empty()) ? b : a;
        }
        int i = a.length()-1, j = b.length()-1;
        for (; i >= 0 && j >= 0; i--, j--) {
            char val = '0', newc = '0';
            if ((a[i] == '0' && b[j] == '1') ||
                (a[i] == '1' && b[j] == '0')) {
                val = '1';
            } else if (a[i] == '0' && b[j] == '0') {
                val = '0';
            } else {
                val = '0';
                newc = '1';
            }
            if (c == '1' && val == '0') {
                val = '1';
            } else if (c == '1' && val == '1') {
                val = '0';
                newc = '1';
            }
            c = newc;
            result.insert(result.begin(), val);
        }
        if (c == '1' && (i >= 0 || j >= 0)) {
            while (c == '1' && i >= 0) {
                char val = (a[i] == '0') ? '1' : '0';
                c = (a[i] == '0') ? '0' : '1';
                result.insert(result.begin(), val);
                i--;
            }
            while (c == '1' && j >= 0) {
                char val = (b[j] == '0') ? '1' : '0';
                c = (b[j] == '0') ? '0' : '1';
                result.insert(result.begin(), val);
                j--;
            }
        }
        if (c == '0' && (i >=0 || j >=0)) {
            if (i >= 0) {
                result.insert(0, a.substr(0, i+1));
            } else {
                result.insert(0, b.substr(0, j+1));
            }
        }
        if (i < 0 && j < 0 && c == '1') {
            result.insert(result.begin(), '1');
        }
        return result;
    }
};

//strStr implementation
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        } else if (haystack.empty() || needle.length() > haystack.length()) {
            return -1;
        }
        for (int i = 0; i <= haystack.length()-needle.length(); i++) {
            if (haystack[i] == needle[0]) {
                string sstr = haystack.substr(i, needle.length());
                if (sstr == needle) {
                    return i;
                }
            }
        }
        return -1;
    }
};
