// author - Aryanthepain
// time - 30 minute
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    
    
    int ogCol = image[sr][sc];
    if(ogCol==color){
        return image;
    }
    
    int m = image.size(), n = image[0].size();
    
    queue<pair<int, int>> q;
    q.push({sr,sc});
    image[sr][sc] = color;
    vector<vector<int>> moves={{0,1}, {0, -1}, {1,0}, {-1,0}};
    
    // bfs
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        
        for(auto &move: moves){
            int curx = cur.first + move[0], cury = cur.second + move[1];
            
            // out of bounds and same color check
            // cout<<"hi"<<endl;
            if(curx >=0 && curx < m && cury >=0 && cury < n){
                if(image[curx][cury]==ogCol){
                image[curx][cury] = color; // change color
                q.push({curx, cury});}
            }
        }
    }
    
    return image;
    }
};