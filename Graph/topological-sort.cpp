#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
#include <vector>
using namespace std;

// Applicable to Directed Acyclic Graphs (DAGs)
class Graph {
    unordered_map<int, list<int>> adjacencyList;
    unordered_map<int, bool> visited;
    stack<int> topologicalOrder;

public:
    void addEdge(int startingVertex, int endingVertex) {
        adjacencyList[startingVertex].push_back(endingVertex);
    }

    void displayAdjacencyList() const {
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

    void topologicalSortHelper(int vertex) {
        visited[vertex] = true;
        for (const auto &neighbour : adjacencyList[vertex]) {
            if (!visited[neighbour]) {
                topologicalSortHelper(neighbour);
            }
        }
        topologicalOrder.push(vertex); // Push after visiting all neighbors
    }

    vector<int> topologicalSort() {
        for (const auto &vertex : adjacencyList) {
            if (!visited[vertex.first]) {
                topologicalSortHelper(vertex.first);
            }
        }

        vector<int> result;
        while (!topologicalOrder.empty()) {
            result.push_back(topologicalOrder.top());
            topologicalOrder.pop();
        }
        return result;
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

    cout << "Adjacency List:" << endl;
    graph.displayAdjacencyList();

    cout << "Topological Sort: ";
    vector<int> result = graph.topologicalSort();
    for (const int &vertex : result) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}
