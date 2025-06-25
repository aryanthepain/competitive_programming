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

void bubble_sort(vector<int> &arr, int &swaps, int n, vector<pair<int, int>> &ans, int vector_number)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(arr[j - 1], arr[j]);
                ans.push_back({vector_number, j});
                swaps++;
            }
        }
    }
}
void lessgo();
int main()
{
    You_are_the_best;
    size_t t = 1;
    cin >> t;

    while (t--)
    {
        lessgo();
    }

    return 0;
}

void lessgo()
{
    // inputting n
    int n;
    cin >> n;
    // defining input and output vectors
    vector<int> a(n), b(n);
    vector<pair<int, int>> ans;

    // inputting vectors
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    // no of swaps
    int k = 0;

    // sort a and b using bubble sort
    bubble_sort(a, k, n, ans, 1);
    bubble_sort(b, k, n, ans, 2);

    // swap individual element of a and b
    for (int i = 0; i < n; i++)
    {
        if (a[i] > b[i])
        {
            ans.push_back({3, i + 1});
            k++;
            // no need to actually swap as answer is being output
            // swap(a[i], b[i]);
        }
    }

    // outputting answer
    cout << k << endl; // no of swaps
    for (auto [x, y] : ans)
        cout << x << " " << y << endl; // type of swap

    return;
}