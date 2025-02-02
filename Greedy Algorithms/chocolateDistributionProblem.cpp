#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    long long findMinDifference(vector<long long>& prices, long long numPrices, long long windowSize) {
        // Step 1: Sort the array to make sure the prices are in order
        sort(prices.begin(), prices.end());
        
        // Step 2: Initialize a variable to store the minimum difference, set it to a very large value
        long long minDifference = LLONG_MAX;

        // Step 3: Iterate through the sorted prices and calculate the difference between the max and min
        // of every window of size `windowSize`
        for (int startIndex = 0; startIndex <= numPrices - windowSize; startIndex++) {
            long long currentDifference = prices[startIndex + windowSize - 1] - prices[startIndex];
            minDifference = min(currentDifference, minDifference);
        }
        
        // Step 4: Return the minimum difference found
        return minDifference;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif

    Solution solution;
    
    // Define a test case where we want to find the minimum difference in a window of size 6
    vector<long long> prices = {12, 11, 15, 43, 23, 123, 75, 234, 23, 43, 2, 31};
    long long numPrices = 12;  // Total number of prices in the array
    long long windowSize = 6;  // Window size to find the minimum difference
    
    // Call the function and output the result
    cout << "The minimum difference is " << solution.findMinDifference(prices, numPrices, windowSize) << endl;
    
    return EXIT_SUCCESS;
}
