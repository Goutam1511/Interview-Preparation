/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
Example 3:

Input: s = ""
Output: 0

Constraints:
0 <= s.length <= 3 * 104
s[i] is '(', or ')'.

Solution : Instead of finding every possible string and checking its validity, we can make use of a stack while scanning the given string to:
1. Check if the string scanned so far is valid.    2. Find the length of the longest valid string.
In order to do so, For every ‘(’ encountered, we push its index onto the stack. For every ‘)’ encountered, we check if the topmost element. 
If it is a '(', then, we pop and update the length of the currently encountered valid string of parentheses which will be the difference 
between the current element's index and the top element of the stack after popping. If stack is empty after popping then, till this point whole
string was valid. In this way, we can continue to calculate the length of the valid substrings and return the length of the longest valid string at the end.
If for a ')', the topmost element of stack is not '(', we push into stack.

Time and Space Complexity : O(n).

Check out other optimal solutions - https://leetcode.com/problems/longest-valid-parentheses/solution/
*/

class Solution {
    static class pair {
        int i;
        char c;
        
        pair(int i, char c) {
            this.i = i;
            this.c = c;
        }
    }
    public int longestValidParentheses(String s) {
        Stack<pair> st = new Stack<>();
        int maxLen = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == ')' && !st.isEmpty() && st.peek().c == '(') {
                st.pop();
                if (!st.isEmpty()) {
                    maxLen = Math.max(i - st.peek().i, maxLen);
                } else {
                    maxLen = Math.max(i + 1, maxLen);
                }
            }
            else {
                st.push(new pair(i, c));
            }
        }
        return maxLen;
    }
}
