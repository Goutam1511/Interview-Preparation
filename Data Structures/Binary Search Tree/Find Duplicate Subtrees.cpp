/*
Given the root of a binary tree, return all duplicate subtrees.
For each kind of duplicate subtrees, you only need to return the root node of any one of them.
Two trees are duplicate if they have the same structure with the same node values.

Example 1:

Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
Example 2:

Input: root = [2,1,1]
Output: [[1]]
Example 3:

Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]

Constraints:

The number of the nodes in the tree will be in the range [1, 10^4]
-200 <= Node.val <= 200

Solution : Something similar like Serializing and deserializing a Binary tree. We convert each subtree into a string
while traversing(post order traversal is important here) and at each node, we check the serialized version of subtree
of that node has been encountered before or not. If not, we store it in a map with count as 1 for future reference else
we check the count. If it is 1, we take a note of the node in result vector and just increase the count so that if 
there is another duplicate, we simply ignore.

 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    map<string, int> strset;
    vector<TreeNode*> res;
    string traverse(TreeNode* node) {
        if (!node) {
            return "N";
        }
        string left = traverse(node->left);
        if (left != "")
            left = "L" + left;
        string right = traverse(node->right);
        if (right != "")
            right = "R" + right;
        string total = to_string(node->val) + left + right;
        if (strset.count(total) && strset[total] == 1) {
            res.push_back(node);
            strset[total]++;
        } else if (!strset.count(total)){
            strset[total] = 1;
        }
        return total;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        traverse(root);
        return res;
    }
};
