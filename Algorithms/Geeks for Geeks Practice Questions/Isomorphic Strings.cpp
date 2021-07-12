/*
Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters.
No two characters may map to the same character, but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"
Output: true
Example 2:

Input: s = "foo", t = "bar"
Output: false
Example 3:

Input: s = "paper", t = "title"
Output: true
 

Constraints:

1 <= s.length <= 5 * 104
t.length == s.length
s and t consist of any valid ascii character.

Solution : Check if sorted occurence of characters are same or not in both in both strings - if there is an unequal occurence of any character, then that difference
can never be mapped. Then map each character of first string to the corresponding character of second string and check if the transformation is actually possible.

Corner Cases:
"bbbaaaba"
"aaabbbba" <-- At first it might seem only checking sorted occcurences of characters in both string serves the purpose but this test case fails.

Time & Space Complexity : O(n)
*/

class Solution {
public:
    string transform(string s, map<char,char> &trmap) {
        for (int i = 0; i < s.length(); i++) {
            s[i] = trmap[s[i]];
        }
        
        return s;
    }
    
    bool isIsomorphic(string s, string t) {
        int i = 0;
        if (s.length() != t.length()) { //Unequal strings can never be isomorphic
            return false;
        }
        vector<int> a(256, 0);
        vector<int> b(256, 0);
        map<char, char> trmap;
        
        for (i = 0; i < s.length(); i++) {
            a[s[i]]++; b[t[i]]++;
        }
        
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        for (i = 0; i < 256; i++) { //Check if sorted occurence of both characters is equal
            if (a[i] != b[i])
                return false;
        }
        
        for (i = 0; i < s.length(); i++) { //Map each character of first string to corresponsing string in second
            if (!trmap.count(s[i])) {
                trmap[s[i]] = t[i];
            }
        }
        
        string transformed = transform(s, trmap); //Check if transformation is actually possible
        if (transformed != t)
            return false;
        return true;
    }
};
