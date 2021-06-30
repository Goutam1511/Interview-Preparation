struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool check_if_present(TreeNode* root, TreeNode* node) {
        if (!root) {
            return false;
        }
        if (root == node) {
            return true;
        }
        return check_if_present(root->right, node) ||
            check_if_present(root->left, node);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p && check_if_present(root, q)) {
            return root;
        } else if (root == q && check_if_present(root, p)) {
            return root;
        }
        
        bool p_present_in_left_tree  = check_if_present(root->left, p);
        bool q_present_in_right_tree = check_if_present(root->right, q);
        bool p_present_in_right_tree = false;
        bool q_present_in_left_tree  = false;
        
        if (!p_present_in_left_tree) {
            p_present_in_right_tree = check_if_present(root->right, p);
        }
        if (!q_present_in_right_tree) {
            q_present_in_left_tree  = check_if_present(root->left, q);
        }
        
        if (p_present_in_left_tree && q_present_in_right_tree) {
            return root;
        } else if (p_present_in_right_tree && q_present_in_left_tree) {
            return root;
        } else if (p_present_in_right_tree && q_present_in_right_tree) {
            return lowestCommonAncestor(root->right, p, q);
        }
        return lowestCommonAncestor(root->left, p, q);
    }
};
