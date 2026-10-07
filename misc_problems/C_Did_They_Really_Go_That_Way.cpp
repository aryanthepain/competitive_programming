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

void bfs(vector<bool> &visited, vector<vector<int>> &adj, vector<int> &level, int curr)
{
    if (visited[curr])
        return;

    visited[curr] = true;

    for (auto &nei : adj[curr])
    {
        if (visited[nei])
            continue;
        level[nei] = level[curr] + 1;
        bfs(visited, adj, level, nei);
    }

    return;
}

void return_yes()
{
    cout << "Yes" << endl;
}
void return_no()
{
    cout << "No" << endl;
}

void lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    // cin >> t;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    int n;
    cin >> n;
    vector<bool> visited_a(n, false);
    // vector<int> explorable(n, 0);
    // explorable[0] = 1;
    vector<vector<int>> adj(n);
    vector<int> level(n, -1);

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int curr = 0;
    level[0] = 0;
    bfs(visited_a, adj, level, curr);

    int prev;
    cin >> prev;
    prev--;

    // debug(level);

    for (int i = 0; i < n - 1; i++)
    {
        cin >> curr;
        curr--;
        // debug(curr);
        // debug(level);
        // debug(visited);
        // debug(adj);

        int diff = level[curr] - level[prev];
        if (diff == 0 || diff == 1)
        {
            prev = curr;
            continue;
        }

        return_no();
        return;
    }

    return_yes();

    return;
}