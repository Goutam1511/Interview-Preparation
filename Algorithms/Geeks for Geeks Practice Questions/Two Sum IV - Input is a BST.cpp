/*
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True

Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False

Solution : Just parse the BST and go on storing the nodes in a set if the (Target - Current Node) doesn't exist else return true as we got the two values.
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
    set<int> nodestorage;
    bool findTarget(TreeNode* root, int k) {
        if (root) {
            if (nodestorage.count(k - root->val)) {
                return true;
            } else {
                nodestorage.insert(root->val);
                return (findTarget(root->left, k) || findTarget(root->right, k));
            }
        }
        return false;
    }
};
