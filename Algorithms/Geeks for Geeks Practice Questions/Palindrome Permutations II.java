/*
Given a string s, return all the palindromic permutations (without duplicates) of it.
You may return the answer in any order. If s has no palindromic permutation, return an empty list.

Example 1:

Input: s = "aabb"
Output: ["abba","baab"]
Example 2:

Input: s = "abc"
Output: []

Constraints:

1 <= s.length <= 16
s consists of only lowercase English letters.

Solution : Backtracking to generate all permutations. But before that, check if input string is palindromable - check if only one or no character has odd count and 
all others are even in number, then proceed backtracking. The key concept used to generate all palindromes is -> first take any one character with even count and take
out two characters, reduce the count and place these two characters at two end of initial string and generate the  palindrome using backtracking. Also if there is at 
all any odd middle character, make sure to pass that middle character as the initial string else pass empty string as initial string. Like this if palindrome generated
has length equal to input string, add it to a set. Set to avoid duplicates.
*/

class Solution {
     int[] charF = new int[26];
     Set<String> pSets = new HashSet<String>();
    
     public void generateAllPalindromes(Map<Character, Integer> map,
                                        String string, int length) {
        if (string.length() == length) {
            pSets.add(string);
            return;
        }
        for (Map.Entry<Character, Integer> e: map.entrySet()) {
            char k = e.getKey();
            int count = e.getValue();
            if(count < 2) continue;
            map.put(k, count-2);
            generateAllPalindromes(map, k + string + k, length);
            map.put(k, count);
        }
     }
    
     public boolean validateIfPalindromePossible(String s) {
         for (int i = 0; i < s.length(); i++) {
             charF[s.charAt(i) - 'a']++;
         }
         int countOfOdds = 0;
         for (int i = 0; i < 26; i++) {
             if (charF[i] % 2 == 1) {
                 countOfOdds++;
             }
             if (countOfOdds > 1) {
                 return false;
             }
         }
         return true;
     }
    
     public List<String> generatePalindromes(String s) {
        if (validateIfPalindromePossible(s)) {
            Map<Character, Integer> m = new HashMap<>();
            char ch = 0;
            for (int i = 0; i < 26; i++) {
                if (charF[i] % 2 == 1) {
                    ch = (char)(i + 'a');
                    m.put(ch, charF[i] - 1);
                } else {
                    m.put((char)(i + 'a'), charF[i]);
                }
            }
            if (ch == 0)
                generateAllPalindromes(m, "", s.length());
            else
                generateAllPalindromes(m, String.valueOf(ch), s.length());
        }
        return new ArrayList<>(pSets);
    }
}
