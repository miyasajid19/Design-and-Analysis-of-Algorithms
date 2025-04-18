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

public:
    Graph() {}
    // adding edges
    void addEdge(int startingVertex, int endingVertex, bool directed = false)
    {
        this->adjacencyList[startingVertex].push_back(endingVertex);
        if (!directed)
            this->adjacencyList[endingVertex].push_back(startingVertex);
    }

    // print the adjacency list
    void print()
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

    // dfs helper function to check if the graph is cyclic
    bool is_cyclic_dfs_helper(int vertex, int parentVertex)
    {
        stack<int> Stack;
        Stack.push(vertex);
        visited[vertex] = true;
        parent[vertex] = parentVertex;
        while (not Stack.empty())
        {
            int topNode = Stack.top();
            Stack.pop();

            // checking its neighbours
            for (auto &neighbour : adjacencyList[topNode])
            {
                // if not visited then visit it
                if (not visited[neighbour])
                {
                    Stack.push(neighbour);
                    visited[neighbour] = true;
                    parent[neighbour] = topNode;
                }
                // if visited and parent is not same then it is cyclic
                else if (parent[topNode] != neighbour)
                {
                    return true;
                }
            }
        }
        return false;
    }

    // is cyclic
    bool is_cyclic_dfs()
    {
        for (auto &vertex : adjacencyList)
        {
            if (!visited[vertex.first])
            {
                if (is_cyclic_dfs_helper(vertex.first, -1))
                    return true;
            }
        }
        return false;
    }

    // bfs helper function to check if the graph is cyclic
    bool is_cyclic_bfs_helper(int vertex, int parentVertex)
    {
        queue<int> Queue;
        Queue.push(vertex);
        visited[vertex] = true;
        parent[vertex] = parentVertex;
        while (not Queue.empty())
        {
            int frontNode = Queue.front();
            Queue.pop();
            // checking its neighbours
            for (auto &neighbour : adjacencyList[frontNode])
            {
                // if not visited then visit it
                if (not visited[neighbour])
                {
                    Queue.push(neighbour);
                    visited[neighbour] = true;
                    parent[neighbour] = frontNode;
                }
                // if visited and parent is not same then it is cyclic
                else if (parent[frontNode] != neighbour)
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_cyclic_bfs()
    {
        for (auto &vertex : adjacencyList)
        {
            if (!visited[vertex.first])
            {
                if (is_cyclic_bfs_helper(vertex.first, -1))
                    return true;
            }
        }
        return false;
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
        cout << "Is the edge directed? (1 for yes, 0 for no): ";
        bool flag;
        cin >> flag;
        graph.addEdge(startingVertex, endingVertex, flag);
    }
    // Print adjacency list
    cout << "Adjacency List: " << endl;
    graph.print();
    // Check for cycles using DFS
    if (graph.is_cyclic_dfs())
    {
        cout << "The graph is cyclic." << endl;
    }
    else
    {
        cout << "The graph is acyclic." << endl;
    }
    // Check for cycles using BFS
    if (graph.is_cyclic_bfs())
    {
        cout << "The graph is cyclic." << endl;
    }
    else
    {
        cout << "The graph is acyclic." << endl;
    }
    return 0;
}