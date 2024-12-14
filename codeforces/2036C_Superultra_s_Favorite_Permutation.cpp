// author:Aryanthepain
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifndef ONLINE_JUDGE
#include "./algo/debug.h"
#else
#define debug(...) 42
#endif

void printVector(vector<int> v, int ignore = 0)
{

    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == ignore)
        {
            continue;
        }

        cout << v[i] << " ";
    }

    return;
}

bool isPrime(int n)
{
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653};

    for (int i = 0; i < primes.size(); i++)
    {
        if (primes[i] * primes[i] > n)
        {
            break;
        }

        if (n % primes[i] == 0)
        {
            return false;
        }
    }

    return true;
}

void lessgo()
{
    size_t n;
    cin >> n;

    // creating odd and even array
    vector<int> odd, even;
    for (int i = 1; i <= n / 2; i++)
    {
        odd.push_back(2 * i - 1);
        even.push_back(2 * i);
    }
    // adding last element to odd array
    if (n % 2 == 1)
    {
        odd.push_back(n);
    }

    for (int i = odd.size() - 1; i >= 0; i--)
    {
        for (int j = even.size() - 1; j >= 0; j--)
        {
            if (!isPrime(odd[i] + even[j]))
            {
                swap(odd[i], odd[odd.size() - 1]);
                odd.push_back(even[j]);
                printVector(odd);
                printVector(even, even[j]);
                cout << endl;
                return;
            }
        }
    }

    cout << "-1" << endl;
    return;

    cout << endl;

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    size_t t;
    cin >> t;

    debug(t);

    while (t--)
    {
        lessgo();
        // int n;
        // cin >> n;
        // cout << (isPrime(n) ? "prime" : "not prime") << endl;
    }

    return 0;
}