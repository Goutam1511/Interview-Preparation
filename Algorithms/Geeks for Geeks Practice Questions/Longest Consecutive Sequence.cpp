/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
Your algorithm should run in O(n) complexity.

Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Solution : The problem is difficult in the sense that we have to keep track of all elements seen beforehand but we cannot sort.
So what we do is maintain a set of all elements and then again traverse the array second time. Now, for each element we go on decrementing,
counting how many previous(preceding) element we can dig upto with the help of our set. We keep track of this count. Simultaenously,
we keep on removing all these elements from our set so that when we face the same elements at a later point, we don't need to consider
them again. When we reach a point, where we see no more preceding element in our set, there might be two case - in our array that 
preceding element was not at all there, else we have already calculated the longest sequence possible upto that element. So, to check 
if second case is true, we search our map to find if the longest sequence for that element is present, if present we add our current 
count with that to obtain the longest sequence upto the current element in consideration.

DRY RUN : Initially, our set contains : [100, 4, 200, 1, 3, 2]
We start with 100, we don't have 99. So, max seq length for 100 - 1. Map = {(100, 1)} Set = [4, 200, 1, 3, 2] longestseq = 1.
We encounter 4, so we keep on decrementing. We have 4, 3, 2, 1 in our set, so count = 4. Set = [200] Map = {(100, 1), (4, 4)} longestseq = 4
Similarly for 200, count = 1. set = [] map = {(100, 1), (4, 4), (200, 1)}. longestseq = 4.
So longest sequence is obtained as 4.

NOTE : Initially, observing the above example gives a feel that use of the map is redundant, but if the same input had been -
[100, 200, 1, 3, 4, 2], we can see that we need the map to track the sequence length of 3 and add it when we encounter 4, as 3 
would have been removed from the set but we would be getting the sequence length of 3 checking the map and adding it with 1 for 4,
to get the actual sequence length of 4.

Space Complexity : O(n) - for hash and map
Time Complexity : Although initially checking the solution, it seems we have one inner loop inside the other, but giving a closer look,
we are actually counting each element in the array only once, so - O(n).

LeetCode Solution : https://leetcode.com/problems/longest-consecutive-sequence/solution/
*/

class Solution {
public:
    int longestseq = 0; //To track the maximum longest sequence seen so far
    int longestConsecutive(vector<int>& nums) {
        set<int> s; //To track all the elements in the array
        map<int, int> trackseqlength; //To track sequence length till that element
        for (int n : nums) {
            s.insert(n);  //Put all the elements in hash
        }
        
        for (int n : nums) { //For each element, check how many preceding elements are there along with it
            int count = 0;
            int beg   = n;       //Temporary var not to loose the element from which we started counting down
            while (s.count(n)) { //While the preceding element exits and have not been considered yet
                count++;         //Increment the sequence length
                s.erase(n);      //Remove that number from hash, not to get considered again 
                n--;             //Decrement to check the next preceding number
            }
            /* Check if the next preceding element has already been considered that's why *
             * not available in set or it has never been existent at all in the array.    */
            if (trackseqlength.count(n)) {
                count += trackseqlength[n]; //If already considered, add it's sequence length to the current element sequence length
            }
            /* Update the map with the current element & sequence length pair so that if an element consecutive to it appears later, it's *
             * original sequence length can be tracked through the map since traces of the current element is being erased from set.      */
            trackseqlength.insert(make_pair(beg, count));
            longestseq = max(count, longestseq); //Update the longest sequence seen so far
        }
        return longestseq;
    }
};
