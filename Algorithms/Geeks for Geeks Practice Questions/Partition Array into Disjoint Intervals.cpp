/*
Given an array nums, partition it into two (contiguous) subarrays left and right so that:

Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.

Example 1:

Input: nums = [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
Example 2:

Input: nums = [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]

Note:

2 <= nums.length <= 30000
0 <= nums[i] <= 106
It is guaranteed there is at least one way to partition nums as described.

Complexity : O(n)
Solution : Find out the minimum element at right side and the maximum element on left side for each index. If the
maximum element of left side for an index is less or equal to the minimum element on right side, then definitely
every element in the left set will be less or equal to every element on right set. Hence, return that index + 1.
*/

class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        vector<int> minimum_right(nums.size(), 0);
        vector<int> maximum_left;
        int i = 0;
        
        int max_so_far = nums[0];
        maximum_left.push_back(nums[0]);
        for (i = 1; i < nums.size(); i++) { //Maximum element on left for each index
            if (nums[i] > max_so_far) {
                max_so_far = nums[i];
            }
            maximum_left.push_back(max_so_far);
        }
        int min_so_far = nums[nums.size() - 1];
        minimum_right[nums.size() - 1] = nums[nums.size() - 1];
        for (i = nums.size() - 2; i >= 0; i--) { //Minimum element on right for each index
            if (nums[i] < min_so_far) {
                min_so_far = nums[i];
            }
            minimum_right[i] = min_so_far;
        }
        
        /*for (int j : maximum_left) {
            cout<<j<<" ";
        }
        cout<<endl;
        for (auto j : minimum_right) {
            cout<<j<<" ";
        }*/
        
      /* If the maximum element of left side for an index is less or equal to the minimum element on right side */
        for (i = 0; i < nums.size() - 1; i++) {
            if (minimum_right[i + 1] >= maximum_left[i]) {
                return i + 1;
            }
        }
        
        return nums.size();
    }
};
