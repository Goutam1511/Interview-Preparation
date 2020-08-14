/*
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Corner Case :
1) Input : aaabbbbbccccdd output : 13
2) Input : bb output : 2

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.

Solution : We need to note that although at first the problem seems to be around some combinatorics or recursion but is actually simple odd-even
tricky problem. We need not bother about how many palindromes can be generated or which will be the longest. We just need to note the simple fact,
that the longest palindrome will be having all the characters that have even count and among the characters that have odd count, we need to take
the lot having the highest count and rest all characters having odd count can be taken leaving aside 1 as it has no other character to pair with.
So longest length possible = (sum of all even counts + highest odd count among all characters having odd count + sum of (odd counts of other characters - 1)).
*/

class Solution {
public:
    int longestPalindrome(string s) {
        int charset[255] = {0};
        int len = 0;
        vector<int> oddvals;
        
        for (int i = 0; i < s.length(); i++) {
            charset[s[i]]++; //Frequency count of characters
        }
        
        for (int i = 0; i < 255; i++) {
            if (charset[i] % 2 == 0) { //If count is even add it
                len += charset[i];
            } else {
                oddvals.push_back(charset[i]); //Push the odd count in a storage to sort
            }
        }
        sort(oddvals.begin(), oddvals.end(), greater<int>()); //Sort the odd counts to find the maximum value
        if (oddvals.size()) //There might not be any odd values as well
            len += oddvals[0]; //Add the highest count
        for (int i = 1; i < oddvals.size(); i++) { //Add up all other oddcounts - 1
            len += (oddvals[i] - 1);
        }
        
        return len;
    }
};
