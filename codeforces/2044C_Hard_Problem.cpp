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
    cin >> t;
    // t=1;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    int m, first_preference, second_preference, no_preference;
    cin >> m >> first_preference >> second_preference >> no_preference;

    int first_row_seat = m;
    int second_row_seat = m;

    int count = 0;

    int first_row_filled = min(first_preference, first_row_seat);
    int second_row_filled = min(second_preference, second_row_seat);

    count = count + first_row_filled + second_row_filled;
    first_row_seat -= first_row_filled;
    second_row_seat -= second_row_filled;

    int seat_left = first_row_seat + second_row_seat;
    count += min(seat_left, no_preference);

    cout << count << endl;

    return;
}