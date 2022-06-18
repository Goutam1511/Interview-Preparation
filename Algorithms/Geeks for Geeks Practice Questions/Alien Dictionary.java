/*
There is a new alien language that uses the English alphabet. However, the order among the letters is unknown to you.
You are given a list of strings words from the alien language's dictionary, where the strings in words are sorted lexicographically by the rules of this new language.
Return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there is no solution, 
return "". If there are multiple solutions, return any of them. A string s is lexicographically smaller than a string t if at the first letter where they differ, 
the letter in s comes before the letter in t in the alien language. If the first min(s.length, t.length) letters are the same, then s is smaller if and only if 
s.length < t.length.

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

Solution : Break the problem into three steps -
1. Extracting dependency rules from the input. For example "A must be before C", "X must be before D", or "E must be before B".
2. Putting the dependency rules into a graph with letters as nodes and dependencies as edges (an adjacency list is best).
3. Topologically sorting the graph nodes.

A few things to keep in mind:

The letters within a word don't tell us anything about the relative order. For example, the presence of the word kitten in the list does not tell us that 
the letter k is before the letter i.
The input can contain words followed by their prefix, for example, abcd and then ab. These cases will never result in a valid alphabet 
(because in a valid alphabet, prefixes are always first). We'll need to make sure our solution detects these cases correctly.
There can be more than one valid alphabet ordering. It is fine for our algorithm to return any one of them.
Your output string must contain all unique letters that were within the input list, including those that could be in any position within the ordering. 
It should not contain any additional letters that were not in the input.

For topological sorting we are using Kahn's Algorithm.
*/

class Solution {
    static class Node {
        char c;
        int count;
        Set<Node> neighbors;
        
        Node(char ch) {
            c = ch;
            count = 0;
            neighbors = new HashSet<>();
        }
    }
    Map<Character, Node> charToNode = new HashMap<>();
    
    public String alienOrder(String[] words) {
        String res = "";
        for (String s : words) {
            char[] chars = s.toCharArray();
            for (int i = 0; i < chars.length; i++) {
                Node chariNode = null;
                if (charToNode.containsKey(chars[i])) {
                    chariNode = charToNode.get(chars[i]);
                } else {
                    chariNode = new Node(chars[i]);
                    charToNode.put(chars[i], chariNode);
                }
            }
        }
        
        for (int i = 0; i < words.length - 1; i++) {
            String word1 = words[i];
            String word2 = words[i + 1];
            //If first word has greater length but second word is a prefix of first word, then order is invalid
            if (word1.length() > word2.length() && word1.startsWith(word2)) {
                //System.out.println(word1 + " " + word2);
                return "";
            }
            
            for (int j = 0; j < Math.min(word1.length(), word2.length()); j++) {
              //Since input words are lexicographically sorted, we extract the first mismatch in character and then derive the edging.
                if (word1.charAt(j) != word2.charAt(j)) {
                    Node word1Node = charToNode.get(word1.charAt(j));
                    Node word2Node = charToNode.get(word2.charAt(j));
                    
                    if (word1Node.neighbors.add(word2Node))
                        word2Node.count++;
                    break;
                }
            }
        }
        //Kahn's algorithm for topological sorting starts with inorder count tracking in queue
        Queue<Node> q = new LinkedList<>();
        for (Character c : charToNode.keySet()) {
            if (charToNode.get(c).count == 0) {
                q.add(charToNode.get(c));
            }
        }
        
        while (!q.isEmpty()) {
            Node n = q.poll();
            res += String.valueOf(n.c);
            
            for (Node neigh : n.neighbors) {
                neigh.count--;
                if (neigh.count == 0) {
                    q.add(neigh);
                }
            }
        }
        //If all the nodes were not reached because they still had some cyclic dependency
        if (res.length() != charToNode.size()) {
            //System.out.println("Result : " + res);
            return "";
        } 
        return res;
    }
}

