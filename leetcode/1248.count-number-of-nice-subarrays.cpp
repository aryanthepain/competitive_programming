/*
 * @lc app=leetcode id=1248 lang=cpp
 *
 * [1248] Count Number of Nice Subarrays
 */

// @lc code=start
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ans=0, n=nums.size();

        int pc=0, oc=0;
        int l=0, r=0;

        while(r<n){
            if(nums[r]%2){
                pc=0;
                oc++;
            }

            while(oc==k){
                pc++;

                if(nums[l]%2)
                    oc--;

                l++;
            }

            ans+=pc;
            r++;
        }

        return ans;
    }
};
// @lc code=end

