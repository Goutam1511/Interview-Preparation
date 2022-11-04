/*
You are given an array of strings words. Each element of words consists of two lowercase English letters.
Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
A palindrome is a string that reads the same forward and backward.

Example 1:

Input: words = ["lc","cl","gg"]
Output: 6
Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
Note that "clgglc" is another longest palindrome that can be created.
Example 2:

Input: words = ["ab","ty","yt","lc","cl","ab"]
Output: 8
Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
Note that "lcyttycl" is another longest palindrome that can be created.
Example 3:

Input: words = ["cc","ll","xx"]
Output: 2
Explanation: One longest palindrome is "cc", of length 2.
Note that "ll" is another longest palindrome that can be created, and so is "xx".
 
Edge Case : ["nn","nn","hg","gn","nn","hh","gh","nn","nh","nh"] Expected OP : 14
Constraints:

1 <= words.length <= 10^5
words[i].length == 2
words[i] consists of lowercase English letters.

Solution : There are mainly 3 observations -
1. For each of the word having two distinct letter, we need the reverse of it in same number to form a pair and contribute +4 to length for each pair
2. For words having both letters same, we need the same word and they will form pairs around the center and contribute +4 to length for each pair - hence these words
will contribute only if they have an even count, in case they have an odd count, their (frequency - 1) * 2 needs to be considered.
3. Only the word having both letters same and highest odd count, can be considered with its odd frequency as it can be placed in the center of the palindrome.
For example - ["nn","nn","hg","gn","nn","hh","gh","nn","nh","nh"]
The OP palindrome would be --> gh nn nn hh nn nn hg
Notice, how the words having distinct letters are in pairs and words having same letters are also in pair around each other. Only the word having same letters and
highest odd count will be in the middle of the palindrome.

Hence, we first iterate through the words and categorize the frequencies in two maps - one stores frequency of words having same letters and the other map stores the
frequency of words having distinct letters for future references. While doing this, if we encounter any word having distinct letters and the reverse of the word having
frequency greater than 0, that means we found a pair for the palindrome and hence we reduce the count of the reverse of the word and add +4 to length. Next, we find
the frequency of the word having same letters and highest odd frequency, we track the frequency as well as the word. Then we iterate the words having same letters &
account their contribution in the way mentioned above while carefully making sure we don't count the contribution for the word having same letters and highest odd
frequency as that will be accounted separately at the last.

Time Complexity : O(n) for iterating the all set of words 
Space Complexity : O(n) for 2 maps storing all words
*/
class Solution {
    public String reverse(String word) {
        StringBuilder str = new StringBuilder(word);
        str.reverse();
        return str.toString();
    }
    
    public int longestPalindrome(String[] words) {
        Map<String, Integer> seenPart = new HashMap<>(); // This will store the words having distinct letters for future reference
        Map<String, Integer> sameWord = new HashMap<>(); // This will store the frequency of words having both letters same
        int len = 0; // Result length of palindrome
        int maxOddSameWrd = 0; // Frequency of word having same letters and odd frequency
        String maxOddWord = null; // Word having same letters and highest odd frequency
        
        for (String word : words) {
            if (word.charAt(0) == word.charAt(1)) { // Update frequency of words having same letters
                sameWord.put(word, sameWord.getOrDefault(word, 0) + 1);
            } else if (seenPart.getOrDefault(reverse(word), 0) > 0) {
              // If there is a word whose reverse word count is > 0, reduce the count and pair up to add to result length + 4
                seenPart.put(reverse(word), seenPart.get(reverse(word)) - 1);
                len += 4;
            } else { // Note down the frequency of the word having distinct letters for future reference
                seenPart.put(word, seenPart.getOrDefault(word, 0) + 1);
            }
        }
        for (Map.Entry<String, Integer> entry : sameWord.entrySet()) { // Find the word having same letters and highest odd count, this will sit in center
            if (entry.getValue() % 2 == 1 && entry.getValue() > maxOddSameWrd) {
                    maxOddSameWrd = entry.getValue();
                    maxOddWord = entry.getKey();
            }
        }
        /* All words having same letters will contribute their (count - 1) * 2 if count is odd else will contribute count * 2 if count is even
         * Make sure while counting the contribution for words having odd count, we are not adding for the word having highest odd count. That
         * will be accounted separately.
         */
        for (Map.Entry<String, Integer> entry : sameWord.entrySet()) {
            if (entry.getValue() % 2 == 0) {
                len += (entry.getValue() * 2);
            } else if (!entry.getKey().equals(maxOddWord)) {
                len += ((entry.getValue() - 1) * 2);
            }
        }
        len += (maxOddSameWrd * 2); // Count the word having same letters and highest odd count. This will sit in middle of palindrome.
        return len;
    }
}

//Optimal Solution : https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/solution/
