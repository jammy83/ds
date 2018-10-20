
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
    
