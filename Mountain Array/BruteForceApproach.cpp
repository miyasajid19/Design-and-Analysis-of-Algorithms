#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution
{
public:
    pair<bool, int> isMountainArray(vector<int> arr)
    {
        int length = arr.size();
        if (length < 3)
            return make_pair(false, -1);

        int peak = -1;

        // Find the peak
        for (int i = 1; i < length - 1; ++i)
        {
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1])  // Peak is found
            {
                peak = i;
                break;
            }
        }

        // If no peak was found or if peak is at the boundaries
        if (peak == -1 || peak == 0 || peak == length - 1)
        {
            return make_pair(false, -1);
        }

        // Check if the array strictly increases up to the peak
        for (int i = 1; i < peak; ++i)
        {
            if (arr[i] <= arr[i - 1])
            {
                return make_pair(false, -1);
            }
        }

        // Check if the array strictly decreases after the peak
        for (int i = peak + 1; i < length; ++i)
        {
            if (arr[i] >= arr[i - 1])
            {
                return make_pair(false, -1);
            }
        }

        return make_pair(true, peak);  // Return true and the peak index
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    Solution s;
    pair<bool, int> result;
    cout << boolalpha;
    vector<vector<int>> testCases = {
        {0, 3, 2, 1},             // Valid mountain
        {0, 2, 3, 4, 5, 2, 1, 0}, // Valid mountain
        {0, 2, 3, 3, 5, 2, 1, 0}, // Invalid (3 is not strictly greater than neighbors)
        {1, 2, 3, 2, 1},          // Valid mountain
        {0, 1, 2, 3, 2, 1},       // Valid mountain
        {1, 1, 1, 1, 1},          // Invalid (no peak)
    };

    for (vector<int> arr : testCases)
    {
        cout << "Array: ";
        for (int i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
        result = s.isMountainArray(arr);
        cout << "Is Mountain Array: " << result.first << endl
             << "Peak Index: " << result.second << endl
             << endl;
    }

    return EXIT_SUCCESS;
}
