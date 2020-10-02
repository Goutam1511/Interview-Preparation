/*
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
Follow up:
Your algorithm should run in O(n) time and uses constant extra space.

Solution : The idea is from the observation:
---The missing minimum positive must be in [1, nums.length]
---So for any element in nums that is greater than nums.length, we don't need to handle them
So what we need to do:
----Put the value of nums[i] - 1 (value === nums[i] - 1) at the pos nums[value]
----Why nums[i] - 1, not nums[i]? Because when nums[i] === 1, nums[i] should be put at nums[0]
The target should be i + 1, when nums[i] != i + 1, because the criteria means the value === nums[i] doesn't exist in the nums array.
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int i = 0;
        int n = nums.size();
        while (i < n)
        {
            if (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
                swap(nums[i], nums[nums[i]-1]);
            else
                i++;
        }
        for (i = 0; i < n; ++i)
            if (nums[i] != (i+1))
                return i+1;
        return n+1;
    }
};

NAIVE SOLUTION with O(n) extra space :

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        vector<int> numssort(nums.size() + 1, -1);
        
        for (int i : nums) {
            if (i <= nums.size() && i > 0) {
                numssort[i] = i;
            }
        }
        
        for (int i = 1; i <= nums.size(); i++) {
            if (numssort[i] == -1) {
                return i;
            }
        }
        return nums.size() + 1;
    }
};
