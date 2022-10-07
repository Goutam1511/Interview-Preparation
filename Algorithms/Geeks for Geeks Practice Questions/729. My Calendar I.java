/*
You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a double booking.
A double booking happens when two events have some non-empty intersection (i.e., some moment is common to both events.).

The event can be represented as a pair of integers start and end that represents a booking on the half-open interval [start, end), the range of real numbers x such
that start <= x < end.

Implement the MyCalendar class:

MyCalendar() Initializes the calendar object.
boolean book(int start, int end) Returns true if the event can be added to the calendar successfully without causing a double booking. Otherwise, return false and do
not add the event to the calendar.

Example 1:

Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]

Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20. 

Constraints:

0 <= start < end <= 109
At most 1000 calls will be made to book.

Solution : We know a TreeMap is a good way to keep track of intervals sorted according to start time, hence we keep a treemap of the booking intervals in form of
<start, end - 1> key-value pair. TreeMap also gives us the facility to search a lower value or upper value in O(logN) time hence we use the same to find before booking
if there is any other interval which has a start time lesser than the current booking request start time and end time greater than the current booking request start
time i.e mathematically - lower interval start time <= current booking request start time <= lower interval end time or if there is any other interval which has a
start time lesser than the current booking request end time and end time greater than the current booking request end time i.e mathematically -
upper interval start time <= current booking request end time <= upper interval end time. If we have any such interval, we return false because there is an overlap &
hence booking not possible else we add the (start, end - 1) key-value pair in our current bookings treemap and return true.

Time Complexity  : O(logN) for each book() call
Space Complexity : O(N) for treeMap
*/

class MyCalendar {
    TreeMap<Integer, Integer> intervals = new TreeMap<>();
    public MyCalendar() {
        
    }
    
    public boolean book(int start, int end) {
        Map.Entry<Integer, Integer> floor = intervals.floorEntry(start);
        if (floor != null && floor.getValue() >= start) {
            return false;
        }
        Map.Entry<Integer, Integer> ceil = intervals.ceilingEntry(start);
        if (ceil != null && ceil.getKey() < end) {
            return false;
        }
        intervals.put(start, end - 1);
        return true;
    }
}
