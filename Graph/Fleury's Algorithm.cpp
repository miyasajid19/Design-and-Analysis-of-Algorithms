#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<list<int>> adj; // Adjacency list

public:
    Graph(int V);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    void printEulerTour();
    void printEulerUtil(int u);
    int DFSCount(int v, vector<bool> &visited);
    bool isValidNextEdge(int u, int v);
};

Graph::Graph(int V) : V(V), adj(V) {}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::removeEdge(int u, int v) {
    adj[u].remove(v);
    adj[v].remove(u);
}

int Graph::DFSCount(int v, vector<bool> &visited) {
    visited[v] = true;
    int count = 1;

    for (int adjVertex : adj[v]) {
        if (!visited[adjVertex]) {
            count += DFSCount(adjVertex, visited);
        }
    }
    return count;
}

bool Graph::isValidNextEdge(int u, int v) {
    // If u has only one adjacent vertex, the edge is valid
    if (adj[u].size() == 1) {
        return true;
    }

    // Count reachable vertices before removing the edge
    vector<bool> visited(V, false);
    int count1 = DFSCount(u, visited);

    // Remove the edge and count reachable vertices again
    removeEdge(u, v);
    fill(visited.begin(), visited.end(), false);
    int count2 = DFSCount(u, visited);

    // Add the edge back
    addEdge(u, v);

    // If removing the edge reduces the reachable vertices, it's a bridge
    return (count1 <= count2);
}

void Graph::printEulerUtil(int u) {
    for (auto it = adj[u].begin(); it != adj[u].end();) {
        int v = *it;
        if (isValidNextEdge(u, v)) {
            cout << u << " -> " << v << endl;
            removeEdge(u, v);
            printEulerUtil(v);
            it = adj[u].begin(); // Reset iterator after modification
        } else {
            ++it;
        }
    }
}

void Graph::printEulerTour() {
    // Find a vertex with an odd degree, if any
    int startVertex = 0;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() % 2 != 0) {
            startVertex = i;
            break;
        }
    }
    printEulerUtil(startVertex);
}

int main() {
    Graph g(9); // Adjusted to accommodate vertices 1 to 8
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 7);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(5, 8);

    cout << "Eulerian Path or Circuit:" << endl;
    g.printEulerTour();

    return 0;
}