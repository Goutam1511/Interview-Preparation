/*
Given a binary tree, return the sum of values of its deepest leaves.

Example 1:
              1
             / \
            2   3
           / \   \
          4   5   6
         /         \
        7           8

Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
 

Constraints:
The number of nodes in the tree is between 1 and 10^4.
The value of nodes is between 1 and 100.

Solution : Traverse the tree two times. Once find the deepest level, second time find the sum of leaves in that level.
*/

/* Definition for a binary tree node. */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    int maxdepth = INT_MIN;
    int sum = 0;
    
    void findMaximumDepth(TreeNode* root, int level) {
        if (root) {
            maxdepth = max(maxdepth, level + 1);
            findMaximumDepth(root->left, level + 1);
            findMaximumDepth(root->right, level + 1);
        }
    }
    
    void findSum(TreeNode* node, int level) {
        if (node) {
            if (level + 1 == maxdepth) {
                sum += node->val;
            } else {
                findSum(node->left, level + 1);
                findSum(node->right, level + 1);
            }
        }
    }
    
    int deepestLeavesSum(TreeNode* root) {
        if (root) {
            findMaximumDepth(root, 0);
        }
        findSum(root, 0);
        return sum;
    }
};
