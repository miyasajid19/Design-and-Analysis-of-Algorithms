#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class Job
{
public:
    int id;
    int deadLine;
    int profit;
    Job(int id, int deadLine, int profit)
    {
        this->id = id;
        this->deadLine = deadLine;
        this->profit = profit;
    }
};
class JobSequencing
{
    vector<Job> jobs;

public:
    JobSequencing() {}
    JobSequencing(vector<Job> jobs)
    {
        this->jobs = jobs;
    }
    void addJob(int id, int deadLine, int profit)
    {
        jobs.push_back(Job(id, deadLine, profit));
    }
    // job sequencing function
    int jobSequencing()
    {
        // sort based on profit
        sort(jobs.begin(), jobs.end(), [](Job &j1, Job &j2)
             { return j1.profit > j2.profit; });

        // find the maximum deadline
        int maxDeadline = 0;
        for (Job &job : jobs)
        {
            maxDeadline = max(maxDeadline, job.deadLine);
        }

        // create a time slot array
        vector<int> timeSlot(maxDeadline + 1, -1);
        vector<int> scheduledJobs;
        int totalProfit = 0;

        // schedule the jobs
        for (Job &job : jobs)
        {
            // find a free time slot for the job
            for (int j = min(maxDeadline, job.deadLine); j > 0; j--)
            {
                if (timeSlot[j] == -1)
                {
                    timeSlot[j] = job.id; // schedule the job
                    scheduledJobs.push_back(job.id);
                    totalProfit += job.profit;
                    break;
                }
            }
        }

        // print the scheduled jobs
        cout << "Scheduled jobs: ";
        for (int jobId : scheduledJobs)
        {
            cout << jobId << " ";
        }

        cout << endl;

        cout << "Total profit: " << totalProfit << endl;
        return totalProfit;
    }
};
int main()
{
    JobSequencing jobSequencer;
    jobSequencer.addJob(1, 2, 100);
    jobSequencer.addJob(2, 1, 19);
    jobSequencer.addJob(3, 2, 27);
    jobSequencer.addJob(4, 1, 25);
    jobSequencer.addJob(5, 3, 15);

    jobSequencer.jobSequencing();
    // Output:
    // Scheduled jobs: 1 3 5
    // Total profit: 142
    return 0;
}