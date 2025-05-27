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

void check_node(int parent, int i, vector<vector<int>> &children, vll &risk, vector<pair<ll, ll>> &ans)
{

    ans[i].first = max(risk[i] - ans[parent].second, risk[i]);
    ans[i].second = min(risk[i], risk[i] - ans[parent].first);
    debug(i);
    debug(ans[i]);

    for (int j = 0; j < children[i].size(); j++)
    {
        if (children[i][j] == parent)
            continue;

        check_node(i, children[i][j], children, risk, ans);
    }

    return;
}

void lessgo()
{
    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    vll risk(n + 1, 0);
    vector<pair<ll, ll>> ans(n + 1);

    // debug(n);

    // inputting risk
    for (int i = 1; i < n + 1; i++)
    {
        ll a;
        cin >> a;
        risk[i] = a;
    }

    // inputting children
    for (int i = 0; i < n - 1; i++)
    {
        int a;
        cin >> a;
        int b;
        cin >> b;

        children[a].push_back(b);
        children[b].push_back(a);
    }

    check_node(0, 1, children, risk, ans);

    // debug(children);
    // debug(risk);
    // debug(ans);
    for (int i = 1; i < n + 1; i++)
    {
        cout << ans[i].first << " ";
    }
    cout << endl;

    return;
}