// author: Aryanthepain
#include "basics.h"

template <typename T>
bool isPrime(T num)
{
    if (num <= 1)
        return false; // 0 and 1 are not prime
    if (num <= 3)
        return true; // 2 and 3 are prime
    if (num % 2 == 0 || num % 3 == 0)
        return false;

    // 6k, 6k+2, 6k+3, 6k+4 all will not be prime
    // 6k+-1 have higher probability of being prime
    // hence, only checking those will give a better constant
    // time complexity: O(root n)

    for (T i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}
