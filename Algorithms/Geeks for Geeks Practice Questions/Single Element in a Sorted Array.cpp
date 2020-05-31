#include <bits/stdc++.h>
using namespace std;


/* Given a sorted array consisting of only integers where every element appears exactly twice,
 * except for one element which appears exactly once.
 * Find this single element that appears only once.
 * Solution: Since array is sorted, we can do binary search. The approach is that, while searching
 * if nums[mid - 1] == nums[mid] and mid - 1 is even, then the single element is on right side & we
 * can ignore searching left side. This is because, uptil mid every element has occurred twice and 
 * hence mid - 1 is bound to be an even index. Same logic if nums[mid] == nums[mid + 1]. But if that
 * doesn't happen, then a single element must be in the left side which has disrupted the indexing.
 * So we should search only in left side.
 * VISUAL DRY RUN : Input : [1, 1, 2, 2, 3, 4, 4]
 * Note the indexes :        0  1  2  3  4  5  6
 * Uptil the occurance of single element, in case of all the coupled elements, first of the pair was
 * in even index and second in odd index. But after the occurance of single element, this reverses. 
 * This fact is used as the logic to determine the bounds in binary search. 
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
