#include <bits/stdc++.h>
using namespace std;

/*
 Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible. 
 Note:
 The length of num is less than 10002 and will be ≥ k.
 The given num does not contain any leading zero.

 Example 1: 
 Input: num = "1432219", k = 3
 Output: "1219"
 Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

 Example 2: 
 Input: num = "10200", k = 1
 Output: "200"
 Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

 Example 3: 
 Input: num = "10", k = 2
 Output: "0"
 Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 
 Solution : UPDATE 22/06/2022 - A better solution would be to use a monotonic stack and whenever we encounter a larger number than stack top, go on popping
 until we encounter a smaller number in top of stack or we exhaust the number of digits that can be removed. We do this because as long as there is a larger
 number in left, we can never make a smaller number removing digits in right.
 
 EDGE CASES : After removal of k digits, check for leading zeroes.
 
 Time and Space : O(number of digits)
 
 class Solution {
    public String removeKdigits(String num, int k) {
        if (k == num.length()) {
            return "0";
        }
        Stack<Character> s = new Stack<>();
        for (char c : num.toCharArray()) {
            while (!s.isEmpty() && s.peek() > c && k > 0) {
                s.pop();
                k--;
            }
            s.push(c);
        }
        while (k-- > 0 && !s.isEmpty()) {
            s.pop();
        }
        String res = "";
        while (!s.isEmpty()) {
            res = String.valueOf(s.pop()) + res;
        }
        //System.out.println(res);
        int i = 0;
        while (i < res.length() && res.charAt(i) == '0') {
            i++;
        }
        if (i < res.length())
            return res.substring(i);

        return "0";
    }
}
 */

class Solution {
public:
    static bool comp(pair<int, int> p1, pair<int, int> p2) {
        return p1.first > p2.first;
    }
    
    string removeKdigits(string num, int k) {
        int i = 0, j = 0;
        if (num.length() <= k)
            return "0";
        else {
            while (k--) {
                bool flag = false;
                for (i = 1; i < num.length(); i++) {
                    if (num[i] < num[i - 1]) {
                        num.erase(num.begin() + i - 1);
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    num.erase(num.end() - 1);
                }
            }
            while (num[0] == '0') {
                num.erase(num.begin());
            }
        }
        if (num.length() == 0) {
            return "0";
        }
        return num;
    }
};

/* Solution taken from : https://medium.com/@saurav.agg19/remove-k-digits-8d5aa221751a */

int main() {
	// Remove K digits LeetCode May Challenge
	return 0;
}
