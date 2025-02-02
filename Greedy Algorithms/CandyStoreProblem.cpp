#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    pair<int, int> calculateMinMaxCost(vector<int> &candies, int freecandy)
    {
        int minCost = 0;
        int maxCost = 0;

        int buy = 0;
        int free = candies.size() - 1; // picking postion of the free
        while (buy <= free)
        {
            minCost += candies[buy];
            buy++;
            free = free - freecandy;
        }

        free = 0;// picking postion of the free
        buy = candies.size() - 1; 
        while (buy >= free)
        {
            maxCost += candies[buy];
            buy--;
            free = free + freecandy;
        }

        return make_pair(minCost, maxCost);
    }
};

int main()
{
    vector<int> candies = {7, 8, 3, 1, 6, 9, 2, 5}; // Costs of the candies
    int free_candies = 2;                           // Number of free candies per purchased candy

    Solution sol;
    pair<int, int> result = sol.calculateMinMaxCost(candies, free_candies);

    cout << "Minimum cost: " << result.first << endl;
    cout << "Maximum cost: " << result.second << endl;

    return 0;
}
