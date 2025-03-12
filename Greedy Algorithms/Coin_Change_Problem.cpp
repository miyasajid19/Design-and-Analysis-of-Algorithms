#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
class solution
{
    vector<int> coins;

public:
    solution(vector<int> coins)
    {
        this->coins = coins;
        // reverse sorting of coins
        sort(this->coins.begin(), this->coins.end(), greater<int>());
    }

    int minimum(int amount)
    {
        if (amount == 0)
            return 0;
        if (amount < 0)
            return -1;
        int count = 0;
        for (int i : coins)
        {
            if (amount / i > 0)
            {
                count += amount / i;
                amount = amount % i;
            }
        }
        return count;
    }
    int MinimumCoins(int amount)
    {
        if (amount == 0)
            return 0;

        if (amount < 0)
            return -1;

        for (int i = 0; i < coins.size(); i++)
        {
            int res = MinimumCoins(amount - coins[i]);
            if (res >= 0)
                return res + 1;
        }
        return -1;
    }
};
int main()
{
    // Define a vector of coin denominations
    vector<int> coins = {1, 2, 5};

    // Create a solution object with the given coin denominations
    solution s(coins);

    // Calculate the minimum number of coins needed to make the amount 11 using the greedy approach
    cout << "Minimum coins needed (Greedy): " << s.minimum(11) << endl;

    // Calculate the minimum number of coins needed to make the amount 11 using the recursive approach
    cout << "Minimum coins needed (Recursive): " << s.MinimumCoins(11) << endl;

    // Return success status
    return EXIT_SUCCESS;
}