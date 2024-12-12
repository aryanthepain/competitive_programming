// author: Aryanthepain
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll ceilDiv(ll a, ll b)
{
    return (a + b - 1) / b;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, a;
    cin >> n >> m >> a;

    cout << ceilDiv(n, a) * ceilDiv(m, a) << endl;

    return 0;
}