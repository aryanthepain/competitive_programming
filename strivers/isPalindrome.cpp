// author: Aryanthepain
#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(string s, int end, int start = 0)
{
    if (start == end - 1)
        return true;

    if (s[end - 1] != s[start])
        return false;

    if (start + 1 == end - 1)
    {
        return true;
    }

    return isPalindrome(s, end - 1, start + 1);
}

int main()
{
    string s;
    cin >> s;
    cout << isPalindrome(s, s.size()) << endl;

    return 0;
}