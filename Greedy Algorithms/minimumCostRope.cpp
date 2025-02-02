#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    // Function to calculate the minimum cost to merge all elements
    int minimumCost(vector<int>& arr) {
        // Create a priority queue (min-heap)
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Push all elements from the array into the min-heap
        for (int num : arr)
            minHeap.push(num);

        // Initialize the total cost
        int totalCost = 0;

        // Continue until only one element is left in the heap
        while (minHeap.size() > 1) {
            // Pop the two smallest elements from the heap
            int smallest = minHeap.top();
            minHeap.pop();
            int secondSmallest = minHeap.top();
            minHeap.pop();

            // Calculate the cost to merge these two elements
            int mergeCost = smallest + secondSmallest;

            // Add the merge cost to the total cost
            totalCost += mergeCost;

            // Push the merged element back into the heap
            minHeap.push(mergeCost);
        }

        // The total cost is stored in totalCost
        return totalCost;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif

    // Create an object of the Solution class
    Solution solution;

    // Example input array (can be customized or taken from user input)
    vector<int> arr = {4, 3, 2, 6};

    // Call the minimumCost function and print the result
    cout << "The minimum cost of merging is: " << solution.minimumCost(arr) << endl;

    return EXIT_SUCCESS;
}
