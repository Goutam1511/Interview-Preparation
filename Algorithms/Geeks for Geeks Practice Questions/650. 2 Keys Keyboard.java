/*
There is only one character 'A' on the screen of a notepad. You can perform one of two operations on this notepad for each step:
Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.

Example 1:

Input: n = 3
Output: 3
Explanation: Initially, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
Example 2:

Input: n = 1
Output: 0

Constraints:
1 <= n <= 1000

Solution : The solution can be derived only by looking at the tags of the problem & the hints. I couldn't come up with the DP solution rather the tags and the hints
of discuss helped come up with the Mathematical solution. We can crack the pattern if we look at 5-10 examples -

1 = 0 ---> this is the base case
2 = 2^1 --> 2 * 1 = 2
3 = 3^1 --> 3 * 1 = 3
4 = 2^2 --> 2 * 2 = 4
5 = 5^1 --> 5 * 1 = 5
6 = 2^1 * 3^1 --> 2 * 1 + 3 * 1 = 5
10 = 2^1 * 5^1 --> 2 * 1 + 5 * 1 = 7
12 = 2^2 * 3^1 --> 2 * 2 + 3 * 1 = 7
24 = 2^3 * 3^1 --> 2 * 3 + 3 * 1 = 9
63 = 3^2 * 7^1 --> 3 * 2 + 7 * 1 = 13

Clearly we can find the mathematical pattern is minimum ops for n = sum of (prime factors * their powers)

Time : O(square root of n) Space : O(1)
*/

class Solution {
    public static int[] findPrimeFactors(int n)
    {
        int[] primeFactors = new int[n + 1];
        if (n == 1) return primeFactors;
        int cnt = 0;
        
        while (n % 2 == 0)
        {
            cnt++;
            n /= 2;
        }
        primeFactors[2] = cnt;

        // n must be odd at this point.  So we can
        // skip one element (Note i = i +2)
        for (int i = 3; i <= Math.sqrt(n); i += 2)
        {
            cnt = 0;
            // While i divides n, print i and divide n
            while (n%i == 0)
            {
                cnt++;
                n /= i;
            }
            primeFactors[i] = cnt;
        }
 
        // This condition is to handle the case when
        // n is a prime number greater than 2
        if (n > 2)
            primeFactors[n]++;
        
        return primeFactors;
    }
    public int minSteps(int n) {
        int[] factors = findPrimeFactors(n);
        int res = 0;
        for (int i = 1; i <= n; i++) {
            res += (i * factors[i]);
        }
        
        return res;
    }
}
