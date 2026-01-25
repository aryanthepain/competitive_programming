#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> grid= {{0,2,2}};
    // vector<vector<int>> grid= {{2,1,1},{0,1,1},{1,0,1}};
    int m=grid.size(), n=grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, -1));

    // initialise multi bfs
    queue<pair<pair<int, int>, int>>   q;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]==2){
                q.push({{i,j}, 0});
                dist[i][j] = 0;
            }
            else if(grid[i][j]==0){
                dist[i][j] = -2;
            }
        }
    }
    
    // run bfs
    int max_dist=0;
    vector<vector<int>> movement = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    while(!q.empty()){
        auto curpt = q.front(); q.pop();
        int curx = curpt.first.first, cury = curpt.first.second, curd = curpt.second;
        // dist[curx][cury] = curd;
        // check moves
        for(auto &v: movement){
            int nx = curx + v[0], ny = cury + v[1];
            if(nx >= 0 && nx<m && ny >=0 && ny <n && dist[nx][ny]==-1){ // in bounds and not visited
                q.push({{nx,ny}, curd+1});
                dist[nx][ny] = curd + 1;
                max_dist = max(max_dist, curd+1);
            }
        }
    }
    
    // check if any is not rotten
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(dist[i][j]==-1){
                cout<<-1<<endl;
                return -1;
            }
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    // all are rotten
    cout << max_dist << endl;
    return max_dist;
}