#include <iostream>
#include <vector>
using namespace std;

class Solution {
    void merge(vector<int>& arr, int start, int middle, int last) {
        int n1 = middle - start + 1;
        int n2 = last - middle;
        vector<int> left(n1), right(n2);

        for (int i = 0; i < n1; i++) {
            left[i] = arr[start + i];
        }
        for (int j = 0; j < n2; j++) {
            right[j] = arr[middle + 1 + j];
        }

        int i = 0, j = 0, k = start;
        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

public:
    void mergeSort(vector<int>& arr, int start, int last) {
        if (start < last) {
            int middle = start + (last - start) / 2;
            mergeSort(arr, start, middle);
            mergeSort(arr, middle + 1, last);
            merge(arr, start, middle, last);
        }
    }
};

int main() {
    vector<int> arr = {1, 5, 2, 7, 3, -8, 0, 3, 1, 7, 7, 9, 3};
    Solution s;

    cout << "Unsorted: ";
    for (const auto& x : arr) {
        cout << x << " ";
    }
    cout << endl;

    s.mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted: ";
    for (const auto& x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
