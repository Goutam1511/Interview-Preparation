/*
Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:

Input: [10,2]
Output: "210"
Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
Note: The result may be very large, so you need to return a string instead of an integer.

**Solution :**
**Intuition**
To construct the largest number, we want to ensure that the most significant digits are occupied by the largest digits.

**Algorithm**
First, we convert each integer to a string. Then, we sort the array of strings.

While it might be tempting to simply sort the numbers in descending order, this causes problems for sets of numbers with the same leading digit.
For example, sorting the problem example in descending order would produce the number 95343039534303, while the correct answer can be achieved by
transposing the 33 and the 3030. Therefore, for each pairwise comparison during the sort, we compare the numbers achieved by concatenating the pair 
in both orders. We can prove that this sorts into the proper order as follows:

Assume that (without loss of generality), for some pair of integers a and b, our comparator dictates that aa should precede bb in sorted order.
This means that a⌢b>b⌢a (where ⌢ represents concatenation). For the sort to produce an incorrect ordering, there must be some c for which b 
precedes c and c precedes a. This is a contradiction because aa⌢b>b⌢a and b⌢c>c⌢b implies a⌢c>c⌢a. In other words, our custom comparator 
preserves transitivity, so the sort is correct.

Once the array is sorted, the most "signficant" number will be at the front. There is a minor edge case that comes up when the array consists of 
only zeroes, so if the most significant number is 00, we can simply return 00. Otherwise, we build a string out of the sorted array and return it.
*/

class Solution {
public:
    static bool comp(int a, int b) { //Compare the concatenated number lexicographically
        if (to_string(a) + to_string(b) < to_string(b) + to_string(a)) {
            return false;
        }
        return true;
    }
    
    string largestNumber(vector<int>& vec) {
        bool allzero = false;
        
        if (vec.size() == 0) {
            return "";
        }
        
        for (int i : vec) { //Check if the vector doesn't have all zeroes
            if (i) {
                allzero = true;
                break;
            }
        }
        
        if (!allzero) //If all items are zero return a single digited "0"
            return "0";
        
        sort(vec.begin(), vec.end(), Solution::comp);
        
        /* Convert vector of sorted numbers into a single string that represents the largest number */
        std::ostringstream vts; 
  
      if (!vec.empty()) 
      { 
        // Convert all but the last element to avoid a trailing "," 
        std::copy(vec.begin(), vec.end()-1, 
            std::ostream_iterator<int>(vts, "")); 

        // Now add the last element with no delimiter 
        vts << vec.back(); 
      } 

      std::cout << vts.str() << std::endl;
        return vts.str();
    }
};
