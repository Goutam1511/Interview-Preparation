/*
Given the root of a binary tree, determine if it is a complete binary tree.
In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Example 1:

Input: root = [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6})
are as far left as possible.
Example 2:

Input: root = [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.

Constraints:

The number of nodes in the tree is in the range [1, 100].
1 <= Node.val <= 1000

Solution : Just do a BFS traversal and check at each level if there is any gap in between nodes in each level filled by null. If yes, then it's not a
complete binary tree, else once we encounter null in a level, that should be the last level. Hence, pop all next level values of queue and check if they
all are none next.

Time & Space Complexity : O(n) for traversing all nodes and storing them in a queue.
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public boolean isCompleteTree(TreeNode root) {
        if (root == null) {
            return true;
        }
        Queue<TreeNode> q = new LinkedList<>();

        q.add(root);
        
        while (!q.isEmpty()) {
            int size = q.size();
            boolean isNullPresent = false;
            
            for (int i = 0; i < size; i++) {
                TreeNode popped = q.poll();

                if (isNullPresent && popped != null) return false;
                if (popped != null) {
                    q.add(popped.left);
                    q.add(popped.right);
                } else {
                    isNullPresent = true;
                }
            }
            if (isNullPresent) {
                while (!q.isEmpty()) {
                    TreeNode popped = q.poll();
                    if (popped != null) return false;
                }
            }
        }
        return true;
    }
}
