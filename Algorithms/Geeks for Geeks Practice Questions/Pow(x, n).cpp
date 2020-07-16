/*
Implement pow(x, n), which calculates x raised to the power n (xn).

Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100
Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
Note:
-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−231, 231 − 1]

Solution : The concept is simple. Once you have computed pow(x, n / 2). No need to compute from n/2 to n. Just multiply result of pow(x, n/2) with itself.
Because as we know for x^n = x^(n/2) * x^(n/2). Note when n is odd, we need to multiply the result of pow(x, n/2) with another x as dividing n/2 when n is
odd, truncates the value to 1 less. Hence, recursively go on computing the result until n = 1 or n = 0 which are the base cases. Also we have to take care
the cases of n > 0 & n < 0 seperately.

Time Complexity : O(log n).
*/

class Solution {
public:
    double myPow(double x, int n) {
        double res = 1;
        double temp;
        
        if (n == 0)
            return 1;
        
        if (n == 1)
            return x;
        
        if (n == -1)
            return (1 / x);
        
        temp = myPow(x, n/2);
        res  = temp * temp;
        
        if (n % 2) {
            if (n < 0) {
                res = res * (1 / x);
            } else {
                res = res * x;
            }
        }
        
        return res;
    }
};
