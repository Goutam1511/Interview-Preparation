/*
Given an array of strings words and an integer k, return the k most frequent strings.
Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.

Example 1:

Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:

Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words, with the number of occurrence being 4, 3, 2 and 1 respectively.

Constraints:

1 <= words.length <= 500
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
k is in the range [1, The number of unique words[i]]
 
Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?

Solution : Classic example of practical heap usage. Heap adds and removes/polls in log(n) time. So we can keep a heap in reverse order that is in case of top k, we can
use a minHeap or in case of bottom k, we can keep a maxHeap. And whenever, the size of heap will exceed k, we can poll out the smallest or largest respectively. In this
manner we can approach this problem.

Time : O(nlogk) -> n elements inserted in heap and each time it takes log(k) for addition and removal.
Space : O(k) for heap of size k
*/

class Solution {
    public List<String> topKFrequent(String[] words, int k) {
        Map<String, Integer> freqWords = new HashMap<>();
        
        for (String w : words) freqWords.put(w, freqWords.getOrDefault(w, 0) + 1);
        
        PriorityQueue<Map.Entry<String, Integer>> q
            = new PriorityQueue<>((a, b) -> a.getValue() == b.getValue() ?
                                b.getKey().compareTo(a.getKey()) : a.getValue() - b.getValue());
        
        for (Map.Entry<String, Integer> e : freqWords.entrySet()) {
            q.add(e);
            if (q.size() > k) {
                q.poll();
            }
        }
        
        List<String> res = new ArrayList<>();
        while (!q.isEmpty()) {
            res.add(q.poll().getKey());
        }
        Collections.reverse(res);
        return res;
    }
}

/*
Alternate Solution : Quick Select in O(n) average time
*/
