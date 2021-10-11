/*
Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

Example 1:

Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
Example 2:

Input: root = [1,2]
Output: 1

Constraints:

The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100

Solution : Compute the sum of the largest path in left subtree and right subtree for every node and update the maximum sum on the fly.
Complexity : O(n)
*/

class Solution {
public:
    int max_so_far = INT_MIN;
    int findDiameter(TreeNode* node) {
        if (!node)
            return 0;
        int left = findDiameter(node->left); //largest path in left subtree
        int right = findDiameter(node->right); //largest path in right subtree
        
        max_so_far = max(max_so_far, left + right); //Check if the diameter is larger than found so far

        return max(left, right) + 1; //return the longest path found so far to it's parent
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        findDiameter(root);
        return max(0, max_so_far);
    }
};
