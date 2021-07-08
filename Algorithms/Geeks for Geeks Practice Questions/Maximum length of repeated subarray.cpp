/*
Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.

Example 1:

Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
Output: 3
Explanation: The repeated subarray with maximum length is [3,2,1].
Example 2:

Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
Output: 5

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 100

Solution : Since a common subarray of A and B must start at some A[i] and B[j], let dp[i][j] be the longest common prefix of A[i:] and B[j:].
Whenever A[i] == B[j], we know dp[i][j] = dp[i+1][j+1] + 1. Also, the answer is max(dp[i][j]) over all i, j.
We can perform bottom-up dynamic programming to find the answer based on this recurrence.
Our loop invariant is that the answer is already calculated correctly and stored in dp for any larger i, j.

Complexity : O(n^2).
*/

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int numsize1 = nums1.size(), numsize2 = nums2.size(),
            i = 0, j = 0, res = 0;
        
        vector<vector<int>> dp(numsize1 + 1, vector<int> (numsize2 + 1, 0));
        
        for (i = numsize1 - 1; i >= 0; i--) {
            for (j = numsize2 - 1; j >= 0; j--) {
                if (nums1[i] == nums2[j]) {
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                    if (res < dp[i][j]) res = dp[i][j];
                }
            }
        }
        
        /*for (i = 0; i < numsize1; i++) {
            for (j = 0; j < numsize2; j++) {
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }*/
        
        return res;
    }
};
