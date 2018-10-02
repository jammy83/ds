//
//  trees.cpp
//  
//
//  Created by Janani Natarajan on 11/22/14.
//
//

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isValidBSTWork(TreeNode *root, TreeNode *min, TreeNode *max) {
        if ((min && root->val <= min->val) ||
            (max && root->val >= max->val)) {
            return false;
        }
        bool lTree = root->left ? isValidBSTWork(root->left, min, root) : true;
        bool rTree = root->right ? isValidBSTWork(root->right, root, max) : true;
        return lTree && rTree;
    }
    
    bool isValidBST(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }
        return isValidBSTWork(root, nullptr, nullptr);
    }
};

class Solution {
public:
    void inorderTraversalWork(TreeNode *root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        inorderTraversalWork(root->left, result);
        result.push_back(root->val);
        inorderTraversalWork(root->right, result);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderTraversalWork(root, result);
        return result;
    }
    // iterative
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s;
        TreeNode *curr = root;
        while (!s.empty() || curr != nullptr) {
            if (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            } else {
                TreeNode *node = s.top();
                result.push_back(node->val); s.pop();
                curr = node->right;
            }
        }
        return result;
    }
};

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushAll(root);
    }
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }
    /** @return the next smallest number */
    int next() {
        TreeNode *node = s.top(); s.pop();
        pushAll(node->right);
        return node->val;
    }
private:
    void pushAll(TreeNode *node) {
        while (node != nullptr) {
            s.push(node);
            node = node->left;
        }
    }
    stack<TreeNode*> s;
};

class Solution {
public:
    TreeNode* searchBST(TreeNode *root, int target) {
        TreeNode *curr = root;
        while (curr != nullptr) {
            if (curr->val == target) {
                return curr;
            } else if (curr->val > target) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return nullptr;
    }
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode *root, int target) {
        TreeNode *curr = root, *prev = nullptr;
        while (curr != nullptr) {
            prev = curr;
            if (target < curr->val) {
                curr = curr->left;
            } else if (target > curr->val) {
                curr = curr->right;
            }
        }
        TreeNode *node = new TreeNode(target);
        if (prev != nullptr) { 
            if (prev->val > target) {
                prev->left = node;
            } else {
                prev->right = node;
            }
        } else {
            root = node;
        }
        return root;
    }
};

class Solution {
public:
    TreeNode* findMinBST(TreeNode *node) {
        while (node->left != nullptr) {
             node = node->left;
        }
        return node;
    }
    TreeNode* inorderSuccessorBST(TreeNode *root, TreeNode *node) {
        // if there is a right subtree
        if (node->right != nullptr) {
            return findMinBST(node->right);
        }
        /////
        TreeNode *p = node->parent;
        while (p != nullptr && node == parent->right) {
            node = p;
            p = p->parent;
        }
        return p;
        /////
        TreeNode *succ = nullptr, *curr = root;
        while (curr != nullptr) {
            if (node->val < curr->val) {
                succ = curr;
                curr = curr->left;
            } else if (node->val > curr->val) {
                curr = curr->right;
            } else {
                break;
            }
        }
        return succ;
        /////
    }
};

class Solution {
public:
    TreeNode* findMaxBST(TreeNode *node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    TreeNode* inorderPredecessorBST(TreeNode *root, TreeNode *node) {
        if (root == nullptr || node == nullptr) {
            return nullptr;
        }
        if (node->left != nullptr) {
            return findMax(node->left);
        }
        ////////
        TreeNode *p = node->parent;
        while (p != nullptr && node == p->left) {
            node = p;
            p = p->parent;
        }
        return p;
        ////////
        TreeNode *pre = nullptr, *curr = root;
        while (curr != nullptr) {
            if (node->val < curr->val) {
                curr = curr->left;
            } else if (node->val > curr->val) {
                pre = curr;
                curr = curr->right;
            } else {
                break;
            }
        }
        return pre;
    }
};

// Delete node from BST
class Solution {
public:
    TreeNode* findMinBST(TreeNode *node) {
        while (node->left != nullptr) {
             node = node->left;
        }
        return node;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
       if (root == nullptr) {
            return nullptr;
        }
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            TreeNode *temp;
            if (root->left == nullptr || root->right == nullptr) {
                temp = root->left ? root->left : root->right;
                delete(root);
                return temp;
            }
            temp = findMinBST(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
        return root; 
    }
};

// check if Binary tree is height balanced
class Solution {
public:
    int isBalancedWork(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        int left = isBalancedWork(root->left);
        int right = isBalancedWork(root->right);
        if (left == -1 || right == -1 || abs(left-right) > 1) {
            return -1;
        }
        return (left > right ? left : right) + 1;
    }
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        return isBalancedWork(root) != -1;
    }
};

// level order traversal of binary tree BFS
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int count = q.size();
            vector<int> level;
            level.reserve(count);
            while (count != 0) {
                TreeNode *next = q.front(); q.pop();
                level.push_back(next->val);
                if (next->left != nullptr) {
                    q.push(next->left);
                }
                if (next->right != nullptr) {
                    q.push(next->right);
                }
                --count;
            }
            result.push_back(level);
        }
        return result;
    }
};

// level order traversal of binary tree using DFS and printing bottom up
class Solution {
public:
    // height can be deduced otherwise using a post-order iterative method or
    // level order traversal using BFS
    int maxHeight(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int left = maxHeight(root->left);
        int right = maxHeight(root->right);
        return left > right ? left + 1 : right + 1;
    }
    void levelOrderBottomWork(TreeNode *root, vector<vector<int>>& result, int level) {
        if (root == nullptr) {
            return;
        }
        result[level-1].push_back(root->val);
        levelOrderBottomWork(root->left, result, level-1);
        levelOrderBottomWork(root->right, result, level-1);
    }
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        int h = maxHeight(root);
        vector<vector<int>> result;
        for (int i = 0; i < h; ++i) {
            result.push_back(vector<int>());
        }
        levelOrderBottomWork(root, result, h);
        return result;
    }
};

class Solution {
public:
    void preorderTraversalWork(TreeNode *root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        /*
        result.push_back(root->val);
        preorderTraversalWork(root->left, result);
        preorderTraversalWork(root->right, result);
        */
        TreeNode *curr = root;
        stack<TreeNode*> s;
        while (curr != nullptr || !s.empty()) {
            if (curr != nullptr) {
                result.push_back(curr->val);
                s.push(curr);
                curr = curr->left;
            } else {
                TreeNode *temp = s.top(); s.pop();
                curr = temp->right;
            }
        }
        /*
        stack<TreeNode*> s;
        s.push(curr);
        while (!s.empty()) {
            TreeNode* temp = s.top(); s.pop();
            result.push_back(temp->val);
            if (temp->right) { s.push(temp->right); }
            if (temp->left)  { s.push(temp->left); }
        }
        */
    }
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        preorderTraversalWork(root, result);
        return result;
    }
};

class Solution {
public:
    void postorderTraversalWork(TreeNode *root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        /*
        postorderTraversalWork(root->left, result);
        postorderTraversalWork(root->right, result);
        result.push_back(root->val);
        */
        TreeNode *curr = root, *last = nullptr;
        stack<TreeNode*> s;
        while (curr != nullptr || !s.empty()) {
            if (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            } else {
                TreeNode *temp = s.top();
                if (temp->right != nullptr && temp->right != last) {
                    curr = temp->right;
                } else {
                    result.push_back(temp->val); s.pop();
                    last = temp;
                }
            }
        }
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        postorderTraversalWork(root, result);
        return result;
    }
};

// LCA of a BST
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!p || !q) {
            return nullptr;
        }
        while (root != nullptr) {
            if (root->val < p->val && root->val < q->val) {
                root = root->right;
            } else if (root->val > p->val && root->val > q->val) {
                root = root->left;
            } else {
                return root;
            }
        }
        return nullptr;
    }
};

// LCA  of a binary tree if both p and q are present in the tree. Otherwise
// search for the other when only one found explicitly.
class Solution {
public:
    TreeNode* lowestCommonAncestorWork(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root == p || root == q) {
            return root;
        }
        TreeNode *lLca = lowestCommonAncestorWork(root->left, p , q);
        TreeNode *rLca = lowestCommonAncestorWork(root->right, p , q);
        if (lLca && rLca) {
            return root;
        }
        return lLca != nullptr ? lLca : rLca;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) {
            return nullptr;
        }
        return lowestCommonAncestorWork(root, p, q);
    }
};

// LCA of a binary tree given the parent pointers
class Solution {
public:
    int getDepth(TreeNode *node) {
        int depth = 0;
        while (node != nullptr) {
            ++depth;
            node = node->parent;
        }
        return depth;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return nullptr;
        }
        int h1 = getDepth(p);
        int h2 = getDepth(q);
        if (h2 > h1) {
            swap(p, q);
        }
        int diff = abs(h1-h2);
        while (diff-- > 0 && p != nullptr) {
            p = p->parent;
        }
        while (p != nullptr && q != nullptr && p != q) {
            p = p->parent;
            p = q->parent;
        }
        return p;
    }
};

// LCA optimized for close ancestors with parent pointers
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || !p || !q) {
            return nullptr;
        }
        set<TreeNode*> map;
        pair<set<TreeNode*>::iterator, bool> result;
        while (p != nullptr|| q != nullptr) {
            if (p != nullptr) {
                result = map.insert(p);
                if (result.second == false) {
                    return p;
                }
                p = p->parent;
            }
            if (q != nullptr) {
                result = map.insert(q);
                if (result.second == false) {
                    return q;
                }
                q = q->parent;
            }
        }
        return nullptr;
    }
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        bool leftToRight = true;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> output(size);
            for (int i = 0; i < size; i++) {
                TreeNode* temp = q.front(); q.pop();
                int index = leftToRight ? i : (size-1-i);
                cout << index;
                output[index] = temp->val;
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
            result.push_back(output);
            leftToRight = !leftToRight;
        }
        return result; 
    }
};

// Maximum height of the tree
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int lheight = maxDepth(root->left);
        int rheight = maxDepth(root->right);
        return lheight > rheight ? lheight + 1 : rheight + 1; 
    }
};

// Minimum height of the tree
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int lheight = minDepth(root->left);
        int rheight = minDepth(root->right);
        // if one of the children is not present, it should still consider
        // the height of the child that is NON-NULL and not return 0.
        if (root->left == nullptr) {
            return rheight + 1;
        } else if (root->right == nullptr) {
            return lheight + 1;
        }
        return lheight < rheight ? lheight + 1 : rheight + 1;
    }
};

// sorted array to balanced BST
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = start + (end - start) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, start, mid-1);
        root->right = sortedArrayToBST(nums, mid+1, end);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty()) {
            return nullptr;
        }
        return sortedArrayToBST(nums, 0, nums.size()-1);
    }
};

// sorted linked list to balanced BST
class Solution {
public:
    int findLen(ListNode *head) {
        int count = 0;
        while (head != nullptr) { 
            ++count;
            head = head->next;
        }
        return count;
    }
    TreeNode* sortedListToBSTWork(ListNode **head, int start, int end) {
        if (start > end) {
            return nullptr;
        } 
        int mid = start + (end-start) / 2;
        TreeNode *left = sortedListToBSTWork(head, start, mid-1);
        TreeNode *root = new TreeNode((*head)->val);
        root->left = left;
        *head = (*head)->next;
        root->right = sortedListToBSTWork(head, mid+1, end);
        return root;
    }
    TreeNode* sortedListToBST(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        int len = findLen(head);
        return sortedListToBSTWork(&head, 0, len-1);
    }
};

// https://stackoverflow.com/questions/33062228/why-it-is-impossible-to-construct-binary-tree-with-pre-order-post-order-and-lev
// Building a binary tree from inorder and postorder traversal
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, int start, int end, vector<int>& postorder,
                       unordered_map<int,int>& map) {
        if (postorder.empty() || start > end) {
            return nullptr;
        }
        vector<int>::reverse_iterator itr = postorder.rbegin();
        int i = map[*itr];
        postorder.resize(postorder.size()-1);
        TreeNode *root = new TreeNode(*itr);
        root->right = buildTree(inorder, i+1, end, postorder, map);
        root->left = buildTree(inorder, start, i-1, postorder, map);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }
        return buildTree(inorder, 0, inorder.size()-1, postorder, map);
    }
};

// Build a binary tree from inorder and pre-order traversal
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, int start, int end,
                       unordered_map<int, int>& map) {
        if (preorder.empty() || start > end) {
            return nullptr;
        }
        vector<int>::iterator itr = preorder.begin();
        int index = map[*itr];
        TreeNode *root = new TreeNode(*itr);
        preorder.erase(preorder.begin());
        root->left = buildTree(preorder, inorder, start, index-1, map);
        root->right = buildTree(preorder, inorder, index+1, end, map);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }
        return buildTree(preorder, inorder, 0, inorder.size()-1, map);
    }
};

// Build a full binary tree from pre-order and post-order
class Solution {
public:
    TreeNode* constructFromPrePostWork(vector<int>& pre, vector<int>& post, int start, int end,
                                       unordered_map<int, int>& mapPost) {
        if (pre.empty() || start > end) {
            return nullptr;
        }
        vector<int>::iterator itr = pre.begin();
        TreeNode *root = new TreeNode(*itr);
        int index = mapPost[*++itr]; cout << index;
        pre.erase(pre.begin());
        if (index <= end) {
            root->left = constructFromPrePostWork(pre, post, start, index, mapPost);
            root->right = constructFromPrePostWork(pre, post, index+1, end, mapPost);
        }
        return root;
    }
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        unordered_map<int, int> m;
        for (int i = 0; i < post.size(); i++) {
            m[post[i]] = i;
        }
        return constructFromPrePostWork(pre, post, 0, pre.size()-1, m);
    }
};

// flatten a binary tree to a linked list in-place
// alternative soln would be to use level order traversal and a prev node pointer and updating prev->right to 
// the next item popped. But that consumes memory for the queue
// O(1) space: recursive soln
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr ||
            (root->left == nullptr && root->right == nullptr)) {
            return;
        }
        if (root->left != nullptr) {
            flatten(root->left);
            TreeNode *tmp = root->right;
            root->right = root->left;
            root->left = nullptr;
            TreeNode *last = root->right;
            while (last->right != nullptr) {
                last = last->right;
            }
            last->right = tmp;
        }
        flatten(root->right);
    }
};

// Binary tree right-side view
class Solution {
public:
    void rightSideViewWork(TreeNode* root, int level, int& max, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        if (level > max) {
            result.push_back(root->val);
            max = level;
        }
        rightSideViewWork(root->right, level+1, max, result);
        rightSideViewWork(root->left, level+1, max, result);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result; int maxLevel = 0;
        rightSideViewWork(root, 1, maxLevel, result);
        return result;
    }
};

// Print boundary of binary tree
class Solution {
public:
    void printBoundaryLeft(TreeNode *root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        if (root->left) {
            result.push_back(root->val);
            printBoundaryLeft(root->left, result);
        } else if (root->right) {
            result.push_back(root->val);
            printBoundaryLeft(root->right, result);
        }
        // don't push leaf nodes
    }
    void printLeaves(TreeNode *root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        printLeaves(root->left, result);
        if (root->left == nullptr && root->right == nullptr) {
            result.push_back(root->val);
        }
        printLeaves(root->right, result);
    }
    void printBoundaryRight(TreeNode *root, vector<int>& result) {
        // bottom-up
        if (root == nullptr) {
            return;
        }
        if (root->right) {
            printBoundaryRight(root->right, result);
            result.push_back(root->val);
        } else if (root->left) {
            printBoundaryLeft(root->left, result);
            result.push_back(root->val);
        }
        // don't push leaf nodes
    }
    vector<int> printBoundaryBinaryTree(TreeNode *root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        printBoundaryLeft(root, result); // top-down of leftmost nodes
        printLeaves(root->left, result); // leaves of left sub-tree
        printLeaves(root->right, result); // leaves of right sub-tree
        printBoundaryRight(root, result); // bottom-up rightmost nodes
        return result;
    }
};

// Print nextRight pointer of a complete binary tree
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connectWork(TreeLinkNode *root) {
        if (root == nullptr) {
            return;
        }
        if (root->left) {
            root->left->next = root->right;
        }
        if (root->right) {
            root->right->next = root->next ? root->next->left : nullptr;
        }
        connectWork(root->left);
        connectWork(root->right);
    }
    void connect(TreeLinkNode *root) {
        if (root == nullptr) {
            return;
        }
        root->next = nullptr;
        return connectWork(root);
    }
};

// print nextRight pointer of any binary tree iteratively
class Solution {
public:
    TreeLinkNode* findNext(TreeLinkNode *node) {
        while (node != nullptr) {
            TreeLinkNode *result = node->left ? node->left : node->right;
            if (result != nullptr) {
                return result;
            }
            node = node->next;
        }
        return nullptr;
    }
    void connect(TreeLinkNode *root) {
        if (root == nullptr) {
            return;
        }
        root->next = nullptr;
        while (root != nullptr) {
            TreeLinkNode *curr = root;
            while (curr != nullptr) {
                if (curr->left) {
                    curr->left->next = curr->right ? curr->right : findNext(curr->next);
                }
                if (curr->right) {
                    curr->right->next = findNext(curr->next);
                }
                curr = curr->next;
            }
            root = root->left ? root->left : (root->right ? root->right : findNext(root->next));
        }
    }
};

// check if a binary tree is symmetric
class Solution {
public:
    bool isSymmetricWork(TreeNode *l, TreeNode *r) {
        return ((l == nullptr && r == nullptr) ||
                (l != nullptr && r != nullptr && l->val == r->val &&
                isSymmetricWork(l->left, r->right) &&
                isSymmetricWork(l->right, r->left)));
    }
    bool isSymmetric(TreeNode *root) {
        return (root == nullptr ||
                isSymmetricWork(root->left, root->right));
    }
};

// Inorder traversal of a binary tree with O(1) space
class Solution {
public:
    vector<int> InorderTraversal(TreeNode *root) {
        TreeNode *prev = nullptr, *curr = root;
        vector<int> result;
        while (curr != nullptr) {
            TreeNode *next = nullptr;
            if (curr->parent == prev) { // processing the left sub-tree
                if (curr->left != nullptr) {
                    next = curr->left;
                } else {
                    result.push_back(curr->val);
                    next = curr->right != nullptr ? curr->right : curr->parent;
                }
            } else if (curr->left == prev) { // done with the left sub-tree
                result.push_back(curr->val);
                next = curr->right != nullptr ? curr->right : curr->parent;
            } else { // done with both children
                next = curr->parent;
            }
            prev = curr;
            curr = next;
        }
        return result;
    }
};

int Tree::kthSmallestElementBST(int k)
{
    node* start = root;
    if (start == NULL) {
        return -1;
    }
    while (start != NULL) {
        if (start->rank+1 == k) {
            return start->key;
        } else if (start->rank < k) {
            start = start->right;
            k -= (start->rank+1);
        } else {
            start = start->left;
        }
    }
    return -1;
}

//What is a subtree? If the values matched?
//Another soln: Enter the elements of the larger tree into a hashTable
//and lookup the elements of the other tree to confirm if its a subtree
//And all this will tell you is that the elements are present.. but
//in what order/structure? It has to be solved like the following..

//'n' - no. of nodes in T1, 'm' - nodes in T2 and 'k' is the
//no. of occurrences of T2's root in T1.
//Time complexity: O(n+km)
bool Tree::isSubTree(Tree* t1, Tree* t2)
{
    if (t2 == NULL || t2->root == NULL) { //empty tree is considered a subtree
        return true;
    }
    if (t1 == NULL || t1->root == NULL) {
        return false;
    }
    return isSubTreeUtil(t1->root, t2->root);
}

bool Tree::isSubTreeUtil(node* t1, node* t2)
{
    if (t1 == NULL) {
        return false;
    }
    if (t1->key == t2->key) {
        if (matchTree(t1, t2)) {
            return true;
        }
    }
    return (isSubTreeUtil(t1->left, t2) ||
            isSubTreeUtil(t1->right, t2));
}

bool Tree::matchTree(node* t1, node* t2)
{
    // if both are empty, return true
    if (!t1 && !t2) {
        return true;
    }
    if (!t1 || !t2) {
        return false;
    }
    if (t1->key != t2->key) {
        return false;
    }
    if (!matchTree(t1->left, t2->left) ||
        !matchTree(t1->right, t2->right)) {
        return false;
    }
    return true;
}

int Tree::convertTreeToSumTree()
{
    node* start = root;
    if (start == NULL) {
        return 0;
    }
    int prev = start->key;
    start->key = convertTreeToSumTree(start->left) + convertTreeToSumTree(start->right);
    return prev+start->key;
}

bool Tree::isFoldable()
{
    if (root == NULL) {
        return false;
    }
    return isFoldableUtil(root->left, root->right);
}

bool Tree::isFoldableUtil(node* n1, node* n2)
{
    if (!n1 && !n2) {
        return true;
    }
    if (!n1 || !n2) {
        return false;
    }
    return (isFoldableUtil(n1->left, n2->right) &&
            isFoldableUtil(n1->right, n2->left));
}

//changes the tree to its mirror image
void Tree::mirror(node* root)
{
    if (root == NULL) {
        return;
    }
    mirror(root->left);
    mirror(root->right);
    if (root->left || root->right) {
        node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

//creates a duplicate node and insert as the left child of the original node
void Tree::doubleTree(node* root)
{
    if (root == NULL) {
        return;
    }
    doubleTree(root->left);
    doubleTree(root->right);
    node* newNode = new node(root->key);
    if (newNode == NULL) {
        return;
    }
    newNode->left = root->left;
    newNode->right = NULL; newNode->parent = root;
    root->left = newNode;
    root->rank++;
}

//print if the tree, starting at the root, leads to a given sum
bool Tree::hasPathSum(node* node, int sum)
{
    // return true if we run out of tree and sum==0
    if (node == NULL) {
        return (sum == 0);
    } else {
        // otherwise check both subtrees
        int subSum = sum - node->key;
        return(hasPathSum(node->left, subSum) ||
               hasPathSum(node->right, subSum));
    }
}

//given a binary tree, print all the paths that lead to a particular sum
//starting from any node in the tree and not necessarily the root
//time complexity: O(nlogn)
bool Tree::findPathWithSum(node* start, vector<node*> &v, int& sum, int target)
{
    if (start == NULL) {
        return false;
    }

    v.push_back(start);
    sum += start->key;
    if (sum == target) {
        for (vector<node*>::iterator* itr = v.begin(); itr != v.end(); itr++) {
            cout << (*itr)->key << " ";
        }
        cout << endl;
        return true;
    }

    if (findPathWithSum(start->left, v, sum, target) ||
        findPathWithSum(start->right, v, sum, target)) {
        return true;
    }

    node* last = v.back();
    sum -= last->key;
    v.pop_back();
    
    return false;
}

struct {
    int key;
    nodeDLL* prev;
    nodeDLL* next;
} nodeDLL;

// do inorder traversal of a binary tree to convert it to a DLL
nodeDLL* Tree::convertTreeToDLL()
{
    node* start = root;
    if (start == NULL) {
        return NULL;
    }
    nodeDLL *head = NULL, *prev = NULL;
    stack<node*> s;
    while (!s.empty() || start != NULL) {
        if (start) {
            s.push(start);
            start = start->left;
        } else {
            node* top = s.top(); s.pop();
            nodeDLL* item = new nodeDLL(top->key);
            if (item == NULL) {
                return NULL;
            }
            if (prev != NULL) {
                prev->next = item;
            } else {
                head = item;
            }
            item->prev = prev;
            item->next = NULL; //safe to set this if this is the last node
            prev = item;
            start = top->right;
        }
    }
    return head;
}
//pre-order traversal with "-1" to denote lack of a child
void Tree::serializeBinaryTree(node* root, FILE *fp)
{
    if (root == NULL) {
        fprintf(fp, "%d ", -1);
        return;
    }
    fprintf(fp, "%d ", root->key);
    serializeBinaryTree(root->left, fp);
    serializeBinaryTree(root->right, fp);
}

//pre-oder traversal
void Tree::deserializeBinaryTree(node** root, FILE *fp)
{
    int val = 0;
    if (!fscanf(fp, "%d ", &val) || val == -1) {
        return;
    }
    *root = new node(val);
    if (!*root) {
        return;
    }
    deserializeBinaryTree(*root->left, fp);
    deserializeBinaryTree(*root->righ, fp);
}

//de-serialize a BST from a pre-order traversal output
node* Tree::deserializeBSTIterative(int* pre, int size)
{
    if (size < 0) {
        return NULL;
    }
    stack<node*> s;
    node* root = new node(pre[0]);
    if (!root) {
        return NULL;
    }
    s.push(root);

    for (int i = 1, node* temp = NULL, *last = NULL; i < size; i++) {
        while (!s.empty() && pre[i] > (temp = s.top())) {
            s.pop();
            last = temp;
        }
        if (last == NULL) {
            node* top = s.top();
            top->left = new node(pre[i]);
            if (!top->left) {
                return NULL:
            }
            s.push(top->left);
        } else {
            last->right = new node(pre[i]);
            if (!last->right) {
                return NULL;
            }
            s.push(last->right);
        }
    }
    return root;
}

// Do an inorder traversal. Note that the horizontal distance from the root
// on either ends determines the order in which the nodes get printed
void Tree::printBinaryTreeInVerticalOrder(node* start)
{
    std::miltimap<int,int> map;
    calculateHorizontalDist(start, 0, map);
    int last = 0;
    for (std::multimap<int,int>::iterator itr = map.begin(); itr != map.end(); itr++) {
        if (last != (*itr).first) {
            cout << endl;
            last = (*itr).first;
        }
        cout << (*itr).second << " ";
    }
}
void Tree::calculateHorizontalDist(node* root, int dist, multimap<int, int>& map) {
    if (root == NULL) {
        return;
    }
    map.insert(std::pair(dist, root->key));
    printBinaryTreeInVerticalOrder(root->left, dist-1, map);
    printBinaryTreeInVerticalOrder(root->right, dist+1, map);
}
