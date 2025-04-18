#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
using namespace std;
class Graph
{
    unordered_map<int, list<int>> adjacencyList;
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    unordered_map<int, bool> inStack;
    vector<int> topologicalOrder;
    unordered_map<int, int> inDegree;
    queue<int> Queue;
public:
    Graph() {}
    void addEdge(int startingVertex, int endingVertex)
    {
        this->adjacencyList[startingVertex].push_back(endingVertex);
        inDegree[endingVertex]++;//used for bfs cycle detection
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

    bool is_cyclic_dfs_helper(int vertex)
    {
        visited[vertex] = true;
        inStack[vertex] = true;
        for (auto &neighbour : adjacencyList[vertex])
        {
            if (!visited[neighbour])
            {
                if (is_cyclic_dfs_helper(neighbour))
                    return true;
            }
            else if (inStack[neighbour])
            {
                return true; // Cycle detected
            }
        }

        inStack[vertex] = false;
        return false; // Placeholder for actual DFS cycle detection logic
    }
    bool is_cyclic_dfs()
    {
        for (auto &vertex : adjacencyList)
        {
            if (!visited[vertex.first])
            {
                if (is_cyclic_dfs_helper(vertex.first))
                    return true; // Cycle detected
            }
        }
        return false; // No cycle detected
    }

    bool is_cyclic_bfs()
    {
        for (auto &vertex : adjacencyList)
        {
            if (inDegree[vertex.first] == 0)
                Queue.push(vertex.first);
        }
        int count = 0;
        while (!Queue.empty())
        {
            int currentVertex = Queue.front();
            count++;
            Queue.pop();
            for (auto &neighbour : adjacencyList[currentVertex])
            {
                inDegree[neighbour]--;
                if (inDegree[neighbour] == 0)
                    Queue.push(neighbour);
            }
        }
        return not (count == adjacencyList.size()); // If count is not equal to the number of vertices, there is a cycle
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
    // Print adjacency list
    cout << "Adjacency List: " << endl;
    graph.displayAdjacencyList();
    // Check for cycles using DFS
    if (graph.is_cyclic_dfs())
    {
        cout << "The graph is cyclic (detected using DFS)." << endl;
    }
    else
    {
        cout << "The graph is acyclic (detected using DFS)." << endl;
    }
    // Check for cycles using BFS
    if (graph.is_cyclic_bfs())
    {
        cout << "The graph is cyclic (detected using BFS)." << endl;
    }
    else
    {
        cout << "The graph is acyclic (detected using BFS)." << endl;
    }
    return 0;
}