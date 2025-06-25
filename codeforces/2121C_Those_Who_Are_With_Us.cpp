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
    cin.tie(0)

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

int lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        cout << lessgo() << endl;
    }

    return 0;
}

int lessgo()
{
    // to find the maximum appearance and the number of times it appears
    int max = 0, count = 0;

    // to get the rows which are maximum
    vector<int> r, c;

    // no of rows and columns
    int m, n;
    cin >> m >> n;

    // inputting the matrix and checking for max value and positions
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int a;
            cin >> a;
            if (a == max)
            {
                count++;
                r.push_back(i);
                c.push_back(j);
            }
            else if (a > max)
            {
                max = a;
                count = 1;
                r = {i};
                c = {j};
            }
        }
    }

    // if only one or two maximum points answer is automatically "max-1"
    if (count < 3)
    {
        return max - 1;
    }

    // finding the optimal row, column using the first two points
    int r1 = r[0], r2 = r[1], c1 = c[0], c2 = c[1];
    bool rowfound = false, colfound = false;
    if (r1 == r2)
    {
        rowfound = true;
    }
    if (c1 == c2)
    {
        colfound = true;
    }

    for (int i = 2; i < count; i++)
    {
        if (rowfound && colfound)
        {
            if (r[i] != r1 && c[i] != c1)
            {
                return max;
            }
        }

        if (!rowfound && !colfound)
        {
            if (c[i] == c1)
            {
                c2 = c1;
                r1 = r2;
                colfound = true;
                rowfound = true;
            }
            else if (c[i] == c2)
            {
                colfound = true;
                rowfound = true;
                c1 = c2;
                r2 = r1;
            }
            else if (r[i] == r1)
            {
                rowfound = true;
                colfound = true;
                r2 = r1;
                c1 = c2;
            }
            else if (r[i] == r2)
            {
                rowfound = true;
                colfound = true;
                r1 = r2;
                c2 = c1;
            }
            else
            {
                return max;
            }
            continue;
        }

        if (rowfound)
        {
            if (r[i] == r1)
            {
                continue;
            }
            else
            {
                colfound = true;
                c1 = c[i];
                c2 = c[i];
                continue;
            }
        }

        // colfound=true
        if (c[i] == c1)
            continue;
        else
        {
            rowfound = true;
            r1 = r[i];
            r2 = r[i];
            continue;
        }
    }

    return max - 1;
}