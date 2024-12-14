// author: Aryanthepain
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define You_are_the_best         \
    ios::sync_with_stdio(false); \
    cin.tie(0)

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

void lessgo();
int main()
{
    You_are_the_best;
    size_t t;
    //  cin >> t;
    t = 1;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void increase_rating(size_t &current_rating)
{
    size_t rating_change;
    cin >> rating_change;

    current_rating += rating_change;

    return;
}

void ignore_change()
{
    size_t rating_change;
    cin >> rating_change;

    return;
}

void lessgo()
{
    size_t n, current_rating;
    cin >> n >> current_rating;

    for (size_t i = 0; i < n; i++)
    {
        size_t div;
        cin >> div;

        if ((div == 1 && current_rating >= 1600 && current_rating <= 2799) || (div == 2 && current_rating >= 1200 && current_rating <= 2399))
        {
            increase_rating(current_rating);
            continue;
        }
        ignore_change();
    }

    cout << current_rating << endl;

    return;
}