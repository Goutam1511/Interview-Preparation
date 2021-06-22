/*
Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.
A subsequence of a string is a new string generated from the original string with some characters (can be none)
deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".

Example 1:

Input: s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
Example 2:

Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2
 

Constraints:

1 <= s.length <= 5 * 104
1 <= words.length <= 5000
1 <= words[i].length <= 50
s and words[i] consist of only lowercase English letters.

Approach : Approach followed is a Hashmap + Binary search where we save all indices of each char of s in a map ie..,
Eg:  s = abacedba
       key   value
map =  [a]   0, 2, 7
       [b]   1, 6
       [c]   3
       [e]   4
       
Now traverse each word in the input vector and check whether it is a subsequence of s using a binary search approach

Eg:  word = aad, traverse each char by char
As a is present twice and in the map when we check for the 2nd char a
then we need to take the 2nd index instead of the 1st index. 
*/

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // Initialize a map to store the indicies of all chars in s
        unordered_map<char, vector<int>> mp;
        
        // Traverse all the chars in s and add the indices to map
        for (int i = 0; i < s.length(); i++) {
            // push the index to map for the current char
            // The indices will be in ascending order for the character
            mp[s[i]].push_back(i);
        }
        
        // Variable to store result
        int numSubseq = 0;
        
        // Temporary variables
        int low;
        bool isSubseq;
        
        // Traverse all the words of the input 
        for (string& word: words) {
            // Lower Index
            // Index that needs to be found should be greater than this low index
            low = -1;
            // Assume current word is a subsequence
            isSubseq = true;
            
            for (char& ch : word) {                
                // Perform a binary search 
                int pos = upper_bound(mp[ch].begin(), mp[ch].end(), low) - mp[ch].begin();
                // Check if the current char is present in map or not
                if (pos == mp[ch].size()) {
                    // no such char present,
                    isSubseq = false;
                    break;
                }
                
                low = mp[ch][pos];
            }

            // Increment result if current word is subsequence of s
            numSubseq += isSubseq;
        }
        
        return numSubseq;
    }
};
