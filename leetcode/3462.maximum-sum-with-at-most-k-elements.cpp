/*
 * @lc app=leetcode id=3462 lang=cpp
 *
 * [3462] Maximum Sum With at Most K Elements
 */

// @lc code=start
#define ll long long
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        if(k==0) return 0;

        int n=grid.size(), m=grid[0].size();

        vector<int> q;
        // greatest limits[i] number of elements for each row into q
        for(auto [i, row]:views::enumerate(grid)){
            auto it = row.begin() + limits[i];

            nth_element(row.begin(), it, row.end(), greater<int>());

            q.insert(q.end(), row.begin(), it);
        }
        
        // first k ele greater than next elements
        n=min(k,(int) q.size());
        nth_element(q.begin(), q.begin()+n, q.end(), greater<int>());

        // sum first k ele
        return accumulate(q.begin(), q.begin() + k, 0ll);
    }
};
// @lc code=end

