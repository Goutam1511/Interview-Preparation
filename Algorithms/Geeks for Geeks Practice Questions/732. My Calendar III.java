/*
A k-booking happens when k events have some non-empty intersection (i.e., there is some time that is common to all k events.)
You are given some events [start, end), after each given event, return an integer k representing the maximum k-booking between all the previous events.
Implement the MyCalendarThree class:

MyCalendarThree() Initializes the object.
int book(int start, int end) Returns an integer k representing the largest integer such that there exists a k-booking in the calendar.

Example 1:

Input
["MyCalendarThree", "book", "book", "book", "book", "book", "book"]
[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output
[null, 1, 1, 2, 3, 3, 3]

Explanation
MyCalendarThree myCalendarThree = new MyCalendarThree();
myCalendarThree.book(10, 20); // return 1, The first event can be booked and is disjoint, so the maximum k-booking is a 1-booking.
myCalendarThree.book(50, 60); // return 1, The second event can be booked and is disjoint, so the maximum k-booking is a 1-booking.
myCalendarThree.book(10, 40); // return 2, The third event [10, 40) intersects the first event, and the maximum k-booking is a 2-booking.
myCalendarThree.book(5, 15); // return 3, The remaining events cause the maximum K-booking to be only a 3-booking.
myCalendarThree.book(5, 10); // return 3
myCalendarThree.book(25, 55); // return 3

Constraints:

0 <= start < end <= 10^9
At most 400 calls will be made to book.

Solution : The sweep-line algorithm works for both My Calendar I, My Calendar II & My Calendar III & is a classic implementation of TreeMap. The same approach is used
here as well and is actually a simpler version than My Calendar II where we had to figure out triple booking. 
Intuition
If we look at each time point separately, our task is to find out how many events are going on at this time point and find the time point of the max number of events.
Every time we book a new event [start, end), what we actually do is add 1 to the event counts to all time points in the range [start, end). The final result of each
book call is exactly the max count of a single time in the whole range of [1, 1e9).
For such kind of problem that increases all counts in some ranges by some constant values several times and asks to obtain all counts for those time points, we have a
very classic solution called sweep-line algorithm: instead of keeping all values of counts in a traditional way, we use a differential array to represent the change
that occurs at each time point. In this problem, we will increase the count by 1 at point start and decrease the count by 1 at point end. After enumerating all booked
events and updating the differential array, we can simulate scanning the differential array with a vertical sweep-line from the origin time point 0 to the maximum 1e9
and obtain the prefix sum at each time point t, which is also the event count of time t. All we need to do now is find the maximum value of such counts when we scan
the array.

Algorithm
Initialize a HashMap diff as empty. We use a HashMap here instead of an array because the times given by the inputs are sparse as there are at most 400 calls of book()
function, we don't have to create records for all numbers in [1, 1e9).
Each time we book a new event [start, end)
Update the diff[start] by adding 1 while diff[end] by subtracting 1.
Initialize an integer cur = 0 to represent the number of intervals at the current time
Enumerate all times that have records in diff in order, accumulate the corresponding value to cur, and record the max value of cur during our enumeration, which is the
result of book() call.

Complexity Analysis
Let N be the number of events booked.

Time Complexity: O(N^2)
For each new event, we update the changes at two points in O(logN) because we keep the TreeMap in sorted order. Then we traverse diff in O(N) time.

Space Complexity: O(N), the size of allBookings.
*/

import java.util.Collections;
class MyCalendarThree {
    Map<Integer, Integer> allBookings = new TreeMap<>();
    public MyCalendarThree() {
        
    }
    
    public int book(int start, int end) {
        allBookings.put(start, allBookings.getOrDefault(start, 0) + 1);
        allBookings.put(end, allBookings.getOrDefault(end, 0) - 1);
        int val = 0;
        int maxVal = 0;
        for (int i : allBookings.values()) {
            val += i;
            maxVal = Math.max(val, maxVal);
        }
        return maxVal;
    }
}
