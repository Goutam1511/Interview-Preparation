/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being
trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9

Constraints:

n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5

Solution : One intuitive solution is to have 2 arrays store the left-most maximum till block[i] including block[i] & right-most maximum till block[i] including block[i]
& then sum of Math.min(left[i], right[i]) - block[i] would the answer. This works because we can trap water only in pockets and pockets are formed by the left most
maximum boundary height and right most maximum boundary height and the minimum of them determines the water level. However, we can optimise this on the fact that 
we don't really need to keep track of all the leftmost maximums or right most maximum in form of array. Instead if we always take into the consideration that we
consider elements using two pointers and we take the lower of left & right elements, then we know there is always a higher boundary on the other side since we are
considering the smaller of left and right and depending on we take the left or right element, we can substract the leftmax - arr[i] or rightmax - arr[i] to get the
trapped water.

Time : O(n)
Space : O(1)
*/

class Solution {
    public int trap(int[] height) {
        int l = 0, r = height.length - 1, maxLeft = 0, maxRight = 0, water = 0;
        
        while (l < r) {
            if (height[l] < height[r]) { // we take the lower height so that we know the other one will always help making the pocket
              // we now only need to consider the left most maximum because we know there is a right maximum which is greater than the left maximum
                maxLeft = Math.max(maxLeft, height[l]);
                water += (maxLeft - height[l++]);
            } else {
                maxRight = Math.max(maxRight, height[r]);
                water += (maxRight - height[r--]);
            }
        }
        
        return water;
    }
}
