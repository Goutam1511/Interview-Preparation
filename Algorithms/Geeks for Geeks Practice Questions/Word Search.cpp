/*
Given a 2D board and a word, find if the word exists in the grid. The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those 
horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example:

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.

Constraints:

    board and word consists only of lowercase and uppercase English letters.
    1 <= board.length <= 200
    1 <= board[i].length <= 200
    1 <= word.length <= 10^3
    
Corner Case :

Input :
[["A","B","C","E"],["S","F","E","S"],["A","D","E","E"]]
"ABCESEEEFS"

NOTE : If we mark on going the nodes visited once and don't undo them when we don't find the word in one direction, then even if the word exists by going in some other
direction and the previously visited node is a part of that, we won't be able to find it. Hence, once we don't find a word in some direction, we have to backtrack and also
mark the previously visited nodes unvisited (Refer corner case). Also, not finding the whole word in one direction, doesn't mean the word doesn't exist there. Hence, we have
to backtrack and search in all directions.

Solution : We use DFS and backtracking to find the word.
*/

class Solution {
public:
    bool findWord(vector<vector<char>>& board, string word, int index,
                 int i, int j, vector<vector<bool>>& visited) {
        if (index == word.length()) { //Full word found
            return true;
        }
        
        if (i < 0 || i >= board.size())
            return false;
        
        if (j < 0 || j >= board[0].size())
            return false;
        
        if (visited[i][j]) //This is not to use the same cell again
            return false; 
        
        if (board[i][j] == word[index]) {
            cout<<i<<" "<<j<<endl;
            visited[i][j] = true;
            /* Search in all directions regardless of the next letter found in one direction */
            bool ret1 = findWord(board, word, index + 1, i - 1, j, visited);
            bool ret2 = findWord(board, word, index + 1, i + 1, j, visited);
            bool ret3 = findWord(board, word, index + 1, i, j - 1, visited);
            bool ret4 = findWord(board, word, index + 1, i, j + 1, visited);
            
            bool flag = (ret1 || ret2 || ret3 || ret4);
            if (!flag) { //If the word is not found then unmark the node, else it will hinder searching that node again after backtracking
                visited[i][j] = false;
            }
            return flag;
        }
        return false;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int rows  = board.size(), columns = 0, i = 0, j = 0;
        bool flag = false;
        
        if (rows) {
            columns = board[0].size();
        }
        
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                if (word[0] == board[i][j]) { //First letter of the word found, start searching for the word
                //Create new visited everytime for every new search, otherwise if there are duplicate letters, then search will be affected
                    vector<vector<bool>> visited(rows, vector<bool> (columns, false));
                    if (findWord(board, word, 0, i, j, visited)) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
};
