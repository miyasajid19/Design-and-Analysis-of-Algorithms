#include <iostream>
#include <string>
#include <vector>
using namespace std;
class KMP
{
   void computeLPSArray(const string &pattern, vector<int> &lps)
    {
        int length = 0; // length of the previous longest prefix suffix
        lps[0] = 0;     // lps[0] is always 0
        int i = 1;

        while (i < pattern.length())
        {
            if (pattern[i] == pattern[length])
            {
                length++;
                lps[i] = length;
                i++;
            }
            else
            {
                if (length != 0)
                    length = lps[length - 1];
                else
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
public:
    KMP() = default;

    void search(const string &text, const string &pattern)
    {
        int text_length = text.length();
        int pattern_length = pattern.length();

        if (pattern_length > text_length || pattern_length == 0)
            return;

        vector<int> lps(pattern_length, 0);
        computeLPSArray(pattern, lps);

        int i = 0; // index for text
        int j = 0; // index for pattern
        while (i < text_length)
        {
            if (pattern[j] == text[i])
            {
                i++;
                j++;
            }
            if (j == pattern_length)
            {
                cout << "Pattern found at index " << i - j << endl;
                j = lps[j - 1];
            }
            else if (i < text_length && pattern[j] != text[i])
            {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
    }
};
int main()
{
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABAB";
    KMP kmp;
    cout << "Knuth-Morris-Pratt Algorithm:" << endl;
    kmp.search(text, pattern);
    return 0;
}