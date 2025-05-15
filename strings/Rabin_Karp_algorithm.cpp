#include <iostream>
#include <string>
using namespace std;

class RabinKarp
{
public:
    RabinKarp() = default;

    void search(const string &text, const string &pattern)
    {
        const int prime = 13;
        const int d = 256; // if 10 digits are used, d = 10
        // if 256 characters are used, d = 256
        int text_length = text.length();
        int pattern_length = pattern.length();

        if (pattern_length > text_length || pattern_length == 0)
            return;

        int h = 1;
        for (int i = 0; i < pattern_length - 1; i++)
            h = (h * d) % prime;
        int pattern_hash = 0;
        int window_hash = 0;

        for (int i = 0; i < pattern_length; i++)
        {
            pattern_hash = (d * pattern_hash + pattern[i]) % prime;
            window_hash = (d * window_hash + text[i]) % prime;
        }

        for (int i = 0; i <= text_length - pattern_length; i++)
        {
            if (pattern_hash == window_hash)
            {
                if (text.substr(i, pattern_length) == pattern)
                    cout << "Pattern found at index " << i << endl;
            }

            if (i < text_length - pattern_length)
            {
                window_hash = (d * (window_hash - text[i] * h) + text[i + pattern_length]) % prime;
                if (window_hash < 0)
                    window_hash += prime;
            }
        }
    }
};

int main()
{
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABAB";
    RabinKarp rk;
    cout << "Rabin-Karp Algorithm:" << endl;
    rk.search(text, pattern);
    return 0;
}
