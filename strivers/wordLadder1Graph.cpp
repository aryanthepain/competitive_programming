// time - 31 min
#include <bits/stc++.h>
using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    int n = wordList.size(), l=beginWord.length();
    int starti = -1;
    int endi = -1;
    for(int i=0; i<n; i++){
        if(wordList[i] == endWord){
            endi = i;
        }
        else if(wordList[i] == beginWord){
            starti = i;
        }

        // early break
        if(starti!=-1 && endi != -1) break;
    }   

    if(starti == -1){
        wordList.push_back(beginWord);
        starti = n;
        if(endi == -1) return 0;
        n++;
    }

    // adjacency list
    vector<vector<int>> adj(n);
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int diff=0;
            for(int k=0; k<l; k++){
                if(wordList[i][k] != wordList[j][k]){
                    diff++;
                }
                if(diff>1) break;
            }

            if(diff==1){
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // BFS
    vector<int> visited(n, -1);
    queue<pair<int, int>> q;

    q.push({starti, 1});
    visited[starti] = 1;

    while(!q.empty()){
        auto cur = q.front(); q.pop();
        int curi = cur.first, curd = cur.second;

        for(auto &v: adj[curi]){
            if(visited[v]==-1){
                // break line
                if(v ==  endi){
                    return curd+1;
                }

                q.push({v, curd+1});
                visited[v] = curd+1;
            }
        }
    }

    // find parent
    

    return 0;
}