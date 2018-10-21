
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
