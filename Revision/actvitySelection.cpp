#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class Activity
{
    vector<pair<int, int>> Activities;

public:
    Activity() {}
    Activity(vector<pair<int, int>> Activities)
    {
        this->Activities = Activities;
    }
    void addActivity(int start, int end)
    {
        Activities.push_back(make_pair(start, end));
    }
    int maxActivities()
    {
        // sort the activities based on their finish time
        sort(Activities.begin(), Activities.end(), [](pair<int, int> a, pair<int, int> b)
             {
//print first and second of a pair
            cout << "a.first: " << a.first << ", a.second: " << a.second << endl;
            cout << "b.first: " << b.first << ", b.second: " << b.second << endl;
            cout << "------------------------" << endl;
            return a.second < b.second; });

        // select the first activity
        int count = 1;
        int lastFinishTime = Activities[0].second;
        // schedule the rest of the activities
        for (pair<int, int> activity : Activities)
        {
            if (activity.first >= lastFinishTime)
            {
                count++;
                lastFinishTime = activity.second;
                cout << "Selected activity: (" << activity.first << ", " << activity.second << ") has been selected" << endl;
            }
        }
        cout<< "Total number of activities selected: " << count << endl;
        return count;
    }
};
int main()
{
    Activity activitySelector;
    activitySelector.addActivity(1, 3);
    activitySelector.addActivity(2, 4);
    activitySelector.addActivity(3, 5);
    activitySelector.addActivity(0, 6);
    activitySelector.addActivity(5, 7);
    activitySelector.addActivity(3, 9);
    activitySelector.addActivity(5, 9);
    activitySelector.addActivity(6, 10);
    activitySelector.addActivity(8, 11);
    activitySelector.maxActivities();
    return 0;
}