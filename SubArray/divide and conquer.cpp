#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class MaximumSubArray
{
    vector<int> arr;

    int crossMaxSubarray(int low, int middle, int high)
    {
        int leftSum = INT_MIN, rightSum = INT_MIN, sum = 0;

        for (int i = middle; i >= low; i--)
        {
            sum += arr[i];
            leftSum = max(leftSum, sum);
        }
        sum = 0;
        for (int i = middle + 1; i <= high; i++)
        {
            sum += arr[i];
            rightSum = max(rightSum, sum);
        }

        return leftSum + rightSum;
    }

    int maximumSubarray(int low, int high)
    {
        if (low == high)
        {
            return arr[low];
        }
        int middle = (high + low) / 2;
        int leftMax = maximumSubarray(low, middle);
        int rightMax = maximumSubarray(middle + 1, high);
        int crossMax = crossMaxSubarray(low, middle, high);
        return max(leftMax, max(rightMax, crossMax));
    }

public:
    MaximumSubArray(const vector<int> &arr) : arr(arr) {}

    int findMaximumSubarray()
    {
        return maximumSubarray(0, arr.size() - 1);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cout << "Enter the number of elements in the array: " << endl;
    int n;
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    MaximumSubArray obj(arr);
    cout << "Maximum sum of subarray is: " << obj.findMaximumSubarray() << endl;

    return 0;
}