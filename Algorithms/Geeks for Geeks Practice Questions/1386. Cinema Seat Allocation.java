/*
A cinema has n rows of seats, numbered from 1 to n and there are ten seats in each row, labelled from 1 to 10 as shown in the figure above.
Given the array reservedSeats containing the numbers of seats already reserved, for example, reservedSeats[i] = [3,8] means the seat located in row 3 and labelled
with 8 is already reserved.
Return the maximum number of four-person groups you can assign on the cinema seats. A four-person group occupies four adjacent seats in one single row.
Seats across an aisle (such as [3,3] and [3,4]) are not considered to be adjacent, but there is an exceptional case on which an aisle split a four-person group,
in that case, the aisle split a four-person group in the middle, which means to have two people on each side.

Example 1:

Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
Output: 4
Explanation: The figure above shows the optimal allocation for four groups, where seats mark with blue are already reserved and contiguous seats mark with orange are for one group.
Example 2:

Input: n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
Output: 2
Example 3:

Input: n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
Output: 4

Constraints:

1 <= n <= 10^9
1 <= reservedSeats.length <= min(10*n, 10^4)
reservedSeats[i].length == 2
1 <= reservedSeats[i][0] <= n
1 <= reservedSeats[i][1] <= 10
All reservedSeats[i] are distinct.

Solution : It is evident that at most 2 families can seat in a row. So we greedily check if we can allocate seats for two families, one family or none. We process only
rows that appear in the input, for other rows we can always allocate seats for two families - i.e just add (n - number of input seats) * 2. For processing the reserved
seats in the input, we store all the row details provided in the input in a map using bit manipulation. We parse the input and set the bit in the row layout that we
are storing as at max there are 10 seats. Check the images provided in question for better understanding : https://leetcode.com/problems/cinema-seat-allocation/

Time & Space Complexity : O(n)
*/

class Solution {
    public static int firstGroupMask  = 0b111100000;
    public static int middleGroupMask = 0b1111000;
    public static int thirdGroupMask  = 0b11110;
    
    public int maxNumberOfFamilies(int n, int[][] reservedSeats) {
        Map<Integer, Integer> reservedSeatsLayout = new TreeMap<>();
        
        for (int[] seat : reservedSeats) {
            reservedSeatsLayout.putIfAbsent(seat[0], 0);
            reservedSeatsLayout.put(seat[0],
                                    reservedSeatsLayout.get(seat[0]) | 1 << (10 - seat[1]));
        }
        
        int countOfFamilies = (n - reservedSeatsLayout.size()) * 2;
        
        for (Map.Entry<Integer, Integer> entry : reservedSeatsLayout.entrySet()) {
            int layout = entry.getValue();
            //System.out.println("Checking for " + entry.getKey() + " " + layout);
            boolean checkMiddle = true;
            if ((layout & firstGroupMask) == 0) {
                //System.out.println("Left end Available");
                countOfFamilies++;
                checkMiddle = false;
            }
            if ((layout & thirdGroupMask) == 0) {
                //System.out.println("Right end Available");
                countOfFamilies++;
                checkMiddle = false;
            }
            if (checkMiddle && ((layout & middleGroupMask) == 0)) {
                //System.out.println("Middle seats Available");
                countOfFamilies++;
            }
        }
        
        return countOfFamilies;
    }
}
