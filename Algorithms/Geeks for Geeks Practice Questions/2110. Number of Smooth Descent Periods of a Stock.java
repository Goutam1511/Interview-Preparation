/*
You are given an integer array prices representing the daily price history of a stock, where prices[i] is the stock price on the ith day.
A smooth descent period of a stock consists of one or more contiguous days such that the price on each day is lower than the price on the preceding day by exactly 1.
The first day of the period is exempted from this rule.

Return the number of smooth descent periods.

Example 1:

Input: prices = [3,2,1,4]
Output: 7
Explanation: There are 7 smooth descent periods:
[3], [2], [1], [4], [3,2], [2,1], and [3,2,1]
Note that a period with one day is a smooth descent period by the definition.
Example 2:

Input: prices = [8,6,7,7]
Output: 4
Explanation: There are 4 smooth descent periods: [8], [6], [7], and [7]
Note that [8,6] is not a smooth descent period as 8 - 6 ≠ 1.
Example 3:

Input: prices = [1]
Output: 1
Explanation: There is 1 smooth descent period: [1] 

Constraints:

1 <= prices.length <= 10^5
1 <= prices[i] <= 10^5

Solution : Forget about stock and other stories. The problem is simply number of subarrays having difference between consecutive elements as 1 and elements are
decreasing. We know for an array with n elements, number of subarrays = n * (n + 1) / 2. We keep on iterating and while iterating we increment the counter as long
as the current element is lesser than previous element by 1 else we add counter * (counter + 1) / 2 to result and we reset the counter to 1. Last thing to take care
is to add the (counter * (counter + 1) / 2) to result at end to account for the last element.

Time : O(N) Space : O(1)
*/

class Solution {
    public long getDescentPeriods(int[] prices) {
        long lastPrice = -1, counter = 0, res = 0;
        for (int price : prices) {
            if (lastPrice - price == 1) {
                counter++;
            } else {
                res += (counter * (counter + 1) / 2);
                counter = 1;
            }
            lastPrice = price;
        }
        res += (counter * (counter + 1) / 2);
        return res;
    }
}
