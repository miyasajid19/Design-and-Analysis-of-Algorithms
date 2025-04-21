#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <climits>
using namespace std;

// Edmonds-Karp Algorithm for finding maximum flow in a flow network
template <typename T>
class EdmondsKarp
{
    unordered_map<T, vector<pair<T, int>>> adj; // Adjacency list (node, capacity)
    T source, sink;                             // Source and sink nodes
    int max_flow;                               // To store the maximum flow

    // Helper function to perform BFS and find an augmenting path
    bool bfs(unordered_map<T, T> &parent_mapping)
    {
        queue<T> bfs_queue;
        set<T> visited;

        bfs_queue.push(source);
        visited.insert(source);

        while (not bfs_queue.empty())
        {
            T current = bfs_queue.front();
            bfs_queue.pop();

            for (auto &neighbor : adj[current])
            {
                if (visited.find(neighbor.first) == visited.end() && neighbor.second > 0)
                {
                    visited.insert(neighbor.first);
                    parent_mapping[neighbor.first] = current;

                    if (neighbor.first == sink)
                    {
                        return true; // Path to sink found
                    }

                    bfs_queue.push(neighbor.first);
                }
            }
        }
        return false; // No path found
    }

    // Helper function to update residual capacities along the augmenting path
    void updateResidualCapacities(const unordered_map<T, T> &parent_mapping, int path_flow)
    {
        for (T v = sink; v != source; v = parent_mapping.at(v))
        {
            T u = parent_mapping.at(v);

            // Reduce capacity in the forward edge
            for (auto &edge : adj[u])
            {
                if (edge.first == v)
                {
                    edge.second -= path_flow;
                    break;
                }
            }

            // Increase capacity in the reverse edge
            bool reverse_edge_found = false;
            for (auto &edge : adj[v])
            {
                if (edge.first == u)
                {
                    edge.second += path_flow;
                    reverse_edge_found = true;
                    break;
                }
            }
            if (!reverse_edge_found)
            {
                adj[v].push_back({u, path_flow});
            }
        }
    }

public:
    EdmondsKarp(const unordered_map<T, vector<pair<T, int>>> &adj_list, T src, T snk)
        : adj(adj_list), source(src), sink(snk), max_flow(0) {}

    // Function to add an edge to the graph
    void addEdge(T u, T v, int capacity)
    {
        adj[u].push_back({v, capacity});
    }

    // Function to compute the maximum flow
    int MaxFlow()
    {
        unordered_map<T, T> parent_mapping;

        while (bfs(parent_mapping))
        {
            // Find the bottleneck capacity in the augmenting path
            int path_flow = INT_MAX;
            for (T v = sink; v != source; v = parent_mapping[v])
            {
                T u = parent_mapping[v];
                for (auto &edge : adj[u])
                {
                    if (edge.first == v)
                    {
                        path_flow = min(path_flow, edge.second);
                        break;
                    }
                }
            }

            // Update residual capacities and add path flow to the overall flow
            updateResidualCapacities(parent_mapping, path_flow);
            max_flow += path_flow;
        }

        return max_flow;
    }
};

int main()
{
    // Example usage of the Edmonds-Karp algorithm
    unordered_map<string, vector<pair<string, int>>> adj_list = {
        {"Source", {{"B", 3}, {"D", 3}}},
        {"B", {{"C", 4}}},
        {"C", {{"Source", 3}, {"D", 1}, {"E", 2}}},
        {"D", {{"E", 2}, {"F", 6}}},
        {"E", {{"B", 1}, {"Sink", 1}}},
        {"F", {{"Sink", 9}}}};

    EdmondsKarp<string> ek(adj_list, "Source", "Sink");
    cout << "Maximum Flow: " << ek.MaxFlow() << endl;

    return 0;
}
