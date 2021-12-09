/*Given an array of non-negative integers arr, you are initially positioned at start index of the array. 
When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.
Notice that you can not jump outside of the array at any time.

Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
 

Constraints:

1 <= arr.length <= 5 * 104
0 <= arr[i] < arr.length
0 <= start < arr.length

Solution : At first, might seem like a dp/recursion problem like other Jump game problem variations but if we carefully give a look, it is actually
a graph problem because -
 - from any index we can only move in two directions
 - once an index is visited we know whether we can reach our destination from there or not so no need to revisit again unlike backtracking/recursion
Both BFS and DFS applicable. BFS gives faster result.

Edge cases :
Input : [4,2,3,0,3,1,2]
         5
Output : true
Input : [3,0,2,1,2]
         2
Output : false
Input : [4,2,3,0,3,1,2]
         0
Output : true
Input : [0,1]
         1
Output : true
*/

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        queue<pair<int, int>> q;
        set<int> visited;
        q.push(make_pair(start, arr[start]));
        
        while (!q.empty()) {
            int currentPos = q.front().first;
            int currentVal = q.front().second;
            //cout<<currentPos<<" "<<currentVal<<endl;
            q.pop();
            
            if (currentVal == 0)
                return true;
            if (currentPos - currentVal >= 0 &&
                !visited.count(currentPos))
                q.push(make_pair(currentPos - currentVal,
                                 arr[currentPos - currentVal]));
            if (currentPos + currentVal <= arr.size() - 1
               && !visited.count(currentPos))
                q.push(make_pair(currentPos + currentVal,
                                 arr[currentPos + currentVal]));
            visited.insert(currentPos);
        }
        
        return false;
    }
};
