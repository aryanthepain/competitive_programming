// author: Aryanthepain
#include <bits/stdc++.h>
using namespace std;

int sum_of_n_numbers(int n, int sum = 0)
{
    if (n == 0)
    {
        return sum;
    }
    return sum_of_n_numbers(n - 1, sum + n);
}

int fact_of_n_numbers(int n, int prod = 1)
{
    if (n == 1 || n == 0)
        return prod;
    return fact_of_n_numbers(n - 1, prod * n);
}

int main()
{
    int n;
    cin >> n;
    cout << sum_of_n_numbers(n) << endl;
    cout << fact_of_n_numbers(n) << endl;

    return 0;
}