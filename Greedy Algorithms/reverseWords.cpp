#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

class solution
{
public:
    string reverseWords(string words)
    {
        words += " ";  // Adding space to handle the last word
        string temp, ans;
        
        // Loop through each character of the string
        for (char x : words)
        {
            if (x == ' ')
            {
                if (!temp.empty())  // To avoid adding empty strings for consecutive spaces
                {
                    ans = temp + " " + ans;  // Add word to the front of ans
                    temp = "";
                }
            }
            else
            {
                temp += x;  // Build the current word
            }
        }
        return ans;
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif
    solution soln;
    cout << soln.reverseWords("all i want was the love and what i get is the pain");
    return EXIT_SUCCESS;
}
