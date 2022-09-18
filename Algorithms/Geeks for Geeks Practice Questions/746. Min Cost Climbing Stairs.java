/*
You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
You can either start from the step with index 0, or the step with index 1. Return the minimum cost to reach the top of the floor.

Example 1:

Input: cost = [10,15,20]
Output: 15
Explanation: You will start at index 1.
- Pay 15 and climb two steps to reach the top.
The total cost is 15.
Example 2:

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.

Constraints:

2 <= cost.length <= 1000
0 <= cost[i] <= 999

Solution : Standard DP problem - cost of 1st step is cost[0] & cost of 2nd step is cost[1]. From step 2, we have 2 options - either to arrive from 1 step behind or
2 step behind, either ways we can reach from 1 step or 2 step behind after adding the cost at step i. Now, one misleading info is we are not looking to reach the
last step but one step beyond that which is the top of the floor. And we can reach the top of floor either from 1 step back or 2 steps back. Hence, we return minimum of
minCost[noOfSteps - 1] or minCost[noOfSteps - 2].

Time & Space Complexity : O(n)
*/

class Solution {
    public int minCostClimbingStairs(int[] cost) {
        int steps = cost.length;
        int[] minCost = new int[steps];
        
        minCost[0] = cost[0];
        minCost[1] = cost[1];
        
        for (int i = 2; i < steps; i++) {
            minCost[i] = Math.min(minCost[i - 1], minCost[i - 2]) + cost[i];
        }

        return Math.min(minCost[steps - 1], minCost[steps - 2]);
    }
}
