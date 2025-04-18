#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;
class Graph
{
    unordered_map<int, list<int>> adjacencyList;
    unordered_map<int, bool> visited;

public:
    Graph() {}

    // adding edges
    void addEdge(int startingVertex, int endingVertex, bool directed = false)
    {
        this->adjacencyList[startingVertex].push_back(endingVertex);
        if (!directed)
            this->adjacencyList[endingVertex].push_back(startingVertex);
    }

    // dfs helper
    void dfs(int startingVertex)
    {
        stack<int>Stack;
        Stack.push(startingVertex);
        visited[startingVertex] = true;

        while(not Stack.empty())
        {
            int top = Stack.top();
            Stack.pop();
            cout << top << " ";
            // iterate through the neighbours of the top vertex 
            for (auto &neighbour : adjacencyList[top])
            {
                if (!visited[neighbour])
                {
                    Stack.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }

    }

    // DFS traversal
    void dfs_traversal()
    {
        for (auto &vertex : adjacencyList)
        {
            if (!visited[vertex.first])
            {
                dfs(vertex.first);
            }
        }
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
        cout << "Enter starting and ending vertex: "<<endl;
        cin >> startingVertex >> endingVertex;
        cout << "Is the edge directed? (1 for yes, 0 for no): "<<endl;
        bool flag;
        cin >> flag;
        graph.addEdge(startingVertex, endingVertex, flag);
    }
    cout << "DFS Traversal: ";
    graph.dfs_traversal();
    cout << endl;
    return 0;
}