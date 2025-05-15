#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StringMatcher
{
    string text;
    string pattern;
    int text_length;
    int pattern_length;

public:
    StringMatcher(string t, string p)
    {
        text = t;
        pattern = p;
        text_length = text.length();
        pattern_length = pattern.length();
    }

    void brute_force()
    {
        vector<int> matches;
        for (int i = 0; i <= text_length - pattern_length; ++i)
        {
            int j = 0;
            while (j < pattern_length && text[i + j] == pattern[j])
            {
                j++;
            }
            if (j == pattern_length)
            {
                matches.push_back(i);
            }
        }

        if (!matches.empty())
        {
            cout << "Pattern found at indices: ";
            for (int idx : matches)
            {
                cout << idx << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "No match found." << endl;
        }
    }
};

int main()
{
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABA";
    StringMatcher sm(text, pattern);
    cout << "Brute Force Approach:" << endl;
    sm.brute_force();
    return 0;
}