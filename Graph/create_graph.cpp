#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <list>
using namespace std;

class Graph
{
    unordered_map<int, list<int>> adjacencyMatrix;

public:
    Graph() {}

    void addEdges(int startingVertex, int endingVertex, bool directed = false)
    {
        this->adjacencyMatrix[startingVertex].push_back(endingVertex);
        if (!directed)
            this->adjacencyMatrix[endingVertex].push_back(startingVertex);
    }

    void displayAdjacencyMatrix()
    {
        for (auto &vertex : adjacencyMatrix)
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

        graph.addEdges(startingVertex, endingVertex, flag);
    }

    cout << "\nAdjacency Matrix Representation:\n";
    graph.displayAdjacencyMatrix();

    return EXIT_SUCCESS;
}