/* 
Counting Set Bits from 1 to N

Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their
binary representation and return them as an array.

Example 1:
Input: 2
Output: [0,1,1]
Example 2:
Input: 5
Output: [0,1,1,2,1,2]

SOLUTION APPROACH : The number of set bit in a mumber is = (the set bits in number /2) + 1 if the number is odd.

VISUAL DRY RUN : 
num               set bits              remarks
 0                    0
 1                    1                 set bits of 0 + 1 for being odd number
 2                    1                 set bits of 1 + 0 for being even number
 3                    2                 set bits of 1 + 1 for being odd number
 .                    .                               .
 .                    .                               .
 .                    .                               .
 7                    3                 set bits of 3 + 1 for being odd number
*/


class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1);
        int i = 0;
        res[0] = 0;
        for (i = 1; i <= num; i++) {
            res[i] = res[i / 2] + (i % 2); //(num % 2);
            //cout<<res[i]<<endl;
        }
        return res;
    }
};
