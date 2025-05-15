#include <bits/stdc++.h>
using namespace std;

class TSPSolver {
private:
    int N;
    vector<vector<int>> adj;
    vector<int> final_path;
    vector<bool> visited;
    int final_res;

    void copyToFinal(const vector<int>& curr_path) {
        for (int i = 0; i < N; i++)
            final_path[i] = curr_path[i];
        final_path[N] = curr_path[0];
    }

    int firstMin(int i) {
        int min_val = INT_MAX;
        for (int k = 0; k < N; k++)
            if (adj[i][k] < min_val && i != k)
                min_val = adj[i][k];
        return min_val;
    }

    int secondMin(int i) {
        int first = INT_MAX, second = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (i == j) continue;

            if (adj[i][j] <= first) {
                second = first;
                first = adj[i][j];
            } else if (adj[i][j] <= second && adj[i][j] != first) {
                second = adj[i][j];
            }
        }
        return second;
    }

    void TSPRec(int curr_bound, int curr_weight, int level, vector<int>& curr_path) {
        if (level == N) {
            if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
                int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
                if (curr_res < final_res) {
                    copyToFinal(curr_path);
                    final_res = curr_res;
                }
            }
            return;
        }

        for (int i = 0; i < N; i++) {
            if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
                int temp = curr_bound;
                curr_weight += adj[curr_path[level - 1]][i];

                if (level == 1) {
                    curr_bound -= (firstMin(curr_path[level - 1]) + firstMin(i)) / 2;
                } else {
                    curr_bound -= (secondMin(curr_path[level - 1]) + firstMin(i)) / 2;
                }

                if (curr_bound + curr_weight < final_res) {
                    curr_path[level] = i;
                    visited[i] = true;

                    TSPRec(curr_bound, curr_weight, level + 1, curr_path);
                }

                curr_weight -= adj[curr_path[level - 1]][i];
                curr_bound = temp;
                fill(visited.begin(), visited.end(), false);
                for (int j = 0; j < level; j++)
                    visited[curr_path[j]] = true;
            }
        }
    }

public:
    TSPSolver(int n, vector<vector<int>> matrix)
        : N(n), adj(matrix), final_path(n + 1), visited(n, false), final_res(INT_MAX) {}

    void solve() {
        vector<int> curr_path(N + 1, -1);
        int curr_bound = 0;

        for (int i = 0; i < N; i++) {
            curr_bound += (firstMin(i) + secondMin(i));
        }

        curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

        visited[0] = true;
        curr_path[0] = 0;

        TSPRec(curr_bound, 0, 1, curr_path);
    }

    void printResult() {
        cout << "Minimum cost : " << final_res << endl;
        cout << "Path Taken : ";
        for (int i = 0; i <= N; i++)
            cout << final_path[i] << " ";
        cout << endl;
    }
};

int main() {
    vector<vector<int>> adj = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSPSolver solver(4, adj);
    solver.solve();
    solver.printResult();

    return 0;
}
