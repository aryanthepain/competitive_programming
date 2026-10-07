/*
 * @lc app=leetcode id=407 lang=cpp
 *
 * [407] Trapping Rain Water II
 */

// @lc code=start
class Solution {
public:
    int trapRainWater(vector<vector<int>>& h) {
        // size of matrix
        int n=h.size(), m=h[0].size();
        
        // single file or 2 file is 0
        if(m<3 || n<3)
            return 0;

        
        priority_queue<pair<int, pair<int, int>>,
                        vector<pair<int, pair<int,int>>>,
                        greater<pair<int, pair<int, int>>>
                        > q;
        
        // push all boundary
        int i1=0, i2=n-1;
        for(int j=0; j<m; j++){
            q.push({h[i1][j], {i1, j}}); // first row
            q.push({h[i2][j], {i2, j}}); // last row
            h[i1][j] = h[i2][j] = -1;
        }
        int j1=0, j2=m-1;
        for(int i=1; i<n-1; i++){
            q.push({h[i][j1], {i, j1}}); // first row
            q.push({h[i][j2], {i, j2}}); // last row
            h[i][j2] = h[i][j1] = -1;
        }
        // q.push({0, {0,0}});


        vector<vector<int>> neighbours= {{0,1}, {1,0}, {-1,0}, {0,-1}};
        int level=0, ans=0;

        // start loop to check all
        while(!q.empty()){
            pair<int, pair<int, int>> curr = q.top(); q.pop();
            int ch=curr.first, crow=curr.second.first, ccol = curr.second.second;
            level = max(ch, level);
            cout << level << endl;

            // check all neighbours
            for(auto ne : neighbours){
                int ncol = ccol + ne[1], nrow = crow + ne[0];
                // if is valid and not visited
                if(ncol>0 && ncol<(m-1) && nrow>0 && nrow <(n-1) && (h[nrow][ncol])!=-1){
                    int height = h[nrow][ncol];
                    q.push({height, {nrow, ncol}});
                    h[nrow][ncol]=-1;

                    if(level> height)
                        ans+=level-height;
                }
            }
        }

        return ans;
    }
};
// @lc code=end

