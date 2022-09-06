/*
Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
A subtree of a node node is node plus every node that is a descendant of node.

Example 1:

Input: root = [1,null,0,0,1]
Output: [1,null,0,null,1]
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.
Example 2:

Input: root = [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]
Example 3:

Input: root = [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]

Corner Cases :

[1]
[0]
[1,1]
[1,0]
[1,null,1]
[1,null,0]
[0,1]
[0,0]
[0,null,1]

Constraints:

The number of nodes in the tree is in the range [1, 200].
Node.val is either 0 or 1.

Solution : Recursively traverse the tree bottom up. Check if the left subtree contains a 1, if not prune it.
Do the same for right. Then return if the subtree itself contained any 1 - left subtree result, right subtree
result + the node value itself. After pruning the whole tree, take care of the root node, ultimately the whole
tree can be pruned out except the root node which may or may not needed to be pruned based on it's value

Complexity : Time : O(n) Space : O(1)
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
    bool prune(TreeNode* node) {
        if (node) {
            bool leftcontains = false;
            if (node->left) { //Check if left subtree contains any 1
                leftcontains = prune(node->left);
            }
            bool rightcontains = false;
            if (node->right) { //Check if right subtree contains any 1
                rightcontains = prune(node->right);
            }
            if (!leftcontains) { //Prune left if doesn't contain any 1
                node->left = NULL;
            }
            if (!rightcontains) { //Prune right if doesn't contain any 1
                node->right = NULL;
            }
            /* If neither the left or right subtree or the node has 1, then 
             * it needs to be pruned. Else if any of them has a 1, keep them.
             */
            return (leftcontains || rightcontains || node->val == 1); 
        }
        return false; //leaf node
    }
    
    TreeNode* pruneTree(TreeNode* root) {
        if (root) {
            if (!prune(root)) {
                /* Even after whole tree pruning, the root note itself may
                 * need to be pruned if it is the only node remaining & even
                 * the root node is also not 1.
                 */
                return NULL;
            }
            return root;
        }
        return NULL;
    }
};

/*
Java Solution -

class Solution {
    public boolean pruneSubTrees(TreeNode node) {
        if (node == null) return false;
        boolean leftContains1 = pruneSubTrees(node.left);
        boolean righContains1 = pruneSubTrees(node.right);
        
        if (!leftContains1) {
            node.left = null;
        }
        if (!righContains1) {
            node.right = null;
        }
        return leftContains1 || righContains1 || node.val == 1;
    }
    public TreeNode pruneTree(TreeNode root) {
        if (!pruneSubTrees(root)) {
            return null;
        }
        return root;
    }
}
*/
