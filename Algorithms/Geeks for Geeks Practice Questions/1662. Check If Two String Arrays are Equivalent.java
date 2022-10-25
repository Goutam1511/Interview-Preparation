/*
Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.
A string is represented by an array if the array elements concatenated in order forms the string.

Example 1:

Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
Output: true
Explanation:
word1 represents string "ab" + "c" -> "abc"
word2 represents string "a" + "bc" -> "abc"
The strings are the same, so return true.
Example 2:

Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
Output: false
Example 3:

Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
Output: true

Constraints:

1 <= word1.length, word2.length <= 10^3
1 <= word1[i].length, word2[i].length <= 10^3
1 <= sum(word1[i].length), sum(word2[i].length) <= 10^3
word1[i] and word2[i] consist of lowercase letters.

Solution : Concatenate both arrays into string and comparing the string gets accepted and hence this problem is marked Easy. Complexity would be O(n) for both space &
time however this can be done in O(1) by maintaining 4 pointers. 2 pointers would be pointing to the array indexes and 2 pointers would be comparing individual characters
in the words of the array. Whenever, any of the word pointers reach end of the word, the array index pointers would be incremented and that word pointer would be wrapped
to zero using modulus operation.

class Solution { //O(n) for time & space
    public boolean arrayStringsAreEqual(String[] word1, String[] word2) {
        String word1res = "";
        String word2res = "";
        
        for (String s : word1)
            word1res += s;
        for (String s : word2)
            word2res += s;
        
        return word1res.equals(word2res);
    }
}

Optimised Solution Complexity : Time - O(n) Space - O(1)
*/

class Solution {
    public boolean arrayStringsAreEqual(String[] word1, String[] word2) {
        int idx1 = 0, idx2 = 0, arrIdx1 = 0, arrIdx2 = 0;
        while (arrIdx1 < word1.length && arrIdx2 < word2.length) {
            if (word1[arrIdx1].charAt(idx1) != word2[arrIdx2].charAt(idx2)) return false;
            idx1 = (++idx1) % word1[arrIdx1].length();
            idx2 = (++idx2) % word2[arrIdx2].length();
            if (idx1 == 0) arrIdx1++;
            if (idx2 == 0) arrIdx2++;
        }
        return arrIdx1 == word1.length && arrIdx2 == word2.length;
    }
}
