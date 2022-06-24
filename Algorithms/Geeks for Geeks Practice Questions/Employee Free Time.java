/*
We are given a list schedule of employees, which represents the working time for each employee.
Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.
Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.
(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. 
For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).  Also, we wouldn't include 
intervals like [5, 5] in our answer, as they have zero length.

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]

Constraints:

1 <= schedule.length , schedule[i].length <= 50
0 <= schedule[i].start < schedule[i].end <= 10^8

Solution : This is an extension to https://leetcode.com/problems/insert-interval/
We first merge all the schedules of employees to get a final set of intervals when all employees are engaged. And then loop over that final set of intervals
to find intervals where employees are free.
*/

/*
// Definition for an Interval.
class Interval {
    public int start;
    public int end;

    public Interval() {}

    public Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
    public List<Interval> mergeInterval(List<Interval> intervals, Interval in) {
        int i = 0, n = intervals.size();
        List<Interval> res = new ArrayList<>();
        while (i < n && intervals.get(i).end < in.start) {
            res.add(intervals.get(i++));
        }
        Interval mergedInterval = in;
        
        /* Merge all the overlapping intervals with new interval together.
         * Number of overlapping intervals with new interval can be several.
         */
        while (i < n && intervals.get(i).start <= in.end) {
            mergedInterval.start = Math.min(in.start,
                                         intervals.get(i).start);
            mergedInterval.end = Math.max(in.end, intervals.get(i).end);
            i++;
        }
        res.add(mergedInterval); //Add final merged interval
        while (i < n) res.add(intervals.get(i++)); //Add remaining non-overlapping intervals
        
        return res;
    }
    public List<Interval> mergeTwoIntervalList(List<Interval> s1,
                                              List<Interval> s2) {
        List<Interval> res = new ArrayList<>(s1);
        for (int i = 0; i < s2.size(); i++) {
            res = mergeInterval(res, s2.get(i));
        }
        return res;
    }
    public List<Interval> employeeFreeTime(List<List<Interval>> schedule) {
        List<Interval> mergedIntervals = schedule.get(0);
        for (int i = 1; i < schedule.size(); i++) {
            mergedIntervals = mergeTwoIntervalList(mergedIntervals, schedule.get(i));
        }
        
        /*for (int i = 0; i < mergedIntervals.size(); i++) {
            System.out.println(mergedIntervals.get(i).start + " " + mergedIntervals.get(i).end);
        }*/
        
        List<Interval> res = new ArrayList<>();
        for (int i = 0; i < mergedIntervals.size() - 1; i++) {
            if (mergedIntervals.get(i + 1).start
                - mergedIntervals.get(i).end > 0) {
                res.add(new Interval(mergedIntervals.get(i).end,
                                    mergedIntervals.get(i + 1).start));
            }
        }
        
        return res;
    }
}
