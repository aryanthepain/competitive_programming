#include <bits/stdc++.h>
using namespace std;

int number(int n, vector<vector<int>> & edges){
    // create adjacency matrix
    vector<vector<int>> adj(n);
    for(auto &v:edges){
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }

    vector<bool> visited(n);
    queue<int> q;
    int ans=0;
    // for loop
    for(int i=0; i<n; i++){
        if(q.empty() && !visited[i]){
            q.push(i);
            ans++;
        }

        while(!q.empty()){
            int curi=q.front(); q.pop();
            visited[curi] = true;
            for(auto &j: adj[curi]){
                if(!visited[j]){
                    q.push(j);
                }
            }
        }
    }

    return ans;
}
int main(){
    int x; cin>>x; // ps no.
    int n;
    vector<vector<int>> edge;

    if(x==2){
        n=6;
        edge = {{1,1}, {0,2}, {2,1}, {4,3}};
    }
    else if(x){
        n=7;
        edge = {{0, 1}, {1, 2}, {2, 3}, {4, 5}};
    } else {
        n=4;
        edge = {{0,1}, {1,2}};
    }

    cout << number(n, edge) << endl;
}