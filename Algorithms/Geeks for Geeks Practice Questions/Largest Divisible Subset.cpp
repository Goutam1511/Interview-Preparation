/*
Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies:
Si % Sj = 0 or Sj % Si = 0.
If there are multiple solutions, return any subset is fine.
Example 1:
Input: [1,2,3]
Output: [1,2] (of course, [1,3] will also be ok)
Example 2:
Input: [1,2,4,8]
Output: [1,2,4,8]

Corner Case Input: [2,4,8,10,240] //If we stop finding the largest subset by checking 240%10 == 0, we will be fooled
Output : [2, 4, 8, 240]

VISUAL DRY RUN :
Input      : [4, 8, 10, 240]
Subsetlen  : [1, 2, 1, 3] 
Last Index : [-1, 0, -1, 1] 

Subset Len of 4   = {4} ------> 1
Subset Len of 8   = {4, 8} ---> 2
Subset Len of 10  = {10} -----> 1
Subset Len of 240 = {4, 8, 240} -> 3 // Note even {10, 240} is a subset but not largest hence we have to traverse whole array while forming subset len array

Last index/addr of 4 -> -1 (No previous divisor)
Last index/addr of 8 -> 0 (Index of 4)
Last index/addr of 10 -> -1 (No previous divisor)
Last index/addr of 240 -> 1 (Index of 8)

Solution Approach : It's a kind of DP. The problem boils down to the problem that we have to find the largest subset where each element
is a multiple to its previous and all other elements. So, we start by sorting the array so that for every j > i, if nums[j] % nums[i] == 0,
then nums[j] is a multiple of nums[i] and all other elements before i for which nums[i] is a multiple of. Another motive of sorting is that,
all divisors of an element will be before it. Now we keep track of the maximum subset lengths that is possible including an element by an
array of same size - "maxsubsetlen". By default, it will be initialized with all 1 as even if an element is not divisible by any other element
it can give a maximum subset of length 1 by including itself. Now for every element from i = 1 to n(as for i = 0, there is no divisor before),
we traverse the whole array till before that element and find if there is a divisor nums[j] then maxsubsetlen[i] = maxsubsetlen[j] + 1 if 
maxsubsetlen[j] + 1 is greater than current maxsubsetlen[i]. Later we travrse this array and we find the maxsubset length possible like this. 
Also while doing this we keep on tracking the index of the divisor that we are considering to tag the current element with as a set in an 
array "lastaddr". This array will be later used to backtrack and find the largest divisible subset - our desired subset.
*/

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<long int> maxsubsetlen(nums.size(), 1); //Keep track of maximum divisible subset for every element, by default min length - 1
        vector<long int> lastaddr(nums.size(), -1); //Keep track of last index before that element which is part of the divisible subset
        vector<int> largestdivisiblesubset; //Required result set
        int i(0), j(0), lastindex(-1);
        long int maxlen = INT_MIN;
        
        sort(nums.begin(), nums.end()); //Sort the input array to keep all divisors of an element before it
        
        for (i = 1; i < nums.size(); i++) {
            for (j = i - 1; j >= 0; j--) {
            /* If nums[i] is divisible by any element before it then a subset can be formed with nums[i] and nums[j] and divisors of nums[j], *
             * but not necessarily that subset is longest for nums[i], so keep on checking the whole array for a bigger subset and update max *
             * possible subset length along with the index of the previous divisor contributing to that subset.                               */
                if (nums[i] % nums[j] == 0 && (maxsubsetlen[j] + 1 > maxsubsetlen[i])) {
                    maxsubsetlen[i] = maxsubsetlen[j] + 1; //Update maxsubsetlen
                    lastaddr[i]     = j; //Update last index or address. This array will help in backtracking to find the result set
                    //break; //Don't break here, check corner case
                }
            }
        }
        
        for (i = 0; i < nums.size(); i++) { //Find the length of the largest divisible subset
            if (maxsubsetlen[i] > maxlen) {
                maxlen    = maxsubsetlen[i];
                lastindex = i; //If a larger divisible subset is found, then update the index with the index of the last element in that subset
            }
        }
        
        //Debug prints
        /*for (i = 0; i < nums.size(); i++) {
            cout<<maxsubsetlen[i]<<" ";
        }
        cout<<endl;
        
        for (i = 0; i < nums.size(); i++) {
            cout<<lastaddr[i]<<" ";
        }
        cout<<endl;*/
        
        /* Backtrack and find the largest divisible subset. The smallest divisor has an entry of -1 in the      *
         * lastaddr array to indicate the end of the subset. So stop backtracking when -1 is found in lastaddr. */                   
        while (lastindex != -1) {  
            largestdivisiblesubset.push_back(nums[lastindex]);
            lastindex = lastaddr[lastindex];
        }
        // Sort it for maintaing the sequence in subset
        sort(largestdivisiblesubset.begin(), largestdivisiblesubset.end());
        
        return largestdivisiblesubset;
        
    }
};
