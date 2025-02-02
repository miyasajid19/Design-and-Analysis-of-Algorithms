#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a job
struct Job {
    int id;       // Job ID
    int deadline; // Job deadline
    int profit;   // Job profit

    Job(int id, int deadline, int profit)
        : id(id), deadline(deadline), profit(profit) {}
};

// Comparison function to sort jobs based on profit in descending order
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to perform job sequencing and return the maximum profit
void jobSequencing(vector<Job>& jobs, int n) {
    // Sort the jobs in decreasing order of profit
    sort(jobs.begin(), jobs.end(), compare);

    // To keep track of free time slots
    vector<bool> slots(n, false);

    int totalProfit = 0; // To accumulate the total profit
    int jobCount = 0;    // To count the number of jobs scheduled

    // Resulting sequence of jobs
    vector<int> result;

    // Traverse through all the jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (latest available slot)
        for (int j = min(n - 1, jobs[i].deadline - 1); j >= 0; j--) {
            if (!slots[j]) {
                // If the slot is free, schedule the job
                slots[j] = true;
                totalProfit += jobs[i].profit;
                jobCount++;
                result.push_back(jobs[i].id);
                break;
            }
        }
    }

    // Output the results
    cout << "Number of jobs scheduled: " << jobCount << endl;
    cout << "Total profit: " << totalProfit << endl;
    cout << "Job sequence: ";
    for (int i = 0; i < jobCount; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main() {
    // Example input: 5 jobs
    vector<Job> jobs = { Job(1, 4, 20), Job(2, 1, 100), Job(3, 1, 19),
                          Job(4, 1, 27), Job(5, 3, 25) };
    int n = jobs.size();

    // Perform job sequencing
    jobSequencing(jobs, n);

    return 0;
}
