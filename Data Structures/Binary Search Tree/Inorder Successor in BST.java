/*
Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST. 
If the given node has no in-order successor in the tree, return null.
The successor of a node p is the node with the smallest key greater than p.val.

Example 1:

Input: root = [2,1,3], p = 1
Output: 2
Explanation: 1's in-order successor node is 2. Note that both p and the return value is of TreeNode type.
Example 2:

Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null
Explanation: There is no in-order successor of the current node, so the answer is null.

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5
All Nodes will have unique values.

Solution : Once we find the node whose inorder successor to be found. There are 3 catches in this -
1. For the node, if it has a right subtree, then the smallest node in right subtree is the required inorder successor.
2. For the node, if it is on the left side of the subtree without any right child, then the parent is the next inorder successor.
3. Otherwise we search all the parent list, till we find a parent whose value is greater than the required node.
4. If there is no parent greater than the node value and no right child then there is no inorder successor.

Time & Space Complexity : O(h)
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public TreeNode findSmallest(TreeNode node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }
    Map<TreeNode, TreeNode> childParent = new HashMap<>();
    public TreeNode inorderSuccessor(TreeNode node, TreeNode parent, TreeNode p) {
        childParent.put(node, parent);
        if (node.val == p.val) {
            if (node.right != null) {
                return findSmallest(node.right);
            } else {
                if (parent.val > p.val) {
                    return parent;
                }
                while (parent != null) {
                    parent = childParent.get(parent);
                    if (parent != null && parent.val > p.val) {
                        return parent;
                    }
                }
                return parent;
            } 
        }
        if (node.val < p.val) {
            return inorderSuccessor(node.right, node, p);
        }
        return inorderSuccessor(node.left, node, p);
    }
    public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
        if (root == p) {
            if (root.right == null) {
                return null;
            } else {
                return findSmallest(root.right);
            }
        }
        return inorderSuccessor(root, null, p);
    }
}
