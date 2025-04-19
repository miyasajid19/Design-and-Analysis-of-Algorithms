#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    void DFS(int v, vector<bool>& visited, stack<int>& Stack);
    void reverseDFS(int v, vector<bool>& visited, vector<int>& component);

public:
    Graph(int V);
    void addEdge(int u, int v);
    void findSCCs();
};

Graph::Graph(int V) : V(V), adj(V) {}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::DFS(int v, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            DFS(u, visited, Stack);
        }
    }
    Stack.push(v);
}

void Graph::reverseDFS(int v, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : adj[v]) {
        if (!visited[u]) {
            reverseDFS(u, visited, component);
        }
    }
}

void Graph::findSCCs() {
    stack<int> Stack;
    vector<bool> visited(V, false);

    // Step 1: Perform DFS and store vertices in stack by finish time
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, visited, Stack);
        }
    }

    // Step 2: Transpose the graph
    Graph transposedGraph(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            transposedGraph.addEdge(v, u);
        }
    }

    // Step 3: Perform DFS on transposed graph in order of stack
    fill(visited.begin(), visited.end(), false);
    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            vector<int> component;
            transposedGraph.reverseDFS(v, visited, component);

            // Print the strongly connected component
            cout << "SCC: ";
            for (int node : component) {
                cout << node << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 0);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "Strongly Connected Components are:\n";
    g.findSCCs();

    return 0;
}