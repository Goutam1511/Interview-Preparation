/*
You are given an integer array nums.
You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

Constraints:
1 <= nums.length <= 104
0 <= nums[i] <= 105

Solution : This format takes care of both Jump Game - I and Jump Game - II. The solution is trivial but there are some nasty edge cases which we need to be
careful about. For the solution, we maintain 3 variables - i - current position, maxReach - maximum we can jump till now and curReach - currently how much we
can move before we need another jump. The curReach keeps track of how many jump we need and is only updated to maxReach when we reach that position through i.

Edge Cases:
1. [0, 1] -> False
2. [0] -> True
3. [1, 1, 1] -> True
4. [1, 2, 3] -> True
*/

class Solution {
    public boolean canJump(int[] nums) {
        int i = 0, curReach = -1, maxReach = nums[0];//At first, we have not started moving so curReach = -1 and maxReach is nums[0]
        if (nums.length == 1) {// We are already at last index
            return true;
        }

        while (i < nums.length) {//Just any looping would do
            while (i < nums.length && i <= curReach) {//While we are inside bounds and have exhausted our limit till current jump
                maxReach = Math.max(i + nums[i], maxReach);//Update maxReach till we can move and find out next limit
                i++;
            }
            if (i <= maxReach) {
              /* This is mainly taken for this Jump game I and not really useful in Jump Game 2 because,
               * in jump game 2 we can always reach the last index but we maintain same template. However,
               * for current problem, we should only update currentReach if our maxReach till last position before we exhausted curReach 
               * is greater than last position, otherwise we know our maxReach didn't get updated so there is no way we can move further.
               */
                curReach = maxReach;
            } else { //We cannot move further because maxReach never got updated, so break and return false
                break;
            }
            if (curReach >= nums.length - 1) { //Already at last index
                return true;
            }
        }
        return false;
    }
}
