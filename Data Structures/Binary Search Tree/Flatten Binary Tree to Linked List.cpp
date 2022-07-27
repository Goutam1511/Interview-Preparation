/*
Given the root of a binary tree, flatten the tree into a "linked list":
The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.

Example 1:

Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [0]
Output: [0]

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100

Follow up: Can you flatten the tree in-place (with O(1) extra space)?

Solution : Do a post-order traversal and flatten each subtree recursively. To flatten a tree, we already have the left and right subtrees flattened recursively.
So we just have to attach the right flattened subtree to the tail of the left flattened subtree and then connect the concatenated flattened subtree to the right
of the root node of the subtree and assign the left pointer of root node to null. But there is an edge case here, if the left flattened subtree has no nodes, then
the right flattened subtree needs to be directly attached to the right node of the root node. We have to check this case before attaching the right flattened
subtree to tail of left flattened subtree. The attach logic is hence -

public TreeNode attach(TreeNode toBeAttached, TreeNode toAttach) {
    if (toBeAttached == null) { // If the left flattened subtree is NULL, the right flattened subtree will be directly attached to right of root node
        return toAttach;
    }
    TreeNode temp = toBeAttached;
    while (temp.right != null) { // Move to end tail of left flattened subtree
        temp = temp.right;
    }
    temp.right = toAttach; // Attach the right flattened subtree
    return toBeAttached; // Return the linked flattened subtrees
}


*/
