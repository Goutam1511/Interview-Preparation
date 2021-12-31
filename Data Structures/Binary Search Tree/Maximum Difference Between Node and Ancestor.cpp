/*
Given the root of a binary tree, find the maximum value v for which there exist different nodes a and b where v = |a.val - b.val| and a is an ancestor of b.
A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an ancestor of b.

Example 1:

Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation: We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
Example 2:

Input: root = [1,null,2,null,0,3]
Output: 3

Constraints:

The number of nodes in the tree is in the range [2, 5000].
0 <= Node.val <= 10^5

Hint : For each subtree, find the minimum value and maximum value of its descendants.

Solution : To make sure min/max values belong to an ancestor, we track min/max from the root till the leaf, and pick the biggest difference among all leaves.
We use the function parameters to track the max and min to make sure the max and min is always from the ancestors only. The biggest difference will always be
between max and min value.
*/

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
    int maxAncestorDiff(TreeNode* r, int mn = 100000, int mx = 0) {
      if (r == nullptr) return mx - mn;
      mx = max(mx, r->val);
      mn = min(mn, r->val);
      return max(maxAncestorDiff(r->left, mn, mx), maxAncestorDiff(r->right, mn, mx));
    }
};
