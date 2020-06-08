/*
Given a simple expression tree, which is also a full binary tree consisting of basic binary operators i.e., + , – ,* and / and some integers, Your task is to evaluate the expression tree.

Input Format:
The first line of input contains an integer T denoting the no of test cases . Then T test cases follow. Each test case contains an integer N denoting the no of nodes. Then in the next line are N space separated values of the nodes of the Binary tree filled in continous way from the left to the right.

Output Format:
For each test case output will be the result obtained by simplifying the expression tree.

Constraints:
1 <= T <= 100
2 <= N <= 500

Your Task:
You need to complete the function evalTree which takes the root of the tree as its only argument and returns an integer denoting the result obtained by simplifying the expression tree.

Example(To be used only for expected Output):
Input:
2
7
+ * - 5 4 100 20
3
- 4 7 
Output:
100
-3
*/

/*The structure of node is as follows */
struct node{
    string data;
    node *left;
    node *right;
};

/* Traverse upto leaf node using PostOrder Traversal, then evaluate bottom up. */
int evalTree(node* root) {
    int left = 0, right = 0;
    string data;
    
    if (root == NULL)
        return 0;
    left  = evalTree(root->left);
    right = evalTree(root->right);
    data  = root->data;
    
    /* If the node is a sign, then compute the left (sign) right *
     * Else, return the numerical value of the node              */
    if (data == "+") {
        return left + right;
    } else if (data == "-") {
        return left - right;
    } else if (data == "*") {
        return left * right;
    } else if (data == "/") {
        return left / right;
    } else {
        return stoi(root->data);
    }
    return -1;
}
