/*
A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
Suppose we need to investigate a mutation from a gene string start to a gene string end where one mutation is defined as one single character changed in the gene
string. For example, "AACCGGTT" --> "AACCGGTA" is one mutation. There is also a gene bank bank that records all the valid gene mutations.
A gene must be in bank to make it a valid gene string.
Given the two gene strings start and end and the gene bank bank, return the minimum number of mutations needed to mutate from start to end. If there is no such
a mutation, return -1.
Note that the starting point is assumed to be valid, so it might not be included in the bank.

Example 1:

Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1
Example 2:

Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2
Example 3:

Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
Output: 3

Constraints:

start.length == 8
end.length == 8
0 <= bank.length <= 10
bank[i].length == 8
start, end, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].

Solution : Generic BFS where for each current state we generate all the next possible states and explore in a level order fashion. For each current state of the string,
we find out all next possible states and for all the states that are currently present in the bank, we add those states in the queue along with the current bank. But,
before adding in queue, we remove the current state from the bank. This MUST be done carefully to make sure we don't fall in a cycle. Also while generating the next
possible states, we have to make sure we don't generate the same state again.
*/

class Solution {
    char[] choices = {'A', 'C', 'G', 'T'};
    public List<String> findAllNextMutations(char[] str) {
        List<String> nextMutations = new ArrayList<>();
        for (int i = 0; i < str.length; i++) {
            char curr = str[i];
            for (char c : choices) {
                if (curr != c) {
                    str[i] = c;
                    nextMutations.add(new String(str));
                }
            }
            str[i] = curr;
        }
        
        return nextMutations;
    }
    public int minMutation(String start, String end, String[] b) {
        Set<String> bank = new HashSet<>();
        for (String s : b) {
            if (!s.equals(start)) bank.add(s);
        }
        
        if (start.equals(end)) return 0;
        if (!bank.contains(end)) return -1;
        
        Queue<Pair<String, Set<String>>> q = new LinkedList<>();
        int steps = 0;
        q.add(new Pair(start, bank));
        
        while (!q.isEmpty()) {
            int sz = q.size();
            
            for (int i = 0; i < sz; i++) {
                Pair<String, Set<String>> p = q.poll();
                
                String curr = p.getKey();
                Set<String> curBank = p.getValue();
                
                List<String> nextMutations = findAllNextMutations(curr.toCharArray());
                for (String next : nextMutations) {
                    if (next.equals(end)) return steps + 1;
                    if (curBank.contains(next)) {
                        Set<String> nextBank = new HashSet<>(curBank);
                        nextBank.remove(next);
                        q.add(new Pair(next, nextBank));
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}

//Better Code Solution : https://leetcode.com/problems/minimum-genetic-mutation/solution/
