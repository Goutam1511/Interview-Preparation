/*
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.
An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
 

Constraints:

1 <= k <= arr.length
1 <= arr.length <= 104
arr is sorted in ascending order.
-104 <= arr[i], x <= 104

Corner Case :
Input = [1,3]
k = 1
x = 2

Solution : First find the closest element to x using binary search. Insert that closest element. Then move either left or right depending on whichever is close
and keep on inserting in the result array. While moving be cautious to step on a valid index(we might run out of bounds). Also, while inserting in the result array,
make sure to insert in front if we are picking element on left and insert at back if we are picking element on right. That will eliminate the need of further sorting
the result

Complexity : O(n) & O(1)
*/

class Solution {
public:
    // Returns element closest to target in arr[]
    int findClosest(vector<int> arr, int n, int target)
    {
        // Corner cases
        if (target <= arr[0])
            return 0;
        if (target >= arr[n - 1])
            return n - 1;

        // Doing binary search
        int i = 0, j = n, mid = 0;
        while (i < j) {
            mid = (i + j) / 2;

            if (arr[mid] == target)
                return mid;

            /* If target is less than array element,
                then search in left */
            if (target < arr[mid]) {

                // If target is greater than previous
                // to mid, return closest of two
                if (mid > 0 && target > arr[mid - 1])
                    return getClosest(arr, mid - 1,
                                      mid, target);

                /* Repeat for left half */
                j = mid;
            }

            // If target is greater than mid
            else {
                if (mid < n - 1 && target < arr[mid + 1])
                    return getClosest(arr, mid,
                                      mid + 1, target);
                // update i
                i = mid + 1;
            }
        }

        // Only single element left after search
        return mid;
    }
    
    int getClosest(vector<int> arr, int i, int j,
               int target)
    {
      /* If element at left is not closer only then pick the right one,
       * else always pick left as even if the difference is equal,
       * left element < right element as array is sorted.
       */
        if (abs(target - arr[i]) > abs(arr[j] - target))
            return j;
        else
            return i;
    }
    
    vector<int> findClosestElements(vector<int>& arr, int k, int target) {
        vector<int> result;
        int closest = findClosest(arr, arr.size(), target), i = 0, j = 0, n = arr.size();
        bool bothvalid = false;
            
        //Target is smaller than the first element in array, hence pick k elements from starting
        if (closest == 0) { 
            for (i = 0; i < k; i++) {
                result.push_back(arr[i]);
            }
            return result;
        } else if (closest == n - 1) { //The reverse scenario, target is greater than all elements
            while (k--) {
                result.push_back(arr[closest--]);
            }
            reverse(result.begin(), result.end());
            return result;
        }
        
        result.push_back(arr[closest]); //Insert closest element
        k--;
        i = closest - 1;
        j = closest + 1;
        bothvalid = i >= 0 && j < n ? true : false;
        
        while (k) {
            //Check if we are still somewhere in the middle of array and i & j are both within bounds of array
            if (bothvalid) { 
                if (abs(target - arr[i]) > abs(arr[j] - target)) {
                  ////Insert this at end as right elements will be always bigger than the previous
                    result.push_back(arr[j]);
                    j++;
                } else {
                  //Insert this at beginning as left elements will be always smaller than the previous
                    result.insert(result.begin(), arr[i]);
                    i--;
                }
            } else if (i >= 0) { //If we have already reached right bound, pick elements only from left
                result.insert(result.begin(), arr[i--]);
            } else { //Pick only elements from right as we reached left bounds
                result.push_back(arr[j++]);
            }
            k--;
            bothvalid = i >= 0 && j < n ? true : false; //Test new i & j within bounds
        }
        
        return result; //Result is always sorted!
    }
};
