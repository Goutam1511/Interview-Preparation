/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. 
Assume that there is only one duplicate number, find the duplicate one.

Example 1:

Input: [1,3,4,2,2]
Output: 2

Example 2:

Input: [3,1,3,4,2]
Output: 3

Note:
    You must not modify the array (assume the array is read only).
    You must use only constant, O(1) extra space.
    Your runtime complexity should be less than O(n2).
    There is only one duplicate number in the array, but it could be repeated more than once.

Solution : The problem is actually reducible to Linked List Cycle Detection. Check https://leetcode.com/problems/find-the-duplicate-number/solution/
Without the strict constraints - other approaches could be using Hashing to go on storing elements in a set and whenever an element is found to be 
already existing, then that element is the required element. Space Complexity : O(n).
Other way is to sort the array, whenever adjacent elements are found same, then that is the duplicate. Here, the array is modified and time 
complexity : O(nlogn) for sorting.
Another approach to the problem if the following - There is only one duplicate number in the array, but it could be repeated more than once was not
there could be summing the whole array up in a variable and substracting that from (n * (n + 1)) / 2, as it is told the array has elements 1 to n
inclusive, so if there is only one duplicate number then the extra duplicate will be the result of substraction.
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int i = 0;
        
        int slow = nums[0], fast = nums[0];
        
        if (nums.size() == 2) { //If 2 elements only, then any one is duplicate
            return nums[1];
        }
        
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while(slow != fast); //Linked List loop detection - phase 1
        
        slow = nums[0]; //Move slow ptr to start
        
        while (slow != fast) { //Both ptr now moves 1 node at a time. Fast ptr start from intersection point
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
};
