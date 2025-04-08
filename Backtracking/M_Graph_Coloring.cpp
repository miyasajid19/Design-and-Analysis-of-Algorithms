#include <iostream>
#include <vector>
using namespace std;

class GraphColoring
{
private:
    int n;                     // Number of nodes
    int m;                     // Number of colors
    vector<vector<int>> graph; // Adjacency matrix
    vector<int> color;         // Color assignment for nodes

    // Function to check if the current color assignment is safe
    bool isSafe(int node, int col)
    {
        for (int k = 0; k < n; k++)
        {
            if (graph[node][k] == 1 && color[k] == col)
            {
                return false;
            }
        }
        return true;
    }

    // Recursive function to solve the graph coloring problem
    bool graphColoringUtil(int node)
    {
        if (node == n)
        {
            return true; // All nodes are colored
        }

        for (int col = 1; col <= m; col++)
        {
            if (isSafe(node, col))
            {
                color[node] = col; // Assign color
                if (graphColoringUtil(node + 1))
                {
                    return true;
                }
                color[node] = 0; // Backtrack
            }
        }
        return false;
    }

public:
    GraphColoring(int nodes, int colors, vector<vector<int>> adjacencyMatrix)
        : n(nodes), m(colors), graph(adjacencyMatrix), color(nodes, 0) {}

    // Function to solve the M-Coloring problem
    bool solve()
    {
        return graphColoringUtil(0); //
    }

    void displayResult()
    {
        if (solve())
        {
            cout << "Solution exists: The graph can be colored with " << m << " colors.\n";
            cout << "Color assignment: ";
            for (int i = 0; i < n; i++)
            {
                cout << color[i] << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "No solution exists: The graph cannot be colored with " << m << " colors.\n";
        }
    }
};

int main()
{
    // Dummy data
    int n = 4; // Number of nodes
    int m = 3; // Number of colors
    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}};

    GraphColoring gc(n, m, adjacencyMatrix);
    gc.displayResult();

    return 0;
}