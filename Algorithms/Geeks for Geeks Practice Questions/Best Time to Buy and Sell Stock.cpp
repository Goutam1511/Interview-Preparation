/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

Solution : We need to find out the maximum difference (which will be the maximum profit) between two numbers in the given array. 
Also, the second number (selling price) must be larger than the first one (buying price). In formal terms, we need to find 
max⁡(prices[j]−prices[i]) for every i and j such that j > i. This can be achieved by storing the minimum value seen so far till i
by maintaining an array leftsmallest and the maximum value seen from i to end of array by maintaining rightgreatest. Leftsmallest
will be populated by going from left to right and Rightgreatest will be populated by traversing from end to start of prices array.
At any point i, difference between Rightgreatest[i] - leftsmallest[i] will give the max profit that can be obtained selling on ith
day. Traversing one more time to track the maximum that can be gained at any i will give the required maximum desired profit.
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int i = 0;
        vector<int> leftsmallest(prices.size(), 0);
        vector<int> rightgreatest(prices.size(), 0);
        int maxm = INT_MIN; 
        
        if (prices.size() == 0)
            return 0;
        
        if (prices.size() == 1)
            return 0;
        //Build the leftsmallest array to store smallest value till 0 to i
        leftsmallest[0] = prices[0];
        for (i = 1; i < prices.size(); i++) {
            leftsmallest[i] = leftsmallest[i - 1] < prices[i] ? leftsmallest[i - 1] : prices[i];
        }
        
        //Build the rightgreatest array to store greatest value from i to end of array 
        rightgreatest[prices.size() - 1] = prices[prices.size() - 1];
        for (i = prices.size() - 2; i >= 0; i--) {
            rightgreatest[i] = rightgreatest[i + 1] > prices[i] ? rightgreatest[i + 1] : prices[i];
        }
        
        //Find the greatest difference at any point in the array to obtain the maximum profit
        for (i = 0; i < prices.size(); i++) {
            maxm = max(maxm, rightgreatest[i] - leftsmallest[i]);
        }
        return maxm;
    }
};

/*
More Optimised One Pass Solution : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/solution 

public class Solution {
    public int maxProfit(int prices[]) {
        int minprice = Integer.MAX_VALUE;
        int maxprofit = 0;
        for (int i = 0; i < prices.length; i++) {
            if (prices[i] < minprice)
                minprice = prices[i];
            else if (prices[i] - minprice > maxprofit)
                maxprofit = prices[i] - minprice;
        }
        return maxprofit;
    }
}
*/


