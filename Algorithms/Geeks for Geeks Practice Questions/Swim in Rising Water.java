/*
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
The rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally adjacent square
if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay 
within the boundaries of the grid during your swim.

Return the least time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

Example 1:

Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
Example 2:

Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
0 <= grid[i][j] < n^2
Each value grid[i][j] is unique.

Solution : The idea is to start with the starting cell and insert all neighbouring cells in a priority queue and visit the cell with the shortest difference with
the current cell and enqueueing the neighbouring nodes and traversing in a similar fashion. This is on the basis of Djikstras algorithm keeping in mind that we
can reach the destination through the shortest path. Also while traversing we constantly update the minimum time based on the maximum value in the route.

Time Complexity : O(N^2logN) -> N^2 because we at max traverse all matrix cells and logN to build the priority queue
Space Complexity : O(N^2) for heap

Another interesting solution is BFS/DFS + Binary Search where we binary search the minimum possible time and do BFS/DFS for all cells that have time value less than
the time decided through binary search

class Solution {
    public int swimInWater(int[][] grid) {
        int N = grid.length;
        int lo = grid[0][0], hi = N * N;
        while (lo < hi) {
            int mi = lo + (hi - lo) / 2;
            if (!possible(mi, grid)) {
                lo = mi + 1;
            } else {
                hi = mi;
            }
        }
        return lo;
    }

    public boolean possible(int T, int[][] grid) {
        int N = grid.length;
        Set<Integer> seen = new HashSet();
        seen.add(0);
        int[] dr = new int[]{1, -1, 0, 0};
        int[] dc = new int[]{0, 0, 1, -1};

        Stack<Integer> stack = new Stack();
        stack.add(0);

        while (!stack.empty()) {
            int k = stack.pop();
            int r = k / N, c = k % N;
            if (r == N-1 && c == N-1) return true;

            for (int i = 0; i < 4; ++i) {
                int cr = r + dr[i], cc = c + dc[i];
                int ck = cr * N + cc;
                if (0 <= cr && cr < N && 0 <= cc && cc < N
                        && !seen.contains(ck) && grid[cr][cc] <= T) {
                    stack.add(ck);
                    seen.add(ck);
                }
            }
        }

        return false;
    }
}

MST / Kruskal is also an efficient solution. Perfect case of Union Find Algorithm.
*/
class Solution {
    static class cell {
        int i;
        int j;
        int d;
        
        cell(int x, int y, int v) {
            i = x;
            j = y;
            d = v;
        }
    }
    
    public boolean isSafe(int i, int j, int r, int c) {
        if (i < 0 || j < 0 || i >= r || j >= c) {
            return false;
        }
        return true;
    }
    public int swimInWater(int[][] grid) {
        int start = grid[0][0];
        int r = grid.length, c = grid[0].length;
        PriorityQueue<cell> pq = new PriorityQueue<cell>((a, b) -> a.d - b.d);
        boolean[][] visited = new boolean[r][c];
        int max = 0;
        
        pq.add(new cell(0, 0, grid[0][0]));
        visited[0][0] = true;
        int[] dx = {0, 1, 0, -1};
        int[] dy = {1, 0, -1, 0};
        
        while (!pq.isEmpty()) {
            cell currentCell = pq.poll();
            int i = currentCell.i;
            int j = currentCell.j;
            max = Math.max(max, currentCell.d);
            if (i == r - 1 && j == c - 1)
                return max;
            
            for (int d = 0; d < 4; d++) {
                if (isSafe(i + dx[d], j + dy[d], r, c)
                    && !visited[i + dx[d]][j + dy[d]]) {
                    visited[i + dx[d]][j + dy[d]] = true;
                    pq.add(new cell(i + dx[d], j + dy[d],
                                    grid[i + dx[d]][j + dy[d]]));
                }
            }
        }
        
        return max;
    }
}

/*

*/
class Solution {
    static class cell {
        int i;
        int j;
        int d;
        
        cell(int x, int y, int v) {
            i = x;
            j = y;
            d = v;
        }
    }
    
    public boolean isSafe(int i, int j, int r, int c) {
        if (i < 0 || j < 0 || i >= r || j >= c) {
            return false;
        }
        return true;
    }
    public int swimInWater(int[][] grid) {
        int start = grid[0][0];
        int r = grid.length, c = grid[0].length;
        PriorityQueue<cell> pq = new PriorityQueue<cell>((a, b) -> a.d - b.d);
        boolean[][] visited = new boolean[r][c];
        int max = 0;
        
        pq.add(new cell(0, 0, grid[0][0]));
        visited[0][0] = true;
        int[] dx = {0, 1, 0, -1};
        int[] dy = {1, 0, -1, 0};
        
        while (!pq.isEmpty()) {
            cell currentCell = pq.poll();
            int i = currentCell.i;
            int j = currentCell.j;
            max = Math.max(max, currentCell.d);
            if (i == r - 1 && j == c - 1)
                return max;
            
            for (int d = 0; d < 4; d++) {
                if (isSafe(i + dx[d], j + dy[d], r, c)
                    && !visited[i + dx[d]][j + dy[d]]) {
                    visited[i + dx[d]][j + dy[d]] = true;
                    pq.add(new cell(i + dx[d], j + dy[d],
                                    grid[i + dx[d]][j + dy[d]]));
                }
            }
        }
        
        return max;
    }
}

/*
Another interesting solution is BFS + Binary Search
*/
