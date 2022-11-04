/*
Given a string s, reverse only all the vowels in the string and return it.
The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Example 1:

Input: s = "hello"
Output: "holle"
Example 2:

Input: s = "leetcode"
Output: "leotcede"

Constraints:

1 <= s.length <= 3 * 10^5
s consist of printable ASCII characters.

Solution : We use two pointers - starting from both sides and move them until they reach other. While moving them one at a time, whenever we reach a vowel, we stop moving
and wait for the other pointer to reach a vowel as well. Then we swap the vowels and again continue until both the pointers meet each other.

Time Complexity : O(n) Space Complexity : O(1)
*/

class Solution {
    public boolean isVowel(char c) {
        char[] vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        for (char v : vowels) if (c == v) return true;
        return false;
    }
    public String reverseVowels(String s) {
        char[] letters = s.toCharArray();
        int low = 0, high = s.length() - 1;
        
        while (low < high) {
            while (low < high && !isVowel(letters[low])) {
                low++;
            }
            
            while (low < high && !isVowel(letters[high])) {
                high--;
            }
            
            if (low < high) {
                char t = letters[low];
                letters[low] = letters[high];
                letters[high] = t;
                low++;
                high--;
            }
            
        }
        return new String(letters);
    }
}
