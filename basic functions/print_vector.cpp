// author: Aryanthepain
#include "basics.h"

template <typename T>
void print_vector(const vector<T> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    return;
}