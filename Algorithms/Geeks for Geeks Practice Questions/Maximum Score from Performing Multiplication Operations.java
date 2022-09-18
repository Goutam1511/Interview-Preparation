/*
You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.
You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:

1. Choose one integer x from either the start or the end of the array nums.
2. Add multipliers[i] * x to your score.
3. Remove x from the array nums.
Return the maximum score after performing m operations.

Example 1:

Input: nums = [1,2,3], multipliers = [3,2,1]
Output: 14
Explanation: An optimal solution is as follows:
- Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
- Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
- Choose from the end, [1], adding 1 * 1 = 1 to the score.
The total score is 9 + 4 + 1 = 14.
Example 2:

Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
Output: 102
Explanation: An optimal solution is as follows:
- Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the score.
- Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
- Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
- Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
- Choose from the end, [-2,7], adding 7 * 6 = 42 to the score. 
The total score is 50 + 15 - 9 + 4 + 42 = 102.

Constraints:

n == nums.length
m == multipliers.length
1 <= m <= 10^3
m <= n <= 10^5
-1000 <= nums[i], multipliers[i] <= 1000

Solution : At first glance, a greedy approach looks promising. In step i, out of nums[start] and nums[end], we can pick the integer x that maximizes x * multipliers[i].
This greedy approach works well for one of the given examples.

nums = [1,2,3], multipliers = [3,2,1]

Taking Decision
‣ From multipliers, we have 3, nums is [1, 2, 3], from 3 * 1 and 3 * 3, pick 3, add 3 * 3 = 9.
‣ From multipliers, we have 2, nums is [1, 2], from 2 * 1 and 2 * 2, pick 2, add 2 * 2 = 4.
‣ From multipliers, we have 1, nums is [1], add 1 * 1 = 1.

Total Score is 9+4+1=14, which is correct
However, it fails for the second example.

nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]

Taking Decision
‣ From multipliers, we have 10, nums is [-5,-3,-3,-2,7,1], from (-10) * (-5) and (-10) * 1, pick -5, add (-10) * (-5) = 50.   
‣ From multipliers, we have -5, nums is [-3,-3,-2,7,1], from (-5) * (-3) and (-5) * 1, pick -3, add (-5) * (-3) = 15.   
‣ From multipliers, we have 3, nums is [-3,-2,7,1], from 3 * (-3) and 3 * 1, pick 1, add 3 * 1 = 3.   
‣ From multipliers, we have 4, nums is [-3,-2,7], from 4 * (-3) and 4 * 7, pick 7, add 4 * 7 = 28.   
‣ From multipliers, we have 6, nums is [-3,-2], from 6 * (-3) and 6 * (-2), pick -2, add 6 * (-2) = -12.   

Total Score is 50+15+3+28+(-12)=84 which isn't optimal.   
102 is Optimal Solution as given in Problem Example.
The logical intuition of why it is not optimal can be deduced from the following two cases:

Greedy is short-sighted. For global optimum, we pick local optimum. But picking this Local Optimum may restrict greater positive product afterward.

nums = [-10,1,1000,1,1,100], multipliers = [1,1,1]
If we pick 100 over -10, we would never ever be able to collect 1000. There are only three elements in multipliers, and we can collect 1000 by taking the left
integers only. But selecting 100 at the first point restricts it. Moreover, what if both ends of nums are identical? We don't know which one to favor. One may 
yield another score, another may yield a very different score.

nums = [2, 1000, -1, 2], multipliers = [1, 1]
a. if we select Left 2 first, then at the next step, there would be a contest between Left 1000 and Right 2.
As per approach we now would select left 1000, obtaining 1002 as the answer.
b. if we select Right 2 first, then at the next step, there would be a contest between Left 2 and Right -1. As per approach we now would select left 2,
obtaining 4 as the answer.

Thus, these examples suggest that we have to look for all two possible combinations at each step:

Select nums[start], now problem reduces to another subproblem with nums being nums[start+1] to nums[end] and multipliers being multipliers[i+1] to multipliers[m-1].
Moreover, the number of operations is lessened by one.
Select nums[end], now problem reduces to another subproblem with nums being nums[start] to nums[end-1] and multipliers being multipliers[i+1] to multipliers[m-1].
Moreover, the number of operations is lessened by one.

We then have to solve these subproblems successively and at each step return the maximum of two possible answers. When all operations are done, we can return 0.

The trick here is that, although there are 3 variables - multipliers[i], left & end to be considered making it a 3-D DP problem, however we can reduce it to a 2-D
DP problem by the formulation -> end = (n - 1) - (i - left).
*/

class Solution {
    public int findMaxScore(int[] nums, int i, int left, int m, int[] mult,
                           Integer[][] memo) {
        if (i == m) return 0;
        if (memo[i][left] != null) return memo[i][left];
        memo[i][left] = Math.max(nums[left] * mult[i]
                                        + findMaxScore(nums, i + 1, left + 1, m, mult, memo),
                        nums[nums.length - 1 - i + left] * mult[i]
                                        + findMaxScore(nums, i + 1, left, m, mult, memo));
        return memo[i][left];
    }
    public int maximumScore(int[] nums, int[] multipliers) {
        int m = multipliers.length;
        int n = nums.length;
        Integer[][] memo = new Integer[m][n];
        return findMaxScore(nums, 0, 0, m, multipliers, memo);
    }
}
