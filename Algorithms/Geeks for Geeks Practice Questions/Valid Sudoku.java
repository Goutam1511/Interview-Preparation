/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:
A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example 1:

Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
Example 2:

Input: board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8.
Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Constraints:
board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.
*/

class Solution {
    boolean[][] rows = new boolean[9][9];
    boolean[][] columns = new boolean[9][9];
    boolean[][][] subbox = new boolean[3][3][9];
    public int[] mapping(int i, int j) {
        int[] coord = new int[2];
        if (i < 3) {
            coord[0] = 0;
        } else if (i < 6) {
            coord[0] = 1;
        } else if (i < 9) {
            coord[0] = 2;
        }
        if (j < 3) {
            coord[1] = 0;
        } else if (j < 6) {
            coord[1] = 1;
        } else if (j < 9) {
            coord[1] = 2;
        }
        return coord;
    }
    
    public boolean isValidSudoku(char[][] board) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int val = board[i][j] - '0' - 1;
                    if (rows[i][val]) {
                        return false;
                    } else {
                        rows[i][val] = true;
                    }
                    if (columns[j][val]) {
                        return false;
                    } else {
                        columns[j][val] = true;
                    }
                    int[] coord = mapping(i, j);
                    if (subbox[coord[0]][coord[1]][val]) {
                        return false;
                    } else {
                        subbox[coord[0]][coord[1]][val] = true;
                    }
                }
            }
        }
        return true;
    }
}
