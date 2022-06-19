/*
You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
Return the number of connected components in the graph.

Example 1:


Input: n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2
Example 2:


Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1
 

Constraints:

1 <= n <= 2000
1 <= edges.length <= 5000
edges[i].length == 2
0 <= ai <= bi < n
ai != bi
There are no repeated edges.

Solution : Typically loop around until all nodes visited by dfs. Each time we loop to cover an unvisited node, we maintain a counter and return.
*/

class Solution {
    public void dfs(int i, boolean[] visited, List<List<Integer>> adj) {
        if (visited[i]) {
            return;
        }
        visited[i] = true;
        for (int neigh : adj.get(i)) {
            if (!visited[neigh]) {
                dfs(neigh, visited, adj);
            }
        }
    }
    public int countComponents(int n, int[][] edges) {
        List<List<Integer>> adj = new ArrayList<>();
        boolean[] visited = new boolean[n];
        
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
        
        for (int i = 0; i < edges.length; i++) {
            int srcNode = edges[i][0];
            int desNode = edges[i][1];
            
            adj.get(srcNode).add(desNode);
            adj.get(desNode).add(srcNode);
        }
        
        boolean allVisited = false;
        int cnt = 0;
        
        while (!allVisited) {
            allVisited = true;
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    allVisited = false;
                    cnt++;
                    dfs(i, visited, adj);
                }
            }
        }
        
        return cnt;
    }
}
