/*
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

Solution Approach : The problem approach is similar to https://www.geeksforgeeks.org/given-an-array-a-and-a-number-x-check-for-pair-in-a-with-sum-as-x/
 
There can be two cases arising while trying to find the longest subarray with equal 0 and 1s.
1) Starting from index 0 we go on checking the number of 0s & 1s. For sake of simplicity, we can replace or consider all 0s with -1s so that if at any
point sum is 0 then it indicates equal 0s and 1s. Now, if at that point length of the subarray from index 0 might be the maximum subarray length having
equal 0s & 1s.
2) Another possibility is the longest subarray starts from some other index greater than 0. To evaluate this, we should go on storing all the sums we
encounter while traversing the binary array in a hashmap. If at any point, we encounter a sum already present in the map, that indicates the number of
0s and 1s from the point where the sum was first encountered till the current point where we're encountering the sum again is same. So we should consider
the length of array between these two points.

Check : https://leetcode.com/problems/contiguous-array/solution/

Time Complexity : O(n)
Space Complexity : O(n)

*/



class Solution {
    public int findMaxLength(int[] nums) {
          
        HashMap<Integer, Integer> hM 
            = new HashMap<Integer, Integer>(); 
        int n= nums.length;
        int sum = 0; 
        int max_len = 0; 
        int ending_index = -1; 
        int start_index = 0; 
  
        //Replacing 0 with -1 for simplicity
        for (int i = 0; i < n; i++) { 
            nums[i] = (nums[i] == 0) ? -1 : 1; 
        } 
  
        for (int i = 0; i < n; i++) {   
            sum += nums[i]; 
  
            //First Case
            if (sum == 0) { 
                max_len = i + 1; 
                ending_index = i; 
            }

            //Second Case : Search for Sum, if present find length between the two points else put the current index and sum in Map  
            if (hM.containsKey(sum)) { 
                if (max_len < i - hM.get(sum)) { 
                    max_len = i - hM.get(sum); 
                    ending_index = i; 
                } 
            } 
            else {
                 hM.put(sum, i); 
            }  
        } 
  
        for (int i = 0; i < n; i++) { 
            nums[i] = (nums[i] == -1) ? 0 : 1; 
        } 
  
        int end = ending_index - max_len + 1; 
        System.out.println(end + " to " + ending_index); 
  
        return max_len;    
    }
}
