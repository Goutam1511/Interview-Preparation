/*
Given an integer array nums, your goal is to make all elements in nums equal. To complete one operation, follow these steps:

Find the largest value in nums. Let its index be i (0-indexed) and its value be largest.
If there are multiple elements with the largest value, pick the smallest i.
Find the next largest value in nums strictly smaller than largest. Let its value be nextLargest.
Reduce nums[i] to nextLargest.
Return the number of operations to make all elements in nums equal.

Example 1:

Input: nums = [5,1,3]
Output: 3
Explanation: It takes 3 operations to make all elements in nums equal:
1. largest = 5 at index 0. nextLargest = 3. Reduce nums[0] to 3. nums = [3,1,3].
2. largest = 3 at index 0. nextLargest = 1. Reduce nums[0] to 1. nums = [1,1,3].
3. largest = 3 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums = [1,1,1].
Example 2:

Input: nums = [1,1,1]
Output: 0
Explanation: All elements in nums are already equal.
Example 3:

Input: nums = [1,1,2,2,3]
Output: 4
Explanation: It takes 4 operations to make all elements in nums equal:
1. largest = 3 at index 4. nextLargest = 2. Reduce nums[4] to 2. nums = [1,1,2,2,2].
2. largest = 2 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums = [1,1,1,2,2].
3. largest = 2 at index 3. nextLargest = 1. Reduce nums[3] to 1. nums = [1,1,1,1,2].
4. largest = 2 at index 4. nextLargest = 1. Reduce nums[4] to 1. nums = [1,1,1,1,1].

Constraints:

1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 5 * 10^4

Solution : https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/editorial/
We are sorting the array and then trying to reduce all elements with maximum value to the next maximum value in one operation.
For example if after sorting [1, 2, 2, 3, 3] then we know in 2 operations, it will become [1, 2, 2, 2, 2] and then next we know in further 4
operations it will be [1, 1, 1, 1, 1] so in total 2 + 4 = 6 we need to find out the total number of operations like this before we reach the smallest
value. Hence for this we start traversing the sorted array from another end and keep on count the frequency of same values till encountering the next
smaller value. We keep on adding the count until we reach the end of smallest value from right side to left.
*/

class Solution {
    public int reductionOperations(int[] nums) {
        if (nums.length == 1) return 0;
        Arrays.sort(nums);
        int extentOfSmallestVal = 1;
        while (extentOfSmallestVal < nums.length
                && nums[extentOfSmallestVal] == nums[0]) {
            extentOfSmallestVal++;
        }
        if (extentOfSmallestVal == nums.length - 1) return 1;
        int i = nums.length - 2;
        int ops = 0;
        int lastSeenIndex = nums.length - 1;
        while (i >= extentOfSmallestVal) {
            while (i >= extentOfSmallestVal && nums[i] == nums[lastSeenIndex]) {
                i--;
            }
            ops += (nums.length - 1 - i);
            lastSeenIndex = i;
        }
        return ops;
    }
}
