/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]

Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7

Corner Cases :
Input = [1]           OP :  1
        [1]                / \
                         NULL NULL
Input = [1,2]         OP :   1
        [1,2]               / \
                         NULL  2
                              / \
                            NULL NULL
Solution : Find each element of preorder in inorder array. The left elements of a particular element from preorder in inorder are
in left subtree of that element & all right elements form the right subtree. The key here is to maintain a static variable or a 
pointer across all levels of recursion to track the index of preorder array to be worked on currently else we will lose track from
the structure of binary tree. This is done because not always the next two elements of the current index, being worked with in the
preorder list, are left and right child(Check corner case 2). Sometimes there are no left or right child at all, hence it's important
to be consistent with the index to be considered in preorder list.
*/

/* Definition for a binary tree node. */
typedef struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 } TreeNode;

/* This utility function helps to find a value in a list by Linear Search */
int findval(int val, int* list, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        if (list[i] == val) {
            return i;
        }        
    }
    return -1;
}

TreeNode* buildTreeUtil(int* preorder, int preorderSize, int* inorder, int inorderSize, int* preindex) {
    TreeNode* root = (TreeNode *)calloc(sizeof(TreeNode), 1);
    if (inorderSize == 0) { //No more elements left return NULL
        return NULL;
    }
    root->val = preorder[(*preindex)++]; //Make the next element of preorder list as the current node
    if (inorderSize == 1) { //Leaf node
        root->left  = NULL;
        root->right = NULL;
    } else {
        int index   = findval(preorder[(*preindex) - 1], inorder, inorderSize);
            
        /* All left elements of the current node value in Inorder are part of left subtree */
        root->left  = buildTreeUtil(preorder, preorderSize, inorder, index, preindex);
        /* All right elements of the current node value in Inorder are part of right subtree */
        root->right = buildTreeUtil(preorder, preorderSize, inorder + index + 1, inorderSize - index - 1, preindex);
    } 
    return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    int preindex = 0;
    return buildTreeUtil(preorder, preorderSize, inorder, inorderSize, &preindex);
}
