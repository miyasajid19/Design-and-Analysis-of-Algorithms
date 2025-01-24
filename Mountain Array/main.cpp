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

        do
        {
            int mid = (high + low) / 2;
            if (arr[mid] < arr[mid + 1])
            {
                // peak is in right half of the array
                low = mid + 1;
            }
            else
            {
                // peak is in left half of the array
                high = mid;
            }
        } while (high != low);
        return make_pair(low == high && low != 0 && high != length - 1, low);
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
        {0, 3, 2, 1},
        {0, 2, 3, 4, 5, 2, 1, 0},
        {0, 2, 3, 3, 5, 2, 1, 0},
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
        cout << "Is Mountain Array: " << result.first << " Peak Index: " << result.second << endl
             << endl;
    }

    return EXIT_SUCCESS;
}