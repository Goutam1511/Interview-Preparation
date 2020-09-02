/*
Given an array of 4 digits, return the largest 24 hour time that can be made.
The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from 00:00, a time is larger if more time has elapsed since midnight.
Return the answer as a string of length 5.  If no valid time can be made, return an empty string.

Example 1:

Input: [1,2,3,4]
Output: "23:41"
Example 2:

Input: [5,5,5,5]
Output: ""

Corner Cases :
Input: [5,5,5,5]
Output: ""
Input: [0,0,0,0]
Output: "00:00"
Input: [4,1,0,0]
Output: "14:00"

Note:
A.length == 4
0 <= A[i] <= 9

Solution : Generate all possible combinations of hour and minutes and store them together as a unique time. Then iterate and filter out the invalid times and
simultaenously find the largest time. Form the string from the largest time and format it such that if length of hour/minute is 1, then we append a 0 in front.
Return the largest time.
Complexity : O(1).
*/

class Solution {
public:
    string largestTimeFromDigits(vector<int>& v) {
        vector<pair<int, int>> times;
        pair<int, int> largest = make_pair(0, 0);
        bool timepossible = false;
        string time;
        
        sort(v.begin(), v.end()); //Sort otherwise next_permutation will run out before generating all possible combinations.
        do {
            times.push_back(make_pair(((v[0] * 10) + v[1]), ((v[2] * 10) + v[3]))); //Make all combinations of hour:minute
        } while(std::next_permutation(v.begin(), v.end()));
        for (auto &i : times) { //Iterate and filter out invalid times
            if ((i.first >= 0 && i.first <= 23)
                && (i.second >= 0 && i.second < 60)) {
                timepossible = true; //Figure out if there is at all a valid time possible to be made
                if ((largest.first < i.first)
                    || (largest.first == i.first
                           && largest.second < i.second)){ //Find the largest valid time
                    largest = i;
                }
            }
        }
        if (!timepossible) //If no valid time possible
            return "";
        else {
            string hour = to_string(largest.first);
            if (hour.length() == 1) { //Append 0 at front if hour is single digit
                hour = "0" + hour;
            }
            string minute = to_string(largest.second);
            if (minute.length() == 1) { //Append 0 at front if minute is single digit
                minute = "0" + minute;
            }
            time = hour + ":" + minute; //Form the formatted string
        }
        return time;
    }
};
