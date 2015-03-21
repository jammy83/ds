//
//  trees.cpp
//  
//
//  Created by Janani Natarajan on 11/22/14.
//
//

#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

// Define a tree node
class node {
 public:
    int key;
    node* left;
    node* right;
    node* parent;
    int rank; // no. of items <= this node's val

    node(int val) : key(val), left(NULL), right(NULL), parent(NULL), rank(1) {}
    ~node() {
        left = right = parent = NULL;
    }
};

// Define a tree
class Tree {
 private:
    node* root;
    int items;

    void destroyTree(node* start);
    bool insertBST(node* n);
    bool isFoldableUtil(node* n1, node* n2);

 public:
    tree() : root(NULL), items(0) {}
    ~tree() {
        destroyTree(root);
    }

    bool isEmpty() { return (root == NULL); }
    // Operations
    bool insertBST(int key);
    node* searchBST(int key);

    // For just binary trees traverse the tree keeping track of min and max
    node* findMinBST(node* start);
    node* findMaxBST(node* start);

    // Traversals for any binary tree including BST
    int traverseByLevel();
    void traverseInOrder(node* start);
    void traverseInOrderIterative(node* start);
    void traversePreOrder(node* start);
    void traversePreOrderItertive(node* start);
    void traversePostOrder(node* start);
    int traversePostOrderIterative(node* start); // returns max depth at root or height of the tree

    bool checkIfBST(node* start);

    // Height: applies to any binary tree (including BST)
    int findHeight();
    int findHeightWrtToAGivenNode(node* p);
    int findMaxDepth(node* start);
    bool checkIfBalanced(node* start);
    int checkIfHeightBalanced(node* start);

    // Use parent pointers or just recuse down the tree
    // A simple inorder traversal of the nodes will tell you this as well.
    node* findPredecessorInOrder();
    node* findSuccessorInOrder();

    //LCA of binary and BST
    node* findLCABST(node* start, int key1, int key2);
    bool findPath(node* start, int key, vector<node*> &path);
    node* findLCA(node* start, int key1, int key2);
    node* findLCAPerf(node* start, node* p, node* q);
    node* findLCAwithParent(node* p, node* q);

    //Rank
    int getRank(int key);
    int kthSmallestElement(int n);
    
    node* createTree(int* arr, int start, int end);
    bool isSubTree(node* t1, node* t2);
    bool matchTree(node* t1, node* t2);
    void convertTreeToSumTree();
    bool isFoldable();
    void mirror();
    void doubleTree();
    bool hasPathSum(node* node, int sum);
    void findPathWithSum(node* start, vector<node*> &v, int& sum, int target);
    nodeDLL* convertTreeToDLL();

    //Serialize/de-serialize
    void serializeBinaryTree(node* root, FILE* fp);
    void deserializeBinaryTree(node** root, FILE* fp);
    node* deserializeBSTIterative(int* pre, int size);

    void printBinaryTreeInVerticalOrder(node* root, int dist, hashTable<int,int>& hT);

    void inOrderTraversalWithoutStack(node* start); // threaded binary tree // not imeplemented
};

void Tree::destroyTree(node* start)
{
    if (start) {
        if (start->left) {
            destroyTree(start->left);
        }
        if (start->right) {
            destroyTree(start->right);
        }
        delete start;
    }
}

bool Tree::insertBST(int key)
{
    node* newNode = new node(key);
    if (node) {
        items++;
        return insert(node);
    }
    return false;
}

//using child pointers, going either left or right reduces the tree by half
//when implemented using arrays, find the mid and compare against that to
//chose the first or the second half of the array.
bool Tree::insertBST(node* n)
{
    node* start = root;
    node* last;
    // try to find the position to insert the item
    while (start != NULL) {
        last = start;
        if (n->key <= start->key) {
            start = start->left;
            start->rank++;
        } else {
            start = start->right;
        }
    }
    if (last == NULL) {
        // tree is empty
        root = last;
    } else {
        if (n->key <= last->key) {
            last->left = n;
            last->rank++;
        } else {
            last->right = n;
        }
    }

    return true;
}

node* Tree:searchBST(int key)
{
    node* start = root;
    while (start != NULL) {
        if (start->key == key) {
            return start;
        } else if (key < start->key) {
            start = start->left;
        } else {
            start = start->right;
        }
    }
    return NULL;
}

node* Tree::findMaxBST(node* start)
{
    node* last = NULL;
    while (start != NULL) {
        last = start;
        start = start->right;
    }
    return last;
}

node* Tree::findMinBST(node* start)
{
    node* last = NULL;
    while (start != NULL) {
        last = start;
        start = start->left;
    }
    return last;
}

// Traversals using recursion.
// Without recursion - use a stack to make use of LIFO property
void Tree::traversePreOrder(node* start)
{
    if (start == NULL) {
        return;
    }
    //Recursion
    cout << start->key << endl;
    traversePreOrder(start->left);
    traversePreOrder(start->right);
}

void Tree::traversePreOrderItertive(node* start)
{
    if (start == NULL) {
        return;
    }
    //Stack
    stack<node*> s;
    s.push(start);
    while (!s.empty()) {
        node* start = s.top();
        s.pop();
        cout << start->key << endl;
        if (start->right) { s.push(start->right); }
        if (start->left) { s.push(start->left); }
    }
}

void Tree::traverseInOrder(node* start)
{
    if (start == NULL) {
        return;
    }
    //Recursion
    traverseInOrder(start->left);
    cout << start->key << endl;
    traverseInOrder(start->right);
}

void Tree::traverseInOrderIterative(node* start)
{
    //Stack
    stack<node*> s;
    while (!s.empty() || start) {
        if (start) {
            s.push(start);
            start = start->left;
        } else {
            node* top = s.top();
            s.pop();
            cout << top->key << endl;
            start = top->right;
        }
    }
}

void Tree:traversePostOrder(node* start)
{
    if (start == NULL) {
        return;
    }
    //Recursion
    traversePostOrder(start->left);
    traversePostOrder(start->right);
    cout << start->key << endl;
}

int Tree::traversePostOrderIterative(node* start)
{
    //Stack
    // Postorder traversal stack has a special property
    // that the size of the stack equals the max depth at that level
    stack<node*> s;
    node* last = NULL;
    int maxDepth = 0;
    while (!s.empty() || start) {
        if (start) {
            s.push(start);
            start = start->left;
            if (s.size() > maxDepth) { maxDepth = s.size(); }
        } else {
            node* top = s.top();
            if (top->right && last != top->right) {
                start = top->right;
            } else {
                cout << top->key << endl;
                s.pop();
                last = top;
            }
        }
    }
    return maxDepth;
}

// returns the height of the tree and prints the
// nodes by level
int Tree::traverseByLevel()
{
    node* start = root;
    if (start == NULL) {
        return 0;
    }
    queue<node*> q;
    q.push(start);
    int height = 0;
    // perform level order traversal
    while (!q.empty()) {
        int count = q.size(); // no. of nodes in the current level
        height++;
        while (count > 0) {
            node* front = q.front();
            q.pop();
            cout << front->key << endl;
            if (front->left) { q.push(front->left); }
            if (front->right) { q.push(front->right); }
            count--;
        }
        cout << endl;
    }
    return height;
}

bool Tree::checkIfBST(node* start, int min, int max)
{
    // Every node's value has to be within the range
    // provided by the min, max values
    if (start == NULL) {
        return false;
    }
    if (start->key > max || start->key < min) {
        return false;
    }
    if (!checkIfBST(start->left, min, start->key) ||
        !checkIfBST(start->right, start->key, max)) {
        return false;
    }
    return true;
}

int Tree::findHeight()
{
    return findMaxDepth(root);
    //iterative - Do a post order traversal iteratively
    // return traversePostOrderIterative(root);
    // return traverseByLevel();
}

int Tree::findMaxDepth(node* start)
{
    if (start == NULL) {
        return 0;
    }
    int leftD = findMaxDepth(start->left);
    int rightD = findMaxDepth(start->right);
    return ((leftD > rightD) ? leftD : rightD) + 1);
}

int findHeightWrtToAGivenNode(node* p)
{
    int height = 0;
    while (p) {
        ++height;
        p = p->parent;
    }
    return height;
}

int Tree::checkIfHeightBalanced(node* start)
{
    if (start == NULL) {
        return 0;
    }
    int left = checkIfHeightBalanced(start->left);
    int right = checkIfHeightBalanced(start->right);
    if (left == -1 || right == -1 || (abs(left - right) > 1)) {
        return -1;
    }
    return (((left > right) ? left : right) + 1);
}

bool Tree::checkIfBalanced(node* start)
{
    if (start == NULL) {
        return false;
    }
    // tree is balanced if the height of the left subtree and
    // height of the right subtree does not differ by more than one.
    int lh = findMaxDepth(start->left);
    int rh = findMaxDepth(start->right);
    if (abs(lh-rh) <= 1 &&
        checkIfBalanced(start->left) &&
        checkIfBalanced(start->right)) {
        return true;
    }
    
    //Efficient solution
    if (checkIfHeightBalanced(start) != -1) {
        return true;
    }
    return false;
}

node* Tree::findPredecessorInOrder(node* start)
{
    if (start == NULL) {
        return NULL;
    }
    if (start->left) {
        return findMaxBST(start->left);
    }
    
    // with parent pointer
    node* p = start->parent;
    while (p != NULL && start == p->left) {
        start = p;
        p = p->parent;
    }
    return p;
    ///////////////////////

    // recurse down the tree
    node* top = root;
    node* p = NULL;
    while (top != NULL) {
        if (start->key < top->key) {
            top = top->left;
        } else if (start->key > top->key) {
            p = top;
            top = top->right;
        } else {
            break;
        }
    }
    return p;
    /////////////////////////
}

node* Tree::findSuccessorInOrder(node* start)
{
    if (start == NULL) {
        return NULL;
    }
    if (start->right) {
        return findMinBST(start->right);
    }

    // with parent pointer
    node* p = start->parent;
    while (p != NULL && start == p->right) {
        start = p;
        p = p->parent;
    }
    return p;
    //////////////////////

    // recurse from the root
    node* top = root;
    node* s = NULL;
    while (top != NULL) {
        if (start->key > top->key) {
            top = top->right;
        } else if (start->key < top->key) {
            // may or may not be in the left; could be just the root
            s = top;
            top = top->left;
        } else {
            break;
        }
    }
    return s;
    ////////////////////////
}

node* findLCABST(node* start, int key1, int key2)
{
    if (start == NULL) {
        return NULL;
    }

    // with the assumption that the keys are in the tree
    while (start != NULL) {
        if (start->key > key1 && start->key > key2) {
            start = start->left;
        } else if (start->key < key1 && start->key < key2) {
            start = start->right;
        } else {
            // if the two nodes are on either side of a node
            // then thats the common ancestor
            break;
        }
    }
    return start;
    
    //recursive
    if (start->key > key1 && start->key > key2) {
        findLCABST(start->left, key1, key2);
    } else if (start->key < key1 && start->key < key2) {
        findLCABST(start->right, key1, key2);
    }
    return start;
    ////////////
}

bool findPath(node* start, int key, vector<node*> &path)
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
    path.pop_back(start);
    return false;
}

node* findLCA(node* start, int key1, int key2)
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

//assumes that both the nodes are in the tree!
node* findLCAPerf(node* start, node* p, node* q)
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

node* findLCAwithParent(node* p, node* q)
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

int getRank(int key)
{
    node* target = searchBST(key);
    return ((target != NULL) ? target->rank : 0);
}

int kthSmallestElement(int n)
{
    node* start = root;
    if (start == NULL) {
        return -1;
    }
    while (start != NULL) {
        if (start->rank+1 == n) {
            return start->key;
        } else if (start->rank < n) {
            start = start->right;
            n -= (start->rank+1);
        } else {
            start = start->left;
        }
    }
}

// create a balanced tree given a sorted array of elements
node* createTree(int* arr, int start, int end)
{
    int mid = (start+end)/2;
    node* root = new node(arr[mid]);
    if (root) {
        root->left = createTree(arr, start, mid-1);
        root->right = createTree(arr, mid+1, end);
    }
    return root;
}

bool isSubTree(Tree* t1, Tree* t2)
{
    if (t1 == NULL || t2 == NULL) {
        return false;
    }
    if (t1->root == NULL || t2->root == NULL) {
        return false;
    }
    vector<node*> v;
    if (findPath(t1->root, t2->root->key, v)) {
        node* head = v.back();
        matchTree(head, t2->root);
    }
}

bool matchTree(node* t1, node* t2)
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

bool isFoldable()
{
    if (root == NULL) {
        return NULL;
    }
    return isFoldableUtil(root->left, root->right);
}

bool isFoldableUtil(node* n1, node* n2)
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
void mirror(node* root)
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

void doubleTree(node* root)
{
    if (root == NULL) {
        return;
    }
    doubleTree(root->left);
    doubleTree(root->right);
    node* newNode = dupNode(root);
    if (newNode == NULL) {
        return;
    }
    newNode->left = root->left;
    root->left = newNode;
}

bool hasPathSum(node* node, int sum)
{
    // return true if we run out of tree and sum==0
    if (node == NULL) {
        return (sum == 0);
    } else {
        // otherwise check both subtrees
        int subSum = sum - node->data;
        return(hasPathSum(node->left, subSum) ||
               hasPathSum(node->right, subSum));
    }
}

void findPathWithSum(node* start, vector<node*> &v, int& sum, int target)
{
    if (start == NULL) {
        return;
    }
    
    v.push_back(start);
    
    sum += start->key;
    if (sum == target) {
        for (vector<node*>::itertor itr = v.begin(); itr != v.end(); itr++) {
            node* n = *itr;
            cout << n->key << " ";
        }
        cout << endl;
    }
    
    findPathWithSum(start->left, v, sum, target);
    findPathWithSum(start->right, v, sum, target);
    
    node* last = v.back();
    sum -= last->key;
    v.pop_back();
}

struct {
    int key;
    nodeDLL* prev;
    nodeDLL* next;
} nodeDLL;

// do inorder traversal of a binary tree to convert it to a DLL
nodeDLL* convertTreeToDLL()
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
            prev = item;
            start = top->right;
        }
    }
    return head;
}


void serializeBinaryTree(node* root, FILE *fp)
{
    if (root == NULL) {
        fprintf(fp, "%d ", -1);
        return;
    }
    fprintf(fp, "%d ", root->key);
    serializeBinaryTree(root->left, fp);
    serializeBinaryTree(root->right, fp);
}

void deserializeBinaryTree(node** root, FILE *fp)
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
node* deserializeBSTIterative(int* pre, int size)
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
void printBinaryTreeInVerticalOrder(node* root, int dist, hashTable<int,int>& hT)
{
    if (root == NULL) {
        return;
    }
    printBinaryTreeInVerticalOrder(root->left, dist-1);
    hT.insert(dist, root->key);
    printBinaryTreeInVerticalOrder(root->right, dist+1);
}

int main()
{
    return 0;
}

