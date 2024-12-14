#include <iostream>
#include <string>
#include <set>

using namespace std;

// Function to check if the substring starting at index `i` in `s` is "1100".
bool is_1100(const string &s, int i)
{
    if (i < 0 || i + 3 >= s.size())
        return false;
    return s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; // Number of test cases
    cin >> t;

    while (t--)
    {
        string s;
        cin >> s;

        int q; // Number of queries
        cin >> q;

        // Precompute the initial positions of "1100"
        set<int> positions;
        for (int i = 0; i + 3 < s.size(); ++i)
        {
            if (is_1100(s, i))
            {
                positions.insert(i);
            }
        }

        while (q--)
        {
            int i, v;
            cin >> i >> v;
            --i; // Convert 1-based index to 0-based

            // Update the string
            s[i] = v + '0';

            // Add new "1100" substrings after the update
            for (int j = i - 3; j <= i; ++j)
            {
                if (j >= 0 && is_1100(s, j))
                {
                    positions.insert(j);
                }
                else
                {
                    positions.erase(j);
                }
            }

            // Output the result for this query
            cout << (positions.empty() ? "NO" : "YES") << '\n';
        }
    }

    return 0;
}
