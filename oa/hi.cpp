#include <bits/stdc++.h>
using namespace std;
#define ll long long

// ——————————————————————————————————————————————
// Global storage of all palindrome‑special strings
static vector<string> pals;
static bool built = false;

// Build all ≈95 palindrome‑special candidates exactly once
void build_pals() {
    if (built) return;
    built = true;

    vector<int> evens = {2,4,6,8};
    vector<int> odds  = {1,3,5,7,9};

    // for each subset of {2,4,6,8}
    for (int mask = 0; mask < (1<<4); mask++) {
        vector<int> De;
        for (int i = 0; i < 4; i++)
            if (mask & (1<<i))
                De.push_back(evens[i]);

        // Case A: no odd digit
        if (!De.empty()) {
            sort(De.begin(), De.end());
            string L;
            for (int d : De)
                L += string(d/2, char('0'+d));
            string R = L;
            reverse(R.begin(), R.end());
            pals.push_back(L + R);
        }

        // Case B: pick exactly one odd digit
        for (int d0 : odds) {
            auto D = De;
            D.push_back(d0);
            sort(D.begin(), D.end());
            string L;
            for (int d : D)
                L += string(d/2, char('0'+d));
            string R = L;
            reverse(R.begin(), R.end());
            pals.push_back(L + char('0'+d0) + R);
        }
    }

    // de‑duplicate and sort by (length, lex)
    sort(pals.begin(), pals.end(),
         [](auto &a, auto &b) {
             if (a.size() != b.size()) return a.size() < b.size();
             return a < b;
         });
    pals.erase(unique(pals.begin(), pals.end()), pals.end());
}

// Given N as a string, find the smallest palindrome‑special > N
int find_next(const string &N) {
    int lo = 0, hi = pals.size();
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        auto &P = pals[mid];
        if (P.size() > N.size() || (P.size() == N.size() && P > N))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// Your solve stub:
ll solve(ll N) {
    if(N < 1) return (ll) 1;
    build_pals();

    string s = to_string(N);
    int idx = find_next(s);
    // we assume idx < pals.size()
    // convert back to ll (within constraints this will fit)
    return stoll(pals[idx]);
}

int main(){
    ll n;
    cin >> n;

    cout << solve(n) << endl;
}