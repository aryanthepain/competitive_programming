// author: Aryanthepain
#include <bits/stdc++.h>
using namespace std;

void reverse(int arr[], int end, int start = 0)
{
    if (start == end - 1)
        return;

    swap(arr[end - 1], arr[start]);

    if (start + 1 == end - 1)
    {
        return;
    }

    reverse(arr, end - 1, start + 1);

    return;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    reverse(arr, n);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}