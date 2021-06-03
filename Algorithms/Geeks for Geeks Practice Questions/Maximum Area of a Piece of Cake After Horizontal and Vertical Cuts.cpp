/*
Q: https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
Given a rectangular cake with height h and width w, and two arrays of integers horizontalCuts and verticalCuts where horizontalCuts[i] is the distance from the top of the 
rectangular cake to the ith horizontal cut and similarly, verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays horizontalCuts and verticalCuts.
Since the answer can be a huge number, return this modulo 10^9 + 7.

Example 1:
Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
Output: 4 
Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts.
After you cut the cake, the green piece of cake has the maximum area.

Example 2:
Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
Output: 6
Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. 
After you cut the cake, the green and yellow pieces of cake have the maximum area.

Example 3
Input: h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
Output: 9
Constraints:

2 <= h, w <= 10^9
1 <= horizontalCuts.length < min(h, 10^5)
1 <= verticalCuts.length < min(w, 10^5)
1 <= horizontalCuts[i] < h
1 <= verticalCuts[i] < w
It is guaranteed that all elements in horizontalCuts are distinct.
It is guaranteed that all elements in verticalCuts are distinct.

Solution :
Sort the arrays, then compute the maximum difference between two consecutive elements for horizontal cuts and vertical cuts.  
The answer is the product of these maximum values in horizontal cuts and vertical cuts.
Complexity : Time : O(nlogn) for sorting & Space : O(1)

Corner Case : 1. For large input store the product in long int and return the modulo otherwise int will overflow.
              Also typecast before multiplying
              2. Consider the two sides also while finding max area see Example Input 2.
*/

#define mod 1000000007

class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        int maxhorizontal = INT_MIN, maxvertical = INT_MIN, i;
        
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        for (i = 0; i < horizontalCuts.size() - 1; i++) {
            maxhorizontal = max(maxhorizontal, horizontalCuts[i + 1] - horizontalCuts[i]);
        }
        for (i = 0; i < verticalCuts.size() - 1; i++) {
            maxvertical = max(maxvertical, verticalCuts[i + 1] - verticalCuts[i]);
        }
        
        maxhorizontal = max(maxhorizontal, (horizontalCuts[0] - 0));
        maxhorizontal = max(maxhorizontal, (h - horizontalCuts[horizontalCuts.size() - 1]));
        maxvertical = max(maxvertical, (verticalCuts[0] - 0));
        maxvertical = max(maxvertical, (w - verticalCuts[verticalCuts.size() - 1]));
        
        long int res = (long)(maxhorizontal % mod) * (long)(maxvertical % mod);
        return (res % mod);
    }
};
