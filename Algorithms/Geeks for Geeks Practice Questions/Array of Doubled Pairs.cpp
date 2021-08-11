/*
Given an array of integers arr of even length, return true if and only if it is possible to reorder it such that arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2.

Example 1:

Input: arr = [3,1,3,6]
Output: false
Example 2:

Input: arr = [2,1,2,6]
Output: false
Example 3:

Input: arr = [4,-2,2,-4]
Output: true
Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
Example 4:

Input: arr = [1,2,4,16,8,4]
Output: false

Constraints:

0 <= arr.length <= 3 * 10^4
arr.length is even.
-10^5 <= arr[i] <= 10^5

Solution : The major problem is that there are negative numbers and duplicates as well. If that hadn't been there, we could have just sorted and checked if every
alternate positive number has a double to pair up with. But since, negative numbers and duplicate are there, we first sort the array according to it's absolute
value and then for each number in the sorted array if that number is already used up before. For this, we maintain a frequency count. If the number is already not
used before, then it must have a double since otherwise arr[2 * i + 1] = 2 * arr[2 * i] for every i till arr.size() / 2 would not be satisfied.
If we could iterate the whole sorted array like this then, the array can be reordered.
*/

class Solution {
public:
    static bool comp(int a, int b) {
        if (abs(a) < abs(b)) {
            return true;
        }
        return false;
    }
    bool canReorderDoubled(vector<int>& arr) {
        map<int, int> count;
        
        for (auto i : arr) {
            if (count.count(i)) {
                count[i]++;
            } else {
                count[i] = 1;
            }
        }
        
        sort(arr.begin(), arr.end(), comp);
        /*for (int i : arr) {
            cout<<i<<" ";
        }
        cout<<endl;*/
        for (int x : arr) {
            if (count.count(x) && count[x] <= 0) {
                continue;
            }
            //cout<<x<<endl;
            if (!count.count(2 * x) || count[2 * x] <= 0) {
                return false;
            }
            //cout<<2 * x<<" "<<count[2 * x]<<endl;
            count[2 * x]--;
            count[x]--;
        }
        return true;
    }
};
