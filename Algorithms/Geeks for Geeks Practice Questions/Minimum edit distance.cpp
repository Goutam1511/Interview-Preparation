#include <bits/stdc++.h>
using namespace std;
/*

Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:

1.Insert a character
2.Delete a character
3.Replace a character

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')


SOLUTION:
https://www.geeksforgeeks.org/edit-distance-dp-5/

VISUAL DRY RUN:

Input: word1 = "horse", word2 = "rose"

DP Table to store the minimum edit distance :
      r o s e
     -------------
    |0 1 2 3 4 
	h	|1 1 2 3 4 
	o	|2 2 1 2 3 
	r	|3 2 2 2 3 
	s	|4 3 3 2 3 
	e	|5 4 4 3 2
	
OUTPUT:
2 (dptable[word1.length()][word2.length()])

*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int dptable[word1.length() + 1][word2.length() + 1] = {0};
        int i(0), j(0);

        for (i = 1; i <=  word2.length(); i++) {
            dptable[0][i] = dptable[0][i - 1] + 1;
        }

        for (i = 1; i <= word1.length(); i++) {
            dptable[i][0] = dptable[i-1][0] + 1;
        }

        for (i = 1; i <= word1.length(); i++) {
            for(j = 1; j <= word2.length(); j++) { 
               if (word1[i-1] == word2[j-1]) {
                   dptable[i][j] = dptable[i-1][j-1];
               } else {
                    dptable[i][j] = 1 + min(min(dptable[i-1][j], dptable[i][j-1]), dptable[i-1][j-1]);
                }
            }
        }

        /*for (i = 0; i <= word1.length(); i++) {
            for(j = 0; j <= word2.length(); j++) { 
                 cout<<dptable[i][j]<<" ";
             }
             cout<<endl;
         }*/

        return dptable[word1.length()][word2.length()];
    }
};

int main() {
	// Minimum Edit Distance Dynamic Programming LeetCode May Challenge 2020
    Solution s1;
    cout<<s1.minDistance("horse", "rose");
	return 0;
}
