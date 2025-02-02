#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

class ActivitySpace
{
public:
    int no_of_meetings(vector<pair<int, int>> activities)
    {
        // Use lambda to sort activities by finish time
        sort(activities.begin(), activities.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        int count = 1;
        int currentFinishTime = activities[0].second;
        cout << "Meeting " << count << " can be scheduled from " 
             << activities[0].first << " to " << currentFinishTime << endl;

        for (size_t i = 1; i < activities.size(); i++)
        {
            if (activities[i].first >= currentFinishTime)
            {
                count++;
                currentFinishTime = activities[i].second;
                cout << "Meeting " << count << " can be scheduled from " 
                     << activities[i].first << " to " << currentFinishTime << endl;
            }
        }
        return count;
    }
};

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    #endif

    // Each pair is {start_time, finish_time}
    vector<pair<int, int>> activities = { {1, 2}, {2, 4}, {0, 3}, {4, 5}, {2, 3}, {5, 7}, {6, 8}, {5, 6} };

    ActivitySpace soln;
    cout << "\nTotal meetings scheduled: " << soln.no_of_meetings(activities) << endl;
    return EXIT_SUCCESS;
}
