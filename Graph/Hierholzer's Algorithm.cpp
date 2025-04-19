#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

// A class that represents an undirected graph
class Graph {
    int V; // No. of vertices
    vector<list<int>> adj; // Adjacency lists

public:
    // Constructor
    Graph(int V) : V(V), adj(V) {}

    // Add and remove edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void rmvEdge(int u, int v);

    // Methods to print Eulerian tour
    void printEulerTour();
    void printEulerUtil(int s);

    // Utility functions
    int DFSCount(int v, vector<bool>& visited);
    bool isValidNextEdge(int u, int v);
};

/* The main function that prints Eulerian Trail. It first
finds an odd degree vertex (if there is any) and then
calls printEulerUtil() to print the path */
void Graph::printEulerTour() {
    int u = 0;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() & 1) {
            u = i;
            break;
        }
    }

    printEulerUtil(u);
    cout << endl;
}

// Print Euler tour starting from vertex u
void Graph::printEulerUtil(int u) {
    for (auto it = adj[u].begin(); it != adj[u].end(); ) {
        int v = *it;

        if (v != -1 && isValidNextEdge(u, v)) {
            cout << u << "-" << v << " ";
            rmvEdge(u, v);
            printEulerUtil(v);
        } else {
            ++it;
        }
    }
}

// Check if edge u-v can be considered as the next edge
bool Graph::isValidNextEdge(int u, int v) {
    int count = count_if(adj[u].begin(), adj[u].end(), [](int x) { return x != -1; });
    if (count == 1) return true;

    vector<bool> visited(V, false);
    int count1 = DFSCount(u, visited);

    rmvEdge(u, v);
    fill(visited.begin(), visited.end(), false);
    int count2 = DFSCount(u, visited);

    addEdge(u, v);

    return count1 <= count2;
}

// Remove edge u-v from the graph
void Graph::rmvEdge(int u, int v) {
    auto it = find(adj[u].begin(), adj[u].end(), v);
    if (it != adj[u].end()) *it = -1;

    it = find(adj[v].begin(), adj[v].end(), u);
    if (it != adj[v].end()) *it = -1;
}

// DFS to count reachable vertices from v
int Graph::DFSCount(int v, vector<bool>& visited) {
    visited[v] = true;
    int count = 1;

    for (int u : adj[v]) {
        if (u != -1 && !visited[u]) {
            count += DFSCount(u, visited);
        }
    }

    return count;
}

// Driver program to test the above function
int main() {
    Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.printEulerTour();

    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    g2.printEulerTour();

    Graph g3(5);
    g3.addEdge(1, 0);
    g3.addEdge(0, 2);
    g3.addEdge(2, 1);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.addEdge(3, 2);
    g3.addEdge(3, 1);
    g3.addEdge(2, 4);
    g3.printEulerTour();

    return 0;
}
