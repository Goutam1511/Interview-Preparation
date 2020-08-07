/*
Given a binary tree, return the vertical order traversal of its nodes values.
For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).
Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes,
we report the values of the nodes in order from top to bottom (decreasing Y coordinates).
If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.
Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.

Example 1:

Input: [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation: 
Without loss of generality, we can assume the root node is at position (0, 0):
Then, the node with value 9 occurs at position (-1, -1);
The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
The node with value 20 occurs at position (1, -1);
The node with value 7 occurs at position (2, -2).
Example 2:

Input: [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation: 
The node with value 5 and the node with value 6 have the same position according to the given scheme.
However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.

Note:
The tree will have between 1 and 1000 nodes.
Each node's value will be between 0 and 1000.

Solution : We will traverse the tree in pre-order fashion. Picking every node and storing it in a map of map 
- map<int, map<int, priority_queue <int, vector<int>, greater<int>>>>. The trick lies in how we store the nodes 
and when two nodes having the same position in same level are encountered, how we print them sorted. For this,
we need to store nodes of same level in a priority queue/min heap. So, we would be needing both the ordinates,
we will store the nodes falling in the same vertical line or with same x in same bucket. Again each bucket will
have sub-buckets to seggregate the nodes having same y values or nodes in same level. This sub-buckets will be
always sorted in non-increasing manner, hence the requirement of priority-queue or min heap.
*/

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /* The bucket structure to store nodes having same x values together  *
     * with again nodes having same x grouped according to their y values */
    map<int, map<int, priority_queue <int, vector<int>, greater<int>>>> storeListofNodes;
    
    void traverseTree(TreeNode* node, int x, int y) {
        //If bucket for that x exists, insert node in the corresponding sub-bucket
        if (storeListofNodes.count(x)) {
            //Check if sub-bucket for y exists
            if (storeListofNodes[x].count(y)) {
                storeListofNodes[x][y].push(node->val);
            } else {
                //If not create a min-heap so that nodes in that sub-bucket are always sorted
                priority_queue <int, vector<int>, greater<int>> temp;
                temp.push(node->val);
                //Insert the sub-bucket for y in x bucket.
                storeListofNodes[x].insert(make_pair(y, temp));
            }
        } else { //Bucket for x doesn't exist. So no question of sub-bucket for y existing. Create everything.
            priority_queue <int, vector<int>, greater<int>> temp;
            map<int, priority_queue <int, vector<int>, greater<int>>> tmap;
            
            temp.push(node->val);
            tmap.insert(make_pair(y, temp));
            storeListofNodes.insert(make_pair(x, tmap));
        }
        if (node->left) { //Recursively go for left and right subtree
        /* The catch here is inorder to keep the nodes having same x from top to bottom,   *
         * instead of assigning the next levels y - 1, we will number them y + 1. This is  *
         * done to keep all the sub-buckets arranged according to their increase in levels *
         * or in other words top to bottom order so during retrieval, they are accessed in *
         * same order.                                                                     */
            traverseTree(node->left, x - 1, y + 1);
        }
        if (node->right) {
            traverseTree(node->right, x + 1, y + 1);
        }
    }
    
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> res;
        
        if(!root) {
            return res;
        }
        traverseTree(root, 0, 0); //Traverse the tree and store nodes
        
        for (auto nodesinsamevl : storeListofNodes) { //Iterate all the sub-buckets. Each item is a sub-bucket
            vector<int> temp; //Store all elements of a sub-bucket as a list
            
            for (auto node : nodesinsamevl.second) {//Iterate the sub-bucket and retrieve all elements of each min-heap
                while(!node.second.empty()) {// While min-heap not empty
                //Each sub-bucket will be added to the same list only to have all nodes having same x in a single list
                    temp.push_back(node.second.top());
                    node.second.pop();
                }
            }
            res.push_back(temp); //Push back list of nodes having same x
        }
        return res; //return list of list
    }
};

