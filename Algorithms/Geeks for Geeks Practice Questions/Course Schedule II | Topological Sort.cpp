/*
There are a total of n courses you have to take, labeled from 0 to n-1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:

Input: 2, [[1,0]] 
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
             course 0. So the correct course order is [0,1] .
Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both     
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. 
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
Note:
You may assume that there are no duplicate edges in the input prerequisites.
Hint #1  
This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, 
no topological ordering exists and therefore it will be impossible to take all courses.
Hint #2  
Topological sort could also be done via BFS.

Solution : Topological Sort via BFS - Kahn's Algorithm taken from GeeksForGeeks

A DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0.
Proof: There’s a simple proof to the above fact is that a DAG does not contain a cycle which means that all paths will be of finite length.
Now let S be the longest path from u(source) to v(destination). Since S is the longest path there can be no incoming edge to u and no outgoing
edge from v, if this situation had occurred then S would not have been the longest path => indegree(u) = 0 and outdegree(v) = 0

Algorithm: Steps involved in finding the topological ordering of a DAG:
Step-1: Compute in-degree (number of incoming edges) for each of the vertex present in the DAG and initialize the count of visited nodes as 0.
Step-2: Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)
Step-3: Remove a vertex from the queue (Dequeue operation) and then.
Increment count of visited nodes by 1.
Decrease in-degree by 1 for all its neighboring nodes.
If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.
Step 4: Repeat Step 3 until the queue is empty.
Step 5: If count of visited nodes is not equal to the number of nodes in the graph then the topological sort is not possible for the given graph.

How to find in-degree of each node?
There are 2 ways to calculate in-degree of every vertex:

Take an in-degree array which will keep track of
Traverse the array of edges and simply increase the counter of the destination node by 1.
for each node in Nodes
    indegree[node] = 0;
for each edge(src, dest) in Edges
    indegree[dest]++
Time Complexity: O(V+E)

Traverse the list for every node and then increment the in-degree of all the nodes connected to it by 1.
    for each node in Nodes
        If (list[node].size()!=0) then
        for each dest in list
            indegree[dest]++;
            
Time Complexity: The outer for loop will be executed V number of times and the inner for loop will be executed E number of times,
thus overall time complexity is O(V+E). The overall time complexity of the algorithm is O(V+E)
*/

class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // Pointer to an array containing adjacency lists 
	bool isCyclicUtil(int v, bool visited[], bool *rs); // used by isCyclic() 
    public: 
        Graph(int V); // Constructor 
        void addEdge(int v, int w); // to add an edge to graph 
        void topologicalSort(vector<int> &res);
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

// The function to do 
// Topological Sort. 
void Graph::topologicalSort(vector<int> &res) 
{ 
    // Create a vector to store 
    // indegrees of all 
    // vertices. Initialize all 
    // indegrees as 0. 
    vector<int> in_degree(V, 0); 
  
    // Traverse adjacency lists 
    // to fill indegrees of 
    // vertices.  This step 
    // takes O(V+E) time 
    for (int u = 0; u < V; u++) { 
        list<int>::iterator itr; 
        for (itr = adj[u].begin(); 
             itr != adj[u].end(); itr++) 
            in_degree[*itr]++; 
    } 
  
    // Create an queue and enqueue 
    // all vertices with indegree 0 
    queue<int> q; 
    for (int i = 0; i < V; i++) 
        if (in_degree[i] == 0) 
            q.push(i); 
  
    // Initialize count of visited vertices 
    int cnt = 0; 
  
    // Create a vector to store 
    // result (A topological 
    // ordering of the vertices) 
    vector<int> top_order; 
  
    // One by one dequeue vertices 
    // from queue and enqueue 
    // adjacents if indegree of 
    // adjacent becomes 0 
    while (!q.empty()) { 
        // Extract front of queue 
        // (or perform dequeue) 
        // and add it to topological order 
        int u = q.front(); 
        q.pop(); 
        top_order.push_back(u); 
  
        // Iterate through all its 
        // neighbouring nodes 
        // of dequeued node u and 
        // decrease their in-degree 
        // by 1 
        list<int>::iterator itr; 
        for (itr = adj[u].begin(); 
             itr != adj[u].end(); itr++) 
  
            // If in-degree becomes zero, 
            // add it to queue 
            if (--in_degree[*itr] == 0) 
                q.push(*itr); 
  
        cnt++; 
    } 
  
    // Check if there was a cycle 
    if (cnt != V) { 
        //cout << "There exists a cycle in the graph\n"; 
        return; 
    } 
  
    // Print topological order 
    for (int i = 0; i < top_order.size(); i++)
        //cout<<top_order[i]<<" ";
        res.push_back(top_order[i]);
    
    reverse(res.begin(), res.end());
} 

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        Graph g(numCourses);
        vector<int> res;
        
        for (int i = 0; i < prerequisites.size(); i++) {
            g.addEdge(prerequisites[i][0], prerequisites[i][1]);
        }
        
        g.topologicalSort(res);
        
        return res;
    }
};
