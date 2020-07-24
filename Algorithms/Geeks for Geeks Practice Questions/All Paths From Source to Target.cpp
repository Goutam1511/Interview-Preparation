/*
Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.
The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []] 
Output: [[0,1,3],[0,2,3]] 
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:
The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of nodes inside one path.

Solution : The idea is to do Depth First Traversal of given directed graph. Start the DFS traversal from source. 
Keep storing the visited vertices in an array or HashMap say ‘path[]’. If the destination vertex is reached, print contents of path[]. 
The important thing is to mark current vertices in the path[] as visited also so that the traversal doesn’t go in a cycle.
Also after visiting all vertices adjacent to one node, we must again mark the same node unvisited so that when it is visited from
some other node, it is not left unexplored.
*/

class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // Pointer to an array containing adjacency lists 
    // A recursive function used by printAllPaths() 
    void printAllPathsUtil(int, int, bool[], int[], int&, vector<vector<int>>&); 
    public: 
        Graph(int V); // Constructor 
        void addEdge(int v, int w); // to add an edge to graph 
        void printAllPaths(int s, int d, vector<vector<int>>& paths);

}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

// Prints all paths from 's' to 'd' 
void Graph::printAllPaths(int s, int d, vector<vector<int>>& paths) 
{ 
    // Mark all the vertices as not visited 
    bool* visited = new bool[V]; 
  
    // Create an array to store paths 
    int* path = new int[V]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // Initialize all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to print all paths 
    printAllPathsUtil(s, d, visited, path, path_index, paths); 
} 
  
// A recursive function to print all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
void Graph::printAllPathsUtil(int u, int d, bool visited[], 
                              int path[], int&
                              path_index, vector<vector<int>>& paths) 
{ 
    // Mark the current node and store it in path[] 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
  
    // If current vertex is same as destination, then print 
    // current path[] 
    if (u == d) { 
        vector<int> pathtemp;
        for (int i = 0; i < path_index; i++) 
            pathtemp.push_back(path[i]); 
        paths.push_back(pathtemp); 
    } 
    else // If current vertex is not destination 
    { 
        // Recur for all the vertices adjacent to current vertex 
        list<int>::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
            if (!visited[*i]) 
                printAllPathsUtil(*i, d, visited, path, path_index, paths); 
    } 
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false; 
} 

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> res;
        if (!graph.size())
            return res;
        Graph g(graph.size());
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                g.addEdge(i, graph[i][j]);
            }
        }
        g.printAllPaths(0, graph.size() - 1, res);
        return res;
    }
};
