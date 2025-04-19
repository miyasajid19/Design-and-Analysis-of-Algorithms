#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

class EdmondsKarp {
private:
    int vertices;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> adj;

public:
    EdmondsKarp(int v) : vertices(v) {
        capacity.resize(v, std::vector<int>(v, 0));
        adj.resize(v);
    }

    void addEdge(int u, int v, int cap) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for residual graph
        capacity[u][v] = cap;
    }

    int bfs(int source, int sink, std::vector<int>& parent) {
        std::fill(parent.begin(), parent.end(), -1);
        parent[source] = -2; // Mark the source as visited
        std::queue<std::pair<int, int>> q;
        q.push({source, INT_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = std::min(flow, capacity[cur][next]);
                    if (next == sink) {
                        return new_flow;
                    }
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

    int maxFlow(int source, int sink) {
        int flow = 0;
        std::vector<int> parent(vertices);
        int new_flow;

        while ((new_flow = bfs(source, sink, parent)) != 0) {
            flow += new_flow;
            int cur = sink;
            while (cur != source) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return flow;
    }
};

int main() {
    // Fixed input
    int vertices = 6;
    EdmondsKarp ek(vertices);

    // Adding edges (u, v, capacity)
    ek.addEdge(0, 1, 16);
    ek.addEdge(0, 2, 13);
    ek.addEdge(1, 2, 10);
    ek.addEdge(1, 3, 12);
    ek.addEdge(2, 1, 4);
    ek.addEdge(2, 4, 14);
    ek.addEdge(3, 2, 9);
    ek.addEdge(3, 5, 20);
    ek.addEdge(4, 3, 7);
    ek.addEdge(4, 5, 4);

    int source = 0, sink = 5;
    std::cout << "The maximum possible flow is " << ek.maxFlow(source, sink) << std::endl;

    return 0;
}