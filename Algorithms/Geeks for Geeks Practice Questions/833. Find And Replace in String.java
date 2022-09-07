/**
You are given a 0-indexed string s that you must perform k replacement operations on. The replacement operations are given as three 0-indexed parallel arrays, indices, sources, and targets, all of length k.

To complete the ith replacement operation:

Check if the substring sources[i] occurs at index indices[i] in the original string s.
If it does not occur, do nothing.
Otherwise if it does occur, replace that substring with targets[i].
For example, if s = "abcd", indices[i] = 0, sources[i] = "ab", and targets[i] = "eee", then the result of this replacement will be "eeecd".

All replacement operations must occur simultaneously, meaning the replacement operations should not affect the indexing of each other. The testcases will be generated
such that the replacements will not overlap.

For example, a testcase with s = "abc", indices = [0, 1], and sources = ["ab","bc"] will not be generated because the "ab" and "bc" replacements overlap.
Return the resulting string after performing all replacement operations on s.

A substring is a contiguous sequence of characters in a string.

Example 1:

Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets = ["eee", "ffff"]
Output: "eeebffff"
Explanation:
"a" occurs at index 0 in s, so we replace it with "eee".
"cd" occurs at index 2 in s, so we replace it with "ffff".
Example 2:

Input: s = "abcd", indices = [0, 2], sources = ["ab","ec"], targets = ["eee","ffff"]
Output: "eeecd"
Explanation:
"ab" occurs at index 0 in s, so we replace it with "eee".
"ec" does not occur at index 2 in s, so we do nothing.

Constraints:

1 <= s.length <= 1000
k == indices.length == sources.length == targets.length
1 <= k <= 100
0 <= indexes[i] < s.length
1 <= sources[i].length, targets[i].length <= 50
s consists of only lowercase English letters.
sources[i] and targets[i] consist of only lowercase English letters.

Note : There is no critical corner cases but note - The testcases will be generated such that the replacements will not overlap.
Solution : The only trick here is to note that if we make all the operations from right to left or end to beginning in the string in reverse order then we don't
need to take any special care for the new string that is forming because of the replacements otherwise if we operated from left to right or beginning to end, then
we would have to be careful about the new offset that is to be tracked because after replacement the new string formed might differ in length with the old string
in most cases. Hence, we just iterate all the operations from end to beginning according to the indices and make the replacement.
*/

class Solution {
    static class ops {
        String src;
        String trg;
        String idx;
        
        ops(String src, String trg, int idx) {
            this.idx = idx;
            this.src = src;
            this.trg = trg;
        }
    }
    public String findReplaceString(String s, int[] indices, String[] sources, String[] targets) {
        int opsLen = indices.length;
        ops[] operations = new ops[opsLen];
        for (int i = 0; i < opsLen; i++) {
            operations[i] = new ops(sources[i], targets[i], indices[i]);
        }
        //Sort the operations according to indices of the string and then perform replacement operations from end of string
        Arrays.sort(operations, (a, b) -> a.idx - b.idx);
        
        StringBuffer sb = new StringBuffer(s);
        
        for (int i = opsLen - 1; i >= 0; i--) {
            String src = operations[i].src;
            String trg = operations[i].trg;
            int idx = operations[i].idx;
            
            if (idx + src.length() <= sb.length()
                && s.substring(idx, idx + src.length()).equals(src)) {
                sb.replace(idx, idx + src.length(), trg);
            }
        }
        return sb.toString();
    }
}
