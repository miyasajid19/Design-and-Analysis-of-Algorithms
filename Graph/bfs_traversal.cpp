#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

class Graph {
    unordered_map<int, list<int>> adjacencyList;
    unordered_map<int, bool> visited;

public:
    // Constructor
    Graph() {}
    
    // Add an edge to the graph
    void addEdge(int startVertex, int endVertex, bool directed = false) {
        adjacencyList[startVertex].push_back(endVertex);
        if (!directed) {
            adjacencyList[endVertex].push_back(startVertex);
        }
    }

    // Print the adjacency list
    void print() const {
        for (const auto &vertex : adjacencyList) {
            cout << vertex.first << " ----> ";
            for (auto it = vertex.second.begin(); it != vertex.second.end(); ++it) {
                cout << *it;
                if (next(it) != vertex.second.end()) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

    // Perform BFS from a given starting vertex
    void bfs(int startVertex) {
        queue<int> q;
        q.push(startVertex);
        visited[startVertex] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (const auto &neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }

    // Perform BFS traversal for all components of the graph
    void bfsTraversal(int startVertex) {
        // Start BFS from the given starting vertex
        if (!visited[startVertex]) {
            bfs(startVertex);
        }

        // Check for unvisited vertices (for disconnected components)
        for (const auto &vertex : adjacencyList) {
            if (!visited[vertex.first]) {
                bfs(vertex.first);
            }
        }
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Graph graph;

    // Input number of vertices and edges
    cout << "How many vertices are there? ";
    int vertices;
    cin >> vertices;

    cout << "How many edges are there? ";
    int edges;
    cin >> edges;

    // Input edges
    for (int i = 0; i < edges; i++) {
        int startVertex, endVertex;
        cout << "Enter starting and ending vertex: ";
        cin >> startVertex >> endVertex;

        cout << "Is the edge directed? (1 for yes, 0 for no): ";
        bool directed;
        cin >> directed;

        graph.addEdge(startVertex, endVertex, directed);
    }

    // Print adjacency list
    cout << "Adjacency List: " << endl;
    graph.print();

    // Perform BFS traversal
    cout << "BFS Traversal: " << endl;
    int startVertex;
    cout << "Enter starting vertex: ";
    cin >> startVertex;

    graph.bfsTraversal(startVertex);
    cout << endl;

    return 0;
}