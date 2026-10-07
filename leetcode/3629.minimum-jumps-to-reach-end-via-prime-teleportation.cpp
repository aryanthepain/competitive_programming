/*
 * @lc app=leetcode id=3629 lang=cpp
 *
 * [3629] Minimum Jumps to Reach End via Prime Teleportation
 */

// @lc code=start

class Solution {
    public:
    
    
    int minJumps(vector<int>& nums) {
        const int MAX = *max_element(nums.begin(), nums.end())+4;
        vector<bool> isPrime(MAX, true);
        vector<bool> usedPrime(MAX, false);
        isPrime[0] = isPrime[1] = false;
        // sieve of eratosthenes
        for(int i=2; i * i < MAX; i++){
            if(!isPrime[i]) continue;
        
            int j=i*i;
            while(j<MAX){
                isPrime[j] = false;
                j+=i;
            }
        }
        
        int n=nums.size();
        if(n==1) return 0;
        if(n==2) return 1;
        // cout << n << endl;

        // store indices
        vector<vector<int>> indices(MAX);
        for(int i=0; i<n; i++){
            indices[nums[i]].push_back(i);
        }

        vector<int> dp(n, -1);
        dp[0] = 0;
        queue<int> q;
        q.push(0);

        while(!q.empty()){
            int i = q.front(); q.pop();

            // at last
            if(i==n-1){
                return dp[n-1];
            }

            int r=i-1;
            if(r>0 && dp[r]==-1){
                dp[r]=1+dp[i];
                q.push(r);
            }

            int l=i+1;
            if(l<n && dp[l]==-1){
                dp[l]=1+dp[i];
                q.push(l);
            }

            if(!isPrime[nums[i]] || usedPrime[nums[i]])
                continue;

            usedPrime[nums[i]] = true;
            for(int p=nums[i]; p<MAX; p+=nums[i]){
                for(auto &j : indices[p]){
                    if(dp[j]==-1){
                        dp[j] = 1+dp[i];
                        q.push(j);
                    }
                }
            }
        }

        return dp[n-1];
    }
};
// @lc code=end

