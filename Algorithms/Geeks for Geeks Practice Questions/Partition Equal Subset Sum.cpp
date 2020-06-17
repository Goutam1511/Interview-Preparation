/*
Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of 
elements in both subsets is equal.

Note:
    Each of the array element will not exceed 100.
    The array size will not exceed 200.

Example 1:

Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:

Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.

Solution : The problem is similar to Subset Sum : (https://www.geeksforgeeks.org/subset-sum-problem-dp-25/). The only exception is
here explicitly sum is not mentioned but sum is sum of all elements in array / 2. Hence, if the array sum is odd, we return false
else we find if the array has an subset = array sum / 2. If it has such subset, then the remaining set will automatically be having
its sum as array sum / 2.

Subset Sum DP solution : So we will create a 2D array of size (arr.size() + 1) * (target + 1) of type boolean. The state DP[i][j]
will be true if there exists a subset of elements from A[0….i] with sum value = ‘j’. The approach for the problem is:

if (A[i] > j)
DP[i][j] = DP[i-1][j]
else 
DP[i][j] = DP[i-1][j] OR DP[i-1][sum-A[i]]

This means that if current element has value greater than ‘current sum value’ we will copy the answer for previous cases
And if the current sum value is greater than the ‘ith’ element we will see if any of previous states have already experienced the
sum=’j’ OR any previous states experienced a value ‘j – A[i]’ which will solve our purpose.

The below simulation will clarify the above approach:

set[]={3, 4, 5, 2}
target=6
 
    0    1    2    3    4    5    6

0   T    F    F    F    F    F    F

3   T    F    F    T    F    F    F
     
4   T    F    F    T    T    F    F   
      
5   T    F    F    T    T    T    F

2   T    F    T    T    T    T    T

End output : table[n][sum]
*/

class Solution {
public:
     bool SubsetSum(int a[], int n, int sum) { //Finding if subset of sum / 2 exists
        int i = 0, j = 0;
        bool table[201][20000] = {false};

        table[0][0] = true;
        for (i = 1; i <= sum; i++) {
            table[0][i] = false;
        }
        for (i = 1; i <= n; i++) {
            table[i][0] = true;
        }
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= sum; j++) {
                if (a[i] > j) {
                    table[i][j] = table[i - 1][j];
                } else {
                    table[i][j] = table[i - 1][j] || table[i - 1][j - a[i]];
                }
            }
        }
        return table[n][sum];
    }
    
    bool canPartition(vector<int>& nums) {
        int a[nums.size() + 1], sum = 0, i = 0;
	    a[0] = 0;
	    for (i = 1; i <= nums.size(); i++) {
	        a[i] = nums[i - 1];
	        sum += a[i];
	    }
	    if (sum % 2) { //Check if array sum is odd
	        return false; 
	    } else { //Find if subset of sum/2 exists
	        return SubsetSum(a, nums.size(), sum / 2);
	    }
    }
};
