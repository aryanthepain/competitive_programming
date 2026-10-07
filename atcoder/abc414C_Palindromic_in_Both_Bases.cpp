#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool isPalBase(ll x, int base)
{
    vector<int> digits;
    while (x)
    {
        digits.push_back(x % base);
        x /= base;
    }
    return equal(digits.begin(), digits.end(), digits.rbegin());
}

void calculate(ll n, ll base, ll &sum)
{
    vector<ll> pals;

    for (int len = 1; len <= 12; ++len)
    {
        int half = (len + 1) / 2;
        ll start = pow(10, half - 1);
        ll end = pow(10, half);

        for (ll i = start; i < end; ++i)
        {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());

            if (len % 2)
                rev = rev.substr(1); // remove middle for odd-length
            ll pal = stoll(s + rev);
            if (pal > n)
                return;
            if (isPalBase(pal, base))
            {

                sum += pal;
            }
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a;
    ll n;
    cin >> a >> n;
    ll sum = 0;
    calculate(n, a, sum);

    cout << sum << endl;
    return 0;
}