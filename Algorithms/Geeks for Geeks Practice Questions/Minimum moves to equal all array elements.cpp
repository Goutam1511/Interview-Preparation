/*
Minimum moves to equal all array elements II | Sorting | LeetCode
Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
In one move, you can increment or decrement an element of the array by 1.

Example 1:

Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
Example 2:

Input: nums = [1,10,2,9]
Output: 16

Example 3:
Input: [1,2,3,4]
Output: 4

Constraints:

n == nums.length
1 <= nums.length <= 105
-109 <= nums[i] <= 109

Solution: The idea is that when the array is sorted, the mid element will always be the one that we need to convert the array elements
into to land up in the optimal moves. For example for [1, 10, 2, 9]-->[2, 2, 2, 2], the mid element after sorting is 2 and if we convert
all elements to 2 we land up with the minimal number of moves needed. For [1, 2, 3] also the same, we need to convert to [2, 2, 2].
*/

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int mid, moves = 0;
        /* Find the mid index - for odd size, this is size/2 but for even size,
         * this is size/2 - 1. For example, for [1, 2, 3, 4], this is arr[1] = 2.
         */
        mid = nums.size() % 2 ? nums.size() / 2 : nums.size() / 2 - 1;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size(); i++) {
            if (i != mid) {
                /* The number of moves needed is the element to be converted to
                 * - the current element value
                 */
                moves += abs(nums[i] - nums[mid]); 
            }
        }
        
        return moves;
    }
};
