#include <bits/stdc++.h>
using namespace std;

/*

Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4

SOLUTION APPROACH : Xor of 2 same numbers is 0. Xor of 0 and a number is the number. Xor is associative. Hence, x xor y xor z xor y xor z = x.
Using this we, find the xor of whole array, same numbers zeroes out leaving the only single number.

*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = nums[0], i = 0;
        
        for (i = 1; i < nums.size(); i++) {
            res = res ^ nums[i];
        }
        return res;
    }
};

int main() {
	// Single Number LeetCode
	return 0;
}
