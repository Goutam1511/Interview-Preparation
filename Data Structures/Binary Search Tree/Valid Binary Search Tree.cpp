/*
Given a binary tree, determine if it is a valid binary search tree (BST).
Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:

    2
   / \
  1   3

Input: [2,1,3]
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

Corner Case : [10, 5, null, null, 15, 6, 20]

Solution : Although at first, it might seem that checking if only the right
node is greater & left node is lesser than the current node recursively will
suffice but that's not the case because we have to ensure the whole left subtree
Must contain nodes lesser than the current node and vice versa for right subtree.

The key to the problem is to remember that, InOrder Traversal of a BST is always a
Sorted array. So we store the result of inorder traversal and check if it is strictly 
increasing in nature. If yes, then the Binary Tree is a valid BST else not.

Time & Space Complexity: O(n) to traverse all nodes and store all nodes.
*/

// Definition for a binary tree node 
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
    vector<int> v;
    void inorder(TreeNode* root) {
        if (!root) {
            return;
        }
        inorder(root->left);
        v.push_back(root->val);
        inorder(root->right);
    }
    
    bool isValidBST(TreeNode* root) {
        if (!root)
            return true;
        inorder(root);
        for (int i = 0; i < v.size() - 1; i++) {
            //cout<<v[i]<<" ";
            if (v[i] >= v[i + 1]) {
                return false;
            }
        }
        return true;
    }
};
