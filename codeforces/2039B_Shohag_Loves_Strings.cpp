// author:Aryanthepain
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void lessgo()
{
    string s;
    cin >> s;

    size_t size = s.size();

    if (size <= 1)
    {
        cout << "-1" << endl;
        return;
    }

    for (size_t i = 0; i < size - 1; i++)
    {
        // 2 letter substring with same letter
        if (s[i] == s[i + 1])
        {
            cout << s[i] << s[i + 1] << endl;
            return;
        }

        // 3 letter substring with different letter
        if (i == size - 2)
            continue;

        if (s[i] != s[i + 2] && s[i + 1] != s[i + 2])
        {
            cout << s[i] << s[i + 1] << s[i + 2] << endl;
            return;
        }
    }

    cout << "-1" << endl;

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    size_t t;
    cin >> t;

    while (t--)
    {
        lessgo();
    }

    return 0;
}