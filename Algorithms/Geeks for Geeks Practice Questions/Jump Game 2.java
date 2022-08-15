/*
Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.
You can assume that you can always reach the last index.

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [2,3,0,1,4]
Output: 2
 

Constraints:
1 <= nums.length <= 104
0 <= nums[i] <= 1000

Solution : This format takes care of both Jump Game - I and Jump Game - II. The solution is trivial but there are some nasty edge cases which we need to be
careful about. For the solution, we maintain 3 variables - i - current position, maxReach - maximum we can jump till now and curReach - currently how much we
can move before we need another jump. The curReach keeps track of how many jump we need and is only updated to maxReach when we reach that position through i.
*/

class Solution {
    public int jump(int[] nums) {
        int i = 0, curReach = -1, maxReach = nums[0], jump = 0; //At first, we have not started moving so curReach = -1 and maxReach is nums[0]
        if (nums.length == 1) { // We are already at last index
            return 0;
        }

        while (i < nums.length) { //Just any looping would do
            while (i < nums.length && i <= curReach) { //While we are inside bounds and have exhausted our limit till current jump
                maxReach = Math.max(i + nums[i], maxReach); //Update maxReach till we can move and find out next limit
                i++;
            }
            if (i <= maxReach) {
              /* This is mainly taken for Jump game I and not really useful here because,
               * in jump game 2 we can always reach the last index but we maintain same template.
               */
                curReach = maxReach; //new reach
                jump++; //Update the number of jumps when we have exhausted last curReach
            } else { //unreachable code in jump 2 because we can always reach last index
                break;
            }
            if (curReach >= nums.length - 1) { //Already at last index ? Break
                break;
            }
        }
        return jump;
    }
}
