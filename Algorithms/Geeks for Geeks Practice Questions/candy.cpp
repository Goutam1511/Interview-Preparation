/*
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Solution : Classic DP problem. Two pass solution - with first pass we gather all the minimum candies that we can allocate without hurting the interest
of the elements in the left because while we are coming from right to left, the current element always gets more candies than the right if required.
In the second pass, while we go from left to right, we take care of the possibility that if somehow an element got more candies than the right neighbour,
the right neighbour can again get compensated as we now account the exact number of final candies in both the neighbour.(see corner case 7)
Also in the second pass, we must consider the maximum value of both the sides while recalculating. (see corner case 8)

Complexity : Time & Space - O(n)

Corner cases :-
1. [1,0,2] --> Minpoint at mid
2. [1,2,2] --> Monotonic increasing
3. [1,0,0,2] --> Minpoint at mid with two equals
4. [1,2,2,1] --> Bell curve
5. [1,2,1,2,1] --> Zigzag
6. [1] --> Single element
7. [1,2,87,87,87,2,1] 
8. [1,3,4,5,2]
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int minsum = 0;
        vector<int> result(ratings.size(), 1);
        
        if(ratings.size() == 1) {
            return 1;
        }
        
            for (int i = ratings.size() - 1; i >= 0; i--) { //First pass from right to left
                //cout<<i<<endl;
                if (i == ratings.size() - 1) { //Rightmost
                    if (ratings[i] > ratings[i - 1]) {
                        result[i] = result[i - 1] + 1;
                    }
                } else if (i == 0) { //Leftmost
                    if (ratings[i] > ratings[i + 1]) {
                        result[i] = result[i + 1] + 1;
                    }
                } else {
                    if (ratings[i - 1] < ratings[i]) {
                        result[i] = result[i - 1] + 1;
                    }
                    if (ratings[i + 1] < ratings[i]) {
                        result[i] = result[i + 1] + 1;
                    }
                }
            }
        
        for (int i = 0; i < ratings.size(); i++) { //Second pass in opposite direction to recalculate
                //cout<<i<<endl;
                if (i == ratings.size() - 1) {
                    if (ratings[i] > ratings[i - 1]) {
                        result[i] = result[i - 1] + 1;
                    }
                } else if (i == 0) {
                    if (ratings[i] > ratings[i + 1]) {
                        result[i] = result[i + 1] + 1;
                    }
                } else {
                    if (ratings[i - 1] < ratings[i]) {
                        result[i] = result[i - 1] + 1;
                    }
                    if (ratings[i + 1] < ratings[i]) {
                      //Here to consider the maximum not to reduce the maximum calculated in above if...
                        result[i] = max(result[i], result[i + 1] + 1); 
                    }
                }
            }
        
        for (auto i : result) {
            //cout<<i<<" ";
            minsum += i;
        }
        
        return minsum;
    }
};
