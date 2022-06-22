/*
Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.

Example 1:

Input: timePoints = ["23:59","00:00"]
Output: 1
Example 2:

Input: timePoints = ["00:00","23:59","00:00"]
Output: 0

Constraints:

2 <= timePoints.length <= 2 * 104
timePoints[i] is in the format "HH:MM".

Solution : Sort the timepoints according to time converted to minutes. Iterate the timestamps and calculate the difference of consecutive timepoints. Only corner
case is round the clock case that is last timepoint to first timepoint - for example "23:59" to "00:00". That case we handle separately.

Time Complexity : O(nlogn) Space Complexity : O(1).
*/

class Solution {
    public int convertTimeToMinute(String a) {
        int h1 = Integer.parseInt(a.split(":")[0]);
        int m1 = Integer.parseInt(a.split(":")[1]);
        return h1 * 60 + m1;
    }
    public int getDiff(String a, String b) {
        return Math.abs(convertTimeToMinute(a) - convertTimeToMinute(b));
    }
    public int findMinDifference(List<String> timePoints) {
        Collections.sort(timePoints,
                        (a, b) -> {
                            return convertTimeToMinute(a)
                                - convertTimeToMinute(b);
                        });
        int mDiff = Integer.MAX_VALUE;
        for (int i = 0; i < timePoints.size() - 1; i++) {
            mDiff = Math.min(mDiff, getDiff(timePoints.get(i),
                                            timePoints.get(i + 1)));
        }
        int corner = convertTimeToMinute(timePoints.get(0))
            + (1440 - convertTimeToMinute(timePoints.get(timePoints.size()-1)));
        return Math.min(mDiff, corner);
    }
}
