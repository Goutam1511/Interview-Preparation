/*
Invert a binary tree.

Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1

*/



/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* This function simply recursively calls itself and
 * interchanges the left and right node of a Binary tree
 */
struct TreeNode* invertTree(struct TreeNode* root){
    struct TreeNode* temp = NULL;
    
    if (root == NULL) {
        return NULL;
    }
    
    invertTree(root->left);
    invertTree(root->right);
    
    temp        = root->left;
    root->left  = root->right;
    root->right = temp;
    return root;
}

int main() {
    //Invert Binary Tree LeetCode
    return 0;

}
