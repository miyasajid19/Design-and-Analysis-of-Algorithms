#include <iostream>
#include <cstdlib>
#include <cmath>  // Include cmath to use ceil function

using namespace std;

class solution {
public:
    int survival_days(int foodPerDay, int daysToSurvive, int foodRequiredPerDay) {
        // can't buy food on Sunday
        int no_of_Sundays = daysToSurvive / 7;
        int buying_days = daysToSurvive - no_of_Sundays;

        // Total food required to survive
        int totalFoodRequired = daysToSurvive * foodRequiredPerDay;

        // Total available food (food can be bought only on non-Sunday days)
        int totalAvailableFood = buying_days * foodPerDay;

        // If the total available food is less than required, survival is not possible
        if (totalAvailableFood < totalFoodRequired) {
            return -1;
        }

        // Calculate food per day needed to survive; use ceil to round up
        int foodNeededPerDay = (int)ceil((double)totalFoodRequired / daysToSurvive);

        // Check if food needed per day can be met with the available buying days
        if (foodNeededPerDay <= foodPerDay) {
            return foodNeededPerDay; // Return food needed per day if it is within the available food per day
        } else {
            return -1; // If it's not possible to buy enough food per day
        }
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif
    solution soln;
    int result = soln.survival_days(4, 10, 3);

    if (result == -1)
        cout << "can't survive" << endl;
    else
        cout << "can survive till "<<result<< " days" << endl;

    return EXIT_SUCCESS;
}
