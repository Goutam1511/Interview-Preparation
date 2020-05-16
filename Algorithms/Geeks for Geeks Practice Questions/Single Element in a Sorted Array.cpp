#include <bits/stdc++.h>
using namespace std;


/* Given a sorted array consisting of only integers where every element appears exactly twice,
 * except for one element which appears exactly once.
 * Find this single element that appears only once.
 */
 
 class Solution {
public:
    int modifiedbinarysearch(vector<int>& nums, int lb, int ub) {
        int mid = (lb + ub)/2;
        
        if ((mid != 0) && (mid != nums.size() - 1) && (nums[mid - 1] != nums[mid])
            && (nums[mid + 1] != nums[mid])) {
            return nums[mid];
        } else if (mid == 0 && nums[mid] != nums[mid + 1]) {
            return nums[mid];
        } else if ((mid == nums.size() - 1) && (nums[mid] != nums[mid - 1])) {
            return nums[mid];
        }
        
        if (nums[mid - 1] == nums[mid]) {
            if ((mid - 1) % 2 == 0) {
                lb = mid + 1;
            } else {
                ub = mid - 2;
            }
        }
        if (nums[mid + 1] == nums[mid]) {
            if (mid % 2 == 0) {
                lb = mid + 2;
            } else {
                ub = mid - 1;
            }
        }
        return modifiedbinarysearch(nums, lb, ub);
    }
    
    int singleNonDuplicate(vector<int>& nums) {
        if (nums.size() == 1)
            return nums[0];
        return modifiedbinarysearch(nums, 0, nums.size() - 1);
    }
};

int main() {
	// Single Element in a sorted Array LeetCode May Challenge Optimized solution O(logn)
	return 0;
}
