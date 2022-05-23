/*
You are given a string s consisting only of characters 'a' and 'b'.
You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
Return the minimum number of deletions needed to make s balanced.

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
Example 2:

Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.
 

Constraints:

1 <= s.length <= 105
s[i] is 'a' or 'b'.

Solution : You need to find for every index the number of Bs before it and the number of A's after it through suffix and prefix sum preprocessing.
The catch here is the points at which we need to check the number of Bs before and number of As after is always between the first index where B occured
and first index where A occured. Also we are to find the total minimum number of characters that need to be removed, so it will be either we remove all
Bs before last A so that string only contains A or we remove all Bs after last A or we remove the unbalanced As and Bs in between first B and last A which
is sum of number of As after + number of Bs before.

Time & Space Complexity : O(n)
*/

class Solution {
    public int minimumDeletions(String s) {
        if (s.length() == 0 || s.length() == 1) {
            return 0;
        } 
        char[] arr = s.toCharArray();
        int n = arr.length;
        int[] numberOfBsBefore = new int[n];
        int[] numberOfAsAfter = new int[n];
        
        numberOfBsBefore[0] = 0;
        numberOfAsAfter[n - 1] = 0;
        int lastA = -1;
        int firstB = -1;
        
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == 'a') {
                lastA = i;
            }
            if (arr[i] == 'b' && firstB == -1) {
                firstB = i;
            }
        }
        if (firstB == -1 || lastA == -1) { // all A or all B
            return 0;
        }
        // calculate number of B before and number of A after any index
        for (int i = 1; i < arr.length; i++) {
            numberOfBsBefore[i] = numberOfBsBefore[i - 1]  + (arr[i - 1] == 'b' ? 1 : 0);
        }
        
        for (int i = n - 2; i >= 0; i--) {
            numberOfAsAfter[i] = numberOfAsAfter[i + 1]  + (arr[i + 1] == 'a' ? 1 : 0);
        }
        // minimum of A to remove after first B or B before last A
        int res = Math.min(numberOfAsAfter[firstB], numberOfBsBefore[lastA]);
        for (int i = firstB; i < lastA; i++) { // between first B and last A if the total number of unbalanced characters is minimum
            res = Math.min(res, numberOfAsAfter[i] + numberOfBsBefore[i]);
        }
        return res;
    }
}
