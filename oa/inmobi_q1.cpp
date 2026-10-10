#include <bits/stdc++.h>
using namespace std;

using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, g;
    cin >> n >> g;
    ll INF= LLONG_MAX-1;

    vector<tuple<ll, ll, ll, int>> p(n);

    for (int i = 0; i < n; i++) {
        ll a, d, pr;
        cin >> a >> d >> pr;
        p[i] = {a, d, pr, i};
    }

    sort(p.begin(), p.end());

    priority_queue<tuple<ll, ll, int, ll>> q;
    priority_queue<ll, vector<ll>, greater<ll>> runq;

    int i=0, done=0;
    ll totwait=0, time=0;
    vector<ll> completion(n);

    while(done<n){
        // all processes till time
        while(i<n && get<0>(p[i])<=time){
            auto [a, d, pr, id] = p[i];
            q.push({pr, -a, -id, d});
            i++;
        }

        // complete processes
        while(!runq.empty() && runq.top()<=time){
            runq.pop();
        }

        // add new process
        while(!q.empty() && runq.size() < g){
            auto [pr, na, ni, d] = q.top();
            q.pop();
            ll a=-na;
            int id=-ni;

            ll finish = time+d;
            completion[id] = finish;
            totwait+=time-a;
            done++;

            if(d>0){
                runq.push(finish);
            }
        }

        // jump to next time
        ll nexta = i<n ? get<0>(p[i]) : INF;
        ll nextd = runq.empty() ? INF: runq.top();

        time = min(nexta, nextd);
    }



    for (ll x : completion)
        cout << x << '\n';

    cout << fixed << setprecision(4)
         << ((long double)totwait) / n << '\n';

    return 0;
}