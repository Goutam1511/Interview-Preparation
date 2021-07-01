/*
An n-bit gray code sequence is a sequence of 2n integers where:

Every integer is in the inclusive range [0, 2n - 1],
The first integer is 0,
An integer appears no more than once in the sequence,
The binary representation of every pair of adjacent integers differs by exactly one bit, and
The binary representation of the first and last integers differs by exactly one bit.
Given an integer n, return any valid n-bit gray code sequence. 

Example 1:

Input: n = 2
Output: [0,1,3,2]
Explanation:
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
[0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
- 00 and 10 differ by one bit
- 10 and 11 differ by one bit
- 11 and 01 differ by one bit
- 01 and 00 differ by one bit
Example 2:

Input: n = 1
Output: [0,1]

Constraints:

1 <= n <= 16

Solution : Consider the sequence generated for n = 0 to 3.
For n = 0 the Gray code sequence is [0].
For n = 1 the Gray code sequence is [0, 1].
Similarly, we had [0, 1] from n = 1 and for n = 2 the Gray code sequence is [00, 01, 11, 10].
By observing the sequences generated with n = 0, 1, 2.... we will find a pattern. We can obtain the Gray code sequence for n from the Gray code sequence for n - 1.
For example the Gray code sequence for n = 3 is [000, 001, 011, 010, 110, 111, 101, 100] (G(3)).
This sequence can be obtained from the sequence [00, 01, 11, 10](say G(2)) for n = 2 as follows :
Add 0 to the (n - 1) th position (0 based indexed, the 2nd bit from the right) to the entire sequence of G(2). [00, 01, 11, 10] -> [000, 001, 011, 010] (G(3a)).
Reverse G(2) sequence and add 1 (1 << n - 1) to the (n - 1)th position (the 2nd bit from the right) [00, 01, 11, 10] -> [10, 11, 01, 00] -> [110, 111 101, 100] (G(3b)).
Concatenate G(3a) and G(3b) to get the Gray code sequence for n = 3 (G(3)) : [000, 001, 011, 010, 110, 111, 101, 100]

Algorithm
Initialize an empty list result and add 00 to it.
Since the Gray code sequence for i bits (G(i)) can be constructed from the Gray code sequence for i - 1 bits (G(i - 1)), 
we run a for loop from i = 1 to n to find Gray code sequences with increasing bits.
At each iteration, we set the bit at (i - 1) th position and assign it to a variable mask. mask is used to set the (i - 1) th bit from the LSB 
of all the numbers present in the current sequence result (G(i - 1)).
Iterate backward over the current sequence result. Add prefix 1 (mask) to each number present in result.
Return result which represents the Gray code sequence with n total bits.
*/

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        result.push_back(0);
        
        for (int i = 1; i <= n; i++) {
            int previousSequenceLength = result.size();
            int mask = 1 << (i - 1);
            for (int j = previousSequenceLength - 1; j >= 0; j--) {
                result.push_back(mask + result[j]);
            }
        }
        return result;
    }
};
