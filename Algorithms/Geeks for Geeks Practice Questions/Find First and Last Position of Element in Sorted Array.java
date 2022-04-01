/*
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].
You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109

Solution : Binary Search - search left for the element till we get the arr[mid] == target for first position and search right till we get arr[mid] == target
Time : O(logn) and Space : O(1)
*/

class Solution {
    public static int findFirst(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == target || arr[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        if (low < arr.length && arr[low] == target) {
            return low;
        }
        if (low < arr.length - 1 && arr[low + 1] == target) {
            return low + 1;
        }
        return -1;
    }
    
    public static int findLast(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        if (high >= 0 && arr[high] == target) {
            return high;
        }
        if (high > 0 && arr[high - 1] == target) {
            return high - 1;
        }
        return -1;
    }
    public int[] searchRange(int[] nums, int target) {
        int[] res = {-1, -1};
        res[0] = findFirst(nums, target);
        res[1] = findLast(nums, target);
        return res;
    }
}
