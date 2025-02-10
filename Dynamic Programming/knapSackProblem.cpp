#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class KnapSack
{
public:
    int Recurrsive(vector<int> const weight, vector<int> const values, int index, int capacity)
    {
        if (index == 0)
        {
            if (weight[0] <= capacity)
                return values[0];
            else
                return 0;
        }

        int inclusive = 0;
        if (weight[index] <= capacity)
            inclusive = values[index] + Recurrsive(weight, values, index - 1, capacity - weight[index]);
        int exclusive = Recurrsive(weight, values, index - 1, capacity);

        return max(inclusive, exclusive);
    }
    int Memoization(vector<int> const weight, const vector<int> values, int index, int capacity, vector<vector<int>> &mappingVector)
    {
        if (index == 0)
            if (weight[0] <= capacity)
                return values[0];
            else
                return 0;
        if (mappingVector[index][capacity] != -1)
            return mappingVector[index][capacity];
        int inclusive = 0;
        if (weight[index] <= capacity)
            inclusive = values[index] + Memoization(weight, values, index - 1, capacity - weight[index], mappingVector);
        int exclusive = Memoization(weight, values, index - 1, capacity, mappingVector);

        mappingVector[index][capacity] = max(inclusive, exclusive);
        return mappingVector[index][capacity];
    }

    int Tabulation(const vector<int> weights, const vector<int> values, int index, int capacity)
    {
        vector<vector<int>> mappingVector(index + 1, vector<int>(capacity + 1, -1));
        for (int weight = weights[0]; weight <= capacity; weight++)
        {
            if (weights[0] <= capacity)
                mappingVector[0][weight] = values[0];
            else
                mappingVector[0][weight] = 0;
        }
        for (int i = 1; i < index; i++)
        {
            for (int weight = 0; weight <= capacity; weight++)
            {
                int inclusive = values[i] + mappingVector[i - 1][weight - weights[i]];
                int exclusive = mappingVector[i - 1][weight];
                mappingVector[i][weight] = max(inclusive, exclusive);
            }
        }
        return mappingVector[index - 1][capacity];
    }
};
int main()
{
    vector<int> weight = {1, 3, 5, 7};
    vector<int> values = {1, 4, 2, 7};
    int capacity = 13;
    KnapSack ks;
    int max_value = ks.Recurrsive(weight, values, weight.size() - 1, capacity);
    cout << "Maximum value in Knapsack = " << max_value << endl;
    vector<vector<int>> mappingVector(weight.size(), vector<int>(capacity + 1, -1));
    int max_value_memo = ks.Memoization(weight, values, weight.size() - 1, capacity, mappingVector);
    cout << "Maximum value in Knapsack with Memoization = " << max_value_memo << endl;
    ks.Tabulation(weight, values, weight.size(), capacity);
    int max_value_tab = ks.Tabulation(weight, values, weight.size(), capacity);
    cout << "Maximum value in Knapsack with Tabulation = " << max_value_tab << endl;
    return EXIT_SUCCESS;
}