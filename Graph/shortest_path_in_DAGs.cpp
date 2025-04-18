#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Graph
{
    unordered_map<int, list<pair<int, int>>> adjacencyList;
    int vertices;

public:
    Graph(int vertices) : vertices(vertices) {}

    void addEdge(int startingVertex, int endingVertex, int weight)
    {
        adjacencyList[startingVertex].push_back(make_pair(endingVertex, weight));
    }

    void printAdjacencyMatrix()
    {
        for (auto &traversingVertex : adjacencyList)
        {
            cout << traversingVertex.first << " ---> ";
            for (pair<int, int> adjacentVertex : traversingVertex.second)
            {
                cout << "[ " << adjacentVertex.first << " , " << adjacentVertex.second << " ]\t";
            }
            cout << endl;
        }
    }

    void dfsFiller(int traversingNode, unordered_map<int, bool> &hasVisited, stack<int> &stk)
    {
        hasVisited[traversingNode] = true;
        for (auto adjacent : adjacencyList[traversingNode])
        {
            if (!hasVisited[adjacent.first])
            {
                dfsFiller(adjacent.first, hasVisited, stk);
            }
        }
        stk.push(traversingNode);
    }

    void topologicalSort(stack<int> &stk)
    {
        unordered_map<int, bool> hasVisited;
        for (int i = 0; i < vertices; i++)
        {
            if (!hasVisited[i])
            {
                dfsFiller(i, hasVisited, stk);
            }
        }
    }

    void getShortestPath(int source, vector<int> &distance, stack<int> &topologicalsort)
    {
        distance[source] = 0;

        while (!topologicalsort.empty())
        {
            int topNode = topologicalsort.top();
            topologicalsort.pop();

            if (distance[topNode] != INT_MAX)
            {
                for (auto temp : adjacencyList[topNode])
                {
                    int sum = distance[topNode] + temp.second;
                    if (sum < distance[temp.first])
                    {
                        distance[temp.first] = sum;
                    }
                }
            }
        }
    }

    vector<int> shortestPath(int source)
    {
        stack<int> topologicalsort;
        vector<int> distance(vertices, INT_MAX);

        topologicalSort(topologicalsort);
        getShortestPath(source, distance, topologicalsort);

        return distance;
    }
};

int main()
{
    Graph graph(6);

    // Adding directed edges with weights
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 6);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 4, 4);
    graph.addEdge(2, 5, 2);
    graph.addEdge(3, 4, -1);
    graph.addEdge(4, 5, -2);

    graph.printAdjacencyMatrix();

    int source = 1; // Source vertex
    vector<int> ans = graph.shortestPath(source);

    cout << "Shortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        if (ans[i] == INT_MAX)
            cout << "INF\t";
        else
            cout << ans[i] << "\t";
    }
    cout << endl;

    return EXIT_SUCCESS;
}