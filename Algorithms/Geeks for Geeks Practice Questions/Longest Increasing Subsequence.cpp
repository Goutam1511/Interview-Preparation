/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:

Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 

Note:
    There may be more than one LIS combination, it is only necessary for you to return the length.
    Your algorithm should run in O(n^2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

Solution Approach : Check https://www.youtube.com/watch?v=CE2b_-XfVDk. This method relies on the fact that the longest increasing subsequence possible upto the ith index  
in a given array is independent of the elements coming later on in the array. Thus, if we know the length of the LIS upto ith index, we can figure out the length of the LIS
possible by including the (i+1)th element based on the elements with indices j such that 0 ≤ j ≤ (i+1). We make use of a dp array to store the required data. dp[i] 
represents the length of the longest increasing subsequence possible considering the array elements upto the ith index only ,by necessarily including the ith element. In 
order to find out dp[i], we need to try to append the current element(nums[i]) in every possible increasing subsequences upto the (i−1)th index(including the (i−1)th( index),
such that the new sequence formed by adding the current element is also an increasing subsequence. Thus, we can easily determine dp[i] using:

dp[i]= max(dp[j] + 1, dp[i]), ∀ nums[j] < nums[i] where 0 <= j < i

At the end, the maximum out of all the dp[i]'s to determine the final result.

Time Complexity : O(n^2)
Space Complexity : O(n).

Better optimization possible to reduce time to O(nlogn).
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        long int i = 0, j = 0;
        
        if (nums.size() == 0) {
            return 0;
        }
        
        vector<int> lis(nums.size(), 1);
        
        for (i = 1; i < nums.size(); i++) {
            for (j = 0; j < i; j++) {
                if (nums[i] > nums[j] && lis[j] + 1 > lis[i]) {
                    lis[i] = lis[j] + 1;
                }
            }
        }
        
        return *max_element(lis.begin(), lis.end());
    }
};
