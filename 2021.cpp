//Happy number
class Solution {
public:
    bool isHappy(int n) {
        set<int> s;
        pair<set<int>::iterator, bool> ret;
        do {
            int sq = getSquare(n);
            ret = s.insert(sq);
            if (ret.second == false)
                return false;
            n = sq;
        } while(n != 1);
        return true;
    }
    int getSquare(int n) {
        int sq = 0;
        do {
            int d = n%10;
            sq += d*d;
            n /= 10;
        } while(n != 0);
        return sq;
    }
};

//Two sum - find 2 numbers that add to target given an unsorted array, contains dups
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_multimap<int, int> m;
        int idx = 0;
        for (int num : nums)
            m.insert(make_pair(num,idx++));
        for (auto itr = m.begin(); itr != m.end(); itr++) {
            auto ret = m.find(target - (itr->first));
            if (ret != m.end() && ret->second != itr->second)
                return {itr->second, ret->second};
        }
        return {};
    }
};

//Find the single non-repeating number in an array
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> s;
        pair<unordered_set<int>::iterator, bool> ret;
        for (int num: nums) {
            ret = s.insert(num);
            if (ret.second == false)
                s.erase(num);
        }
        return *s.begin();
    }
};

//Check if an array of integers contains any duplicates
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> s;
        for (int num: nums) {
            pair<unordered_set<int>::iterator, bool> ret;
            ret = s.insert(num);
            if (ret.second == false) {
                return true;
            }
        }
        return false;
    }
};

//Compute pow(x,n) in logn time
class Solution {
public:
    double myPow(double x, int n) {
        long n1 = n;
        if (n < 0) {
            n1 = -n1;
            x= 1/x;
        }
        return fastPow(x,n1);
    }
    double fastPow(double x, long n) {
        if (n==0)
            return 1.0;
        double half = fastPow(x, n/2);
        if (n%2 == 0)
            return half * half;
        return half * half * x;
    }
};

//Median of 2 sorted arrays of same or varying lengths
//Refer to: https://medium.com/@hazemu/finding-the-median-of-2-sorted-arrays-in-logarithmic-time-1d3f2ecbeb46
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() <= nums2.size())
            return findMedianWork(nums1.data(), nums1.size(), nums2.data(), nums2.size());
        return findMedianWork(nums2.data(), nums2.size(), nums1.data(), nums1.size());
    }
    double findMedianWork(int a[], int n, int b[], int m) {
        int leftHalfLen = (n+m+1)/2;
        // Since A is guaranteed to be the shorter array, 
        // we know it can contribute 0 or all of its values.
        int aMinCount = 0, aMaxCount = n;
        while (aMinCount <= aMaxCount) {
            int aCount = aMinCount + ((aMaxCount - aMinCount) / 2);
            int bCount = leftHalfLen - aCount;
            if (aCount > 0 && a[aCount - 1] > b[bCount]) // comp x with y' 
                aMaxCount = aCount - 1; // Decrease A's contribution size; x lies in the right half.
            else if (aCount < n && b[bCount - 1] > a[aCount]) { // comp y with x'
                // Decrease B's contribution size, i.e. increase A's contribution size; 
                // y lies in the right half.
                aMinCount = aCount + 1;
            } else {
                // Both x and y are not beyond the left half. We found the right aCount.
                // If n+m is odd, the median is the greater of x and y.
                int leftHalfEnd = 
                    (aCount == 0)             // A not contributing?
                        ? b[bCount - 1]       // aCount = 0 implies bCount > 0
                        : (bCount == 0)       // B is not contributing?
                            ? a[aCount - 1]   // bCount = 0 implies aCount > 0
                            : max(a[aCount - 1], b[bCount - 1]); 
                if ((n+m)%2)
                    return leftHalfEnd;

                // n+m is even. To compute the median, we need to find 
                // the first element in the right half as well, which will be the smaller 
                // of A[aCount] and B[bCount]. Remember that aCount could be equal
                // to A.Length, bCount could be equal to B.Length (if all the values 
                // of A or B are in the left half).
                int rightHalfStart = 
                    (aCount == n)          // A is all in the left half?
                        ? b[bCount]        // aCount = aLen implies bCount < B.Length 
                        : (bCount == m)    // B is all in the left half?
                            ? a[aCount]    // bCount = B.Length implies aCount < A.Length 
                            : min(a[aCount], b[bCount]);
                return (leftHalfEnd + rightHalfStart) / 2.0;
            }
        }
        return 0.0;
    }
};

//Intersection of 2 arrays - II - with duplicates and unsorted
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_multiset<int> s;
        vector<int>* nums;
        if (nums1.size() < nums2.size()) {
            copy(nums1.begin(), nums1.end(), inserter(s, s.begin()));
            nums = &nums2;
        } else {
            copy(nums2.begin(), nums2.end(), inserter(s, s.begin()));
            nums = &nums1;
        }
        vector<int> result;
        for (auto itr = nums->begin(); itr != nums->end(); ++itr) {
            unordered_multiset<int>::iterator sitr = s.find(*itr);
            if (sitr != s.end()) {
                result.push_back(*itr);
                s.erase(sitr);
            }
        }
        return result;
    }
};

//Intersection of 2 arrays - with duplicates & unsorted. Result should not contain dups.
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size(); ) {
            if (nums1[i] == nums2[j]) {
                int val = nums1[i];
                result.push_back(val);                
                while (i < nums1.size() && nums1[i] == val)
                    i++;
                while (j < nums2.size() && nums2[j] == val)
                    j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else
                j++;
        }
        return result;
    }
};

//Given a static sorted array with unknown size, search for a target value and return its index
class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        //find the left and right boundaries of the target to apply BST
        int low = 0, high = 1;
        //define the right boundary
        while (reader.get(high) < target) {
            low = high;
            high <<= 1;
        }
        return ApplyBST(reader, low, high, target);
    }
    int ApplyBST(const ArrayReader& reader, int low, int high, int target) {
        while (low <= high) {
            int mid = low + (high-low)/2;
            int val = reader.get(mid);
            if (val == target)
                return mid;
            if (val < target)
                low = mid + 1;
            else
                high = mid - 1; 
        }
        return -1;
    }
};

//Given a BST, find the value that is closest to the target
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        TreeNode* curr = root;
        int result = curr->val;
        while (curr != nullptr) {
            result = abs(curr->val-target) < abs(result-target) ? curr->val : result;
            if (curr->val <= target)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return result;
    }
};

//Find min and max simultaneously in an array by reducing the no. of comparisons
class Solution {
public: 
    vector<int> findMinMax(vector<int>& nums) {
        vector<int> result(2);
        if (nums.size() <= 1)
            return {nums.front(), nums.front()};
        if (nums[0] > nums[1]) {
            result[0] = nums[1];
            result[1] = nums[0];
        } else {
            result[0] = nums[0];
            result[1] = nums[1];
        }
        for (int i = 2;i+1 < nums.size(); i += 2) {
            if (nums[i] > nums[i+1]) {
                result[1] = max(result[1], nums[i]);
                result[0] = min(result[0], nums[i+1]);
            } else {
                result[1] = max(result[1], nums[i+1]);
                result[0] = min(result[0], nums[i]);
            }
        }
        if (nums.size() % 2) {
            result[0] = min(result[0], nums.back());
            result[1] = max(result[1], nums.back());
        }
        return result;
    }
};

//Search for the element equal to its index in a sorted array with distinct integers
class Solution {
public:
    int search(vector<int>nums) {
        int low = 0, high = nums.size()-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[mid] == mid)
                return mid;
            if (nums[mid] > mid)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return -1;
    }
};

//Find the first element greater than a given number in a sorted array
class Solution {
public:
    int findFirstLargeOf(vector<int> nums, int x) {
        int low = 0, high = nums.size() - 1, result = -1;
        while (low < high) {
            int mid = low + (high-low)/2;
            if (nums[mid] > x) {
                result = mid;
                high = mid - 1;
            } else
                low = mid + 1;
        }
        return result;
    }
};

//Find K closest elements
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> result;
        if (x < arr[0]) {
            copy(arr.begin(), arr.begin()+k, back_inserter(result));
            return result;
        }
        if (x > arr[arr.size()-1]) {
            copy(arr.end()-k, arr.end(), back_inserter(result));
            return result;
        }
        // closest elements lie between [l-k-1, l+k-1]
        int l = findClosestElement(arr, x), r = l+1, count = 0;
        while (l >= 0 && r < arr.size() && count < k) {
            if (abs(arr[l]-x) <= abs(arr[r]-x))
                result.push_back(arr[l--]);
            else
                result.push_back(arr[r++]);
            count++;
        }
        while (r < arr.size() && count !=k) {
            result.push_back(arr[r++]);
            count++;
        }
        while (l >= 0 && count != k) {
            result.push_back(arr[l--]);
            count++;
        }
        sort(result.begin(), result.end());
        return result;
    }
    //Find the element closest (<=) to x
    int findClosestElement(vector<int> nums, int x) {
        int low = 0, high = nums.size() - 1, result = -1;
        while (low < high) {
            int mid = low + (high-low)/2;
            if (nums[mid] <= x) {
                low = mid + 1;
                result = mid;
            } else
                high = mid - 1;
        }
        return result;
    }
    /*
    int findClosestElement(vector<int> nums, int x) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = low + (high-low)/2;
            if (nums[mid] <= x && nums[mid+1] > x) //requires mid, mid+1 to be present for this comp
                return mid;
            if (nums[mid] > x)
                high = mid - 1;
            else
                low = mid + 1;
        }
        //low==high
        if (low != nums.size() && nums[low] <= x) //closest element, so check for '<='
            return low;
        return -1;
    }*/
};

//First and last occurrence of an element in a sorted array
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result {INT_MAX, INT_MIN};
        int low = 0, high = nums.size()-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[mid] < target)
                low = mid + 1;
            else if (nums[mid] > target)
                high = mid - 1;
            else {
                result[0] = min(result[0], mid);
                result[1] = max(result[1], mid);
                high = mid - 1;
            }                
        }
        if (result[0] == INT_MAX)
            return {-1, -1};
        //search for the last position of the element in "right" side of the array beyond "max" position
        low = result[1], high = nums.size()-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[mid] < target)
                low = mid + 1;
            else if (nums[mid] > target)
                high = mid - 1;
            else {
                result[1] = max(result[1], mid);
                low = mid + 1;
            }                
        }
        return result;
    }
};

//First occurrence of an element in a sorted array
class Solution {
public:    
    int searchFirstOf(vector<int>& nums, int k) {
        int result = -1, low = 0, high = nums.size()-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[mid] < k)
                low = mid + 1;
            else if (nums[mid] > k)
                high = mid - 1;
            else {
                result = mid;
                high = mid - 1;
            }                
        }
        return result;
    }
};

//First bad version
class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1, high = n;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (isBadVersion(mid)) {
                if (low == mid)
                    return low;
                high = mid;
            }
            else
                low = mid+1;
        }
        return -1;
    }
};

//Find peak element (or) Peak index in a mountain array
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return search(nums, 0, nums.size()-1);
    }
    int search(vector<int>& nums, int low, int high) {
        if (low == high)
            return low;
        int mid = low + (high-low)/2;
        if (nums[mid] > nums[mid+1])
            return search(nums, low, mid);
        return search(nums, mid+1, high);
    }
};

//Search in a 2d matrix with sorted rows 
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int low = 0, high = matrix.size()-1, n = matrix[0].size();
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (matrix[mid][0] == target || matrix[mid][n-1] == target)
                return true;
            if (matrix[mid][0] < target) {
                if (target < matrix[mid][n-1])
                    return BS(matrix, mid, target);
                low = mid+1;
            } else {
                high = mid-1;
            }
        }
        return false;
    }
    bool BS(vector<vector<int>>& matrix, int row, int target) {
        int low = 0, high = matrix[0].size()-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (matrix[row][mid] == target)
                return true;
            if (matrix[row][mid] < target)
                low = mid + 1;
            else 
                high = mid - 1;
        }
        return false;
    }
};

//Search a 2D matix where the rows and columns are individually sorted
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int row = 0, col = matrix[0].size()-1; row < matrix.size() && col >= 0; ) {
            if (matrix[row][col] == target)
                return true;
            if (target > matrix[row][col])
                row++;
            else
                col--;
        }
        return false;
    }
};

//SQRT of a number - BST problem : when looking for an integer whose square is close to the number given
class Solution {
public:
    int mySqrt(int x) {
        int low = 0, high = x;
        while (low <= high) {
            long mid = low + (high-low)/2;
            long val = mid*mid;
            if (val <= x)
                low = mid + 1;
            else 
                high = mid - 1;
        }
        return low-1;
    }
};

//Find the min element in a sorted cyclical/rotated sorted array
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        if (nums.size() == 1 || nums[low] < nums[high])
            return nums[0];
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[low] <= nums[mid]) {
                if (mid+1 <= high && nums[mid] > nums[mid+1])
                    return nums[mid+1];
                else
                    low = mid+1;
            } else if (nums[mid] < nums[high]) {
                if (mid-1 >= low && nums[mid-1] > nums[mid])
                    return nums[mid];
                else
                    high = mid-1;
            }
        }
        return -1;
    }
    //Alternative solution:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        if (nums.size() == 1 || nums[low] < nums[high])
            return nums[0];
        while (low < high) {
            int mid = low + (high-low)/2;
            if (nums[mid] > nums[high])
                low = mid + 1;
            else
                high = mid;
        }
        //low==high
        return nums[low];
    }
};
//Find min element in a rotated sorted array (II) with duplicates
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        if (nums.size() == 1 || nums[low] < nums[high])
            return nums[0];
        while (low < high) {
            int mid = low + (high-low)/2;
            if (nums[mid] > nums[high])
                low = mid + 1;
            else if (nums[mid] < nums[high])
                high = mid;
            else //nums[mid]==nums[high]
                high -= 1;
            /* value of mid and high are the same, we can't be sure where the inflection point is
             * e.g) {3,3,1,3} or {10,1,10,10,10} illustrates the min element can be to the left or
             * right of the mid when nums[mid]==nums[high]
             */
        }
        //low==high
        return nums[low];
    }
};

//Search in a rotated sorted array
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return searchTarget(nums, target, 0, nums.size()-1);
    }
    int searchTarget(vector<int>& nums, int target, int low, int high) {
        if (low > high)
            return -1;
        int mid = low + (high-low)/2;
        if (nums[mid] == target)
            return mid;
        if (nums[low] <= nums[mid]) {
            if (nums[low] <= target && target < nums[mid])
                return searchTarget(nums, target, low, mid-1);
            else 
                return searchTarget(nums, target, mid+1, high);
        } else {
            if (nums[mid] < target && target <= nums[high])
                return searchTarget(nums, target, mid+1, high);
            else
                return searchTarget(nums, target, low, mid-1);
        }
        return -1;
    }
};

//Guess number higher or lower - play a guessing game to pick number higher or lower
class Solution {
public:
    int guessNumber(int n) {
        int low = 1, high = n;
        while (low <= high) {
            int mid = low + (high-low)/2;
            int res = guess(mid);
            if (res == 0)
                return mid;
            else if (res == 1)
                low = mid+1;
            else 
                high = mid-1;
        }
        return -1;
    }
};

//Simple BST to search for a number in a given array
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return searchTarget(nums, target, 0, nums.size()-1);
    }
    int searchTarget(vector<int>& nums, int target, int low, int high) {
        if (low > high)
            return -1;
        int mid = (low + high) / 2;
        if (target == nums[mid]) {
            return mid;
        } else if (target < nums[mid]) {
            return searchTarget(nums, target, low, mid-1);
        } else {
            return searchTarget(nums, target, mid+1, high);
        }
    }
};

//Max consecutive ones II - flip atmost one of the zeroes to get the max consecutive ones
#include <algorithm>
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int count = INT_MIN, len = 0, right = 0;
        bool track = false;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                if (!track) {
                    track = true;
                    len++;
                } else {
                    count = max(count, len);
                    len = right + 1; right = 0;
                }
            } else {
                len++;
                if (track)
                    right++;
            }
        }
        return max(count, len);
    }
};

//Longest common prefix
#include <algorithm>
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";
        int len = INT_MAX;
        for (string str : strs)
            len = min(len, (int)str.length()); // this is the max possible length of the prefix
        string prefix;
        int low = 0, high = len;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (isCommonPrefix(strs, low, mid)) {
                prefix += strs[0].substr(low, mid-low+1);
                low = mid + 1; // prefix can be longer. search the other half
            } else
                high = mid - 1; // prefix must be shorter since no common match found
        }
        return prefix;
    }
    bool isCommonPrefix(vector<string>& strs, int begin, int end) {
        string prefix = strs[0];
        for (string str : strs) {
            for (int j = begin; j <= end; j++) {
                if (str[j] != prefix[j]) {
                    return false;
                }
            }
        }
        return true;
    }
};

//Permute the elements of an array - EOP book
#include <boost/dynamic_bitset>
class Solution {
public:
    void applyPermutation(vector<int>& nums, vector<int>& p) {
        if (nums.empty())
            return;
        dynamic_bitset<> b(nums.size());
        for (int i = 0; b.count() < nums.size(); i++) {
            int j = i, orig = nums[j];
            do {
                if (!b.test(j)) {
                    int next = p[j];
                    swap(nums[next], orig);
                    b.set(j);
                    j = next;
                }
            } while (i != j);
        }
    }
};

//Rotate array
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.empty())
            return;
        k = k % nums.size();
        int count = 0;
        for (int i = 0; count < nums.size(); i++) {
            int j = i, orig = nums[j];
            do {
                int next = (j+k)%nums.size();
                swap(nums[next], orig);
                j = next;
                count++;
            } while (i != j);
        }
    }
};

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

//Pascal's triangle - II (bottom-up)
class Solution {
public:
    int getIndex(int i, int j, map<pair<int, int>, int>& m) {
        if (j == 0 || i == j)
            return 1;
        else {
            auto itr = m.find(make_pair(i,j));
            if (itr != m.end())
                return itr->second;
            else {
                int val = getIndex(i-1, j-1, m) + getIndex(i-1, j, m);
                m[make_pair(i,j)] = val;
                return val;
            }
        }
    }
    vector<int> getRow(int rowIndex) {
        vector<int> result;
        map<pair<int, int>, int> m;
        for (int j = 0; j <= rowIndex; j++) {
            result.push_back(getIndex(rowIndex, j, m));    
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
