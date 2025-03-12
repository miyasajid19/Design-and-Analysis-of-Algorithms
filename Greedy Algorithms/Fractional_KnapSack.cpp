#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an item
class Item
{
public:
    int value;
    int weight;

    // Constructor
    Item(int v, int w) : value(v), weight(w) {}
};

// Function to compare two items based on their value-to-weight ratio
bool compare(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to solve the Fractional Knapsack Problem
double fractionalKnapsack(int capacity, vector<Item> &items)
{
    // Sort items by their value-to-weight ratio in descending order
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0; // Total value of knapsack

    for (Item item : items)
    {
        if (capacity == 0)
            break; // If the knapsack is full

        // Take as much as possible from the current item
        if (item.weight <= capacity)
        {
            // If the item can be completely added
            totalValue += item.value;
            capacity -= item.weight;
        }
        else
        {
            // Take the fractional part of the item
            totalValue += item.value * ((double)capacity / item.weight);
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main()
{
    // Example input: 6 items, knapsack capacity 16
    int n = 6;         // Number of items
    int capacity = 16; // Capacity of knapsack

    vector<Item> items = {
        Item(6, 6),
        Item(2, 10),
        Item(1, 3),
        Item(8, 5),
        Item(3, 1),
        Item(5, 3)};

    // Display the items
    cout << "Items (value, weight):" << endl;
    for (const Item &item : items)
    {
        cout << "(" << item.value << ", " << item.weight << ")" << endl;
    }

    // Get the maximum value that can be obtained
    double maxValue = fractionalKnapsack(capacity, items);

    // Display the result
    cout << "Maximum value in Knapsack with capacity " << capacity << " = " << maxValue << endl;

    return 0;
}
