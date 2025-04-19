#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

class FordFulkerson {
private:
    int n; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list (node, capacity)

    // Function to perform BFS and find an augmenting path
    bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < n; v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    if (v == t) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return false;
    }

public:
    FordFulkerson(int vertices) : n(vertices), adj(vertices) {}

    // Function to add an edge to the graph
    void addEdge(int u, int v, int capacity) {
        adj[u].emplace_back(v, capacity);
    }

    // Function to implement the Ford-Fulkerson algorithm
    int getMaxFlow(int source, int sink) {
        vector<vector<int>> rGraph(n, vector<int>(n, 0));

        // Build the residual graph from the adjacency list
        for (int u = 0; u < n; u++) {
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int capacity = edge.second;
                rGraph[u][v] = capacity;
            }
        }

        vector<int> parent(n); // Array to store the augmenting path
        int maxFlow = 0;       // Initialize max flow to 0

        while (bfs(rGraph, source, sink, parent)) {
            int pathFlow = INT_MAX;

            // Find the minimum residual capacity in the augmenting path
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, rGraph[u][v]);
            }

            // Update residual capacities of the edges and reverse edges
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }
};

int main() {
    // Fixed input
    int vertices = 6;
    FordFulkerson ff(vertices);

    // Adding edges (u, v, capacity)
    ff.addEdge(0, 1, 16);
    ff.addEdge(0, 2, 13);
    ff.addEdge(1, 2, 10);
    ff.addEdge(1, 3, 12);
    ff.addEdge(2, 1, 4);
    ff.addEdge(2, 4, 14);
    ff.addEdge(3, 2, 9);
    ff.addEdge(3, 5, 20);
    ff.addEdge(4, 3, 7);
    ff.addEdge(4, 5, 4);

    int source = 0, sink = 5;

    cout << "The maximum possible flow is: " << ff.getMaxFlow(source, sink) << endl;

    return 0;
}