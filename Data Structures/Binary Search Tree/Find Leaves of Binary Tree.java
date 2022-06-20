/*
Given the root of a binary tree, collect a tree's nodes as if you were doing this:

Collect all the leaf nodes.
Remove all the leaf nodes.
Repeat until the tree is empty.

Example 1:

Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]
Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.
Example 2:

Input: root = [1]
Output: [[1]]

Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100

Solution : The key to the problem is the deepest nodes/leaves gets removed first. The second deepest nodes get removed next as they become the leaves next. Hence, we just
need to evaluate the depth of all nodes and bucket them. And then sort the buckets as per depth and return the same as result. For this we can just store all the same
depth nodes in a treemap with depth as key as list of nodes as value as we know treemap keeps it's keys sorted. Next just iterate the treemap which will be in ascending
order of depth and add list of nodes in result.

Complexity : O(n) for traversing the whole tree and storing all nodes
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
    public int traverse(TreeNode node, Map<Integer, List<Integer>> m) {
        if (node == null) {
            return 0;
        }
        if (node.left == null && node.right == null) {
            List<Integer> arr = m.getOrDefault(1, new ArrayList<>());
            arr.add(node.val);
            m.put(1, arr);
            return 1;
        }
        int leftDepth = traverse(node.left, m);
        int rightDepth = traverse(node.right, m);
        int d = Math.max(leftDepth, rightDepth) + 1;
        List<Integer> arr = m.getOrDefault(d, new ArrayList<>());
        arr.add(node.val);
        m.put(d, arr);
        return d;
    }
    public List<List<Integer>> findLeaves(TreeNode root) {
        Map<Integer, List<Integer>> depthToNodes = new TreeMap<>();
        traverse(root, depthToNodes);
        List<List<Integer>> res = new ArrayList<>();
        for (Map.Entry<Integer, List<Integer>> e : depthToNodes.entrySet()) {
            res.add(e.getValue());
        }
        return res;
    }
}
