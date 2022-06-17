/*
Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: true
 
Constraints:

0 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti < endi <= 10^6

Edge cases :
1. interval length = 0
2. [[7,10],[2,5],[3,4]]

Solution : Like Merge Intervals and Car pool problem or Overlapping Intervals, the go forward is to first sort the intervals on the basis of start time.
Then start tracking the end time of each interval and if any overlap found, return false else update the latest end time of interval.

Time Complexity : O(n)
Space Complexity : O(1)
*/

class Solution {
    public boolean canAttendMeetings(int[][] intervals) {
        if (intervals.length == 0) {
            return true;
        }
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));
        
        int end = intervals[0][1];
        
        for (int i = 1; i < intervals.length; i++) {
            if (intervals[i][0] < end) {
                return false;
            } else if (end < intervals[i][1]) {
                end = intervals[i][1];
            }
        }
        return true;
    }
}
