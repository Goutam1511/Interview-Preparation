/*
There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the 
Atlantic Ocean touches the island's right and bottom edges. The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights
where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less
than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.

Example 1:
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean 
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean 
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean 
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean 
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean 
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
Example 2:

Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.

Constraints:

m == heights.length
n == heights[r].length
1 <= m, n <= 200
0 <= heights[r][c] <= 10^5

Solution : We just need to visualize the problem in a reverse fashion and we can easily see, that in the question it is asked to find the cells from land from
which water can flow to both atlantic and pacific ocean, but we can do the reverse. That is we can trace those cells from water which have the neighbouring
cells height more than current cell. We can start from the borders and trace our way back into the land using DFS. We can mark those cells in a seperate matrix
with two masks - 1 for pacific ocean and 2 for atlantic ocean - and start traversing for each border cell using DFS and mark the reachable cells for each ocean.
After applying 1 & 2 as masks which has binary value 01 & 10, the cells which are common to both atlantic and pacific will have mask value 3 that is 11 - note
this is because we are doing OR.

TC & SC : O(m * n)
*/

class Solution {
    int[][] dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    public boolean isSafe(int i, int j, int rows, int cols) {
        if (i < 0 || j < 0 || i >= rows || j >= cols) return false;
        return true;
    }
    
    public void dfs(int i, int j, int[][] heights,
                    int mask, boolean[][] visited, int[][] marks) {
        int rows = heights.length, cols = heights[0].length;
        if (visited[i][j]) return;
        visited[i][j] = true;
        marks[i][j] |= mask;
        
        for (int[] d : dir) {
            int newI = i + d[0];
            int newJ = j + d[1];
            
            if (isSafe(newI, newJ, rows, cols) && heights[newI][newJ] >= heights[i][j]) {
                dfs(newI, newJ, heights, mask, visited, marks);
            }
        }
    }
    
    public List<List<Integer>> pacificAtlantic(int[][] heights) {
        int rows = heights.length, cols = heights[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int[][] marks = new int[rows][cols];
        List<List<Integer>> res = new ArrayList<>();
        
        for (int i = 0; i < rows; i++) {
            dfs(i, 0, heights, 1, visited, marks);
        }
        
        for (int i = 0; i < cols; i++) {
            dfs(0, i, heights, 1, visited, marks);
        }
        visited = new boolean[rows][cols];
        for (int i = 0; i < rows; i++) {
            dfs(i, cols - 1, heights, 2, visited, marks);
        }
        
        for (int i = 0; i < cols; i++) {
            dfs(rows - 1, i, heights, 2, visited, marks);
        }
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                //System.out.println(i + " " + j + " " + marks[i][j]);
                if (marks[i][j] == 3) {
                    List<Integer> temp = new ArrayList<>();
                    temp.add(i);
                    temp.add(j);
                    res.add(temp);
                }
            }
        }
        
        return res;
    }
}
