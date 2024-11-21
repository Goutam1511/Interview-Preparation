/*
You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where
guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.

A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a
wall or another guard. A cell is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.

Example 1:


Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
Output: 7
Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
There are a total of 7 unguarded cells, so we return 7.
Example 2:


Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
Output: 4
Explanation: The unguarded cells are shown in green in the above diagram.
There are a total of 4 unguarded cells, so we return 4.
 

Constraints:

1 <= m, n <= 105
2 <= m * n <= 105
1 <= guards.length, walls.length <= 5 * 104
2 <= guards.length + walls.length <= m * n
guards[i].length == walls[j].length == 2
0 <= rowi, rowj < m
0 <= coli, colj < n
All the positions in guards and walls are unique.

Solution : https://leetcode.com/problems/count-unguarded-cells-in-the-grid/solutions/6069443/clean-readable-java-code-simulation-with-extra-memory/
*/

class Solution {
    int[][] dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    boolean withinBounds(int[][] graph, int x, int y) {
        int m = graph.length, n = graph[0].length;

        if (x >= 0 && y >= 0 && x < m && y < n) return true;
        return false;
    }

    void traverse(int[][] graph, int[] d, int[] start, Set<String> obstacles) {
        int curX = start[0] + d[0], curY = start[1] + d[1];
        while (withinBounds(graph, curX, curY)
                && !obstacles.contains(curX + " " + curY)) {
            graph[curX][curY] = 1;
            curX += d[0];
            curY += d[1];
        }
    }

    public int countUnguarded(int m, int n, int[][] guards, int[][] walls) {
        int[][] graph = new int[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = 0;
            }
        }

        Set<String> obstacles = new HashSet<>();

        for (int[] arr : walls) {
            graph[arr[0]][arr[1]] = 1;
            obstacles.add(arr[0] + " " + arr[1]);
        }

        for (int[] arr : guards) {
            obstacles.add(arr[0] + " " + arr[1]);
        }

        for (int[] start : guards) {
            graph[start[0]][start[1]] = 1;
            for (int[] d : dir) {
                traverse(graph, d, start, obstacles);
            }
        }
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] == 0) {
                    // System.out.println(i + " " + j);
                    cnt++;
                }
            }
        }
        return cnt;
    }
}
