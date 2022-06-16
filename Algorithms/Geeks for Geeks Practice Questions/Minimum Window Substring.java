/*
Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates)
is included in the window. If there is no such substring, return the empty string "". The testcases will be generated such that the answer is unique.
A substring is a contiguous sequence of characters within the string.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 
Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.

Follow up: Could you find an algorithm that runs in O(m + n) time?

Solution : Two pointers - increase right pointer and include a characters, then increment left pointer till characterset can be achieved to decrease window size.
Complexity : O(M + N) & O(1)
*/

class Solution {
    public boolean checkIfAllCharsPresent(int[] charSset, int[] charTset) {
        for (int i = 0; i < 256; i++) {
            if (charSset[i] < charTset[i]) {
                //System.out.println(i + " " + charSset[i] + " " + charTset[i]);
                return false;
            }
        }
        return true;
    }
    public String minWindow(String s, String t) {
        int[] charTset = new int[256];
        for (char c : t.toCharArray()) {
            charTset[c]++;
        }
        
        int j = 0;
        int i = 0;
        int left = -1;
        int right = -1;
        int min = s.length() + 1;
        
        int[] charSset = new int[256];
        
        while (j < s.length()) {
            charSset[s.charAt(j)]++;
            while (i <= j && checkIfAllCharsPresent(charSset, charTset)) {
                /*System.out.println(i + " " + j);
                System.out.println(s.substring(i, j + 1));*/
                if (min > j - i) {  
                    left = i;
                    right = j;
                    min = j - i;
                }
                charSset[s.charAt(i)]--;
                i++;
            }
            j++;
        }
        if (min == s.length() + 1)
            return "";
        
        return s.substring(left, right + 1);
    }
}
