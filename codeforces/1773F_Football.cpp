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
    // cin >> t;
    t = 1;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void print_scores(const vector<int> &t1s, const vector<int> &t2s, int draws)
{
    cout << draws << endl;
    for (int i = 0; i < t1s.size(); i++)
    {
        cout << t1s[i] << ":" << t2s[i] << endl;
    }

    return;
}

void lessgo()
{
    int n, a, b;
    cin >> n >> a >> b;
    int draws = n - a - b;

    vector<int> team_1_scores(n);
    vector<int> team_2_scores(n);

    int i = 0;
    while (i < n - 1 && a > 0)
    {
        a--;
        team_1_scores[i]++;
        i++;
    }
    while (i < n - 1 && b > 0)
    {
        b--;
        team_2_scores[i]++;
        i++;
    }

    if (a != b)
    {
        team_1_scores[n - 1] = a;
        team_2_scores[n - 1] = b;
        draws = 0;
        print_scores(team_1_scores, team_2_scores, draws);
        return;
    }

    if (n == 1)
    {
        team_1_scores[0] = a;
        team_2_scores[0] = b;
        draws = 1;
        print_scores(team_1_scores, team_2_scores, draws);
        return;
    }

    if (a == 0)
    {
        print_scores(team_1_scores, team_2_scores, draws);
        return;
    }

    team_1_scores[0]++;
    a--;
    team_1_scores[n - 1] = a;
    team_2_scores[n - 1] = b;
    draws = 0;
    print_scores(team_1_scores, team_2_scores, draws);

    return;
}