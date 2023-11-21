/*
You are given an array nums that consists of non-negative integers. Let us define rev(x) as the reverse of the non-negative integer x.
For example, rev(123) = 321, and rev(120) = 21. A pair of indices (i, j) is nice if it satisfies all of the following conditions:

0 <= i < j < nums.length
nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
Return the number of nice pairs of indices. Since that number can be too large, return it modulo 10^9 + 7.

Example 1:

Input: nums = [42,11,1,97]
Output: 2
Explanation: The two pairs are:
 - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
 - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.
Example 2:

Input: nums = [13,10,35,24,76]
Output: 4

Solution : The condition can be rearranged to (nums[i] - rev(nums[i])) == (nums[j] - rev(nums[j])). Transform each nums[i] into (nums[i] - rev(nums[i])).
Then, count the number of (i, j) pairs that have equal values. Keep a map storing the frequencies of values that you have seen so far.
For each i, check if nums[i] is in the map. If it is, then add that count to the overall count. Then, increment the frequency of nums[i]. OR 
for each overall frequency we can have nC2 pairs.

Time Complexity : O(n)
Space Complexity : O(n) for hashmap
*/

class Solution {
    private int reverse(int num) {
        int rev = 0;
        while (num > 0) {
            int d = num % 10;
            num = num / 10;
            rev = rev * 10 + d;
        }
        return rev;
    }
    public int countNicePairs(int[] nums) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int rev = reverse(nums[i]);
            nums[i] = nums[i] - rev;
            freq.put(nums[i], freq.getOrDefault(nums[i], 0) + 1);
        }
        int res = 0;
        for (int val : freq.values()) {
            long in = (((long)val * (long)(val - 1)) / 2) % 1000000007;
            res = (res + (int)(in)) % 1000000007;
        }
        return res;
    }
}
