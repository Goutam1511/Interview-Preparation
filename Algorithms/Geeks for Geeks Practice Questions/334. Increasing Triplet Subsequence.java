/*
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists,
return false.

Example 1:

Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

Constraints:

1 <= nums.length <= 5 * 10^5
-2^31 <= nums[i] <= 2^31 - 1

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?

Solution : If thought a little deeply, the question boils down to whether there are three increasing numbers. For that we just need to find the smallest two numbers &
if there is another number greater than the smallest two numbers figured so far.

Time : O(n) Space : O(1)
*/

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int firstSmallestTillHere = INT_MAX;
        int secondSmallestTillHere = INT_MAX;
        
        for(int i: nums) {
            if(i <= firstSmallestTillHere) {
                firstSmallestTillHere = i;
            } else if(i <= secondSmallestTillHere) {
                secondSmallestTillHere = i;
            } else {
                return true;
            }
        }
        
        return false;
    }
};
