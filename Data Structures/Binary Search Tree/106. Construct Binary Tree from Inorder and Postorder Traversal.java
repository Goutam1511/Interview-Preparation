/*
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the
same tree, construct and return the binary tree.

Example 1:

Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]

Constraints:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.

Solution : For inorder the order of traversal is -> left subtree -> root -> right subtree and for postorder it is always 
left subtree -> right subtree -> root. For postorder, root is always at last Keeping this in mind, we maintain a postOrderIndex pointer and then find out
the element at postorder[postOrderIndex] value in inorder array. Anything that is left to the element in inorder forms the left subtree and anything at
right forms the right subtree. We have to keep in mind that since, we are going from right to left in postorder, we MUST form the right subtree first to
keep the sanity of postorderIndex variable.
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
    int postOrderIndex;
    public TreeNode build(int[] inOrder, int inorderLeft, int inorderRight, int[] postOrder) {
        if (inorderRight < inorderLeft || postOrderIndex < 0) return null;
        if (inorderRight == inorderLeft) return new TreeNode(postOrder[postOrderIndex--]);
        TreeNode newNode = null;
        for (int i = inorderLeft; i <= inorderRight; i++) {
            if (inOrder[i] == postOrder[postOrderIndex]) {
                newNode = new TreeNode(postOrder[postOrderIndex--]);
                newNode.right = build(inOrder, i + 1, inorderRight, postOrder);
                newNode.left  = build(inOrder, inorderLeft, i - 1, postOrder);
                break;
            }
        }
        return newNode;
    }
    public TreeNode buildTree(int[] inorder, int[] postorder) {
        postOrderIndex = postorder.length - 1;
        return build(inorder, 0, inorder.length - 1, postorder);
    }
}
