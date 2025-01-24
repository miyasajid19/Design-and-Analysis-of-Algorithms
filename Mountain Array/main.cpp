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

        int low = 1;
        int high = length - 2;

        // Binary search to find the peak
        while (low < high)
        {
            int mid = (high + low) / 2;
            if (arr[mid] < arr[mid + 1])
            {
                // Peak is in the right half
                low = mid + 1;
            }
            else
            {
                // Peak is in the left half
                high = mid;
            }
        }

        // Check if the low (peak) is a valid peak
        int peak = low;
        if (peak == 0 || peak == length - 1 || arr[peak] <= arr[peak - 1] || arr[peak] <= arr[peak + 1] || arr[peak] == arr[peak - 1] || arr[peak] == arr[peak + 1])
        {
            return make_pair(false, -1); // invalid if peak is at the boundary or not strictly greater
        }

        return make_pair(true, peak);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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