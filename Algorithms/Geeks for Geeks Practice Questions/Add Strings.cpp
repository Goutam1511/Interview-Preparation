/*
Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.
You must solve the problem without using any built-in library for handling large integers (such as BigInteger).
You must also not convert the inputs to integers directly.

Example 1:

Input: num1 = "11", num2 = "123"
Output: "134"
Example 2:

Input: num1 = "456", num2 = "77"
Output: "533"
Example 3:

Input: num1 = "0", num2 = "0"
Output: "0"

Constraints:

1 <= num1.length, num2.length <= 104
num1 and num2 consist of only digits.
num1 and num2 don't have any leading zeros except for the zero itself.

Solution : Just do manual addition from last digit till first in the way human addition works(keep carry in mind).
Edge cases :
1. "456" --> Uneven length strings. Carry to be propagated and one string ended. (trick is to consider carry even when one string has ended)
   "77"
2. "1" --> Check for extra carry at the end of addition
   "9"
*/

class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, carry = 0;
        string result;
        
        while (i >= 0 && j >= 0) {
            int numi = num1[i] - '0';
            int numj = num2[j] - '0';
            cout<<numi<<" "<<numj<<endl;
            
            if (numi + numj + carry > 9) {
                int div = (numi + numj + carry) % 10;
                carry =  (numi + numj + carry) / 10;
                result = to_string(div) + result;
            } else {
                result = to_string(numi + numj + carry) + result;
                carry = 0;
            }
            i--;
            j--;
        }
        
        while (i >= 0) {
            int numi = num1[i--] - '0';
            if (numi + carry > 9) {
                int div = (numi + carry) % 10;
                carry =  (numi + carry) / 10;
                result = to_string(div) + result;
            } else {
                result = to_string(numi + carry) + result;
                carry = 0;
            }
        }
        while (j >= 0) {
            int numj = num2[j--] - '0';
            if (numj + carry > 9) {
                int div = (numj + carry) % 10;
                carry =  (numj + carry) / 10;
                result = to_string(div) + result;
            } else {
                result = to_string(numj + carry) + result;
                carry = 0;
            }
        }
        
        return carry != 0 ? to_string(carry) + result : result;
    }
};
