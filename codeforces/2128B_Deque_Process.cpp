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
    cin >> t;

    while (t--)
    {
        lessgo();
        // debug(t);
        // cout<<lessgo()<<endl;
    }

    return 0;
}

void takeRight(bool &greater, int &l, int &r, int &cur, vector<int> &a)
{
    cout << "R";
    if (cur > a[r])
    {
        greater = false;
    }
    else
    {
        greater = true;
    }
    cur = a[r];
    r--;
}

void takeLeft(bool &greater, int &l, int &r, int &cur, vector<int> &a)
{
    cout << "L";
    if (cur > a[l])
    {
        greater = false;
    }
    else
    {
        greater = true;
    }
    cur = a[l];
    l++;
}

ll lessgo()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i]; // input the array

    // check start
    // int run = 0, count = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if (a[i] > a[i + 1])
    //     {
    //         if (run > 0)
    //         {
    //             break;
    //         }
    //         else
    //         {
    //             run--;
    //         }
    //     }
    //     else if (a[i] < a[i + 1])
    //     {
    //         if (run < 0)
    //         {
    //             break;
    //         }
    //         else
    //         {
    //             run++;
    //         }
    //     }
    //     if (run >= 5 || run <= -5)
    //     {
    //         count++;
    //         cout << "L";
    //     }
    // }

    // for (int i = 0; i < n - count; i++)
    // {
    //     cout << "R";
    // }

    // cout << endl;

    int cur = 0, l = 0, r = n - 1;
    bool greater = true;

    while (l < r)
    {
        if (a[l] > cur && a[r] < cur)
        {
            if (greater)
            {
                takeRight(greater, l, r, cur, a);
            }
            else
            {
                takeLeft(greater, l, r, cur, a);
            }
        }
        else if (a[l] < cur && a[r] > cur)
        {
            if (greater)
            {
                takeLeft(greater, l, r, cur, a);
            }
            else
            {
                takeRight(greater, l, r, cur, a);
            }
        }
        else
        { // same side
            if (greater)
            {
                if (a[r] > a[l])
                {
                    takeRight(greater, l, r, cur, a);
                }
                else
                {
                    takeLeft(greater, l, r, cur, a);
                }
            }
            else
            {
                if (a[r] < a[l])
                {
                    takeRight(greater, l, r, cur, a);
                }
                else
                {
                    takeLeft(greater, l, r, cur, a);
                }
            }
        }
        // debug(greater);
    }

    cout << "L" << endl;

    return 0;
}