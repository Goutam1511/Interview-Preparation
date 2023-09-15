/*
You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|,
where |val| denotes the absolute value of val.
Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

Example 1:

Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation: 

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.
Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18

Constraints:

1 <= points.length <= 1000
-10^6 <= xi, yi <= 10^6
All pairs (xi, yi) are distinct.

Solution : Classic case of Minimum Spanning Tree - we are given to find the cost of forming MST here. A difficult version of this is -
https://www.codingninjas.com/studio/problem-details/water-supply-in-a-village_1380956

We are just finding out all the edges here and then connecting the edges using Kruskal's algorithm involving DSU and PQ.
Time Complexity : O(ELogE) where E is the number of edges here which is N^2 as every point will have an edge between them
Space : O(E) for storing the edges in PQ
*/

class Solution {
    static class DSU {
        int[] parent;
        int[] height;
        DSU(int n) {
            parent = new int[n];
            height = new int[n];

            for (int i = 0; i < n; i++) {
                parent[i] = i;
                height[i] = 1;
            }
        }

        int find(int u) {
            if(u == parent[u])
                return u;
            else
                return parent[u] = find(parent[u]);
        }

        void combine(int u, int v) {
            u = find(u);
            v = find(v);
            
            if(u == v)
                return;
            else {
                if(height[u] > height[v]) {
                    parent[v] = u;
                    height[u] += height[v];
                } else {
                    parent[u] = v;
                    height[v] += height[u];
                }
            
            }
        }
    }

    static class points {
        int dist;
        int point1;
        int point2;;

        points(int d, int p1, int p2) {
            dist = d;
            point1 = p1;
            point2 = p2;
        }
    }

    private int calculateDist(int[] p1, int[] p2) {
        return Math.abs(p1[0] - p2[0]) + Math.abs(p1[1] - p2[1]);
    }
    public int minCostConnectPoints(int[][] points) {
        DSU dsu = new DSU(points.length);

        PriorityQueue<points> pq = new PriorityQueue<>((a, b) -> a.dist - b.dist);

        for (int i = 0; i < points.length; i++) { // Calculate the edges
            for (int j = 0; j < points.length; j++) {
                if (i != j) {
                    pq.add(new points(calculateDist(points[i], points[j]),
                                        i, j));
                }
            }
        }
        int res = 0;
        while (!pq.isEmpty()) { // Classic Kruskal - join least weighted edges if the points are disjoint
            points cur = pq.poll();
            int p1 = cur.point1;
            int p2 = cur.point2;
            if (dsu.find(p1) != dsu.find(p2)) {
                dsu.combine(p1, p2);
                res += cur.dist;
            }
        }
        return res;
    }
}
