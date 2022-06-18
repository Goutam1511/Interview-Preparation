/*
You are given an m x n grid rooms initialized with these three possible values.
-1 -> A wall or an obstacle.
0  -> A gate.
INF -> Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example 1:

Input: rooms = [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
Example 2:

Input: rooms = [[-1]]
Output: [[-1]]

Constraints:

m == rooms.length
n == rooms[i].length
1 <= m, n <= 250
rooms[i][j] is -1, 0, or 2^31 - 1.

Solution : A classic variation of the Rotten Oranges problem. First step is to queue up all the gates. Then we can start with the gates and visit all the 
neighbouring cells and update their values and then proceed again to visit their neighbours using BFS. The key is to store the last updated value of any cell 
and add neighbours to the queue only if their value is greater than 1 + current cell value. By this, we can limit visiting all the cells since at any point, 
if the neighbouring cell has a value lesser than current cell, that implies there is another gate nearer to the cell than the gate we have started exploring.

Time & Space Complexity : O(MN) -> At worst case we loop over all cells in BFS and we end up storing all the cells in the matrix.
*/

class Solution {
    static class pair {
        int i;
        int j;
        int val;
        
        pair(int i, int j, int val) {
            this.i = i;
            this.j = j;
            this.val = val;
        }
    }
    int[] dx = new int[]{0, 0, 1, -1};
    int[] dy = new int[]{1, -1, 0, 0};
    
    public boolean isSafe(int i, int j, int[][] rooms) {
        if (i < 0 || j < 0 || i >= rooms.length || j >= rooms[0].length) {
            return false;
        }
        return true;
    }
    
    public void wallsAndGates(int[][] rooms) {
        Queue<pair> q = new LinkedList<>();
        for (int i = 0; i < rooms.length; i++) {
            for (int j = 0; j < rooms[i].length; j++) {
                if (rooms[i][j] == 0) {
                    q.add(new pair(i, j, 0));
                }
            }
        }
        
        while (!q.isEmpty()) {
            pair p = q.poll();
            
            int i = p.i;
            int j = p.j;
            int v = p.val;
            for (int d = 0; d < 4; d++) {
                //System.out.println(i + " " + j + " " + d);
                if (isSafe(i + dx[d], j + dy[d], rooms)
                    && rooms[i + dx[d]][j + dy[d]] != -1 //Check if neighbour is not an obstacle
                    && rooms[i + dx[d]][j + dy[d]] > p.val + 1) { //Check if new value in neighbor actually helps reducing the distance
                    rooms[i + dx[d]][j + dy[d]] = p.val + 1; //Update neighbor value and queue neighbor
                    q.add(new pair(i + dx[d], j + dy[d], rooms[i + dx[d]][j + dy[d]]));
                }
            }
        }
    }
}
