/*
We can shift a string by shifting each of its letters to its successive letter.

For example, "abc" can be shifted to be "bcd".
We can keep shifting the string to form a sequence.

For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
Given an array of strings strings, group all strings[i] that belong to the same shifting sequence. You may return the answer in any order.

Example 1:

Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
Example 2:

Input: strings = ["a"]
Output: [["a"]]

Constraints:

1 <= strings.length <= 200
1 <= strings[i].length <= 50
strings[i] consists of lowercase English letters.

Solution : We can group two strings if the difference of all characters in two strings remains constant throughout the two strings. First, we group by the length.
Obviously, if two string lengths are not equal, they can't belong to same groups. Hence, first we bucket them basis on lengths. Then for equal length strings, we
bucket them based on the property stated previously. For this whole thing, we create a data structure of Map<Integer, Map<String, List<String>>> 
--> <Length, <Bucket of each shifted strings in sequence>>. For Bucket of each shifted string sequence, we have taken the key as the first string in the sequence and
we test all the strings of same bucket with this key.

Complexity : O(N * K) -> k is length of strings
*/

class Solution {
    Map<Integer, Map<String, List<String>>> m = new HashMap<>();
    
    public int computeDiff(char c1, char c2) {
        int diff = c1 - c2;
        if (diff < 0) {
            diff += 26;
        }
        return diff;
    }
    
    public boolean compute(String s1, String s2) {
        int diff = computeDiff(s1.charAt(0), s2.charAt(0));
        
        for (int i = 1; i < s1.length(); i++) {
            if (computeDiff(s1.charAt(i), s2.charAt(i)) != diff) {
                return false;
            }
        }
        return true;
    }
    public List<List<String>> groupStrings(String[] strings) {
        for (String s : strings) {
            if (m.containsKey(s.length())) {
                boolean found = false;
                for (Map.Entry<String, List<String>> e : m.get(s.length()).entrySet()) {
                    if (compute(e.getKey(), s)) {
                        e.getValue().add(s);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    List<String> arr = new ArrayList<>();
                    arr.add(s);
                    m.get(s.length()).put(s, arr);
                }
            } else {
                Map<String, List<String>> mnew = new HashMap<>();
                List<String> arr = new ArrayList<>();
                arr.add(s);
                mnew.put(s, arr);
                m.put(s.length(), mnew);
            }
        }
        List<List<String>> res = new ArrayList<>();
        for (int i : m.keySet()) {
            for (String s : m.get(i).keySet()) {
                res.add(m.get(i).get(s));
            }
        }
        
        return res;
    }
}
