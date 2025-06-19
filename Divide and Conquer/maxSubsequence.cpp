#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
class Solution
{
public:
    int bruteforce(vector<int> array)
    {
        int maxsum = INT_MIN;
        for (int i = 0; i < array.size(); i++)
        {
            int sum = 0;
            for (int j = i; j < array.size(); j++)
            {
                sum += array[j];
                maxsum = max(maxsum, sum);
            }
        }
        return maxsum;
    }
    int cross_Sum(vector<int> array, int low, int middle, int high)
    {
        int leftsum = INT_MIN, rightsum = INT_MIN;
        int sum = 0;
        for (int i = middle; i >= low; i--)
        {
            sum += array[i];
            leftsum = max(leftsum, sum);
        }
        sum = 0;
        for (int i = middle + 1; i <= high; i++)
        {
            sum += array[i];
            rightsum = max(rightsum, sum);
        }

        return leftsum + rightsum;
    }
    int divideAndConquer(vector<int> array, int low, int high)
    {
        if (low == high)
            return array[low];

        int middle = (high + low) >> 1;
        int leftMax = divideAndConquer(array, low, middle);
        int rightMax = divideAndConquer(array, middle + 1, high);
        int crosssum = cross_Sum(array, low, middle, high);

        return max(leftMax, max(rightMax, crosssum));
    }
};
int main()
{
    vector<int> array = {-2,-3,4,-1,-2,1,5,-3};
    Solution s;
    cout << "Brute force ::" << s.bruteforce(array) << endl;
    cout << "Divide and Conquer ::" << s.divideAndConquer(array, 0, array.size() - 1);
    return EXIT_SUCCESS;
}