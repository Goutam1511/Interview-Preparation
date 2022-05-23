/*
A string s is called good if there are no two different characters in s that have the same frequency.
Given a string s, return the minimum number of characters you need to delete to make s good.

The frequency of a character in a string is the number of times it appears in the string. For example,
in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.

Example 1:

Input: s = "aab"
Output: 0
Explanation: s is already good.
Example 2:

Input: s = "aaabbbcc"
Output: 2
Explanation: You can delete two 'b's resulting in the good string "aaabcc".
Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".
Example 3:

Input: s = "ceabaacb"
Output: 2
Explanation: You can delete both 'c's resulting in the good string "eabaab".
Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).

Constraints:

1 <= s.length <= 105
s contains only lowercase English letters.

Solution : As we can only delete characters, if we have multiple characters having the same frequency, we must decrease all the frequencies of them, except one.
Sort the alphabet characters by their frequencies non-increasingly. Iterate on the alphabet characters, keep decreasing the frequency of the current character 
until it reaches a value that has not appeared before.
*/

class Solution {
    static class pair {
        char c;
        int freq;
        
        pair(char c, int f) {
            this.c = c;
            this.freq = f;
        }
    }
    public int minDeletions(String s) {
        Comparator<pair> valueComparator = new Comparator<pair>() {
            public int compare(pair k1, pair k2) {
                return k2.freq - k1.freq;
            }
        };
        int[] freqMap = new int[26];
        char[] charsOfS = s.toCharArray();
        int res = 0;
        
        for (char c : charsOfS) { //calculate frequencies of characters
            freqMap[c - 'a']++;
        }
        
        PriorityQueue<pair> pq = new PriorityQueue<>(valueComparator);
        
        for (int i = 0; i < 26; i++) { //sort the frequencies in descending order through heap
            pq.add(new pair((char)('a' + i), freqMap[i]));
        }
        // sorting in descending order helps to account the minimal reduction in characters needed
        
        Set<Integer> valuesPresent = new HashSet<>();
        while (!pq.isEmpty()) { // check if a frequency already exists, if exists then decrement it until it is never seen before
            pair p = pq.poll();
            while (p.freq > 0 && valuesPresent.contains(p.freq)) {
                p.freq--;
                res++;
            }
            if (p.freq > 0) {
                valuesPresent.add(p.freq);
            }
        }
        
        return res;
    }
}
