/*
You are given a 0-indexed integer array nums of length n.
The average difference of the index i is the absolute difference between the average of the first i + 1 elements of nums and the average of the last n - i - 1 elements.
Both averages should be rounded down to the nearest integer.
Return the index with the minimum average difference. If there are multiple such indices, return the smallest one.

Note:

The absolute difference of two numbers is the absolute value of their difference.
The average of n elements is the sum of the n elements divided (integer division) by n.
The average of 0 elements is considered to be 0.

Example 1:

Input: nums = [2,5,3,9,5,3]
Output: 3
Explanation:
- The average difference of index 0 is: |2 / 1 - (5 + 3 + 9 + 5 + 3) / 5| = |2 / 1 - 25 / 5| = |2 - 5| = 3.
- The average difference of index 1 is: |(2 + 5) / 2 - (3 + 9 + 5 + 3) / 4| = |7 / 2 - 20 / 4| = |3 - 5| = 2.
- The average difference of index 2 is: |(2 + 5 + 3) / 3 - (9 + 5 + 3) / 3| = |10 / 3 - 17 / 3| = |3 - 5| = 2.
- The average difference of index 3 is: |(2 + 5 + 3 + 9) / 4 - (5 + 3) / 2| = |19 / 4 - 8 / 2| = |4 - 4| = 0.
- The average difference of index 4 is: |(2 + 5 + 3 + 9 + 5) / 5 - 3 / 1| = |24 / 5 - 3 / 1| = |4 - 3| = 1.
- The average difference of index 5 is: |(2 + 5 + 3 + 9 + 5 + 3) / 6 - 0| = |27 / 6 - 0| = |4 - 0| = 4.
The average difference of index 3 is the minimum average difference so return 3.
Example 2:

Input: nums = [0]
Output: 0
Explanation:
The only index is 0 so return 0.
The average difference of index 0 is: |0 / 1 - 0| = |0 - 0| = 0.

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5

Algorithm -
Initialize variables:

n, integer to store the number of elements in the array.
minAvgDiff, initialized with a large integer value, stores the minimum average difference.
totalSum, a variable to store the sum of all elements of the nums array.
currPrefixSum, a variable to store the sum of all elements till the current index of the nums array.
ans, integer to store the index where we found the minimum average difference.
Iterate on the nums array and calculate totalSum.

Iterate over each index of the nums array:

At each index i, we add the current element in currPrefixSum, to get the sum of all elements of the nums array from index 0 to index i, and divide the sum by i + 1
to get the average of the left part of the array. Similarly, we can get the sum of elements from index i + 1 to n - 1 after subtracting the left part's sum from the
total sum of the array, and then divide it by n - i - 1 to get the average of the right part of the array. If the difference between the average of the left and right
part of the array is smaller than minAvgDiff, then store this difference in minAvgDiff and the current index i in ans.
Return ans.

Complexity Analysis
Here, N is the number of elements in the nums array.

Time complexity: O(n).

We iterate over each index of the nums array and at each index, we calculate averages of two parts in constant time using currSum and totalSum variables.
Thus, for finding the difference of averages at nn indices, it will take O(n)O(n) time.
Space complexity: O(1).

We have only used some integer variables. Thus, the space used is constant.
*/

class Solution {
    public int minimumAverageDifference(int[] nums) {
        long total = 0;
        for (int num : nums) {
            total += num;
        }
        int n = nums.length;
        long curTotal = 0;
        int minIndx = -1;
        long curDiff = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            curTotal += nums[i];
            long avg = curTotal / (i + 1);
            long otherAvg = 0;
            if (i < n - 1)
                otherAvg = (total - curTotal) / (n - i - 1);
            long diff = Math.abs(avg - otherAvg);
            if (diff < curDiff) {
                curDiff = diff;
                minIndx = i;
            }
        }
        
        return minIndx;
    }
}
