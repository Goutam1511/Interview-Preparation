/*
There are 2N people a company is planning to interview. The cost of flying the i-th person to city A is costs[i][0], and the cost of flying the i-th person to city B is costs[i][1].

Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.

 

Example 1:

Input: [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation: 
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.

 

Note:

    1 <= costs.length <= 100
    It is guaranteed that costs.length is even.
    1 <= costs[i][0], costs[i][1] <= 1000

Solution Approach : This is a classic Greedy Problem. Approach is to sort the costs array descending according to the difference of
cost of sending the person to city A & sending the person to city B. Then sum up the cost of sending first N persons to A & last N
persons to B. The idea is to include those N persons in A for whom sending to A will save maximum cost in a greedy fashion. The remaining
N persons are sent to B.
*/

class Solution {
public:
    static bool comp(vector<int> v1, vector<int> v2) {
        return (v1[0] - v1[1]) < (v2[0] - v2[1]);
    }
    
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int res = 0, i = 0;
        sort(costs.begin(), costs.end(), Solution::comp);
        for (i = 0; i < costs.size() / 2; i++) {
            res += costs[i][0];
        }
        for (i = costs.size() / 2; i < costs.size(); i++) {
            res += costs[i][1];
        }
        return res;
    }
};
