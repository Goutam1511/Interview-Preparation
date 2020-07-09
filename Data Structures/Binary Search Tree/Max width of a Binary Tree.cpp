#include <bits/stdc++.h>
using namespace std;
 
/*
Given a binary tree, write a function to get the maximum width of the given tree. 
The width of a tree is the maximum width among all levels. The binary tree has the 
same structure as a full binary tree, but some nodes are null.
The width of one level is defined as the length between the end-nodes (the leftmost
and right most non-null nodes in the level, where the null nodes between the 
end-nodes are also counted into the length calculation).
 
Example 1:
Input: 
 
           1
         /   \
        3     2
       / \     \  
      5   3     9 
 
Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 
 
          1
         /  
        3    
       / \       
      5   3     
 
Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 
 
          1
         / \
        3   2 
       /        
      5      
 
Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 
 
          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8
(6,null,null,null,null,null,null,7).

Corner case :
                  1
		 / \
		2   3
		   /
		   4
		 /   \
		1     2
	       / \   / \
	      1   2 3   4
 
Solution Approach : We go on traversing the nodes level using two queues following
(Reference : Binary Tree Bottom up Level Order Traversal (Github)). While storing
the child nodes in the queue, we also store it's position in the binary tree.
While traversing each level, we find the difference of position of first node
and the last node in the queue to understand the width of that level and accordingly
update the maxwidth.
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
 
    int widthOfBinaryTree(TreeNode* root) {
        int maxwidth = 0;
        vector<pair<TreeNode*, unsigned long long int>> q;
        bool nextlevhasnode = true;
 
        if (root == NULL)
            return 0;
 
        q.push_back(make_pair(root, 1)); //Push the root in current queue
 
        while (q.size()) { //While current queue is not empty
            vector<pair<TreeNode*, unsigned long long int>> nextlev; //The queue/vector for next level nodes
            int currentwidth;
 
            /* find the difference of position of first node and the last node in the queue *
             * to understand the width of that level and accordingly update the maxwidth.   */
 
            currentwidth = (q.back().second - q.front().second) + 1;
            maxwidth = max(currentwidth, maxwidth);
 
            for (int i = 0; i < q.size(); i++) { 
            	//For each node in current queue, add their children in nextlev queue
                if (q[i].first->left) {
                    nextlev.push_back(make_pair(q[i].first->left, (unsigned long long)((unsigned long long)q[i].second * 2)));
                }
                if (q[i].first->right) {
                    nextlev.push_back(make_pair(q[i].first->right, (unsigned long long)((unsigned long long)q[i].second * 2) + 1));
                }
            }
 
            q = nextlev;
        }
 
        return maxwidth;
    }
};
 
int main() {
	// Max width of a Binary Tree Leetcode
	return 0;
}
