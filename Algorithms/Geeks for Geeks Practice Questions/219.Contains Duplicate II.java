/*
Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

Example 1:

Input: nums = [1,2,3,1], k = 3
Output: true
Example 2:

Input: nums = [1,0,1,1], k = 1
Output: true
Example 3:

Input: nums = [1,2,3,1,2,3], k = 2
Output: false

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
0 <= k <= 10^5

Solution : Maintain a set of all elements seen within range k. Check if current element is present within set, that means current element remains within i - k range. If
present, return true else first remove nums[i - k] if i > k then add current element.

Edge Case : k = 0 return false
*/

class Solution {
    public boolean containsNearbyDuplicate(int[] nums, int k) {
        if (k == 0) return false;
        Set<Integer> seenWithinRange = new HashSet<>();
        for (int i = 0; i < nums.length; i++) {
            if (seenWithinRange.contains(nums[i])) return true;
            if (i >= k) seenWithinRange.remove(nums[i - k]);
            seenWithinRange.add(nums[i]);
        }
        return false;
    }
}
