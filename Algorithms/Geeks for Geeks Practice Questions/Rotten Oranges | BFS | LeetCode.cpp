/*
In a given grid, each cell can have one of three values:

the value 0 representing an empty cell;
the value 1 representing a fresh orange;
the value 2 representing a rotten orange.
Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.

Note:
1 <= grid.length <= 10
1 <= grid[0].length <= 10
grid[i][j] is only 0, 1, or 2.

Solution : Very unique problem related to BFS. One kind of example where BFS will work but DFS will not because we need the
smallest time in which all the cells can be reached from one cell. We first queue in all the rotten cells in a queue(check
the corner case to understand why we first queue in all the rotten cells first instead of doing BFS on all the rotten cells
1 at a time) and then start doing normal BFS to reach all the cells that can be reachable from the rotten cells. While doing
so, we increment the time everytime we encounter a fresh orange cell as it takes 1 minute for a fresh orange to rot. We not
only store the neighbouring nodes in queue but also the time taken to reach there so that when we encounter a fresh orange
cell, we obtain the smallest time taken to reach that cell and we can update the maximum time needed to rot all the oranges.
After all this, if any fresh oranges remain which we check by traversing the grid again, we return -1 else we return the 
maximum time taken.

Corner Cases:
1. This is to understand that we will consider updating the time only when a fresh orange is rotting. Because
already rotten orange doesn't take time and immediately starts rotting the neighbours if any fresh orange is there.
Input : [[2,2,2,1,1]] 
Output : 2

2. This is to understand the fact that we need to queue in all the rotten oranges at first and then consider
doing BFS parallely for all those rotten oranges to gain the smallest time by which all the fresh oranges will
rot. If we had called BFS for each rotten oranges seperately, we would get a much longer time as for both the
rotten oranges the BFS would be called seperately to give output as 4. But instead we will queue in both rotten
oranges seperately and consider rotting fresh oranges from both side simulatenously to gain minimum time as 2.
Input : [[1,2,1,1,2,1,1]]
Output : 2
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int maxtime = 0;
    queue<pair<pair<int, int>, int>> q;

public:
    void rotneighbours(vector<vector<int>>& grid,
                       vector<vector<bool>>& visited) {
        int i = 0, j = 0, time = 0;
        
        while (!q.empty()) { //Normal BFS exit condition - while the queue is not empty.
            i = q.front().first.first; //Obtain cell location
            j = q.front().first.second;
            time = q.front().second; //Obtain the time now/needed to reach that cell
            q.pop(); //Remove the cell

            if (grid[i][j] == 1) { //If this is a fresh orange cell
                time++; //It takes 1 more minute than current time to rot so update time
                maxtime = max(time, maxtime); //Update the maximum time if more than current time
                grid[i][j] = 2; //Mark it rotten
            }
            //If the cell is either turned rotten or was rotten before and not been visited before
            if (grid[i][j] == 2 && !visited[i][j]) {
            //If the neighbouring cell is not empty cell and a valid cell and had not been visited yet
                if (i < grid.size() - 1 && grid[i + 1][j]
                    && !visited[i + 1][j])
                    q.push(make_pair(make_pair(i + 1, j), time)); //Push it into queue along with current time
                if (i > 0 && grid[i - 1][j]
                   && !visited[i - 1][j])
                    q.push(make_pair(make_pair(i - 1, j), time));
                if (j < grid[0].size() - 1 && grid[i][j + 1]
                   && !visited[i][j + 1])
                    q.push(make_pair(make_pair(i, j + 1), time));
                if (j > 0 && grid[i][j - 1]
                   && !visited[i][j - 1])
                    q.push(make_pair(make_pair(i, j - 1), time));
            }
            visited[i][j] = true; //Mark current node visited.
        }
    }
    
    int orangesRotting(vector<vector<int>>& grid) {
        int i = 0, j = 0, rows = grid.size(), columns = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool> (columns, false));
        
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
            /* Queue in all the rotten cells. Each of them will start rotting their     *
             * neighbour oranges independently so we initialize the time as 0 for each. */
                if (grid[i][j] == 2) {
                    q.push(make_pair(make_pair(i, j), 0));
                }
            }
        }
        rotneighbours(grid, visited); //Call BFS function for the queued cells.
        for (i = 0; i < rows; i++) { //Check if still any fresh oranges remaining.
            for (j = 0; j < columns; j++) {
                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }
        return maxtime; //Return max time needed
    }
};

int main() {
	// Rotten Oranges | BFS | LeetCode
	return 0;
}
