/*
You are given the root of a binary tree where each node has a value in the range [0, 25] representing the letters 'a' to 'z'.

Return the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

As a reminder, any shorter prefix of a string is lexicographically smaller.

For example, "ab" is lexicographically smaller than "aba".
A leaf of a node is a node that has no children.

Corner Case : [4, 0, 1, 1]

      4
     / \
    0   1
   /
  1
Solution : Initially, we might feel like we would generate strings back from leaf to root following the methodology given in question.
But that will just complicate things - try for the given corner case, you'll get it. There are just too many cases you have to handle then.
Instead, just form the string while traversing in a straight forward manner and reverse when you reach leaf node. Maintain the smallest
lexicographically seen string so far and compare the same with the other strings formed whenever you reach leaf node and update accordingly.
*/

class Solution {
public:
    string lexo_smallest = "";
    set<string> strings;
    
    char return_char(int i) {
        return "abcdefghijklmnopqrstuvwxyz"[i];
    }
    string return_smaller(string a, string b) {
        if (a == "")
            return b;
        if (b == "")
            return a;
        for (int i = 0; i < min(a.length(), b.length()); i++) {
            if (a[i] < b[i])
                return a;
            else if (a[i] > b[i])
                return b;
        }
        return a.length() < b.length() ? a : b;
    }
    
    void smallestFromLeaft(TreeNode* node, string s) {
        if (node) {
            s = s + return_char(node->val);
            if (!node->left && !node->right) {
                reverse(s.begin(), s.end());
                lexo_smallest = return_smaller(lexo_smallest,
                                                s);
            }
            smallestFromLeaft(node->left, s);
            smallestFromLeaft(node->right, s);
        }
        return;
    }
    
    string smallestFromLeaf(TreeNode* node) {
        smallestFromLeaft(node, "");
        return lexo_smallest;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
