/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) and (i, 0). 
Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.

Notice that you may not slant the container.

Solution : The intuition behind this approach is that the area formed between the lines will always be limited by the height of the shorter line. Further, the farther the lines, the more will be the area obtained.

We take two pointers, one at the beginning and one at the end of the array constituting the length of the lines. 
Futher, we maintain a variable maxarea to store the maximum area obtained till now. At every step, we find out the area formed between them, 
update maxarea and move the pointer pointing to the shorter line towards the other end by one step.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int maxarea = 0;
        
        while (l < r) {
            maxarea = max((min(height[l], height[r]) * (r - l)), maxarea);
            if (height[r] > height[l]) {
                l++;
            } else {
                r--;
            }
        }
        
        return maxarea;
    }
};
