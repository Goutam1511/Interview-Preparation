/*
Given an m x n binary matrix mat, return the length of the longest line of consecutive one in the matrix.
The line could be horizontal, vertical, diagonal, or anti-diagonal.

Example 1:


Input: mat = [[0,1,1,0],[0,1,1,0],[0,0,0,1]]
Output: 3
Example 2:


Input: mat = [[1,1,1,1],[0,1,1,0],[0,0,0,1]]
Output: 4
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.

Solution : Initially, it might feel like just taking a 2D DP array of same size and updating the DP matrix on the fly while iterating the matrix based on checking the
four neighbouring cells - left, top, top left diagonal and top right anti-diagonal but that is not the case. Because we are here looking for lines, not the max possible
path having 1s. Hence, it might get overriden and we need to keep all these 4 states separate from each other and the trick is to maintain a 3D DP matrix - dp[i][j][dir]
where dir is the state which we are considering - horizontal, vertical, diagonal or anti-diagonal.

Time Complexity : O(mn)
Space Complexity : 4mn = O(mn)
*/

class Solution {
    boolean isSafe(int i, int j, int r, int c) {
        if (i < 0 || j < 0 || i >= r || j >= c) {
            return false;
        }
        return true;
    }
    
    int[] dx = {-1, 0, -1, -1};
    int[] dy = {0, -1, -1, 1};
    public int longestLine(int[][] mat) {
        int r = mat.length, c = mat[0].length;
        int[][][] dp = new int[r][c][4];
        
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (mat[i][j] == 1) {
                    for (int d = 0; d < 4; d++) {
                        dp[i][j][d] = 1;
                        if (isSafe(i + dx[d], j + dy[d], r, c))
                            dp[i][j][d] = Math.max(dp[i][j][d],
                                               1 + dp[i + dx[d]][j + dy[d]][d]);
                    }
                }
                
            }
        }
        int max = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                for (int d = 0; d < 4; d++)
                    max = Math.max(dp[i][j][d], max);
            }
        }
        
        return max;
    }
}
