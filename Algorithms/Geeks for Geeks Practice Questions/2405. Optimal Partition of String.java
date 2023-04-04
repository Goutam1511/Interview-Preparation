/*
Given a string s, partition the string into one or more substrings such that the characters in each substring are unique.
That is, no letter appears in a single substring more than once. Return the minimum number of substrings in such a partition.
Note that each character should belong to exactly one substring in a partition.

Example 1:

Input: s = "abacaba"
Output: 4
Explanation:
Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
It can be shown that 4 is the minimum number of substrings needed.
Example 2:

Input: s = "ssssss"
Output: 6
Explanation:
The only valid partition is ("s","s","s","s","s","s").

Constraints:

1 <= s.length <= 10^5
s consists of only English lowercase letters.

Solution : Initially although it might seem like it's a recursive problem since there can be multiple solutions but through trial and error it can be
proved that greedy solution works perfectly where we can maintain a character set and keep on adding to the existing character set until and unless we
encounter an already existing character, and when we encounter an already existing character in characterset, we can add the counter and reset the charset.

Time Complexity : O(n) Space Complexity : O(1) because charset is of 26 characters
*/

class Solution {
    public int partitionString(String s) {
        boolean[] isPresent = new boolean[26];
        int cnt = 1;
        
        for (char c : s.toCharArray()) {
            if (isPresent[c - 'a']) {
                cnt++;
                isPresent = new boolean[26];
            }
            isPresent[c - 'a'] = true;
        }
        return cnt;
    }
}
