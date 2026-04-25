/*
There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.
You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words
are sorted lexicographically by the rules of this new language.

If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".

Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules.
If there are multiple solutions, return any of them.

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
 

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.

Solution: Toplogical Sort to decode the dependency between characters. If "wrt" is before "wrf" --> that denotes f is dependent on t.
Note if there is an input like ["wr","w"] that is an invalid. Also we should be able to detect cyclic dependency.
*/

class Solution {
    public String alienOrder(String[] words) {
        Map<Character, Set<Character>> charToCharDep = new HashMap<>();
        Map<Character, Integer> outstandingDeps = new HashMap<>();
        Queue<Character> q = new LinkedList<>();
        StringBuilder sb = new StringBuilder();

        for (String word : words) {
            for (char c : word.toCharArray()) {
                charToCharDep.put(c, new HashSet<>());
                outstandingDeps.put(c , 0);
            }
        }
        
        for (int i = 0; i < words.length - 1; i++) {
            String word1 = words[i];
            String word2 = words[i + 1];
          
            // Note if there is an input like ["wr","w"] that is an invalid
            if (word2.length() < word1.length() && word1.startsWith(word2)) {
                return "";
            }
            int j = 0;
            while (j < word1.length() && j < word2.length() && word1.charAt(j) == word2.charAt(j)) {
                j++;
            }
            
            if (j < word1.length() && j < word2.length()
                && !charToCharDep.get(word1.charAt(j)).contains(word2.charAt(j))) {
                charToCharDep.get(word1.charAt(j)).add(word2.charAt(j));
                outstandingDeps.put(word2.charAt(j), outstandingDeps.get(word2.charAt(j)) + 1);
            }
        }

        /*for (Map.Entry<Character, Set<Character>> e : charToCharDep.entrySet()) {
            System.out.print(e.getKey() + "->[");
            e.getValue().forEach(v -> System.out.print(v + ","));
            System.out.print("]\n");
        }
        for (Map.Entry<Character, Integer> e : outstandingDeps.entrySet()) {
            System.out.println(e.getKey() + "-> " + e.getValue());
        }*/

        for (Map.Entry<Character, Integer> e : outstandingDeps.entrySet()) {
            if (e.getValue() == 0) q.add(e.getKey());
        }

        while (!q.isEmpty()) {
            char c = q.poll();
            sb.append(c);

            for (char d : charToCharDep.get(c)) {
                outstandingDeps.put(d, outstandingDeps.get(d) - 1);
                if (outstandingDeps.get(d) <= 0) {
                    q.add(d);
                }
            }
        }
        // Cyclic dependency
        if (sb.length() < outstandingDeps.size()) return "";

        return sb.toString();
    }
}
