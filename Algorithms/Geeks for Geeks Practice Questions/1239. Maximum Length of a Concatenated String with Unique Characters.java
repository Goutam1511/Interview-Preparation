/*
You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
Return the maximum possible length of s.
A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Example 1:

Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.
Example 2:

Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").
Example 3:

Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.

Constraints:

1 <= arr.length <= 16
1 <= arr[i].length <= 26
arr[i] contains only lowercase English letters.

Solution : If we carefully notice the constraints, we can notice that this type of small constraints always hint at recursion. We will be using backtracking/recursion
and each point of recursion, we will consider the current word and try to find the longest concatenation that can be formed and then we will ignore the current word at
hand and pass on the word formed so far to next index to see if that leads to a longer word. For both the operation, we would have to check if the word formed so far
have all unique letters or not in it.

Time Complexity : We explore all the possible combinations which is 2^(Number of words in list) and for each combination we check if string consists of unique letters
O(Length of all words Combined * 2^(Number of words in list))
*/

class Solution {
    int maxLen = 0;
    public boolean isUnique(String s) { //check if all letters are unique in string
        Set<Character> presentChars = new HashSet<>();
        for (char c : s.toCharArray()) {
            if (presentChars.contains(c)) {
                return false;
            }
            presentChars.add(c);
        }
        return true;
    }
    public void findMaxLen(List<String> arr, String curr, int index) {
        if (index == arr.size()) { //Base case
            maxLen = Math.max(curr.length(), maxLen);
            return;
        }
        maxLen = Math.max(curr.length(), maxLen);
        
        String newStr = new String(curr + arr.get(index)); //Consider current word and add it, move forward if it leads to string with unique letters
        if (isUnique(newStr))
            findMaxLen(arr, newStr, index + 1);
        findMaxLen(arr, curr, index + 1); //Ignore current word and move forward
    }
    public int maxLength(List<String> arr) {
        for (int i = 0; i < arr.size(); i++) {
            if (!isUnique(arr.get(i))) { //Optimisation : If word itself is not formed of unique letters, then ignore it
                arr.remove(i);
            }
        }
        findMaxLen(arr, "", 0);
        return maxLen;
    }
}
