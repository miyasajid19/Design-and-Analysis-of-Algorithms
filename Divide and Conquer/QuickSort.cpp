#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int partition(vector<int>& arr, int start, int last) {
        int pivotElement = arr[last];
        int i = start - 1;
        for (int j = start; j < last; j++) {
            if (arr[j] < pivotElement) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[last]);
        return i + 1;
    }

public:
    void quickSort(vector<int>& arr, int start, int last) {
        if (start < last) {
            int pivotIndex = partition(arr, start, last);
            quickSort(arr, start, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, last);
        }
    }
};

int main() {
    vector<int> arr = {1, 5, 2, 7, 3, -8, 0, 3, 1, 7, 7, 9, 3};
    Solution s;
    cout << "Unsorted: ";
    for (auto x : arr) {
        cout << x << " ";
    }
    cout << endl;
    s.quickSort(arr, 0, arr.size() - 1);
    cout << "Sorted: ";
    for (auto x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}
