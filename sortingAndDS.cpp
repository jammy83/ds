//
//  sorting.cpp
//  
//
//  Created by Janani Natarajan on 12/13/14.
//
//

#include <iostream>

using namespace std;

static const int CUTOFF = 7;

// mergesort arr[start...end] using aux[start...end]
void combine(int* arr, int start, int mid, int end, int* aux)
{
    if (arr[mid+1] > arr[mid]) {
        return; // nothing to be done; the 2 sub arrays are already sorted since
                // beginning of the second sub-array is greater than the end of
                // previous sub-array
    }
    // copy contents into the aux array
    for (int i = start; i <= end, i++) {
        aux[i] = arr[i];
    }
    // aux *now* contains the sorted subarrays
    int i = start, j = mid+1;
    for (int k = start; k <= end; k++) {
        if (j > end || aux[i] <= aux[j]) {
            arr[k] = aux[i++];
        } else if (i > mid || aux[i] > aux[j]) {
            arr[k] = aux[j++];
        }
    }
    //arr[start..end] contains the sorted items
}

void mergesort(int* arr, int start, int end, int* aux)
{
    if (end <= start) {
        return;
    }
    int mid = start+end/2;
    mergesort(arr, start, mid, aux);
    mergesort(arr, mid+1, end, aux);
    combine(arr, start, mid, end, aux);
}

// insertion sort. Everything to the left of the array is sorted
// for the new element, tries to find a spot through exchanges
void insertionSort(int* arr, int start, int end)
{
    for (int i = start; i <= end; i++) {
        for (int j = i; j > start && a[j] < a[j-1]; j--) {
            int temp = a[j-1];
            a[j-1] = a[j];
            a[j] = temp;
        }
    }
}

void combinePerf(int* src, int start, int mid, int end, int* dst)
{
    // src contains the sorted sub arrays
    int i = start, j = mid+1;
    for (int k = start; k <= end; k++) {
        if (j > end || src[i] <= src[j]) {
            dst[k] = src[i++];
        } else if (i > mid || src[i] > src[j]) {
            dst[k] = src[j++];
        }
    }
    // dst[start..end] contains the sorted items
}

// src and dst are expected to contain all the elements on
// the very first invocation
// dst contains the resultant sorted array
void mergesortPerf(int* src, int start, int end, int* dst)
{
    if (end <= start+CUTOFF) {
        insertionSort(dst, start, end);
    }
    int mid = start+end/2;
    mergesortPerf(dst, start, mid, src); // flipped the src and dst
    mergesortPerf(dst, mid+1, end, src); // ditto
    // now dst will have the elements and src will have the sorted subarrays
    if (src[mid+1] > src[mid]) {
        for (int i = start; i <= end; i++) dst[i] = src[i];
        return;
    }
    combinePerf(src, start, mid, end, dst);
}

void selectionSort(int* arr, int start, int end)
{
    for (int i = 0; i <= end; i++) {
        int min = i;
        for (int j = i+1; j <= end; j++) {
            if (arr[j] < min) {
                min = j; // store the index with the smallest element in the subarray starting at i+1
            }
        }
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

//chose the pivot element to be the last element of the array
int partition(int* arr, int start, int end)
{
    int pivot = arr[end];
    int j = -1;
    for (int i = start; i < end; i++) {
        if (arr[i] <= pivot) {
            if (i > 0 && a[i-1] > pivot) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                j++;
            }
        } else if (j == -1) {
            j = i;
        }
    }
    arr[end] = arr[j];
    arr[j] = pivot;
    // return the pivot index
    return j;
}

void quicksort(int* arr, int start, int end)
{
    if (start < end) {
        int pivot = partition(arr, start, end);
        quicksort(arr, start, pivot-1);
        quicksort(arr, pivot+1, end);
    }
}


//https://www.cs.berkeley.edu/~jrs/61b/lec/25


// heap represented by an array:
// for a given 'i', left = 2i and right = 2i+1 and parent = floor(i/2)
// len - heap size not the size of the array
void maxHeapify(iint* arr, int len, int i)
{
    int l = 2*i;
    int r = (2*i)+1;
    int maxIndex = i;
    if (l > len || r > len) {
        return;
    }
    maxIndex = (arr[l] > arr[r]) ? l : r;
    if (arr[maxIndex] > arr[i]) { //one of the children is > parent
        int temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
        return maxHeapify(arr, len, maxIndex);
    }
}

void buildMaxHeap(int* arr, int size)
{
    for (int i = size/2; i >= 1; i--) {
        maxHeapify(arr, size, i);
    }
}

// arr runs from 1..size
void heapsort(int* arr, int size)
{
    buildMaxHeap(arr, size);
    int len = size;
    for (int i = size; i > 1; i--) {
        int temp = a[i];
        a[i] = a[1]; // swap the max element with the last
        a[1] = temp;
        len--;
        maxHeapify(arr, len, 1);
    }
}

// priority queues
int heapExtractMax(int* arr, int size)
{
    if (size < 1) {
        return -1;
    }
    int max = arr[1];
    arr[1] = arr[size];
    maxHeapify(arr, size-1, 1);
    return max;
}

bool heapIncreaseKey(int* arr, int size, int i, int key)
{
    if (key < arr[i]) {
        return false;
    }
    arr[i] = key;
    // push the max element up..
    while (i > 1 && arr[i/2] < arr[i]) { // parent less than the updated child
        int temp = arr[i/2];
        arr[i/2] = arr[i];
        arr[i] = temp;
        i = i/2;
    }
}

void maxHeapInsert(int* arr, int size, int key)
{
    arr[size+1] = -1;
    heapIncreaseKey(arr, size, size+1, key);
}


//min PQ
//Similar to max, just reverse the order of comparisons
//implement heapDecreaseKey() instead of heapIncreaseKey() for maxPQ
//Heapsort - min element is the arr[1]; return that and move arr[size] to arr[1]
//and call minHeapify()


//Indexed min PQ
class IndexedMinPQ {
 private:
    int* pq;
    int* qp;
    int* keys;
    int size; // max size of the queue
    int len; // current length of the queue

    void minHeapify(int i); // bubble down
    void swap(int i, int j);
    void bubbleUp(int i);

 public:
    IndexedMinPQ(int val) {
        size = val+1;
        pq = new int[size];
        qp = new int[size];
        for (int i = 1; i <= size; i++) {
            qp[i] = -1;
        }
        keys = new int[size];
        len = 0;
    }
    ~IndexedMinPQ() {
        if (pq) { delete[] pq; pq = NULL; }
        if (qp) { delete[] qp; qp= NULL; }
        if (keys) { delete[] keys; keys = NULL; }
    }
    bool insert(int i, int key);
    void decreaseKey(int i, int key);
    void increaseKey(int i, int key);
    void delete(int i);
    int deleteMin();
    bool empty() { return (len == 0); }
    bool contains(int i) {
        if (i < 0 || i > size) {
            return false;
        }
        return (qp[i] != -1);
    }
    int minIndex() {
        if (len == 0) {
            return -1;
        }
        return pq[1];
    }
    int minKey() {
        if (len == 0) {
            return -1;
        }
        return keys[pq[1]];
    }
};

void IndexedMinPQ::insert(int i, int key)
{
    if (i < 0 || i > size) {
        return;
    }
    keys[i] = key;
    qp[i] = ++len;
    pq[len] = i;
    return bubbleUp(i);
}

void IndexedMinPQ::swap(int i, int j)
{
    int temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
    
    //update the inverse mapping
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void IndexedMinPQ::minHeapify(int i) // bubble down
{
    int l = 2*i;
    int r = 2*i + 1;
    if (l > len || r > len) {
        return;
    }
    int minIndex = (keys[l] < keys[r]) ? l : r;
    if (pq[i] > pq[minIndex]) {
        swap(i, minIndex);
        return minHeapify(minIndex);
    }
}

bool IndexedMinPQ::bubbleUp(int i)
{
    while (i > 1 && keys[i/2] > keys[i]) {
        swap(i, i/2);
        i = i/2;
    }
}

void IndexedMinPQ::decreaseKey(int i, int key)
{
    if (i < 0 || i > size || keys[i] < key) {
        return;
    }
    keys[i] = key;
    bubbleUp(qp[i]);
}

void IndexedMinPQ::increaseKey(int i, int key)
{
    if (i < 0 || i > size || keys[i] > key) {
        return;
    }
    keys[i] = key;
    minHeapify(qp[i]);
}

int IndexedMinPQ::deleteMin()
{
    if (len == 0) {
        return -1;
    }
    int min = pq[1];
    qp[min] = -1;
    keys[min] = -1;
    swap(1, len--);
    pq[len+1] = -1; // one element less with the last one moved to 1 and heapified
    minHeapify(1);
    return min;
}

void IndexedMinPQ::delete(int i)
{
    int heapIndex = qp[i];
    qp[i] = -1;
    keys[i] = -1;
    swap(heapIndex, len--);
    minHeapify(heapIndex);
    bubbleUp(heapIndex);
    pq[len+1] = -1;
}

//Union find data structure
class UnionFind {
 private:
    int* parent;
    int* rank;
    int count; // no. of connected components
    int items; // no. of elements

 public:
    UnionFind(int val) : count(val), items(val) {
        parent = new parent(val);
        rank = new rank(val);
        for (int i = 0; i < val; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    ~UnionFind() {
        if (parent) { delete[] parent; parent = NULL; }
        if (rank) { delete[] rank; rank = NULL; }
    }
    // find the root of the tree walking up the parent pointers
    // the idea is that all the connected components are from the
    // same subtree and hence share the parent which is marked as
    // the root of the tree -- which connected component am I a part of?
    int find(int v);
    bool connected(int v, int w) {
        return (find(v) == find(w)); // are the two items connected
    }
    void union(int v, int w); // merges the 2 components
    int getCount() const { return count; }
};

int UnionFind::find(int v)
{
    if (v < 0 || v > items) {
        return -1;
    }
    while (parent[v] != v) {
        parent[v] = parent[parent[v]]; // path compression by halving
        v = parent[v];
    }
    return v;
}

void UnionFind::union(int v, int w)
{
    int i = find(v);
    int j = find(w);
    if (i == j) return;
    
    if (rank[i] < rank[j]) {
        parent[i] = j;
    } else if (rank[j] < rank[i]) {
        parent[j] = i;
    } else {
        parent[j] = i;
        rank[i]++;
    }
    count--;
}

int main()
{
    return 0;
}
