// author: Aryanthepain
#include "basics.h"

template <typename T>
void input_vector(vector<T> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        cin << v[i];
    }

    return;
}