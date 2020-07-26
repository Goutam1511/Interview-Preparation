/*
Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

Example:
Input: 38
Output: 2 
Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2. 
             Since 2 has only one digit, return it.
Follow up:
Could you do it without any loop/recursion in O(1) runtime?

Source : https://en.wikipedia.org/wiki/Digital_root

Solution : The digital root (also repeated digital sum) of a natural number in a given number base 
is the (single digit) value obtained by an iterative process of summing digits, on each iteration 
using the result from the previous iteration to compute a digit sum. The process continues until a 
single-digit number is reached.

Formula for the Digital root is : 
d(n) = 0                          if n == 0    b is the base of n
     = 1 + ((n - 1) mod (b - 1))  if n != 0    for decimals b is 10, b - 1 = 9
     
Proof : https://leetcode.com/articles/add-digits/
*/

class Solution {
public:
    int addDigits(int num) {
        return (1 + ((num - 1) % 9));
    }
};
