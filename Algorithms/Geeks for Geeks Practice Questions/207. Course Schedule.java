/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where
prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.

Solution : Topological sort
*/

class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        int[] noOfDependencyCourse = new int[numCourses];
        List<Set<Integer>> dependentCourses = new ArrayList<>();
        
        for (int i = 0; i < numCourses; i++) {
            dependentCourses.add(new HashSet<>());
        }
        
        for (int[] prereq : prerequisites) {
            noOfDependencyCourse[prereq[0]]++; //Increase the counter for the course who has dependency
            dependentCourses.get(prereq[1]).add(prereq[0]); //Add the dependent on the list of course which has dependency on
        }
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < numCourses; i++) {
            if (noOfDependencyCourse[i] == 0) { //Check courses which has no dependency & add to queue
                q.add(i);
            }
        }
        int courseCompleted = 0;
        while (!q.isEmpty()) {
            int toProcess = q.poll(); //Process current course that doesn't have any dependency and increase the count of courses processed
            courseCompleted++;
            
            for (int dependent : dependentCourses.get(toProcess)) { 
                noOfDependencyCourse[dependent]--; //For every course which is dependent on current course, decrease dependency
                
                if (noOfDependencyCourse[dependent] == 0) { //If the dependent course count is empty then all dependencies visited, insert in queue
                    q.add(dependent);
                }
            }
        }
        
        return courseCompleted == numCourses; //If all courses can be visited then there is no cycle
    }
}
