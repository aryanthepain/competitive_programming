#
# @lc app=leetcode id=1 lang=python3
#
# [1] Two Sum
#

# @lc code=start
class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        seen = {}
        for i, num in enumerate(nums):
            compliment = target - num
            if compliment in seen:
                return [i, seen[compliment]]
            seen[num] = i
        
# @lc code=end

