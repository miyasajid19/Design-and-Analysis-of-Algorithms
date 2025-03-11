#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
class minimumPlatform
{
private:
    vector<int> arrival;
    vector<int> departure;

public:
    static void sortDepartureAsPerArrival(vector<int> a, vector<int> b)
    {
        int n = a.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (a[i] > a[j])
                {
                    swap(a[i], a[j]);
                    swap(b[i], b[j]);
                }
            }
        }
    }
    minimumPlatform(vector<int> arrival, vector<int> departure)
    {
        this->arrival = arrival;
        this->departure = departure;
    }

    // naive approach
    int NaiveApproach()
    {
        int n = arrival.size();
        int platform = 1;
        for (int i = 0; i < n; i++)
        {
            int count = 1;
            for (int j = i + 1; j < n; j++)
            {
                if ((arrival[j] >= arrival[i] && arrival[j] <= departure[i]) || (arrival[j] <= arrival[i] && departure[j] >= arrival[i]))
                {
                    count++;
                }
            }
            platform = max(platform, count);
        }
        return platform;
    }

    // efficient greedy approach
    int GreedyApproach()
    {
        int n = arrival.size();
        vector<int> arrival_ = arrival;
        vector<int> departure_ = departure;
        sortDepartureAsPerArrival(arrival_, departure_);
        int platform = 0;
        int max_platform = 0;
        int i = 0, j = 0;
        while (i < n && j < n)
        {
            if (arrival_[i] <= departure_[j])
            {
                platform++;
                i++;
            }
            else
            {
                platform--;
                j++;
            }
            max_platform = max(max_platform, platform);
        }
        return max_platform;
    }
    // sweep line algorithm
    int SweepLineAlgorithm()
    {
        int n = arrival.size();
        vector<pair<string, int>> events;
        for (int i = 0; i < n; i++)
        {
            events.push_back({"arrival", arrival[i]});
            events.push_back({"departure", departure[i]});
        }
        sort(events.begin(), events.end(), [](pair<string, int> a, pair<string, int> b)
             {
            if (a.second == b.second)
            {
                return a.first < b.first;
            }
            return a.second < b.second; });
        int platform = 0;
        int max_platform = 0;
        for (int i = 0; i < 2 * n; i++)
        {
            if (events[i].first == "arrival")
            {
                platform++;
            }
            else
            {
                platform--;
            }
            max_platform = max(max_platform, platform);
        }
        return max_platform;
    }
};

int main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    vector<int> arrival = {900, 940, 950, 1100, 1500, 1800};
    vector<int> departure = {910, 1200, 1120, 1130, 1900, 2000};
    minimumPlatform mp(arrival, departure);
    cout<<"Naive Approach :: " << mp.NaiveApproach() << endl;
    cout <<"Greedy Approach :: "<< mp.GreedyApproach() << endl;
    cout << "Sweep Line Approach :: "<<mp.SweepLineAlgorithm() << endl;
    return EXIT_SUCCESS;
}