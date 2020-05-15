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
