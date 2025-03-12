#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class Solution
{
    vector<vector<int>> array;
    int row, column;

public:
    Solution(vector<vector<int>> &array) : array(array)
    {
        this->row = array.size();
        this->column = array[0].size();
    }

    int recurrsive(int i, int j, int &maximumsquare)
    {
        if (i >= row || j >= column)
        {
            return 0;
        }

        int right = recurrsive(i, j + 1, maximumsquare);
        int diagonal = recurrsive(i + 1, j + 1, maximumsquare);
        int left = recurrsive(i + 1, j, maximumsquare);

        if (array[i][j] == 1)
        {
            int ans = 1 + min(right, min(left, diagonal));
            maximumsquare = max(maximumsquare, ans);
            return ans;
        }
        else
            return 0;
    }

    int maxSquare()
    {
        int maximumsquare = 0;
        recurrsive(0, 0, maximumsquare);
        return maximumsquare * maximumsquare;
    }
};
int main()
{

    vector<vector<int>> array = {{1, 0, 1, 0, 0},
                                 {1, 0, 1, 1, 1},
                                 {1, 1, 1, 1, 1},
                                 {1, 0, 0, 1, 0}};
    Solution sol(array);
    cout<<"The Maximum Possible array of Square Matrix is " << sol.maxSquare() << endl;
    return EXIT_SUCCESS;
}