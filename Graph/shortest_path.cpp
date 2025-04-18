#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
    unordered_map<int, list<int>> adjacencyList;
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;

public:
    // Add an edge to the graph (undirected)
    void addEdge(int startingVertex, int endingVertex)
    {
        adjacencyList[startingVertex].push_back(endingVertex);
        adjacencyList[endingVertex].push_back(startingVertex);
    }

    // Display the adjacency list of the graph
    void displayAdjacencyList() const
    {
        for (const auto &vertex : adjacencyList)
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
        cout << endl;
    }

    // Find the shortest path using BFS
    vector<int> shortestPath(int startingVertex, int endingVertex)
    {
        queue<int> Queue;
        Queue.push(startingVertex);
        visited[startingVertex] = true;
        parent[startingVertex] = -1;

        while (!Queue.empty())
        {
            int frontNode = Queue.front();
            Queue.pop();

            for (const auto &neighbour : adjacencyList[frontNode])
            {
                if (!visited[neighbour])
                {
                    Queue.push(neighbour);
                    visited[neighbour] = true;
                    parent[neighbour] = frontNode;
                }
            }

            // If the ending vertex is visited, construct the path
            if (visited[endingVertex])
            {
                vector<int> path;
                int currentNode = endingVertex;
                while (currentNode != -1)
                {
                    path.push_back(currentNode);
                    currentNode = parent[currentNode];
                }
                reverse(path.begin(), path.end());
                return path;
            }
        }

        // Return an empty vector if no path is found
        return {};
    }
};

int main()
{
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
    for (int i = 0; i < edges; i++)
    {
        int startingVertex, endingVertex;
        cout << "Enter starting and ending vertex: ";
        cin >> startingVertex >> endingVertex;
        graph.addEdge(startingVertex, endingVertex);
    }

    // Display adjacency list
    graph.displayAdjacencyList();

    // Input starting and ending vertices for shortest path
    cout << "Enter starting and ending vertex for shortest path: ";
    int startingVertex, endingVertex;
    cin >> startingVertex >> endingVertex;

    // Find and display the shortest path
    vector<int> path = graph.shortestPath(startingVertex, endingVertex);
    if (!path.empty())
    {
        cout << "Shortest path from " << startingVertex << " to " << endingVertex << ": ";
        for (const auto &node : path)
        {
            cout << node << " ";
        }
        cout << endl;
        cout << "Shortest path length: " << path.size() - 1 << endl;
    }
    else
    {
        cout << "No path exists between " << startingVertex << " and " << endingVertex << "." << endl;
    }

    return 0;
}