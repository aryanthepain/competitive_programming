// author: Aryanthepain
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<long long> vll;
#define all(v) v.begin(), v.end()
#define srt(v) sort(v.begin(), v.end())
#define minm(v) *min_element(v.begin(), v.end())
#define maxm(v) *max_element(v.begin(), v.end())
#define add(v) accumulate(v.begin(), v.end(), 0)

#define You_are_the_best         \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0)

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

ll lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    // cin >> t;

    while (t--)
    {
        // lessgo();
        if (lessgo())
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}

enum Word
{
    NONE,
    ERASE,
    DREAM
};

ll lessgo()
{
    enum Word curr_word = NONE;
    string s;
    cin >> s;
    int n = s.size();

    int l = 0;
    // debug(n);
    string next;
    char temp;
    while (l < n)
    {
        // debug(l);
        // debug((char)s[l]);
        // debug(curr_word);
        if (curr_word == NONE)
        {
            try
            {
                next = s.substr(l, 5);
            }
            catch (const std::exception &e)
            {
                return 0;
            }

            if (next == "erase")
            {
                curr_word = ERASE;
                continue;
            }
            else if (next == "dream")
            {
                curr_word = DREAM;
                continue;
            }
            else
            {
                return 0;
            }
        }
        else if (curr_word == ERASE)
        {
            curr_word = NONE;
            try
            {
                temp = s.at(l + 5);
                if (temp == 'r')
                {
                    l += 6;
                    continue;
                }
            }
            catch (const std::exception &e)
            {
                l += 5;
                continue;
            }

            l += 5;
            continue;
        }
        else // curr_word=DREAM
        {
            curr_word = NONE;
            try
            {
                next = s.substr(l + 5, 2);
            }
            catch (const std::exception &e)
            {
                l += 5;
                continue;
            }

            if (next == "er")
            {
                try
                {
                    temp = s.at(l + 7);
                }
                catch (const std::exception &e)
                {
                    l += 7;
                    continue;
                }

                if (temp == 'a')
                {
                    l += 5;
                }
                else
                {
                    l += 7;
                }
            }
            else
            {
                l += 5;
            }
            continue;
        }
    }

    return 1;
}