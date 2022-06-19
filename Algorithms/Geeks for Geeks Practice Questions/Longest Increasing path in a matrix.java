/*
Given an m x n integers matrix, return the length of the longest increasing path in matrix.
From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary 

Example 1:

Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
Example 3:

Input: matrix = [[1]]
Output: 1
 
Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1

Solution : The challenge is to visualize and understand that this is a graph problem. The initial hunch might be repeated DFS from each cell to calculate the 
maximum distance reachable from each cell. Needless to say that, it will TLE. Next approach can be DFS with memoization where we store the max distance from a cell.
And when we reach the same cell while traversing from a neighbour, we update the value of the neighbouring parent cell based on the stored value in cell and return
without going further - i.e prune the DFS based on already visited cells. This is an accepted approach

However, the best approach is to note that, there is a directed graph hidden in this matrix - for 1st example, we can see the cell at (2,2) has two neighbours (2,1)
and (1,1) - directed eges because the reverse is not possible because value of (2,2) cell is 1 which is lesser than the neighbours. Now whenever, we notice this 
ordering, we can conclude that we can perform topological sorting to find the longest chain for each cell. Again, this would be a Dynamic programming problem because,
we are not only performing the topological sorting to travese the graph in an ordered manner but also we are updating the longest path on the fly based on nodes 
visited earlier.

We represent each cell as below Node data structure -

static class Node {
    int val = 1; <== 1 because each cell itself a path contributing 1 but this will be updated to longest path possible till this node
    int counter = 0; <==== number of neighbour nodes that are pointing/depending on current node
    List<Node> neighbours = new ArrayList<>(); <== all neighbours that we can visit from this node or in other words all neighbours with matrix value greater
                                                    than current node
}

As normal with topological sorting, first we figure out the nodes with counter or indegree as 0. Then we queue them up and until queue is empty, we poll the head of
queue and decrement the indegree of all neighbouring nodes. But not only this, we also update the val (longest path possible) for all neighbouring nodes -
        neigh.val = Math.max(neigh.val, currentNode.val + 1);
        
Finally, if we traverse the nodes again, we can find the longest path possible in the matrix based on current states of the node.

Time Complexity : O(V + E) -> V are vertices and E is the edges -> Typical for Topological sorting
Space Complexity : O(MN) -> M rows and N Columns in matrix
*/

class Solution {
    static class Node {
        int val = 1;
        int counter = 0;
        List<Node> neighbours = new ArrayList<>();
    }
    
    int[] dx = new int[]{0, 0, -1, 1};
    int[] dy = new int[]{-1, 1, 0, 0};
    
    public boolean isSafe(int i, int j, int rows, int columns) {
        if (i < 0 || j < 0 || i >= rows || j >= columns) {
            return false;
        }
        return true;
    }
    public int longestIncreasingPath(int[][] matrix) {
        int r = matrix.length, c = matrix[0].length;
        Node[][] nodes = new Node[r][c];
        
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                nodes[i][j] = new Node();
            }
        }
        
        Queue<Node> q = new LinkedList<>();
        
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                for (int d = 0; d < 4; d++) {
                    if (isSafe(i + dx[d], j + dy[d], r, c)
                        && matrix[i + dx[d]][j + dy[d]] > matrix[i][j]) {
                        nodes[i + dx[d]][j + dy[d]].counter++;
                        nodes[i][j].neighbours.add(nodes[i + dx[d]][j + dy[d]]);
                    }
                }
            }
        }
        
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (nodes[i][j].counter == 0) {
                    q.add(nodes[i][j]);
                }
            }
        }        
        
        while (!q.isEmpty()) {
            Node node = q.poll();
            int val = node.val;
            
            for (Node neigh : node.neighbours) {
                neigh.counter--;
                neigh.val = Math.max(neigh.val, val + 1);
                if (neigh.counter == 0) {
                    q.add(neigh);
                }
            }
        }
        int longest = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                longest = Math.max(nodes[i][j].val, longest);
            }
        }
        
        return longest;
    }
}
