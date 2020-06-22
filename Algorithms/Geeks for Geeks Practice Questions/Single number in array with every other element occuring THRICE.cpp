/*
Given a non-empty array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,3,2]
Output: 3

Example 2:

Input: [0,1,0,1,0,1,99]
Output: 99

NOTE : Here the XOR trick or marking each element negative will not work as the elements are occuring thrice i.e odd number of times.

Solution : The approach is towards bitwise manipulation. The mathematics behind the solution is that, if every element occurs thrice, then
it will contribute 3 0 or 3 1s in every bit position considering the number is a 32 or m bit integer. Then if all element occurs 3 times &
1 element occurs 1 time, then if we take the sum of all 0s and 1s in a bit position, we should have 3x + 1 or 3x number of 1s. 3x comes from
all the element occuring thrice, and extra 1 depends on whether the single element has 1 or 0 in that bit position. So like this, if we
calculate all the sum of number of 1s in every bit position and store the individual count in a 32/m bit array, then each element in the array
will be either 3x + 1/3x and if we take the modulus of these counts, then we are essentially getting back the binary representation of the number
that is single. We can easily get back the number from the binary representation which is our output

VISUAL DRY RUN :

1) Input: [2,2,3,2]
                   position |--> 1 0
                   -----------------
                          2 |--> 1 0
                          2 |--> 1 0
                          3 |--> 1 1
                          2 |--> 1 0
Count of 1s in each position --> 4 1  (4 in position 1 --> 3 from 2 occuring thrice & 1 from single 3, 
                                       1 in position 0 --> 1 from single 3, 3 0s from 2)
Count of 1s after modulus 3  --> 1 1 ---> binary representation of 3

Output: 3

2) Input: [0,1,0,1,0,1,10]
                   position |--> 3 2 1 0
                   -----------------------
                          0 |--> 0 0 0 0
                          1 |--> 0 0 0 1
                          0 |--> 0 0 0 0
                          1 |--> 0 0 0 1
                          0 |--> 0 0 0 0
                          1 |--> 0 0 0 1
                         10 |--> 1 0 1 0
Count of 1s in each position --> 1 0 1 3 (0th position : 3 1s from 1,
                                          1th position : 1 1 from 10,
                                          2nd position : 0 1s,
                                          3rd position : 1 1 from 10)
Count of 1s after modulus 3  --> 1 0 1 0 (binary representation of 10)

Output: 10
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int bitwisecount[sizeof(int) * 8] = {0}; //Array to store the sum count of 1 in each bit position
        int result = 0;
        long int i = 0, bitpos = 0;
        
        for (bitpos = 0; bitpos < sizeof(int) * 8; bitpos++) { //Iterate over each bit position
            for (i = 0; i < nums.size(); i++) { //Iterate over the array
               /* Find if the current array element has 1 in  *
                * the currently bit position being calculated */
                if (nums[i] % 2) { 
                    bitwisecount[bitpos]++; //If yes, increase the bitwise 1 count at that bit position
                }
                nums[i] = nums[i] >> 1; //Right shift the number and make it ready for next bit position
            }
        }
        
        for (bitpos = 0; bitpos < sizeof(int) * 8; bitpos++) {
            /* Calculate the modulus of 3 in each bit position   *
             * Simulataenously, form the required single element */
            bitwisecount[bitpos] = bitwisecount[bitpos] % 3;
            result += (bitwisecount[bitpos] * (long int)pow(2, bitpos));
        }
        
        return result;
    }
};
