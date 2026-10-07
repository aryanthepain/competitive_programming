#include <bits/stdc++.h>
using namespace std;

int lg2[200005];
long long sp[19][200005];

long long qr(int l, int r)
{
    int p = lg2[r - l + 1];
    return max(sp[p][l], sp[p][r - (1 << p) + 1]);
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> sp[0][i];

    for (int i = 2; i <= m; i++)
        lg2[i] = lg2[i / 2] + 1;
    for (int p = 1; p < 19; p++)
    {
        int len = 1 << p;
        for (int i = 1; i + len - 1 <= m; i++)
            sp[p][i] = max(sp[p - 1][i], sp[p - 1][i + len / 2]);
    }

    int q;
    cin >> q;
    while (q--)
    {
        long long xs, ys, xf, yf, k;
        cin >> xs >> ys >> xf >> yf >> k;

        long long dx = xf - xs, dy = yf - ys;
        long long adx = abs(dx), ady = abs(dy);

        if (adx % k != 0 || ady % k != 0)
        {
            cout << "NO\n";
            continue;
        }

        long long tot = adx / k + ady / k;

        if (dy == 0)
        {
            cout << "YES " << tot << "\n";
            continue;
        }

        int l = (int)min(ys, yf), r = (int)max(ys, yf);
        long long mc = qr(l, r);
        long long mx = max(xs, xf);

        if (mx > mc)
            cout << "YES " << tot << "\n";
        else
            cout << "NO\n";
    }
}