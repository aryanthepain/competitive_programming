#include <bits/stdc++.h>
using namespace std;

void print_1_to_n(int n, int curr = 1)
{
    cout << curr << " ";
    if (curr == n)
    {
        cout << endl;
        return;
    }

    print_1_to_n(n, curr + 1);
    return;
}

void print_n_to_1(int n)
{
    cout << n << " ";

    if (n == 1)
    {
        cout << endl;
        return;
    }

    print_n_to_1(n - 1);
    return;
}

int main()
{
    int n;
    cin >> n;

    print_1_to_n(n);
    print_n_to_1(n);

    return 0;
}
