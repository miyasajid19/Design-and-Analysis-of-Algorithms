#include <iostream>
#include <vector>
using namespace std;

class HamiltonianPath {
private:
    int V; // Number of vertices
    vector<vector<int>> graph; // Adjacency matrix
    vector<int> path; // Stores the Hamiltonian path

    bool isSafe(int v, int pos) {
        // Check if the vertex is adjacent to the previous vertex in the path
        if (graph[path[pos - 1]][v] == 0)
            return false;

        // Check if the vertex is already included in the path
        for (int i = 0; i < pos; i++) {
            if (path[i] == v)
                return false;
        }

        return true;
    }

    bool solveHamiltonianPath(int pos) {
        // Base case: If all vertices are included in the path
        if (pos == V)
            return true;

        // Try different vertices as the next candidate
        for (int v = 0; v < V; v++) {
            if (isSafe(v, pos)) {
                path[pos] = v;

                if (solveHamiltonianPath(pos + 1))
                    return true;

                // Backtrack
                path[pos] = -1;
            }
        }

        return false;
    }

public:
    HamiltonianPath(int vertices, vector<vector<int>> adjacencyMatrix)
        : V(vertices), graph(adjacencyMatrix), path(vertices, -1) {}

    void findHamiltonianPath() {
        // Start from the first vertex
        path[0] = 0;

        if (solveHamiltonianPath(1)) {
            cout << "Hamiltonian Path found: ";
            for (int v : path)
                cout << v << " ";
            cout << endl;
        } else {
            cout << "No Hamiltonian Path exists." << endl;
        }
    }
};

int main() {
    // Fixed input graph (adjacency matrix)
    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    HamiltonianPath hp(4, adjacencyMatrix);
    hp.findHamiltonianPath();

    return 0;
}