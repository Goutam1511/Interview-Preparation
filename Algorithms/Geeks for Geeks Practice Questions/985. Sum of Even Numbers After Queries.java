/*
You are given an integer array nums and an array queries where queries[i] = [vali, indexi].
For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even values of nums.
Return an integer array answer where answer[i] is the answer to the ith query.

Example 1:

Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
Output: [8,6,2,4]
Explanation: At the beginning, the array is [1,2,3,4].
After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
After adding -3 to nums[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
After adding -4 to nums[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
After adding 2 to nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.
Example 2:

Input: nums = [1], queries = [[4,0]]
Output: [0]

Constraints:

1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
1 <= queries.length <= 10^4
-10^4 <= vali <= 10^4
0 <= index[i] < nums.length

Solution : The only important observation is that, when working on a query the other elements of nums doesn't change and hence if we first find out the sum of all even
numbers in nums, for each query, when we are adding a value to a number in nums array, we are always substracting an even number from the precomputed sum if the number
was even previous to the query operation, and then adding an even number to the precomputed sum if after adding the value given in the query operation, the number turns
out to become even.

Time Complexity : O(N + Q) Space Complexity : O(1) excluding the answer array
*/

class Solution {
    public int[] sumEvenAfterQueries(int[] nums, int[][] queries) {
        int allEvenSums = 0;
        for (int i : nums) {
            if (i % 2 == 0) allEvenSums += i;
        }
        int[] answer = new int[queries.length];
        int idx = 0;
        for (int[] query : queries) {
            int index = query[1];
            int val   = query[0];
            
            int oldVal = nums[index];
            if (oldVal % 2 == 0) allEvenSums -= oldVal;
            nums[index] += val;
            if (nums[index] % 2 == 0) allEvenSums += nums[index];
            answer[idx++] = allEvenSums;
        }
        
        return answer;
    }
}
