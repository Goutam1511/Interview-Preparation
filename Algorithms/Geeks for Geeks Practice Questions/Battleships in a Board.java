/*
Given an m x n matrix board where each cell is a battleship 'X' or empty '.', return the number of the battleships on board.
Battleships can only be placed horizontally or vertically on board. In other words, they can only be made of the shape 1 x k (1 row, k columns)
or k x 1 (k rows, 1 column), where k can be of any size. At least one horizontal or vertical cell separates between two battleships (i.e.,
there are no adjacent battleships). 

Example 1:

Input: board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
Output: 2
Example 2:

Input: board = [["."]]
Output: 0

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j] is either '.' or 'X'.

Follow up: Could you do it in one-pass, using only O(1) extra memory and without modifying the values board?

Solution : Iterate the matrix and DFS on each character marked 'X' which is still marked unvisited and increment count. Next, in dfs mark all adjacent cells with
'X' as visited. This will help in automatically marking all individual ship cells visited and will increase the count for only individual ship as each ship is told
to have atleast one cell gap.

Time & Space : O(n*n);
*/

class Solution {
    int[] dx = {0, 1, 0, -1};
    int[] dy = {1, 0, -1, 0};

    public boolean isSafe(int i, int j, int r, int c) {
        if (i < 0 || j < 0 || j >= c || i >= r) {
            return false;
        }
        return true;
    }

    public void dfs(char[][] board, int r, int c, int i, int j, boolean[][] visited) {
        if (visited[i][j]) {
            return;
        }

        visited[i][j] = true;
        for (int d = 0; d < 4; d++) {
            if (isSafe(i + dx[d], j + dy[d], r, c)
                    && board[i + dx[d]][j + dy[d]] == 'X') {
                    dfs(board, r, c, i + dx[d], j + dy[d], visited);
            }
        }
    }
    
    public int countBattleships(char[][] board) {
        int rows = board.length, cols = board[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int cnt = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == 'X' && !visited[i][j]) {
                    System.out.println(i + " " + j);
                    dfs(board, rows, cols, i, j, visited);
                    cnt++;
                }
            }
        }
        
        return cnt;
    }
}
