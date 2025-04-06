#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;
class RatInMaze
{
    vector<vector<int>> maze;
    vector<string> paths;
    int n, m;
    vector<vector<bool>> visited;

    bool isSafeMove(int new_x, int new_y)
    {
        return new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && maze[new_x][new_y] == 1 && !visited[new_x][new_y];
    }
    void findPathUtil(int x, int y, string path)
    {
        // current position is the destination
        if (x == n - 1 && y == m - 1)
        {
            paths.push_back(path);
            return;
        }

        // possible moves: down, left, right, up
        visited[x][y] = true; // mark the current cell as visited

        // down
        if (isSafeMove(x + 1, y))
        {
            findPathUtil(x + 1, y, path + 'D');
        }
        // left
        if (isSafeMove(x, y - 1))
        {
            findPathUtil(x, y - 1, path + 'L');
        }
        // right
        if (isSafeMove(x, y + 1))
        {
            findPathUtil(x, y + 1, path + 'R');
        }
        // up
        if (isSafeMove(x - 1, y))
        {
            findPathUtil(x - 1, y, path + 'U');
        }
        visited[x][y] = false; // backtrack: unmark the current cell
    }

public:
    RatInMaze(vector<vector<int>> maze, int n, int m)
    {
        this->maze = maze;
        this->n = n;
        this->m = m;
        this->visited.resize(n, vector<bool>(m, false));
    }
    vector<string> findPaths()
    {
        // can reach the destination only if the start and end points are 1
        if (maze[0][0] == 0 || maze[n - 1][m - 1] == 0)
            return paths;
        visited[0][0] = true;
        findPathUtil(0, 0, "");
        return paths;
    }
};
int main()
{
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}};
    int n = maze.size();
    int m = maze[0].size();
    RatInMaze rat(maze, n, m);
    vector<string> paths = rat.findPaths();
    if (paths.empty())
    {
        cout << "No path exists" << endl;
    }
    else
    {
        cout << "Paths to reach the destination:" << endl;
        for (const string &path : paths)
        {
            cout << path << endl;
        }
    }

    return EXIT_SUCCESS;
}