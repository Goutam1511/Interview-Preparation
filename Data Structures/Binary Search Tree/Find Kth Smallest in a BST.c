/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 
 /*
 Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Example 1:

Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1

Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3

Solution Approach :
We start to traverse in-order maintaining a count and for each node, after traversing it's left subtree
we decrement the count because as per property of BST, the left subtree always has smaller nodes, so if
at node i, the count becomes 0, that means there were i - 1 smaller nodes in its left subtree and i is
the required kth smallest node. 

VISUAL DRY RUN

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3

While recursing following in-order:
the call stack goes : 5->3->2->1 and then backtracking starts.
When at 1, k = 2 because 1->left & 1->right == NULL.
When at 2, k = 1 because 2->right == NULL.
When at 3, k = 0 and res = 3.
We can stop here because anyhow further recursions are meaningless.
The output is hence 3.
 */

void utilFindKthSmallest(struct TreeNode* root, int* k, int* res) {
    if (!root)
        return;
    utilFindKthSmallest(root->left, k, res);
    (*k)--;
    if (*k == 0)
        *res = root->val;
    utilFindKthSmallest(root->right, k, res);
}

int kthSmallest(struct TreeNode* root, int k){
    int res;
    utilFindKthSmallest(root, &k, &res);
    return res;
}
