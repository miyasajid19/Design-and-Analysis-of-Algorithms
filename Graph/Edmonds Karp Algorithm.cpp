#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;
// Edmonds-Karp Algorithm for finding maximum flow in a flow network
template <typename T>
class EdmondsKarp
{
    unordered_map<T, T> parent_mapping; // To store the path
    queue<T> bfs_queue;                 // To store the BFS queue
    set<T> visited;                     // To store the visited nodes
    T source, sink;                     // Source and sink nodes
    int max_flow;                       // To store the maximum flow
    // Number of nodes in the grap
    int num_nodes;
    unordered_map<T, vector<pair<T, int>>> adj; // Adjacency list (node, capacity)
public:
    EdmondsKarp(unordered_map<T, vector<pair<T, int>>> adj_list, T src, T snk) : adj(adj_list), source(src), sink(snk), max_flow(0)
    {
        num_nodes = adj_list.size();
    }
    EdmondsKarp(int n) : num_nodes(n), max_flow(0) {}

    // Function to add an edge to the graph
    void addEdge(T u, T v, int capacity)
    {
        adj[u].push_back({v, capacity});
    }
    void setSource(T src)
    {
        source = src;
    }
    void setSink(T snk)
    {
        sink = snk;
    }
    void set(T src, T snk)
    {
        source = src;
        sink = snk;
    }

    int MaxFlow()
    {
        // add source to the queue
        bfs_queue.push(source);
        // mark the source as visited
        visited.insert(source);

        // apply BFS to find the path from source to sink
        while (not bfs_queue.empty())
        {
            // pop the front of the queue
            T front_element = bfs_queue.front();
            bfs_queue.pop();
            // check if we reached the sink
            if (front_element == sink)
            {
                // trace path from sink to source
                T current = sink;
                while (current != source)
                {
                    // get the parent of the current node
                    T parent = parent_mapping[current];
                    // find the capacity of the edge from parent to current
                    int capacity = 0;
                    for (auto &edge : adj[parent])
                    {
                        if (edge.first == current)
                        {
                            capacity = edge.second;
                            break;
                        }
                    }
                    // update the capacity of the edge from parent to current
                    for (auto &edge : adj[parent])
                    {
                        if (edge.first == current)
                        {
                            edge.second -= capacity;
                            break;
                        }
                    }
                    // update the capacity of the edge from current to parent
                    bool found = false;
                    for (auto &edge : adj[current])
                    {
                        if (edge.first == parent)
                        {
                            edge.second += capacity;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        adj[current].push_back({parent, capacity});
                    }
                    // update the max flow
                    max_flow += capacity;
                    // move to the parent node
                    current = parent;
                }
                // clear the visited set and the parent mapping
                visited.clear();
                parent_mapping.clear();
                // add source to the queue
                bfs_queue.push(source);
            }

            // explore  all unexplored neighbors of the front element
            for (auto &neighbours : adj[front_element])
            {
                // check if the neighbour is not visited and has capacity left
                if (visited.find(neighbours.first) == visited.end() && neighbours.second > 0)
                {
                    // mark the neighbour as visited
                    visited.insert(neighbours.first);
                    // add the neighbour to the queue
                    bfs_queue.push(neighbours.first);
                    // set the parent of the neighbour to the front element
                    parent_mapping[neighbours.first] = front_element;
                }
            }
        }
        return max_flow;
    }
};
int main()
{
    // Example usage of the Edmonds-Karp algorithm
    unordered_map<string, vector<pair<string, int>>> adj_list;
    adj_list["Source"].push_back({"A", 16});
    adj_list["A"].push_back({"B", 13});
    adj_list["B"].push_back({"A", 10});
    adj_list["B"].push_back({"C", 12});
    adj_list["A"].push_back({"C", 4});
    adj_list["A"].push_back({"D", 14});
    adj_list["C"].push_back({"A", 9});
    adj_list["C"].push_back({"Sink", 20});
    adj_list["D"].push_back({"C", 7});
    adj_list["D"].push_back({"Sink", 4});
    EdmondsKarp<string> ek(adj_list, "Source", "Sink");
    cout << "Maximum Flow: " << ek.MaxFlow() << endl;
    return 0;
}