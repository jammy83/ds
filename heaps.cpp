
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
 
//sort an almost sorted array
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
