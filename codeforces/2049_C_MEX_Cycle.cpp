// author: Aryanthepain
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define You_are_the_best         \
    ios::sync_with_stdio(false); \
    cin.tie(0)
#define MAXcolors 2e5

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

void addEdge(vector<vector<int>> &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void vertexColoring(const vector<vector<int>> &adj, vector<int> &colors)
{
    int n = adj.size();
    colors.assign(n, -1); // no color=-1

    colors[0] = 0;
    vector<bool> available(MAXcolors, false);

    for (int u = 1; u < n; u++)
    {
        // adjacent vertice color unavailable
        for (int v : adj[u])
        {
            if (colors[v] != -1)
            {
                available[colors[v]] = true;
            }
        }

        for (int color = 0; color < MAXcolors; color++)
        {
            if (!available[color])
            {
                colors[u] = color;
                break;
            }
        }

        // Reset the values
        for (int v : adj[u])
        {
            if (colors[v] != -1)
            {
                available[colors[v]] = false;
            }
        }
    }
}

template <typename T>
void print_vector(const vector<T> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    return;
}

void lessgo()
{
    ll n;
    cin >> n;
    vector<vector<int>> adj(n);

    addEdge(adj, 0, n - 1);
    for (ll i = 0; i <= n - 2; i++)
    {
        addEdge(adj, i, i + 1);
    }

    ll l, r;
    cin >> l >> r;
    addEdge(adj, l - 1, r - 1); // 1 based index

    vector<int> colors;
    vertexColoring(adj, colors);

    print_vector(colors);

    return;
}
