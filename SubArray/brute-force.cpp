#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int maxSumSUbArray(vector<int>arr)
{
    int MaxSum=INT_MIN;
    for (int i=0;i<arr.size();i++)
    {
        int sum=0;
        for (int j=i;j<arr.size();j++)
        {
            sum+=arr[j];
            MaxSum=max(MaxSum,sum);
        }
    }
    return MaxSum;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << "Enter the number of elements in the array: "<<endl;
    int n;
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements of the array: "<<endl;    
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
cout<<"maximum sum of subarray is: "<<maxSumSUbArray(arr);

    return EXIT_SUCCESS;
}