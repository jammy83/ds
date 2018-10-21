
// Merge K sorted lists
struct ListNodeComp {
    bool operator<(const ListNodeComp& rhs) const {
        return item->val > rhs.item->val;
    }
    ListNode *item;
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNodeComp, vector<ListNodeComp>> minHeap;
        for (ListNode *node : lists) {
            if (node != nullptr) {
                minHeap.emplace(ListNodeComp{node});
            }
        }
        ListNode *result = nullptr, *prev = nullptr;
        while (!minHeap.empty()) {
            ListNodeComp top = minHeap.top();
            ListNode *topItem = top.item;
            minHeap.pop();
            if (result == nullptr) {
                result = topItem;
            } else {
                prev->next = topItem;
            }
            prev = topItem;
            ListNode *nextItem = topItem->next;
            topItem->next = nullptr;
            if (nextItem != nullptr) {
                minHeap.emplace(ListNodeComp{nextItem});
            }
        }
        return result;
    }
};

// merge K sorted arrays
struct vectorComp {
    bool operator<(const vectorComp& rhs) const {
        return *current > rhs.current;
    }
    vector<int>::iterator current;
    vector<int>::iterator end;
}
class Solution {
    vector<int> mergeSortedArrays(const vector<vector<int>>& arrays) {
        priority_queue<vectorComp, vector<vectorComp>> minHeap;
        for (const vector<int>& arr : arrays) {
            if (!arr.empty()) {
                minHeap.emplace_back(vectorComp{arr.begin(), arr.end()});    
            }
        }
        vector<int> result;
        while (!minHeap.empty()) {
            vectorComp t = minHeap.top();
            minHeap.pop();
            result.push_back(*t.current);
            if (t.current != t.end) {
                minHeap.emplace_back(vectorComp{next(t.current), t.end});
            }
        }
        return result;
    }
};
 
// sort an almost sorted array
// push k+1 elements into the min heap and sort
class Solution {
    vector<int> sortedAlmostSortedArray(istringstream s, int k) {
        vector<int> result;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int i = 0; i < k && *s >> x; ++i) {
            minHeap.push(x);
        }
        while (*s >> x) {
            minHeap.push(x);
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        return result;
    }   
};

// sort an increasing decreasing array
class Solution {
    vector<int> sortIncDecArray(const vector<int>& a) {
        vector<vector<int>> arrays;
        bool increasing = true;
        int start = 0;
        for (int i = 1; i <= a.size(); i++) {
            if (i == a.size() ||
                (a[i-1] < a[i] && !increasing) ||
                (a[i-1] > a[i] && increasing)) {
                if (increasing) {
                    arrays.push_back(a.begin() + start, a.begin() + i);
                } else {
                    arrays.push_back(a.rbegin() + a.size() - i, a.rbegin() + a.size() - start);
                }
                start = i;
                increasing = !increasing;
            }
        }
        return mergeSortedArrays(arrays);
    }
};

// Running median
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    void addNum(int num) {
        if (minHeap.empty()) {
            minHeap.emplace(num);
        } else {
            if (num >= minHeap.top()) {
                minHeap.emplace(num);
            } else {
                maxHeap.emplace(num);
            }
        }
        reHeap();
    }
    // median of the stream is the avg of 2 middle elements in case 
    // of event set of numbers and the middle element in case of odd set
    // It is computed as the avg of max from the smaller set and min from
    // the larger set of elements.
    double findMedian() {
        if (minHeap.size() == maxHeap.size()) {
            return (minHeap.top()+maxHeap.top()) / 2;
        }
        return minHeap.top();
    }
private:
    priority_queue<double, vector<double>, less<double>> maxHeap;
    priority_queue<double, vector<double>, greater<double>> minHeap;
    void reHeap() {
        if (minHeap.size() > maxHeap.size() + 1) {
            maxHeap.emplace(minHeap.top());
            minHeap.pop();
        } else if (maxHeap.size() > minHeap.size()) {
            minHeap.emplace(maxHeap.top());
            maxHeap.pop();
        }
    }
};

// Implement stack using heap
class myStack {
public:
    void push(int num) {
        maxHeap.emplace(valueWithRank{num, timestamp++});
    }
    int pop() {
        if (maxHeap.empty()) {
            return -1;
        }
        int value = maxHeap.top().val;
        maxHeap.pop();
        return value;
    }
    int peek {
        return maxHeap.top().val;
    }
private:
    struct valueWithRank {
        bool operator<(const valueWithRank& rhs) {
            return rank < rhs.rank;
        }
        int val;
        int rank;
    };
    priority_queue<valueWithRank, vector<valueWithRank>> maxHeap;
    int timestamp;
};
