
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
