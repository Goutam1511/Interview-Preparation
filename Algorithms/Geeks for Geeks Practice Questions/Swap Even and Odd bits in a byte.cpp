#include <bits/stdc++.h>
using namespace std;

/*
Given an unsigned 8-bit integer, swap its even and odd bits. The 1st and 2nd bit should be swapped,
the 3rd and 4th bit should be swapped, and so on.

For example, 10101010 should be 01010101.

Bonus: Can you do this in one line?

Solution : https://www.dailycodingproblem.com/blog/neat-bitwise-trick/#:~:text=Solution,odd%20bitmask%20left%20by%20one.
*/

class Solution {
	public:
	char swapEvenOddBits(char x) {
		return ((x & 0b10101010) >> 1) | ((x & 0b01010101) << 1);
	}
};

int main() {
	// Swap Even and Odd bits in a Byte DailyCoding
	Solution s;
	char n = s.swapEvenOddBits(0b10101010);
	while (n) {
    if (n & 1)
        printf("1");
    else
        printf("0");
    	n >>= 1;
	}
	return 0;
}
