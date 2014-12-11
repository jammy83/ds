// Graphs
#include <iostream>
#include <queue>
#include <list>

using namespace std;

// Node
typedef struct {
    int index;
    int weight;
} edgeNode;

// Graph
class Graph {
    static int const grey = 0;
    static int const white = 1;
    static int const black = 2;
 
 private:
    int nVertices;
    int nEdges;
    bool weighted;
    bool directed;
    list<edgeNode> *adjList; // edgeNode* adjList[nVertices+1]; or list<int> *adjList
    stack<int> s; // stack to record the processed vertices

    // traversal info
    struct traversalInfo {
        bool *discovered;
        bool *processed;
        int *parent;
        int *color; // for finding bipartite graphs using two-coloring
        // Used by DFS both for directed and undirected graphs
        int *entryTime; // half of the difference between the exitTime and
        int *exitTime;  // entryTime will yield the no. of descendants of a given node

        traversalInfo : discovered(NULL), processed(NULL), parent(NULL), color(NULL),
            entryTime(NULL), exitTime(NULL) {}
        ~traversalInfo {
            if (discovered) { delete[] discovered; discovered = NULL; }
            if (processed) { delete[] processed; processed = NULL; }
            if (parent) { delete[] parent; parent = NULL; }
            if (color) { delete[] color; color = NULL; }
            if (entryTime) { delete[] entryTime; entryTime = NULL; }
            if (exitTime) { delete[] exitTime; exitTime = NULL; }
        }
    } info;

    void processEdge(int v1, int v2);
    void processVertexEarly();
    void processVertexLate();
    void initTraversalInfo();
    int complementColor(int c) {
        if (c == grey) { 
            return grey;
        } else { 
            return ((c == white) ? black : white);
        }
    }
    void DFSUtil(int start, int& time);
    void edgeClassification(); // Only DAG will have all the four edge types
    // DFS will encounter tree and back edges
    // BFS will encounter tree and cross edges

 public:
    Graph(int v);
    ~Graph();
    void addEdge(int start, int end);
    // BFS and its applications
    void BFS(int start);
    int connectedComponents();
    bool bipartite();
    void findPath(int start, int end);
    // DFS and its applications
    void DFS();
    void findCycles();
    void performTopologicalSort();
};

Graph::Graph(int v) : nVertices(v), nEdges(0), weighted(false), directed(false) {
    adjList = new list<edgeNode>[v];
    info.discovered = new bool[nVertices+1];
    info.processed = new bool[nVertices+1];
    info.parent = new int[nVertices+1];
    info.color = new int[nVertices+1];
    info.entryTime = new int[nVertices+1];
    info.exitTime = new int[nVertices+1];
}

Graph::~Graph()
{
    delete[] adjList;
}
    
void Graph::addEdge(int start, int end)
{
    edgeNode node = {end, 0};
    adjList[start].push_back(node);
    if (!directed) {
        edgeNode snode = {start, 0};
        adjList[end].push_back(snode);
    }
    nEdges++;
}

void Graph::initTraversalInfo()
{
    for (int i = 1; i <= nVertices; i++) {
        info.discovered[i] = info.processed[i] = false;
        info.parent[i] = -1;
        info.color[i] = grey;
        info.entryTime[i] = 0;
        info.exitTime[i] = 0;
    }
}

void processEdge(int v1, int v2)
{
    // Bipartite
    if (info.color[v1] == info.color[v2]) {
        cout << "Not bipartite";
        return;
    }
    info.color[v2] = complementColor(info.color[v1]);
    
    //Edge classification
    if (info.parent[v2] == v1) {
        cout << "%d --> %d : tree edge\n" << v1 << v2;
    } else if (info.discovered[v2] == true && info.processed[v2] == false) {
        cout << "%d --> %d : back edge. Not a DAG" << v1 << v2;
    } else if (info.processed[v2] == true && info.entryTime[v1] < info.entryTime[v2]) {
        cout << "%d --> %d : forward edge" << v1 << v2;
    } else if (info.processed[v2] == true && info.entryTime[v1] > info.entryTime[v2]) {
        cout << "%d --> %d : cross edge" << v1 << v2;
    }
}

void processVertexEarly(int v)
{
    return;
}

void processVertexLate(int v)
{
    s.push(v);
    return;
}

// BFS
void Graph::BFS(int start)
{
    // initialize
    initTraversalInfo();

    queue<int> visit; // maintain a queue of nodes to be visited

    info.discovered[start] = true;
    visit.push(start);
    
    while (!visit.empty())  {
        // pop the first node to visit from the queue
        int top = visit.front();
        visit.pop();

        processed[top] = true;
        processVertexEarly(top);

        // walk the adjacency list of the vertex
        for (list<edgeNode>::iterator itr = adjList[top].begin();
             itr != adjList[top].end(); itr++) {

            edgeNode curr = *itr;
            int v = curr.index;

            if (info.processed[v] == false || directed) {
                processEdge(top, v);
            }
            if (info.discovered[v] == false) {
                info.discovered[v] = true;
                info.parent[v] = top;
                visit.push(v);
            }
        }
        
        processVertexLate(top);
    }    
}

int Graph::connectedComponents()
{
    initTraversalInfo();
    for (int i = 1, c = 0; i <= nVertices; i++) {
        if (info.discovered[i] == false) {
            c++;
            BFS(i);  
        }
    }
    return c;
}

bool Graph::bipartite()
{
    initTraversalInfo();
    for (int i = 1; i <= nVertices; i++) {
        if (info.discovered[i] == false) {
            info.color[i] = white;
            bfs(i);
        }
    }
    return true;
}

void Graph::findPath(int start, int end)
{
    if (start == end || end == -1) {
        cout << "%d\n" << start;
    } else {
        findPath(start, info.parent[end]);
        cout << "%d\n" << end;
    }
}

void Graph::DFS()
{
    initTraversalInfo();

    for (int i = 1; i <= nVertices; i++) {
        if (info.discovered[i] == false) {
            int time = 0;
            DFSUtil(i, time); // perform DFS from all the vertices to traverse
                              // the entire graph if there are vertices that are disconnected
        }
    }
}

void Graph::DFSUtil(int start, int& time)
{
    info.discovered[start] = true;
    info.entryTime[start] = ++time;

    processVertextEarly(start);

    for (list<edgeNode>::iterator itr = adjList[start].begin();
         itr != adjList[start].end(); itr++) {
        edgeNode curr = *itr;
        int index = curr.index;
        if (info.discovered[index] == false) {
            parent[index] = start;
            processEdge(start, index);
            DFSUtil(index, time);
        } else if (info.processed[index] == false || directed) {
            // back edge
            processEdge(start, index);
        }
    }
 
    info.processed[start] = true;  
    info.exitTime[start] = ++time;
 
    processVertexLate(start);
}

void Graph::findCycles()
{
    initTraversalInfo();
    for (int i = 1; i <= nVertices; i++) {
        if (info.discovered[i] == false) {
            DFS(i);
        }
    }
    // if edge classification returned back edge, then there is a cycle
}

void Graph::performTopologicalSort()
{
    initTraversalInfo();
    // Use a stack to record the vertices whose neighbours were
    // completely explored. That's the one with the max constraints and
    // reverse that to get the one with the least or zero constraints
    // The vertex will get pushed onto the stack inside processVertexLate()
    for (int i = 1; i <= nVertices; i++) {
        if (info.discovered[i] == false) {
            DFS(i);
        }
    }
    while (!s.empty()) {
        int index = s.top(); s.pop();
        cout << index << endl;
    }
}

// strongly connected components
// Minimum spanning tree - Prim, Kruskal
// Dijkstra's algo - shortest path


