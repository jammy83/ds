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

// leven order traversal of binary tree BFS
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

// LCA  of a binary tree

void Tree::traverseLevelOrderZigZag(node* start)
{
    if (start == NULL) {
        return;
    }
    stack<node*> s;
    s.push(start);
    bool leftToRight = false;
    while (!s.empty()) {
        int count = s.size();
        while (count > 0) {
            node* curr = s.top(); s.pop();
            cout << curr->key << " ";
            if (leftToRight) {
                if (curr->right) s.push(curr->right);
                if (curr->left) s.push(curr->left);
            } else {
                if (curr->left) s.push(curr->left);
                if (curr->right) s.push(curr->right);
            }
            count--;
        }
        cout << endl;
        leftToRight = !leftToRight;
    }
}

//using parent pointer
int Tree::findHeightWrtToAGivenNode(node* p)
{
    int height = 0;
    while (p) {
        ++height;
        p = p->parent;
    }
    return height;
}

node* Tree::findLCABST(node* start, int key1, int key2)
{
    // with the assumption that the keys are in the tree
    while (start != NULL) {
        if (start->key > key1 && start->key > key2) {
            start = start->left;
        } else if (start->key < key1 && start->key < key2) {
            start = start->right;
        } else {
            // if the two nodes are on either side of a node
            // then thats the common ancestor
            return start;
        }
    }
    return NULL;
    
    //recursive
    if (start == NULL) {
        return NULL;
    }
    if (start->key > key1 && start->key > key2) {
        findLCABST(start->left, key1, key2);
    } else if (start->key < key1 && start->key < key2) {
        findLCABST(start->right, key1, key2);
    }
    return start;
    ////////////
}

bool Tree::findPath(node* start, int key, vector<node*> &path)
{
    if (start == NULL) {
        return false;
    }
    path.push_back(start);
    if (start->key == key) {
        return true;
    }
    // findPath seems to work like inorder traversal if you want
    // to implement this iteratively
    if ((start->left && findPath(start->left, key, path)) ||
        (start->right && findPath(start->right, key, path)) ) {
        return true;
    }
    path.pop_back();
    return false;
}

//This solution below won't work..Basically comparison of the 2 vectors aren't correct.
node* Tree::findLCA(node* start, int key1, int key2)
{
    if (start == NULL) {
        return NULL;
    }
    vector<node*> v1;
    vector<node*> v2;
    if (!findPath(start, key1, v1) || !findPath(start, key2, v2)) {
        return NULL;
    }
    int i = 0;
    for ( ; i < v1.size() && i < v2.size(); ++i) {
        if (v1[i] != v2[i]) {
            break;
        }
    }
    if (i > 0) {
        return v1[i-1];
    }
    return NULL;
}

//assumes that both the nodes *are* in the tree!
node* Tree::findLCAPerf(node* start, node* p, node* q)
{
    if (start == NULL) {
        return NULL;
    }
    if (start == p || start == q) {
        return start;
    }
    node* l = findLCAPerf(start->left, p, q);
    node* r = findLCAPerf(start->right, p, q);
    if (l && r) {
        return start;
    }
    return l ? l : r;
}

node* Tree::findLCAwithParent(node* p, node* q)
{
    int h1 = findHeightWrtToAGivenNode(p);
    int h2 = findHeightWrtToAGivenNode(q);
    
    // swap both nodes in case p is deeper than q.
    if (h1 > h2) {
        int temp = h1; h1 = h2; h2 = temp;
        node* t = p; p = q; q = t;
    }
    // invariant: h1 <= h2.
    int dh = h2 - h1;
    for (int h = 0; h < dh && q != NULL; ++h) {
        q = q->parent;
    }
    while (p && q) {
        if (p == q) return p;
        p = p->parent;
        q = q->parent;
    }
    return NULL;  // p and q are not in the same tree
}

int Tree::getRankBST(int key)
{
    node* target = searchBST(key);
    return ((target != NULL) ? target->rank : 0);
}

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

//create a balanced tree given a sorted array of elements
//Time complexity O(n)
node* Tree::sortedArrayToBalancedBST(int* arr, int start, int end)
{
    if (start > end) return NULL;

    int mid = start + (end-start) / 2; //avoids overflow
    node* root = new node(arr[mid]);
    if (root) {
        root->left = sortedArrayToBalancedBST(arr, start, mid-1);
        root->right = sortedArrayToBalancedBST(arr, mid+1, end);
    }
    return root;
}

//Naive solution: Always finding the middle element traversing n/2 elements each time
//Time Complexity: O(nlogn)
//Below is the bottom-up approach taken by just walking the linked list and
//constructing the tree by linking them to its parent
//Time Complexity: O(n)
node* Tree::sortedListToBalancedBST(LinkedListnode** head, int start, int end)
{
    if (start > end) return NULL;

    int mid = start + (end-start) / 2; //avoids overflow
    node* leftChild = sortedListToBST(head, start, mid-1);
    node* parent = new node((*head)->_data);
    if (parent) {
        parent->left = leftChild;
        *head = (*head)->_next;
        parent->right = sortedListToBST(head, mid+1, end);
    }
    return parent;
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

//connect nodes in the same level using 'nextRight' pointer
void Tree::populateNextRight(treeNodeSpl* start)
{
    if (start == NULL) {
        return;
    }
    if (start->left) {
        start->left->nextRight = start->right;
    }
    if (start->right) {
        start->right->nextRight = (start->nextRight) ?
                                  start->nextRight->left : NULL;
    }
    populateNextRight(start->left);
    populateNextRight(start->right);
}

int main()
{
    return 0;
}

