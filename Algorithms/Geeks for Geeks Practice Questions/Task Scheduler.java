/*
Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different task. Tasks could be done in any order.
Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.
However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array), that is that there must
be at least n units of time between any two same tasks.
Return the least number of units of times that the CPU will take to finish all the given tasks.

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A

Constraints:

1 <= task.length <= 10^4
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].

Solution : This is a classic example of greedy job scheduling with deadline. Jobs with more frequency should be completed first. So, we store the character and
frequency count into the priority queue and poll characters with higher frequency one by one. However, this would have been simpler if there was no concept of
cooldown. But, we have to maintain the cooldown as well. Hence, to make sure character with higher frequency don't keep coming up within k time units where k
is the cooldown period, we store them in a queue of size k after polling instead of directly adding again with newer frequency count into the priority queue. And
we add the same character to priority queue again, only after we have elapsed k time period into the queue through the below check -

if (queue.size() == n + 1) {
     pair poll = queue.poll();
     if (poll.cnt > 0) {
         pq.add(poll);
     }
 }
 
 Now, there can be cases, when the other tasks are completed before the task with highest frequency. In those cases, our priority queue would be empty and that's
 completely fine. The CPU would be idle in these cases but we must not bring tasks from queue to priority queue before k time units have elapsed. We would denote
 these cases with dummy pair <'#', 0> and keep track of the idle time periods.
 
 Time & Space Complexity : O(n)
 
 Edge cases - if k == 0, then time required is tasks.length
 
 Note this question is almost same as - https://leetcode.com/problems/rearrange-string-k-distance-apart/discuss/83252/Java-AC-Solution-using-PriorityQueue-and-HashMap
*/

class Solution {
    static class pair {
        char c;
        int cnt;
        
        pair(char ch, int v) {
            c = ch;
            cnt = v;
        }
    }
    public int leastInterval(char[] tasks, int n) {
        if (tasks.length == 0) {
            return 0;
        }
        if (n == 0) {
            return tasks.length;
        }

        int len = tasks.length;

        Map<Character, Integer> map = new HashMap<>();
        PriorityQueue<pair> pq = new PriorityQueue<>((a, b) -> b.cnt - a.cnt);

        for (int i = 0; i < len; i++) {
            char c = tasks[i];
            int count = map.getOrDefault(c, 0) + 1;
            map.put(c, count);
        } 
        for (Map.Entry<Character, Integer> e : map.entrySet()) {
            pair p = new pair(e.getKey(), e.getValue());
            pq.add(p);
        }

        Queue<pair> queue = 
            new LinkedList<>();
        int i = 0, cnt = 0;

        while (i < len) {
            pair entry = null;
            if (pq.size() == 0) {
                entry = new pair('#', 0);
                //System.out.print("#");
            } else {
                entry = pq.remove();
                //System.out.print(entry.c);
                int newVal = entry.cnt - 1;
                entry.cnt = newVal;
                i++;
            }
            cnt++;
            queue.offer(entry);
            if (queue.size() == n + 1) {
                pair poll = queue.poll();
                if (poll.cnt > 0) {
                    pq.add(poll);
                }
            }
        }
        //System.out.print("\n");
        return cnt;
    }
}
