// Kahn's Algorithm is used to find the topological ordering of a directed acyclic graph (DAG).
// It works by repeatedly removing nodes with no incoming edges (in-degree 0) and adding them to the topological order.
// This algorithm uses a queue to process nodes with in-degree 0 and updates the in-degree of their neighbors.

#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;
class Graph
{
    unordered_map<int, list<int>> adjacencyList;
    unordered_map<int, bool> visited;
    queue<int> Queue;
    unordered_map<int, int> inDegree;
    vector<int> topologicalOrder;

public:
    Graph() {}
    void addEdge(int startingVertex, int endingVertex)
    {
        this->adjacencyList[startingVertex].push_back(endingVertex);
        inDegree[endingVertex]++;
    }
    void displayAdjacencyList()
    {
        for (auto &vertex : adjacencyList)
        {
            cout << vertex.first << " ----> ";
            for (auto it = vertex.second.begin(); it != vertex.second.end(); ++it)
            {
                cout << *it;
                if (next(it) != vertex.second.end())
                    cout << ", ";
            }
            cout << endl;
        }
    }

    vector<int> topologicalSortKahn()
    {
        for (auto &vertex : adjacencyList)
        {
            if (inDegree[vertex.first] == 0)
                Queue.push(vertex.first);
        }
        while (!Queue.empty())
        {
            int currentVertex = Queue.front();
            topologicalOrder.push_back(currentVertex);
            Queue.pop();
            for (auto &neighbour : adjacencyList[currentVertex])
            {
                inDegree[neighbour]--;
                if (inDegree[neighbour] == 0)
                    Queue.push(neighbour);
            }
        }
        return topologicalOrder;
    }
};
int main()
{
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
    for (int i = 0; i < edges; i++)
    {
        int startingVertex, endingVertex;
        cout << "Enter starting and ending vertex: ";
        cin >> startingVertex >> endingVertex;
        graph.addEdge(startingVertex, endingVertex);
    }
    cout << "Adjacency List:" << endl;
    graph.displayAdjacencyList();
    cout << "Topological Sort using Kahn's Algorithm: ";
    vector<int> result = graph.topologicalSortKahn();
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i];
        if (i != result.size() - 1)
            cout << " -> ";
    }
    cout << endl;
    return 0;
}