/**
Given the root of a binary tree, construct a string consisting of parenthesis and integers from a binary tree with the preorder traversal way, and return it.
Omit all the empty parenthesis pairs that do not affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:

Input: root = [1,2,3,4]
Output: "1(2(4))(3)"
Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need to omit all the unnecessary empty parenthesis pairs. And it will be "1(2(4))(3)"
Example 2:

Input: root = [1,2,3,null,4] <-- Corner Case
Output: "1(2()(4))(3)"
Explanation: Almost the same as the first example, except we cannot omit the first parenthesis pair to break the one-to-one mapping relationship between the input
and the output.

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-1000 <= Node.val <= 1000

Solution : This solution is very simple. We simply need to do the preorder traversal of the given Binary Tree. But, along with this, we need to make use of braces
at appropriate positions. But, we also need to make sure that we omit the unnecessary braces. To do the preorder traversal, we make use of recursion. We print the
current node and call the same given function for the left and the right children of the node in that order(if they exist). For every node encountered, the following
cases are possible.

Case 1: Both the left child and the right child exist for the current node. In this case, we need to put the braces () around both the left child's preorder traversal
output and the right child's preorder traversal output.
Case 2: None of the left or the right child exist for the current node. In this case, as shown in the figure below, considering empty braces for the null left and
right children is redundant. Hence, we need not put braces for any of them.
Case 3: Only the left child exists for the current node. As the figure below shows, putting empty braces for the right child in this case is unnecessary while
considering the preorder traversal. This is because the right child will always come after the left child in the preorder traversal. Thus, omitting the empty braces
for the right child also leads to same mapping between the string and the binary tree.
Case 4: Only the right child exists for the current node. In this case, we need to consider the empty braces for the left child. This is because, during the preorder
traversal, the left child needs to be considered first. Thus, to indicate that the child following the current node is a right child we need to put a pair of empty
braces for the left child.
Just by taking care of the cases, mentioned above, we can obtain the required output string.
*/

class Solution {
    public String tree2str(TreeNode root) {
        if (root == null) return "";
        if (root.left == null && root.right == null)
            return String.valueOf(root.val);
        String left = tree2str(root.left);
        String righ = tree2str(root.right);
        
        left = "(" + left + ")";
        if (righ.length() > 0) righ = "(" + righ + ")";
        return String.valueOf(root.val) + left + righ;
    }
}
