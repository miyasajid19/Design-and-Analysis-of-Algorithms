#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
using namespace std;

class Graph {
    unordered_map<int, list<int>> adjacencyList;

    // Helper function for DFS cycle detection
    bool isCyclicDFSHelper(int vertex, unordered_map<int, bool> &visited, int parent) {
        visited[vertex] = true;

        for (auto &neighbour : adjacencyList[vertex]) {
            if (!visited[neighbour]) {
                if (isCyclicDFSHelper(neighbour, visited, vertex)) {
                    return true;
                }
            } else if (neighbour != parent) {
                return true;
            }
        }
        return false;
    }

    // Helper function for BFS cycle detection
    bool isCyclicBFSHelper(int startVertex, unordered_map<int, bool> &visited) {
        queue<pair<int, int>> Queue; // {currentVertex, parentVertex}
        Queue.push({startVertex, -1});
        visited[startVertex] = true;

        while (!Queue.empty()) {
            int vertex = Queue.front().first;
            int parent = Queue.front().second;
            Queue.pop();

            for (auto &neighbour : adjacencyList[vertex]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    Queue.push({neighbour, vertex});
                } else if (neighbour != parent) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    // Add an edge to the graph
    void addEdge(int startingVertex, int endingVertex) {
        adjacencyList[startingVertex].push_back(endingVertex);
        adjacencyList[endingVertex].push_back(startingVertex);
    }

    // Print the adjacency list
    void print() const {
        for (const auto &vertex : adjacencyList) {
            cout << vertex.first << " ----> ";
            for (auto it = vertex.second.begin(); it != vertex.second.end(); ++it) {
                cout << *it;
                if (next(it) != vertex.second.end())
                    cout << ", ";
            }
            cout << endl;
        }
    }

    // Check if the graph contains a cycle using DFS
    bool isCyclicDFS() {
        unordered_map<int, bool> visited;
        for (const auto &vertex : adjacencyList) {
            if (!visited[vertex.first]) {
                if (isCyclicDFSHelper(vertex.first, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Check if the graph contains a cycle using BFS
    bool isCyclicBFS() {
        unordered_map<int, bool> visited;
        for (const auto &vertex : adjacencyList) {
            if (!visited[vertex.first]) {
                if (isCyclicBFSHelper(vertex.first, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Graph graph;
    cout << "How many vertices are there? ";
    int vertices;
    cin >> vertices;
    cout << "How many edges are there? ";
    int edges;
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        int startingVertex, endingVertex;
        cout << "Enter starting and ending vertex: ";
        cin >> startingVertex >> endingVertex;
        graph.addEdge(startingVertex, endingVertex);
    }

    // Print adjacency list
    cout << "Adjacency List: " << endl;
    graph.print();

    // Check for cycles using DFS
    if (graph.isCyclicDFS()) {
        cout << "The graph is cyclic (detected using DFS)." << endl;
    } else {
        cout << "The graph is acyclic (detected using DFS)." << endl;
    }

    // Check for cycles using BFS
    if (graph.isCyclicBFS()) {
        cout << "The graph is cyclic (detected using BFS)." << endl;
    } else {
        cout << "The graph is acyclic (detected using BFS)." << endl;
    }

    return 0;
}
