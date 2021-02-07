/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---

Solution : Use queue two queues to traverse the tree in a level-order fashion and for each level take the right-most node from the queue and form the result vector.
Complexity : O(n)
*/


//Definition for a binary tree node.
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        vector<TreeNode*> q; //Queue for Current level being processed
        if (!root)
            return result;
        q.push_back(root);
        
        while (!q.empty()) { //While all levels not processed
            vector<TreeNode*> temp; //Queue for next level to be formed
            for (int i = 0; i < q.size(); i++) { //Form next level
                if (q[i]->left) {
                    temp.push_back(q[i]->left);
                }
                if (q[i]->right) {
                    temp.push_back(q[i]->right);
                }
            }
            result.push_back((q.back())->val); //Rightmost node
            q = temp; //Reassign the queue
        }
        return result;
    }
};
