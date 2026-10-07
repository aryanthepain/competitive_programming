#include <bits/stdc++.h>
using namespace std;

int getMinOperations(int n, vector<int>& data) {
    int l=0, r=n-1;

    vector<unordered_set<int>> disc(n);
    // int v = 0;
    while(l<r){
        if(!(data[l]==data[r])){
            int high = max(data[l], data[r]);
            int low = min(data[l], data[r]);

            // cerr<< l << r << endl;

            // int count = disc[low].size();

            disc[low].insert(high);
            disc[high].insert(low);

            // if(disc[low].size()!=count){
            //     v++;
            // }
        }

        l++;
        r--;
    }

    // calculate discrepancies
    int sum=0;
    for(int i=0; i<n; i++){
        if(disc[i].size())
            sum++;
    }


    // connected components
    vector<bool> visited(n);
    queue<int> q;

    int comp = 0;
    for(int i=0; i<n; i++){
        if(!visited[i] && disc[i].size()){
            q.push(i);
            comp++;
        }

        while(!q.empty()){
            int curr = q.front(); q.pop();
            visited[curr] = true;

            for(auto &child:disc[curr]){
                if(!visited[child])
                    q.push(child);
            }

        }

    }

    return sum - comp;
}

int main() {
    int n;
    cin >> n;

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    cout << getMinOperations(n, data) << '\n';

    return 0;
}