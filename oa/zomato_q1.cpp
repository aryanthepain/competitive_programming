#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'checkLogTables' function below.
 *
 * The function is expected to return a STRING.
 *
 * The function accepts following parameters:
 *  1. INTEGER process_nodes
 *  2. INTEGER_ARRAY process_from
 *  3. INTEGER_ARRAY process_to
 *  4. INTEGER q
 *  5. 2D_INTEGER_ARRAY queries
 */

char checkQuery(vector<int> &query, int n, vector<vector<int>> &adj){
    // for(auto &q:query){
    //     cerr << q;
    // }
    // cerr<<endl;

    // for(auto &vect:adj){
    //     cerr<<"=";
    //     for(auto &ele:vect){
    //         cerr<<ele;
    //     }
    //     cerr<<endl;
    // }

    if(query[0]!=1) return '0';
    // cerr << "first ele not 1" << endl;

    queue<int> seq;
    seq.push(1);
    vector<bool> visited(n+1, false);
    visited[1] = true;

    // pointer for current pos
    int ptr=1;

    while(!seq.empty()){
        if(ptr>n-1) break;
        int parent = seq.front(); seq.pop();
        vector<int> children = adj[parent];
        visited[parent] = true;

        if(children.size() == 0 ) continue;
        cerr << "parent " << parent  << endl;

        cerr << "inner loop" << endl;
        while(true){
            if(ptr>n-1) break;

            int next = query[ptr];
            if(visited[next]) return '0';
            // visited[next] = true;

            cerr << next;

            // if one of the children
            if(find(children.begin(), children.end(), next)!=children.end()){
                cerr << " is a child" << endl;
                // if(visited[next]) return '0';
                seq.push(next); 
                ptr++;
                continue;
            }
            cerr << " not a child" << endl;
            for(auto &child: children){
                if(!visited[child]) return '0';
            }
            ptr++;
            break;
        }

    }
    cerr << "last ptr " << ptr << endl;
    // pointer is at last
    if(ptr>n-1) return '1';
    cerr<< "pointer not at last" << endl;
    return '0';
}

string checkLogTables(int process_nodes, vector<int> &process_from, vector<int> &process_to, int q, vector<vector<int>> &queries) {
    // for(int i=0; i<process_nodes-1; i++){
    //     cerr << "adj list" << i <<endl;
    //     cerr << process_from[i] << process_to[i] <<endl;
    // }
    
    // create adj list
    vector<vector<int>> adj(process_nodes+1);
    for(int i=0; i<process_nodes-1; i++){
        adj[process_from[i]].push_back(process_to[i]);
        adj[process_to[i]].push_back(process_from[i]);
        // cerr << "loop complete" << i <<endl;
    }

    string ans="";
    for(int i=0; i<q; i++){
        cerr << "query "<<i<<endl;
        ans+=checkQuery(queries[i], process_nodes, adj);
        cerr << endl;
    }
    // cerr<<ans<<endl;
    return ans;
}

int main() {
    int process_nodes, edges;
    cin >> process_nodes >> edges;

    vector<int> process_from(edges);
    vector<int> process_to(edges);

    for (int i = 0; i < edges; i++) {
        cin >> process_from[i] >> process_to[i];
    }

    int q;
    cin >> q;

    int g1, g2;
    cin >> g1 >> g2;

    vector<vector<int>> queries(q, vector<int>(process_nodes));

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < process_nodes; j++) {
            cin >> queries[i][j];
        }
    }
    // cerr << "queries" << endl;
    // for (int i = 0; i < q; i++) {
    //     for (int j = 0; j < process_nodes; j++) {
    //         cerr<< queries[i][j];
    //     }
    //     cerr << endl;
    // }
    
    // cerr << "main function called" <<endl;
    cout << checkLogTables(
        process_nodes,
        process_from,
        process_to,
        q,
        queries
    ) << '\n';

    return 0;
}