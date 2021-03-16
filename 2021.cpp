//Evaluate RPN
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (string str: tokens) {
            if (str == "+" || str == "-" || str == "*" || str == "/") {
                int val2 = s.top(); s.pop();
                int val1 = s.top(); s.pop();
                int res = 0;
                if (str == "+")
                    res = val1 + val2;
                if (str == "-")
                    res = val1 - val2;
                if (str == "*")
                    res = val1 * val2;
                if (str == "/")
                    res = val1 / val2;
                s.push(res);
            } else
                s.push(stoi(str));
        }
        return s.top();
    }
};

//Daily temperatures - find a warmer climate day closest to today
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> result(T.size());
        stack<int> s;
        for (int i = T.size()-1; i >= 0; i--) {
            while (!s.empty() && T[s.top()] <= T[i])
                s.pop();
            result[i] = s.empty() ? 0 : s.top() - i;
            s.push(i);
        }
        return result;
    }
};

//valid parentheses
class Solution {
public:
    bool isValid(string s) {
        stack<char> p;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[')
                p.push(c);
            else if (c == ')' || c == '}' || c == ']') {
                if (p.empty())
                    return false;
                char t = p.top();
                if ((c == ')' && t != '(') || (c == '}' && t != '{') || (c == ']' && t != '['))
                    return false;
                p.pop();
            }
        }
        return p.empty();
    }
};

//Max queue
class MaxQueue {
public:
    MaxQueue() {}
    void push(int x) {
        q.push(x);
        while(!maxQ.empty() && maxQ.back() < x)
            maxQ.pop_back();
        maxQ.push_back(x);
    }
    int pop() {
        int val = q.front();
        q.pop();
        if (maxQ.front() == val)
            maxQ.pop_front();
        return val;
    }
    int getMax() {
        return maxQ.front();
    }
    queue<int> q;
    deque<int> maxQ;
};

//Stack that returns the min element
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {}  
    void push(int x) {
        s.push(x);
        if (minS.empty() || x <= minS.top())
            minS.push(x);
    }
    void pop() {
        int val = s.top();
        s.pop();
        if (!minS.empty() && minS.top() == val)
            minS.pop();
    }
    int top() {
        return s.top();
    }
    int getMin() {
        return minS.top();
    }
    stack<int> s;
    stack<int> minS;
};

//Implement stack with max retrieval and removal
//Retrieving max element only needs another stack alone but since we need to support popMax(),
//using priority_queue with hashset (for lazy removal from priority_queue)
class MaxStack {
public:
    /** initialize your data structure here. */
    MaxStack() {}   
    void push(int x) {
        s.push(x);
        maxH.push(x);
    }
    int pop() {
        int ret = s.top();
        s.pop();
        if (!maxH.empty() && maxH.top() == ret)
            maxH.pop();
        else
            del.insert(ret);
        return ret;
    }
    int top() {
        return s.top();
    }
    int peekMax() {
        remove();
        return maxH.top();
    }
    int popMax() {
        remove();
        stack<int> s1;
        int max = maxH.top();
        while (!s.empty() && s.top() != max) {
            s1.emplace(s.top()); s.pop();
        }
        s.pop();
        while (!s1.empty()) {
            s.emplace(s1.top()); s1.pop();
        }
        maxH.pop();
        return max;
    }
    void remove() {
        auto itr = del.find(maxH.top());
        while (!del.empty() && itr != del.end()) {
            maxH.pop(); del.erase(itr);
            itr = del.find(maxH.top());
        }
    }
    stack<int> s;
    priority_queue<int, vector<int>> maxH; //max-heap
    unordered_multiset<int> del;
};

//Implement queue with 2 stacks
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {}
    /** Push element x to the back of queue. */
    void push(int x) {
        while (!f.empty()) {
            b.emplace(f.top()); f.pop();
        }
        b.push(x);
    }
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int val = peek();
        if (!f.empty())
            f.pop();
        return val;
    }
    /** Get the front element. */
    int peek() {
        while (!b.empty()) {
            f.emplace(b.top()); b.pop();
        }
        return f.empty() ? -1 : f.top();
    }
    /** Returns whether the queue is empty. */
    bool empty() {
        return (f.empty() && b.empty());    
    }
    stack<int> f;
    stack<int> b;
};

// Wall and gates 
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.size() == 0)
            return;
        int EMPTY = INT_MAX, GATE = 0;
        int m = rooms.size(), n = rooms[0].size();
        vector<vector<int>> nb{{0,1}, {0,-1}, {-1,0}, {1,0}}; //neighbors
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == GATE)
                    q.push(make_pair(i,j));
            }
        }
        //Find the shortest distance to each empty room from closest gate
        while (!q.empty()) {
            int i = q.front().first, j = q.front().second;
            q.pop();
            for (int k = 0; k < nb.size(); k++) {
                int r = i + nb[k][0], c = j + nb[k][1];
                if (r < 0 || c < 0 || r >= m || c >= n || rooms[r][c] != EMPTY)
                    continue;
                rooms[r][c] = rooms[i][j] + 1;
                q.push(make_pair(r,c));
            }
        }
    }
};

//Implement a circular queue
class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        nums.resize(k);
        head = tail = -1;
    }
    bool enQueue(int value) {
        if (!isFull()) {
            if (head == -1)
                head = 0;
            tail = ++tail % nums.capacity();
            nums[tail] = value;
            return true;
        }
        return false;
    }
    bool deQueue() {
        if (!isEmpty()) {
            head = (head == tail) ? head = tail = -1 : ++head % nums.capacity();
            return true;
        }
        return false;
    }
    int Front() {
        return (!isEmpty()) ? nums[head] : -1;
    }
    int Rear() {
        return (!isEmpty()) ? nums[tail] : -1;
    }
    bool isEmpty() {
        return (head == -1 && tail == -1);
    }
    bool isFull() {
        return (!isEmpty() && ((tail+1) % nums.capacity()) == head);
    }
    vector<int> nums;
    int head, tail;
};

//Schedule to minimize waiting times given service time
class Solution {
public:
    int minWaitingTime(vector<int> service_time) {
        int total_time = 0, prev = 0;
        for (int i = 1; i < service_time.size(); i++) {
            int curr_time = service_time[i-1] + prev;
            total_time += curr_time;
            prev = curr_time;
        }
        return total_time;
    }
};

//Find the majority element which occurs >= 50%
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int elem, count = 0;
        for (int num: nums) {
            if (count == 0) {
                elem = num;
                ++count;
            } else if (elem == num) {
                ++count;
            } else
                --count;
        }
        return elem;
    }
};

//Find duplicate subtree
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return result;
    }
    string dfs(TreeNode *node) {
        if (node == nullptr)
            return "$";
        string hash = to_string(node->val) + "," + dfs(node->left) + "," + dfs(node->right);
        m[hash]++;
        if (m[hash] == 2)
            result.push_back(node);
        return hash;
    }
    unordered_map<string, int> m;
    vector<TreeNode*> result;
};

//4Sum
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        return kSum(nums, target, 0, 4);
    }
    vector<vector<int>> kSum(vector<int>& nums, int target, int start, int k) {
        vector<vector<int>> res;
        if (start == nums.size() || nums[start] * k > target || target > nums.back() * k)
            return res;
        if (k == 2)
            return twoSum(nums, target, start);
        for (int i = start; i < nums.size(); ++i) {
            if (i == start || nums[i - 1] != nums[i]) {
                for (auto &set : kSum(nums, target - nums[i], i + 1, k - 1)) {
                    res.push_back({nums[i]});
                    res.back().insert(end(res.back()), begin(set), end(set));
                }
            }
        }
        return res;
    }
    //TwoSum: sorted array, one pass hash table lookup solution
    vector<vector<int>> twoSum(vector<int>& nums, int target, int start) {
        vector<vector<int>> res;
        unordered_set<int> s;
        for (auto i = start; i < nums.size(); ++i) {
            if (res.empty() || res.back()[1] != nums[i]) {
                if (s.count(target - nums[i]))
                    res.push_back({target - nums[i], nums[i]});
            }
            s.insert(nums[i]);
        }
        return res;
    }
};

//Sudoku checker
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        //validate row
        for (int i = 0; i < board.size(); i++) {
            if (validate(board, i, i, 0, board[0].size()-1) == false)
                return false;
        }
        //validate col
        for (int j = 0; j < board[0].size(); j++) {
            if (validate(board, 0, board.size()-1, j, j) == false)
                return false;
        }
        //validate 3*3 matrix
        for (int i = 0; i < board.size(); i+=3) {
            for (int j = 0; j < board[0].size(); j+=3) {
                if (validate(board, i, i+3-1, j, j+3-1) == false)
                    return false;
            }
        }
        return true;
    }
    bool validate(vector<vector<char>>& board, int row, int rend, int col, int cend) {
        bitset<10> bitMap;
        for (int i = row; i <= rend; i++) {
            for (int j = col; j <= cend; j++) {
                if (board[i][j] != '.') {
                    int val = (int)board[i][j] - '0';
                    if (bitMap.test(val))
                        return false;
                    bitMap.set(val);
                }
            }
        }
        return true;
    }
};

//Sliding window maximum
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        for (int i = 0; i < k; i++)
            add(nums[i]);
        for(int i = k; i < nums.size(); i++) {
            result.push_back(q.front());
            add(nums[i]);
            remove(nums[i-k]);
        }
        result.push_back(q.front());
        return result;
    }
    void add(int n) {
        while (!q.empty() && q.back() < n)
            q.pop_back();
        q.push_back(n);
    }
    void remove(int n) {
        if (!q.empty() && q.front() == n)
            q.pop_front();
    }
    deque<int> q;
};
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> s;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            s.insert(nums[i]);
            if (s.size() > k)
                s.erase(s.find(nums[i-k]));
            if (s.size() >= k)
                result.push_back(*s.rbegin());
        }
        return result;
    }
}

//Implement a stack API using heap
class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
        index = 0;
    }
    /** Push element x onto stack. */
    void push(int x) {
        q.push({x, index++});
    }
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if (q.empty())
            return -1;
        int val = q.top().val;
        q.pop();
        return val;
    }
    /** Get the top element. */
    int top() {
        return q.top().val;
    }
    /** Returns whether the stack is empty. */
    bool empty() {
       return q.empty(); 
    }
    struct node {
        int val;
        int in;
        bool operator< (const node& b) const {
            return in < b.in;
        }
    };
    priority_queue<node, vector<node>> q; // max queue
    int index;
};

//Sliding window median
//Solution uses 2 multisets since deletion and re-heapifying operation is costly with priority_queue
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        multiset<int> minSet, maxSet;
        for (int i = 0; i < nums.size(); i++) {
            //add number
            if (minSet.empty())
                minSet.insert(nums[i]);
            else {
                if (nums[i] > *minSet.begin())
                    minSet.insert(nums[i]);
                else
                    maxSet.insert(nums[i]);
            }
            //maintain the sliding window
            if (i >= k) {
                if (nums[i-k] >= *minSet.begin())
                    minSet.erase(minSet.find(nums[i-k]));
                else
                    maxSet.erase(maxSet.find(nums[i-k]));
            }
            //re-heap
            if (minSet.size() > maxSet.size()+1) {
                maxSet.insert(*minSet.begin());
                minSet.erase(minSet.begin());
            } else if (maxSet.size() > minSet.size()) {
                minSet.insert(*maxSet.rbegin());
                maxSet.erase(prev(maxSet.end()));
            }
            //find median   
            if (i + 1 >= k) {
                double median = (k&1) ? *minSet.begin() : ((double)*minSet.begin()+(double)*maxSet.rbegin())/2;
                result.push_back(median);
            }
        }
        return result;
    }
};

//Median from data stream
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    void addNum(int num) {
        if (minQ.empty())
            minQ.push(num);
        else {
            if (num >= minQ.top())
                minQ.push(num);
            else
                maxQ.push(num);
        }
        //Re-heap
        if (minQ.size() > maxQ.size() + 1) {
            maxQ.push(minQ.top());
            minQ.pop();
        } else if (maxQ.size() > minQ.size()) {
            minQ.push(maxQ.top());
            maxQ.pop();
        }
    }
    double findMedian() {
        if (maxQ.size() == minQ.size())
            return (double)(maxQ.top()+minQ.top())/2;
        return minQ.top();
    }
    priority_queue<int, vector<int>> maxQ;
    priority_queue<int, vector<int>, greater<int>> minQ;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

//Merge K sorted lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;
        priority_queue<ListNode*, vector<ListNode*>, compare> q;
        for (ListNode* l : lists) {
            if (l != nullptr)
                q.push(l);
        }
        if (q.empty())
            return nullptr;
        ListNode *head, *prev;
        head = prev = q.top(); q.pop();
        if (prev->next) {
            q.push(prev->next);
        }
        while (!q.empty()) {
            prev->next = q.top(); q.pop();
            prev = prev->next;
            if (prev->next)
                q.push(prev->next);
        }
        return head;
    }
    struct compare {
        bool operator()(const ListNode* l, const ListNode* r) {
            return l->val > r->val;
        }
    };
};

//Merge 2 sorted lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr || l2 == nullptr)
            return (l1 == nullptr) ? l2 : l1;
        ListNode *head, *next, *prev;
        head = next = nullptr;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                next = l1; l1 = l1->next;
            } else {
                next = l2; l2 = l2->next;
            }
            if (head == nullptr) {
                head = prev = next;
            } else {
                prev->next = next;
                prev = next;
            }
        }
        if (prev != nullptr)
            prev->next = (l1 != nullptr) ? l1 : l2;
        return head;
    }
};

//Find the Kth largest element in an array
class Solution {
public:
    /* Using priority queue/heap
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q; //min-heap
        for (int num : nums) {
            q.push(num);
            if (q.size() > k)
                q.pop();
        }
        return q.top();
    }
    */
    //Using quickselect algorithm. Avg case O(n); worst case O(n^2)
    int findKthLargest(vector<int>& nums, int k) {
        int low = 0, high = nums.size()-1;
        int x = nums.size() - k; //kth largest is the (size - k)th smallest
        default_random_engine gen((random_device())());
        while (low <= high) {
            int pivot = uniform_int_distribution<int> {low,high}(gen);
            int newPivot = partition(low, high, pivot, nums);
            if (newPivot == x)
                return nums[x];
            if (newPivot < x)
                low = newPivot + 1;
            else
                high = newPivot - 1;
        }
        return -1;
    }
    int partition(int low, int high, int pivot, vector<int>& nums) {
        int pval = nums[pivot];
        int wIndex = low;
        swap(nums[pivot], nums[high]); //move pivot element to the end
        for (int i = low; i <= high; i++) {
            if (nums[i] < pval)
                swap(nums[i], nums[wIndex++]);
        }
        swap(nums[wIndex], nums[high]);
        return wIndex;
    }
};

//Kth largest element in a stream
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        x = k;
        for (int num: nums) {
            q.push(num);
            if (q.size() > x) 
                q.pop();
        }
    }
    int add(int val) {
        q.push(val);
        if (q.size() > x) 
            q.pop();
        return q.top();
    }
    priority_queue<int, vector<int>, greater<int>> q;
    int x;        
};

//Power of 3
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n < 1)
            return false;
        while (n % 3 == 0)
            n /= 3;
        return n == 1;
        //return (int)(log10(n) / log10(3)) % 1 == 0;
        //return Integer.toString(n, 3).matches("^10*$");
        //return n > 0 && 1162261467 % n == 0;
    }
};

//Moving average
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        window = size;
        sum = 0;
    }
    double next(int val) {
        q.push_back(val);
        sum += val;
        if (q.size() > window) {
            sum -= q.front();
            q.pop_front();
        }
        return (double)sum/q.size();
    }
    deque<int> q;
    int window;
    int sum;
};

//Randomized Set
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        s.clear();
        srand(time(nullptr));
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        return s.insert(val).second;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        return s.erase(val) > 0;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        auto itr = s.begin();
        advance(itr, rand() % s.size());
        return *itr;
    }
    unordered_set<int> s;
};

//Longest consecutive sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int maxLength = 0, left = 0, right = 0;
        while (!s.empty()) {
            int num = *(s.begin());
            s.erase(num);
            left = num-1;
            while (s.find(left) != s.end()) {
                s.erase(left);
                left--;
            }
            right = num+1;
            while (s.find(right) != s.end()) {
                s.erase(right);
                right++;
            }
            maxLength = max(maxLength, right-left-1); //since left,right goes 1 beyond whats found
        }
        return maxLength;
    }
};

//Longest substring without repeating characters
//In "fsfetwenwe" string, notice that longest substring is "sfetw" and any substring starting before 'e'
//at index 3 (and after index 1) need not be examined as it will be shorter with a dup 'e' at 6.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int/*index*/> m;
        size_t length = 0, startIdx = 0;
        pair<unordered_map<char, int>::iterator, bool> ret;
        for (size_t i = 0; i < s.length(); i++) {
            ret = m.insert(make_pair(s[i], i));
            if (ret.second == false) { //failed to insert
                if (ret.first->second >= startIdx) {
                    //dup is in the subarray being validated
                    length = max(length, i-startIdx);
                    startIdx = ret.first->second + 1;
                }
                ret.first->second = i;
            }
        }
        return max(length, s.length()-startIdx);
    }
};

//Three sum
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> result;
        if (nums.empty() || nums.size() <= 2)
            return {};
        unordered_map<int/*val*/, int/*index*/> m;
        for (int i = 0; i < nums.size(); i++)
            m[nums[i]] = i; // only unique elements wil be present
        unordered_set<int> dups;
        for (int i = 0; i < nums.size()-1; i++) {
            if (dups.insert(nums[i]).second) { // not a dup element
                for (int j = i+1; j < nums.size(); j++) {
                    int complement = -nums[i]-nums[j];
                    auto itr = m.find(complement);
                    if (itr != m.end() && itr->second != i && itr->second != j) {
                        vector<int> triplet = {nums[i], nums[j], complement};
                        sort(triplet.begin(), triplet.end());
                        result.insert(triplet);
                    }
                }
            }
        }
        return vector<vector<int>>(begin(result), end(result));
    }
};
//Time: O(n^2), space: O(m) - m unique elements of nums & n - total size of nums.

//Valid abbreviation
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string>& dictionary) {
        m.clear();
        for (string s : dictionary)
            m[getAbbr(s)].insert(s);
    }
    string getAbbr(string s) {
        int n = s.length();
        if (n <= 2)
            return s;
        return (s[0] + to_string(n-2) + s[n-1]);
    }
    bool isUnique(string word) {
        auto itr = m.find(getAbbr(word));
        if (itr == m.end())
            return true;
        set<string>& s = itr->second;
        if (s.size() == 1 && s.find(word) != s.end())
            return true;
        return false;
    }
    map<string, set<string>> m;
};

// Jewels and stones
class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        set<char> j;
        for (char c : jewels)
            j.insert(c);
        int count = 0;
        for (char c : stones) {
            if (j.find(c) != j.end())
                ++count;
        }
        return count;
    }
};

//Top K frequent elements
//Note: read up on quickselect and Median of medians
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (int num: nums)
            m[num] += 1;
        priority_queue<Node, vector<Node>, Comp> q; //min-heap, maintaining only K elements
        for (auto itr = m.begin(); itr != m.end(); ++itr) {
            q.push({itr->first, itr->second});
            if (q.size() > k)
                q.pop(); //replace
        }
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.top().val); q.pop();
        }
        return result;
    }
    struct Node {
        int val;
        int count;    
    };
    struct Comp {
        bool operator()(const Node& a, const Node& b) {
            return a.count > b.count; // creating a min heap
        }    
    };
};

//Group anagrams
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (string str: strs) {
            string sstr(str);
            sort(sstr.begin(), sstr.end());
            m[sstr].emplace_back(str);
        }
        vector<vector<string>> result;
        for (auto itr = m.begin(); itr != m.end(); ++itr) {
            result.push_back(itr->second);
        }
        return result;
    }
};

//valid anagram
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        unordered_multiset<char> s1;
        for (char c : s)
            s1.insert(c);
        for (char c : t) {
            auto itr = s1.find(c);
            if (itr != s1.end())
                s1.erase(itr);
        }
        return s1.size()==0;
    }
};

//Isomorphic
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length())
            return false;
        unordered_map<char, int> m1;
        string s1, s2;
        for (int i = 0; i < s.length(); i++) {
            auto itr = m1.find(s[i]);
            if (itr == m1.end())
                m1[s[i]] = i;
            char c = (itr == m1.end()) ? i : itr->second;
            s1 += c;
        }
        m1.clear();
        for (int i = 0; i < t.length(); i++) {
            auto itr = m1.find(t[i]);
            if (itr == m1.end())
                m1[t[i]] = i;
            char c = (itr == m1.end()) ? i : itr->second;
            s2 += c;
        }
        return (s1 == s2);
    }
};

//Logger rate limiter
class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        m.clear();
        interval = 10;
    }    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        auto itr = m.find(message);
        if (itr == m.end() ||
            (itr != m.end() && ((timestamp-itr->second) >= interval))) {
            m[message] = timestamp;
            return true;
        }
        return false;
    }
    map<string, int> m;
    int interval;
};

//Contains Duplicates II
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int/*val*/, int/*index*/> m;
        for (int i = 0; i < nums.size(); i++) {
            auto itr = m.find(nums[i]);
            if (itr == m.end())
                m[nums[i]] = i;
            else {
                if (abs(itr->second-i) <= k)
                    return true;
                m[nums[i]] = i;
            }
        }
        return false;
    }
};

//First unique character in a string
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, pair<int/*index*/, int/*count*/>> m;
        for (int i = 0; i < s.length(); i++) {
            auto itr = m.find(s[i]);
            if (itr == m.end())
                m[s[i]] = make_pair(i, 1);
            else {
                pair<int,int>& p = itr->second;
                p.second += 1;
                m[s[i]] = p;
            }
        }
        int index = INT_MAX;
        for (auto itr = m.begin(); itr != m.end(); ++itr) {
            pair<int,int>& p = itr->second;
            if (p.second == 1)
                index = min(index, p.first);
        }
        return index == INT_MAX ? -1 : index;
    }
};

//Minimum index sum of 2 lists
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        map<string, int> m2;
        map<int, vector<string>> choices;
        for (int i = 0; i < list2.size(); i++)
            m2[list2[i]] = i;
        for (int i = 0; i < list1.size(); i++) {
            auto itr = m2.find(list1[i]);
            if (itr != m2.end()) {
                int sum = i+itr->second;
                auto citr = choices.find(sum);
                if (citr == choices.end())
                    choices[sum] = {list1[i]};
                else
                    citr->second.push_back(list1[i]);
            }
        }
        return choices.begin()->second;
    }
};

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
//Use of bitset is a viable option when there are no duplicate characters,
//otherwise use an array to track the occurrences
//sliding window computation for s2 speeds up the computation
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.empty() || s2.empty() || s2.length() < s1.length())
            return false;
        vector<int> h1(26,0), h2(26,0);
        for (int i = 0; i < s1.length(); i++) {
            h1[s1[i] - 'a']++;
            h2[s2[i] - 'a']++;
        }
        for (int i = 0; i < s2.length() - s1.length(); i++) {
            if (h1 == h2)
                return true;
            h2[s2[i+s1.length()] - 'a']++;
            h2[s2[i] - 'a']--;
        }
        return (h1 == h2);
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
        if (nums.empty())
            return -1;
        unordered_set<int> s(nums.begin(), nums.end());
        if (s.size() == 1)
            return *s.begin();
        if (s.size() == 2) {
            auto itr = s.begin(); advance(itr, 1);
            return max(*s.begin(), *itr);
        }
        priority_queue<int, vector<int>, greater<int>> q; //min-heap
        for (auto itr = s.begin(); itr != s.end(); itr++) {
            q.push(*itr);
            if (q.size() > 3)
                q.pop();
        }
        return q.top();
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
