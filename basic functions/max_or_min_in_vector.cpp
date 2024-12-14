// author: Aryanthepain
#include "basics.h"

// Return the maximum value found in the vector
template <typename T>
T max_in_vector(const vector<T> &v)
{
    T max = v[0];

    for (size_t i = 1; i < v.size(); i++)
    {
        if (max < v[i])
        {
            max = v[i];
        }
    }

    return max;
}

// Return the minimum value found in the vector
template <typename T>
T min_in_vector(const vector<T> &v)
{
    T min = v[0];

    for (size_t i = 1; i < v.size(); i++)
    {
        if (min > v[i])
        {
            min = v[i];
        }
    }

    return min;
}