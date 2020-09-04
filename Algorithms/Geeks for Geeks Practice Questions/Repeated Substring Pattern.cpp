#include <bits/stdc++.h>
using namespace std;

/*
Given a non-empty string check if it can be constructed by taking a substring of
it and appending multiple copies of the substring together. You may assume the 
given string consists of lowercase English letters only and its length will not 
exceed 10000.

Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:

Input: "aba"
Output: False
Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" 
twice.)

Solution : We iterate 
*/

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        set<char> setofchars;
        
        if (s.length() < 2) { //Empty string or a character cannot have substring
            return false;
        }
        
        for (char c : s) { //Insert all characters of the main string in set
            setofchars.insert(c);
        }
        
        for (int i = 0; i < s.length() / 2; i++) {
        	/* If until this point at i, the substring (0, i) contains all the
        	 * characters in main string then it is a good candidate for checking
        	 * if we can repeat it to form the main string. The process how we 
        	 * check this is, we put all characters of main string in a set and
        	 * iterate till half of the string (since after that we cannot repeat
        	 * the substring anymore) and remove each character from set. If set
        	 * is empty, that means till i, all characters of the main string are
        	 * present. Then we check if repeating that size of the substring can
        	 * give us main string by checking s.length() % (i + 1) == 0. If all
        	 * these conditions satisfy then we can repeat the substring (0, i) 
        	 * to check if we can form the main string.
        	 */
            setofchars.erase(s[i]);
            if (setofchars.empty() && (s.length() % (i + 1) == 0)) {
                string substring = s.substr(0, i + 1);
                //cout<<substring<<endl;
                int repeatcount  = s.length() / (i + 1);
                string repeatstr = "";
                
                while (repeatcount) {
                    repeatstr = repeatstr + substring;
                    repeatcount--;
                }
                //cout<<repeatstr<<endl;
                if (repeatstr == s)
                    return true;
            }
        }
        return false;
    }
};

int main() {
	// Repeated Substring Pattern | String | LeetCode
	Solution s;
	cout<<s.repeatedSubstringPattern("abab")<<endl;
	cout<<s.repeatedSubstringPattern("abac")<<endl;
	cout<<s.repeatedSubstringPattern("aba")<<endl;
	cout<<s.repeatedSubstringPattern("abcabcabcabc")<<endl;
	cout<<s.repeatedSubstringPattern("babbabbabbabbab")<<endl;
	cout<<s.repeatedSubstringPattern("ba")<<endl;
	return 0;
}
