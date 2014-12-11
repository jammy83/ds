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
 private:
    int key;
    node* left;
    node* right;
    node* parent;
 public:
    node(int val) : key(val), left(NULL), right(NULL), parent(NULL) {}
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

 public:
    tree() : root(NULL), items(0) {}
    ~tree() {
        destroyTree(root);
    }

    bool isEmpty() { return (root == NULL); }
    // Operations
    bool insertBST(int key);
    node* searchBST(int key);
    bool findPath(node* start, int key, stack<node*> &path);
    node* findLCA(node* start, int key1, int key2);
    node* findLCABST(node* start, int key1, int key2);
    //Use parent pointers or just recuse down the tree
    // A simple inorder traversal of the nodes will tell you this as well.
    node* findPredecessorInOrder();
    node* findSuccessorInOrder();
    // For just binary trees traverse the tree keeping
    // track of min and max
    node* findMinBST(node* start);
    node* findMaxBST(node* start);
    // - Traversals for any binary tree including BST -
    int traverseByLevel();
    void traverseInOrder(node* start);
    void traverseInOrderIterative(node* start);
    void traversePreOrder(node* start);
    void traversePreOrderItertive(node* start);
    void traversePostOrder(node* start);
    int traversePostOrderIterative(node* start); // returns max depth at root or height of the tree
    // ------------------------------------------------
    // applies to any binary tree (including BST)
    int findHeight();
    int findMaxDepth(node* start);
    bool checkIfBalanced(node* start);
    int checkIfHeightBalanced(node* start);
    // simply do an inorder traversal and check if the values are in a sorted order
    // maintain the previous visited node and check if prev <= curr to avoid a complete traversal
    // Or apply the property that max(left subtree) <= root < min(right subtree).
    bool checkIfBST(node* start);
    node* createTree(int* arr, int start, int end);
    bool isSubTree(node* t1, node* t2);
    bool matchTree(node* t1, node* t2);
    void inOrderTraversalWithoutStack(node* start); // threaded binary tree
    void convertTreeToSumTree();
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
    while (start->right != NULL) {
        start = start->right;
    }
    return start;
}

node* Tree::findMinBST(node* start)
{
    while (start->left != NULL) {
        start = start->left;
    }
    return start;
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

int Tree::findHeight()
{
    return findMaxDepth(root);
    //iterative - Do a post order traversal iteratively
    return traversePostOrderIterative(root);
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

// returns the height of the tree
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
    if (left == -1 || right == -1) {
        return -1;
    }
    if (abs(left - right) > 1) {
        return -1;
    } else {
        return (((left > right) ? left : right) + 1);
    }
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
        } else if (start->key < root->key) {
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

bool findPath(node* start, int key, stack<node*> &path) // the path will be stored in the reverse order
{
    if (start == NULL) {
        return false;
    }
    path.push(start);
    if (start->key == key) {
        return true;
    }
    // findPath seems to work like inorde traversal if you want
    // to implement this iteratively
    if ((start->left && findPath(start->left, key, path)) ||
        (start->right && findPath(start->right, key, path)) ) {
        return true;
    }
    path.pop(start);
    return false;
}

node* findLCA(node* start, int key1, int key2)
{
    if (start == NULL) {
        return NULL;
    }
    stack<node*> s1;
    stack<node*> s2;
    if (!findPath(start, key1, s1) || !findPath(start, key2, s2)) {
        return NULL;
    }
    while (!s1.empty() && !s2.empty()) {
        node* n1 = s1.top(); s1.pop();
        node* n2 = s2.top(); s2.pop();
        if (n1->key == n2->key) {
            return n1;
        }
    }
    return NULL;
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
    stack<node*> s;
    if (findPath(t1->root, t2->root->key, s)) {
        node* head = s.top(); s.pop();
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

int main()
{
    return 0;
}
