/*
You are given an array of positive integers nums and want to erase a subarray containing unique elements. 
The score you get by erasing the subarray is equal to the sum of its elements.
Return the maximum score you can get by erasing exactly one subarray.

An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

Example 1:
Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6

Example 2:
Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].

Constraints:
1 <= nums.length <= 105
1 <= nums[i] <= 104

Solution : Question is same as maximum substring with no repeating characters. We just find out the maximum subarray with no repeating element through sliding
window or two pointer technique. While we move the pointers, we increase or decrease current sum accordingly and update the subarray sum on the fly. We also
track the unique elements in the subarray through Hashset

Complexity : Both O(n)
*/


class Solution {
    public int maximumUniqueSubarray(int[] nums) {
        int i = 0, j = 0;
        Set<Integer> s = new HashSet<>();
        int sum  = 0;
        int maxSum = 0;
        
        while (i < nums.length && j < nums.length) {
            if (!s.contains(nums[j])) {
                sum += nums[j];
                s.add(nums[j++]);
                maxSum = Math.max(maxSum, sum);
            } else {
                sum -= nums[i];
                s.remove(nums[i++]);
            }
        }
        
        return maxSum;
    }
}
