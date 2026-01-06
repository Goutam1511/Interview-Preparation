/*
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

Example 1:

Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Example 2:

Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5

Solution : Classic BFS keeping track of sum in each level
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
    static class Pair {
        int first;
        int second;

        Pair(int level, int sum) {
            first = level;
            second = sum;
        }
    }
    // This pair keeps track of current level vs maxSum.
    private Pair p = new Pair(Integer.MAX_VALUE, Integer.MIN_VALUE);

    
    // Process each level - find current sum as well as queue up non-null nodes for next level.
    private Queue<TreeNode> processCurrentLevel(Queue<TreeNode> q, int curLevel) {
        Queue<TreeNode> newLevel = new LinkedList<>();
        int sum = 0;

        while (!q.isEmpty()) {
            TreeNode curr = q.poll();
            sum += curr.val;
            if (curr.left != null) newLevel.add(curr.left);
            if (curr.right != null) newLevel.add(curr.right);
        }
        //System.out.println(curLevel + " " + sum);
        if (p.second < sum) {
            p.first = curLevel;
            p.second = sum;
        }
        return newLevel;
    }
    public int maxLevelSum(TreeNode root) {
        if (root == null) return 1;
        Queue<TreeNode> q = new LinkedList<>();
        
        q.add(root);
        int curLevel = 0;
        while (!q.isEmpty()) {
            curLevel++;
            q = processCurrentLevel(q, curLevel);
        }

        return p.first;
    }
}
