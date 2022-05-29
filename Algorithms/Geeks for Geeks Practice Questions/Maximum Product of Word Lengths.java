/*
Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters.
If no such two words exist, return 0.

Example 1:

Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4
Explanation: The two words can be "ab", "cd".
Example 3:

Input: words = ["a","aa","aaa","aaaa"]
Output: 0
Explanation: No such pair of words.

Constraints:
2 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i] consists only of lowercase English letters.

Solution : Track the characters present in each word in a 2d boolean array(rows for each word and columns for each character)
and then run two loops and compare each pair of word to check if there is common character. If not, find product of length and
update maximum length.
Time Complexity : 26 * n^2 (26 because to find common characters we are just traversing a boolean array of length 26) = O(n^2)
Space Complexity : 26 * number of words = O(n)

Better solution using Bitmasking - https://leetcode.com/problems/maximum-product-of-word-lengths/discuss/2085761/JAVA-oror-Bit-manipulation-approach
*/

class Solution {
    public boolean checkCommon(boolean[] arr1, boolean[] arr2) {
        for (int i = 0; i < 26; i++) {
            if (arr1[i] && arr2[i]) {
                return true;
            }
        }
        return false;
    }
    public int maxProduct(String[] words) {
        boolean[][] charSetOfWords = new boolean[words.length][26];
        int len = 0;
        
        for (int i = 0; i < words.length; i++) {
            for (char c : words[i].toCharArray()) {
                charSetOfWords[i][c - 'a'] = true;
            }
        }
        
        for (int i = 0; i < words.length - 1; i++) {
            for (int j = i + 1; j < words.length; j++) {
                if (!checkCommon(charSetOfWords[i], charSetOfWords[j])) {
                    len = Math.max(len, words[i].length() * words[j].length());
                }
            }
        }
        
        return len;        
    }
}
