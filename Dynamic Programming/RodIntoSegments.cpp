#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class RodIntoSegments
{
public:
    int Recursion(int size, int segment_1, int segment_2, int segment_3)
    {
        if (size == 0)
            return 0;
        if (size < 0)
            return INT_MIN;
        int a = Recursion(size - segment_1, segment_1, segment_2, segment_3) + 1;
        int b = Recursion(size - segment_2, segment_1, segment_2, segment_3) + 1;
        int c = Recursion(size - segment_3, segment_1, segment_2, segment_3) + 1;
        return max({a, b, c});
    }

    int Memoization(int size, int segment_1, int segment_2, int segment_3, vector<int> &mappingVector)
    {
        if (size < 0)
            return INT_MIN;
        if (size == 0)
            return 0;
        if (mappingVector[size] != -1)
            return mappingVector[size];

        int a = Memoization(size - segment_1, segment_1, segment_2, segment_3, mappingVector) + 1;
        int b = Memoization(size - segment_2, segment_1, segment_2, segment_3, mappingVector) + 1;
        int c = Memoization(size - segment_3, segment_1, segment_2, segment_3, mappingVector) + 1;
        mappingVector[size] = max({a, b, c});
        return mappingVector[size];
    }

    int Tabulation(int size, int segment_1, int segment_2, int segment_3)
    {
        vector<int> mappingVector(size + 1, -1);
        mappingVector[0] = 0;

        for (int i = 1; i <= size; i++)
        {
            if (i - segment_1 >= 0 && mappingVector[i - segment_1] != -1)
                mappingVector[i] = max(mappingVector[i], mappingVector[i - segment_1] + 1);
            if (i - segment_2 >= 0 && mappingVector[i - segment_2] != -1)
                mappingVector[i] = max(mappingVector[i], mappingVector[i - segment_2] + 1);
            if (i - segment_3 >= 0 && mappingVector[i - segment_3] != -1)
                mappingVector[i] = max(mappingVector[i], mappingVector[i - segment_3] + 1);
        }
        if (mappingVector[size] < 0)
            return 0;
        else
            return mappingVector[size];
    }
    //space optimization is not possible
};

int main()
{
    RodIntoSegments rod;
    int size = 7;
    int segment_1 = 2;
    int segment_2 = 3;
    int segment_3 = 4;

    int result = rod.Recursion(size, segment_1, segment_2, segment_3);
    cout << "Maximum number of segments (Recursion): " << result << endl;

    vector<int> mappingVector(size + 1, -1);
    result = rod.Memoization(size, segment_1, segment_2, segment_3, mappingVector);
    cout << "Maximum number of segments (Memoization): " << result << endl;
    result = rod.Tabulation(size, segment_1, segment_2, segment_3);
    cout << "Maximum number of segments (Tabulation): " << result << endl;
    return EXIT_SUCCESS;
}
