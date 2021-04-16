/*
Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and
removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.
Return the final string after all such duplicate removals have been made.
It is guaranteed that the answer is unique.

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"

Constraints:
1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.

Solution : Use a stack to store the characters, when there are k same characters, delete them.
To make it more efficient, use a pair to store the value and the count of each character.
*/

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int>> st;
        string res;
        
        for (int i = 0; i < s.length(); i++) {
            if(!st.empty()) {
                if (st.top().first == s[i]) {
                    st.top().second++;
                    cout<<s[i]<<" "<<st.top().second<<endl;
                } else {
                    st.push(make_pair(s[i], 1));
                }
            } else {
                st.push(make_pair(s[i], 1));
            }
            if (st.top().second == k) {
                st.pop();
            }
        }
        
        while (!st.empty()) {
            res = res + string(st.top().second, st.top().first);
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
