/*
Given an integer n, return the least number of perfect square numbers that sum to n.
A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself.
For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

Constraints:
1 <= n <= 10^4

Solution : Initially might look like Greedy but actually DP - see first example. We first identify all the perfect squares till the number and store them in a set. Then,
we build up the number of least perfect squares in a bottom up dp - with the recurring relation -

  if j is a perfect square and i is a number greater than equal to j, then dp[i] = Math.min(1 + dp[i -j], dp[i]) with dp[i] = i initially because a number can be at max
  summation of i times 1.
  
 Space : O(n) Time : O(n ^ 3/2) because we are looping n times over the square roots till n.
*/

class Solution {
    Set<Integer> sqrtSet = new HashSet<>();
    
    public boolean checkIfPerfectSquare(int n, int i) {
        return i * i == n;
    }
    
    public int numSquares(int n) {
        int sqrt = (int)Math.sqrt(n);
        int[] dp = new int[n + 1];
        
        if (n == 1) {
            return 1;
        }
        
        if (checkIfPerfectSquare(n, sqrt)) { //If number is a perfect square
            return 1;
        }
        
        for (int i = 1; i <= sqrt; i++) {
            sqrtSet.add(i * i);
        }
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = i; // At max i can be sum of 1 i times
            for (int j : sqrtSet) {
                if (j <= i)
                    dp[i] = Math.min(1 + dp[i - j], dp[i]); 
            }
        }
        
        return dp[n];
    }
}
