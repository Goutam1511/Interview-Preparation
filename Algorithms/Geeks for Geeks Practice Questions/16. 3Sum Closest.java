/*
Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.
Return the sum of the three integers. You may assume that each input would have exactly one solution.

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0). 

Constraints:

3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-10^4 <= target <= 10^4

Solution : The approach is same as 3Sum - sort and keeping one element fixed, search for 2 other elements through 2 pointer. However, since we are not searching for the
exact target sum, we try out all elements within the left to right range and pick the closest sum.

Time Complexity : O(N^2) Space Complexity : O(1)
*/

class Solution {
    public int threeSumClosest(int[] nums, int target) {
        Arrays.sort(nums);
        int curDiff = Integer.MAX_VALUE;
        int ans = Integer.MAX_VALUE;
        
        for (int i = 0; i < nums.length - 2; i++) {
            int left = i + 1, right = nums.length - 1;
            while (left < right) {
                if (Math.abs(nums[i] + nums[left] + nums[right] - target) < curDiff) {
                    curDiff = Math.abs(nums[i] + nums[left] + nums[right] - target);
                    ans = nums[i] + nums[left] + nums[right];
                }
                if (nums[i] + nums[left] + nums[right] == target) {
                    return target;
                } else if (nums[i] + nums[left] + nums[right] < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return ans;
    }
}
