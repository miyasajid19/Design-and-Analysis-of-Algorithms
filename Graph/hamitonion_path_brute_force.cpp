#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    int numVertices;

public:
    Graph(const vector<vector<int>>& matrix) : adjacencyMatrix(matrix), numVertices(matrix.size()) {}

    // Function to check if a given permutation is a Hamiltonian Path
    bool isHamiltonianPath(const vector<int>& path) const {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            if (adjacencyMatrix[path[i]][path[i + 1]] == 0) {
                return false; // No edge between consecutive vertices
            }
        }
        return true;
    }

    void findHamiltonianPath() const {
        vector<int> vertices(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            vertices[i] = i;
        }

        bool found = false;
        do {
            if (isHamiltonianPath(vertices)) {
                found = true;
                cout << "Hamiltonian Path found: ";
                for (int v : vertices) {
                    cout << v << " ";
                }
                cout << endl;
                break;
            }
        } while (next_permutation(vertices.begin(), vertices.end()));

        if (!found) {
            cout << "No Hamiltonian Path exists.\n";
        }
    }
};

int main() {
    // Fixed input adjacency matrix
    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    Graph graph(adjacencyMatrix);
    graph.findHamiltonianPath();

    return 0;
}