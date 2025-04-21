#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class KnapsackProblem
{
    vector<pair<double, double>> items; // pair of (value, weight)
    int capacity;

public:
    KnapsackProblem(int capacity)
    {
        this->capacity = capacity;
    }
    KnapsackProblem(vector<pair<double, double>> items, int capacity)
    {
        this->items = items;
        this->capacity = capacity;
    }
    void addItem(double value, double weight)
    {
        items.push_back(make_pair(value, weight));
    }
    // knapsack function
    pair<vector<pair<double, double>>, double> knapsack()
    {
        // sorting based on value/weight ratio
        sort(items.begin(), items.end(), [](pair<double, double> &a, pair<double, double> &b)
             { return (double)a.first / a.second > (double)b.first / b.second; });

        int totalValue = 0;
        int remainingCapacity = capacity;
        vector<pair<double, double>> selectedItems; // pair of (value, weight)
        // select items
        for (pair<double, double> job : items)
        {
            if (remainingCapacity >= job.second)
            {
                selectedItems.push_back(job);    // select the item
                totalValue += job.first;         // add the value of the item to the total value
                remainingCapacity -= job.second; // reduce the remaining capacity
            }
            else
            {
                // take fraction of the item
                double fraction = (double)remainingCapacity / job.second;                        // calculate the fraction of the item to take
                totalValue += job.first * fraction;                                              // add the value of the fraction of the item to the total value
                selectedItems.push_back(make_pair(job.first * fraction, job.second * fraction)); // add the fraction of the item to the selected items
                remainingCapacity = 0;                                                           // no remaining capacity
            }
        }
        return make_pair(selectedItems, totalValue); // return the selected items and the total value
    }
};
int main()
{
    int capacity = 50;                  // capacity of the knapsack
    KnapsackProblem knapsack(capacity); // create a knapsack with capacity 50
    knapsack.addItem(60, 10);           // add items to the knapsack
    knapsack.addItem(100, 20);
    knapsack.addItem(120, 30);
    pair<vector<pair<double, double>>, double> result = knapsack.knapsack(); // call the knapsack function
    cout << "Selected items: " << endl;
    for (pair<double, double> item : result.first) // print the selected items
    {
        cout << "Value: " << item.first << ", Weight: " << item.second << endl;
    }
    cout << "Total value: " << result.second << endl;                          // print the total value
    cout << "Total weight: " << capacity - result.first.back().second << endl; // print the total weight
    return 0;
}