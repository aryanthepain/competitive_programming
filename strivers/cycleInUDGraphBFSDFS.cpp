// 12 min

int main(){
    vector<int> visited(n, false);
    queue<pair<int,int>> q; // curr index and parent
    q.push({0, -1});

    for(int i=0; i<n; i++){
        if(q.empty()){
            if(!visited[i]){
                q.push(i);
            }
        }

        while(!q.empty()){
            auto cur = q.front(); q.pop();
            int curi = cur.first, parent = cur.second;
            
            if(visited[curi]){ // cycle detected
                return true;
            }
            visited[curi] = true;

            // push neighbours
            for(auto &v: adj[curi]){
                if(v==parent){
                    continue;
                }

                // not parent but visited, hence cycle
                if(visited[v])
                    return true;

                q.push({v, curi});
            }
        }
    }

    return false;
}