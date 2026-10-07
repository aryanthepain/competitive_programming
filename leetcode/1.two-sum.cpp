/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // sort vector
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());


        int n = nums.size();
        int l = 0, r = n-1;

        while(r>l){
            int total = sorted[l] + sorted[r];

            if(total == target) break;
            if(total > target){
                r--;
                continue;
            }
            l++;
            continue;
        }
        cout << l << "," << r << " = l,r" << endl;

        int i=-1, j=-1;

        for(int k=0; k<n; k++){
            if(i>=0 && j>=0){
                break;
            }

            if(nums[k]==sorted[l] && i<0){
                i=k;
                continue;
            }
            if(nums[k]==sorted[r] && j<0){
                j=k;
            }
        }

        cout << "i,j = " << i <<","<<j<<endl;

        return vector<int>{i, j};
    }
};
// @lc code=end

