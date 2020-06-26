/*
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:

Input: [1,2,3]
Output: 6

Example 2:

Input: [1,2,3,4]
Output: 24

Note:
    The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
    Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.
    
Corner Cases :

Input:  [-10, -3, -5, -6, -20] (No positive integer)
Output: -90 (-3 * -5 * -6)

Input:  [1, -4, 3, -6, 7, 0] (Both positive and negative integers)
Output: 168 (-4 * -6 * 7)

Input: [-1, 2, 3, 6] (Only one single -ve integer)
Output: 36

Solution : In this case, when both +ve & -ve integers are present, the maximum product can come from an array in either of 2 ways -
1) From 2 greatest negative integers and 1 positive integer OR 2) From 3 positive integers. In case, 2 -ve integers are not there,
the maximum product will always come from 3 positive integers. In case where no positive integers are present, then max product is
the product of smallest 2 inetegers. For these observations, refer the corner cases.

However, in our case, we need not handle all these cases seperately, the easiest approach is to first sort the array in order of 
magnitude and then start from last and traverse the array from back and find out the 2 largest -ve integers by magnitude & largest
positive integer by magnitude. If these are found then compare the product of these 3 with product of largest 3 positive integers 
after sorting the array normally. Else, if these are not found, simply return the product of last 3 elements of sorted array.

Time Complexity : O(nlogn) for sorting.
*/

class Solution {
public:
    static bool compare(int a, int b) { //Comparator function to sort by magnitude
        return abs(a) < abs(b);
    }
    
    int maximumProduct(vector<int>& nums) {
        int i = 0, largestneg = INT_MAX, seclargestneg = INT_MAX, largestpos = INT_MIN;
        bool largestnegset = false, seclargestnegset = false, largestposset = false;
        bool all3f = false;
        int largestprod = INT_MIN;
        
        if (nums.size() == 3) { //If size is 3, there is only 1 product which is largest
            return nums[0] * nums[1] * nums[2];
        }
        
        sort(nums.begin(), nums.end(), compare); //Sort by magnitude.
        
        /* Debug prints
        for (i = 0; i < nums.size(); i++) {
            cout<<nums[i]<<" ";
        }
        cout<<endl;*/
        
        /* Find the largest and second largest -ve number by magnitude *
         * and find the largest positive integer in the array          */
        for (i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] < 0) { //If number is negative
                if (!largestnegset) { //If we haven't found the largest negative yet
                    largestneg = nums[i];
                    largestnegset = true;
                } else if (!seclargestnegset) { //If we haven't found second largest negative yet
                    seclargestneg = nums[i];
                    seclargestnegset = true;
                }
            } else { //Number is positive
                if (!largestposset) { //If we haven't found largest positive yet.
                    largestpos = nums[i];
                    largestposset = true;
                }
            }
            if (largestnegset && seclargestnegset && largestposset) { //If all 3 found
                all3f = true;
                break;
            }
        }
        
        if (all3f) { //Find product of 2 largest negatives and largest positive
            largestprod = largestneg * seclargestneg * largestpos;
        }
        
        //cout<<largestprod<<endl;
        sort(nums.begin(), nums.end(), greater<int>()); //Sort in descending order
        
        /* Compare whether product of 2 largest negative & largest *
         * positive is greater than the 3 largest positive numbers */
        if (largestprod > nums[0] * nums[1] * nums[2]) {  
            return largestprod;
        } else {
            return nums[0] * nums[1] * nums[2];
        }
    }
};
