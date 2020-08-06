/*
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

Solution : The catch lies in the fact 1 ≤ a[i] ≤ n. We can simply iterate and change the values at nums[abs(nums[i]) - 1] to -ve of its value.
So next time if we encounter a -ve value at nums[abs(nums[i]) - 1], we would know that element must have been modified once before so nums[i] is duplicate.
*/

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[abs(nums[i]) - 1] < 0) { //The element must have been modified before that's why became negative
                res.push_back(abs(nums[i])); //Push duplicate element
            } else {
                nums[abs(nums[i]) - 1] = -1 * nums[abs(nums[i]) - 1]; //Mark the element at that position as negative
            }
        }
        return res;
    }
};
