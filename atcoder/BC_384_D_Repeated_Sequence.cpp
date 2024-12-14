// author: Aryanthepain
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
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
    lessgo();

    return 0;
}

bool check_validity(size_t required_sum, const vector<size_t> &v)
{
    size_t n = v.size();
    size_t current_sum = 0;
    size_t start = 0;
    // end and start both are included in the sum

    // Simulate a circular array by looping through twice
    for (size_t end = 0; end < 2 * n; end++)
    {
        current_sum += v[end % n];

        // Shrink the window if it exceeds required_sum
        while (current_sum > required_sum && start < end)
        {
            current_sum -= v[start % n];
            start++;
        }

        // Check if we found the required sum
        if (current_sum == required_sum)
        {
            return true;
        }
    }
    return false;
}

void lessgo()
{
    size_t array_size, required_sum;
    cin >> array_size >> required_sum;
    vector<size_t> v(array_size);
    size_t sum_of_all_numbers = 0;

    for (size_t i = 0; i < array_size; i++)
    {
        cin >> v[i];
        sum_of_all_numbers += v[i];

        if (required_sum == sum_of_all_numbers || required_sum == v[i])
        {
            cout << "Yes" << endl;
            return;
        }
    }

    if (required_sum % sum_of_all_numbers == 0)
    {
        cout << "Yes" << endl;
        return;
    }

    if (check_validity(required_sum % sum_of_all_numbers, v))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return;
}