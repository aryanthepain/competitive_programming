/*
 * @lc app=leetcode id=907 lang=cpp
 *
 * [907] Sum of Subarray Minimums
 */

// @lc code=start
#define ll long long
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        ll MOD = 1e9+7;

        int n=arr.size();

        vector<ll> left(n);
        vector<ll> right(n);
        stack<int> s;
        
        // ple
        for(int i=0; i<n; i++){
            while(!s.empty() && arr[s.top()]>arr[i]){
                s.pop();
            }

            left[i] = s.empty() ? i+1 : i - s.top();
            s.push(i);
        }
        
        s = stack<int>();
        
        //nle
        for(int i=n-1; i>=0; i--){
            while(!s.empty() && arr[s.top()]>=arr[i]){
                s.pop();
            }

            right[i] = s.empty() ? n-i : s.top() - i;
            s.push(i);
        }

        ll ans=0;
        for(int i=0; i<n; i++){
            
            ans=(ans+arr[i]*left[i]*right[i])%MOD;
        }

        return (int) ans;
    }
};
// @lc code=end

