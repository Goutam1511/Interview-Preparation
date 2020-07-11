/*
Given a set of distinct integers, nums, return all possible subsets (the power set).
Note: The solution set must not contain duplicate subsets.

Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

Solution : Recursively compute all the subsets. To compute all the subsets, branch it to two recursions, one including the
element at index i & another not including the index i. Store the intermediate subsets formed using a set to avoid duplicates.

Time Complexity : O(2^n) to generate all subsets for a set of length n.
*/

class Solution {
public:
    set<vector<int>> s;
    
    void generateCombination(vector<int>& nums, vector<int> v,
                             int index) {
        if (index >= nums.size()) {
            return;
        }
        s.insert(v); //Subset not including element at index i
        //Recursively compute all subsets not including element at index i
        generateCombination(nums, v, index + 1);
        v.push_back(nums[index]); //Subset including element at index i
        s.insert(v);
        //Recursively compute all subsets including element at index i
        generateCombination(nums, v, index + 1);
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> v;
        generateCombination(nums, v, 0);
        vector<vector<int>> res(s.begin(), s.end());
        return res;
    }
};
