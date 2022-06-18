/*
The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). 
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. 
Given the current state of the m x n grid board, return the next state.

Example 1:

Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
Example 2:

Input: board = [[1,1],[1,0]]
Output: [[1,1],[1,1]]
 
Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 25
board[i][j] is 0 or 1.
 
Follow up:

Could you solve it in-place? Remember that the board needs to be updated simultaneously: You cannot update some cells first and then use their updated values
to update other cells. In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the 
active area encroaches upon the border of the array (i.e., live cells reach the border). How would you address these problems?

Solution : Bit manipulation to store two states - next state and present state in same cell. Current state is 0 or 1. We can store both current state and next states
using two bits -

Next State - 0 Current State - 0 Combined - 0
Next State - 0 Current State - 1 Combined - 1
Next State - 1 Current State - 0 Combined - 2
Next State - 1 Current State - 1 Combined - 3

To set the next state, we use two masks - livemask - 2 and deadmask - 0. Livemask is 2 to set the 2nd bit and for deadmask it is 0, we want to keep the same state.
To convert back the whole board after all operations, we just need to shift all cells by 1 bit right.

Time Complexity : O(MN), Space Complexity : O(1)
*/

class Solution {
    int[] dx = new int[]{0, 0, -1, 1, -1, 1, -1, 1};
    int[] dy = new int[]{-1, 1, 0, 0, -1, 1, 1, -1};
    
    int liveMask = 2;
    int deadMask = 0;
    
    public void convertState(int[][] board, int i, int j, int cnt) {
        if (cnt < 2) {
            board[i][j] = board[i][j] | deadMask;
        } else if (cnt > 3) {
            board[i][j] = board[i][j] | deadMask;
        } else if (cnt == 3 && board[i][j] == 0) {
            board[i][j] = board[i][j] | liveMask;
        } else if ((cnt == 2 || cnt == 3) && board[i][j] == 1) {
            board[i][j] = board[i][j] | liveMask;
        }
    }
    
    public boolean checkNeighbor(int i, int j, int[][] board) {
        return board[i][j] % 2 == 1;
    }
    
    public void convertBack(int[][] board, int i, int j) {
        board[i][j] = board[i][j] >> 1;
    }
    
    public boolean isSafe(int i, int j, int[][] board) {
        int rows = board.length, column = board[0].length;
        if (i < 0 || j < 0 || i >= rows || j >= column) {
            return false;
        }
        return true;
    }

    public void gameOfLife(int[][] board) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                int cnt = 0;
                for (int d = 0; d < 8; d++) {
                    if (isSafe(i + dx[d], j + dy[d], board)
                        && checkNeighbor(i + dx[d], j + dy[d], board)) {
                        cnt++;
                    }
                }
                //System.out.println(i + " " + j + " " + cnt);
                convertState(board, i, j, cnt);
            }
        }
        
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                convertBack(board, i, j);
            }
        }
    }
}
