+/*
 * @lc app=leetcode id=3640 lang=cpp
 *
 * [3640] Trionic Array II
 */

// @lc code=start
#define ll long long
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        ll NEG=-(1e16);
        
        ll ans=NEG;
        ll up=NEG, down=NEG, tri=NEG;
        ll oup, odown, otri;
        int n=nums.size();

        for(int i=1; i<n; i++){
            ll x=nums[i], prev=nums[i-1];
            oup =up;
            odown=down;
            otri=tri;

            if(x>prev){
                // p1
                up=max(oup+x, prev + x);

                // p3
                tri=max(otri+x, odown + x);

                down=NEG;
            } else if(x<prev){
                //p2
                down=max(oup+x, odown+x);

                up=tri=NEG;
            } else{
                up = down = tri = NEG;
            }

            ans=max(ans, tri);
        }
        
        return ans;
    }
};
// @lc code=end

