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
        lessgo();
        // cout<<lessgo()<<endl;
    }

    return 0;
}

ll lessgo()
{
    string s, t;
    cin >> s >> t;

    unordered_map<char, int> smap;
    unordered_map<char, int> tmap;

    // add characters to map
    for (auto &a : s)
    {
        smap[a]++;
    }
    for (auto &a : t)
    {
        tmap[a]++;
    }

    // unordered_map<char, int> umap(tmap);

    int changes = smap['?'];
    smap['?'] = 0;
    int count = 0;
    while (changes > 0)
    {
        count++;
        for (auto &a : tmap)
        {
            changes -= max(a.second - smap[a.first], 0);
            smap[a.first] = max(smap[a.first] - a.second, 0);
        }
    }
    for (auto &a : tmap)
    {
        a.second *= count;
    }

    for (auto &a : s)
    {
        if (tmap.empty())
        {
            cout << 'a';
            continue;
        }

        if (a == '?')
        {
            cout << tmap.begin()->first;
            tmap.begin()->second--;
            if (tmap.begin()->second == 0)
            {
                tmap.erase(tmap.begin()->first);
            }
        }
        else
            cout << a;
    }

    return 0;
}