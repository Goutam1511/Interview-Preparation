/*
Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Note:
1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A is sorted in non-decreasing order.

Corner Cases : 1) Input containing all negatives may give seg fault. 2) Input containing all positives.

Solution : We find out the first positive from the array and go with a two pointer approach. We first start from the least negative and iterate
backwards to max negative in the array and while doing this, we store their squares in an array. Again, we start from first positive and go till
end storing the squares of all the positives. Obviously, these two arrays are sorted. Now the problem boils down to merging two sorted arrays.
*/

class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int i = 0, j = 0, n = A.size();
        vector<int> squareofneg;
        vector<int> squareofpos;
        vector<int> res;
        
        while (j < A.size() && A[j] < 0) { //Find first positive
            j++;
        }
        
        i = j - 1;
        
        while (i >= 0) { //Iterate back till first to store squares of all negative
            squareofneg.push_back(A[i] * A[i]);
            i--;
        }
        
        while (j < n) { //Traverse all positives and store their squares
            squareofpos.push_back(A[j] * A[j]);
            j++;
        }

        /*for (i = 0; i < squareofneg.size(); i++) {
            cout<<squareofneg[i]<<" ";
        }
        cout<<endl;
        
        for (i = 0; i < squareofpos.size(); i++) {
            cout<<squareofpos[i]<<" ";
        }
        cout<<endl;*/
        
        if (squareofneg.size() == 0) { //If there was no negative, return squares of all positive
            return squareofpos;
        }
        
        if (!squareofpos.size()) //If there was no positive, return squares of all negatives
            return squareofneg;
        
        i = 0;
        j = 0;
        
        while (i < squareofneg.size() && j < squareofpos.size()) { //From here on, merge the two already sorted arrays
            if (squareofneg[i] < squareofpos[j]) {
                res.push_back(squareofneg[i]);
                i++;
            } else {
                res.push_back(squareofpos[j]);
                j++;
            }
        }
        
        while (i < squareofneg.size()) {
            res.push_back(squareofneg[i]);
            i++;
        }
        
        while (j < squareofpos.size()) {
            res.push_back(squareofpos[j]);
            j++;
        }
        
        return res;
    }
};
