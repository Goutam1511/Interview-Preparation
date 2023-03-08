/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile.
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23

Constraints:

1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9

Solution : Exact same problem as 2187. Minimum Time to Complete Trips / 1011. Capacity To Ship Packages Within D Days / Aggressive Cows using Binary Search
*/
class Solution {
    public boolean canEat(int[] piles, int time, int speed) {
        int timeTaken = 0;
        for (int p : piles) {
            timeTaken += (int)Math.ceil((double)p / (double)speed);
            if (timeTaken > time) return false;
        }
        return timeTaken <= time;
    }
    public int minEatingSpeed(int[] piles, int h) {
        int maxSpeed = Arrays.stream(piles).max().getAsInt();
        int minSpeed = 1;
        
        int minSpeedRequired = maxSpeed;

        while (maxSpeed >= minSpeed) {
            int middle = minSpeed + (maxSpeed - minSpeed) / 2;
            
            if (canEat(piles, h, middle)) {
                minSpeedRequired = middle;
                maxSpeed = middle - 1;
            } else {
                minSpeed = middle + 1;
            }
        }
        return minSpeedRequired;
    }
}
