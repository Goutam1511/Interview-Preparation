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

Solution : Here there are two challenges -
1. To uniquely identify if a subtree is present.
2. If a subtree is present, check if previously another duplicate has already been added into result or node.

To uniquely identify a subtree, we are traversing in post order manner and transforming the subtree into string through 
<node.val + "L" + left subtree + "R" + right subtree>. Next we are checking if the same result string for a subtree is already present in a map used for tracking.
If present, we increment the count in the map, but before that we check if the count was 1. If it was 1, then we are sure it is the 1st duplicate, we can safely add
that node in result.

Time & Space : O(n)
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
    Map<String, Integer> nodes = new HashMap<>();
    List<TreeNode> res = new ArrayList<>();
    public String traverse(TreeNode node) {
        if (node == null) {
            return "";
        }
        String left = traverse(node.left);
        String right = traverse(node.right);
        
        String resNode = String.valueOf(node.val) + "L" + left + "R" + right;
        if (nodes.containsKey(resNode) && nodes.get(resNode) == 1) {
            res.add(node);
        }
        nodes.put(resNode, nodes.getOrDefault(resNode, 0) + 1);
        return resNode;
    }
    public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
        traverse(root);
        return res;
    }
}
