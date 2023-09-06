/*
Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
The length of each part should be as equal as possible: no two parts should have a size differing by more than one.
This may lead to some parts being null.
The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a
size greater than or equal to parts occurring later. Return an array of the k parts.

Example 1:

Input: head = [1,2,3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation:
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but its string representation as a ListNode is [].
Example 2:

Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
Output: [[1,2,3,4],[5,6,7],[8,9,10]]
Explanation:
The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.

Constraints:

The number of nodes in the list is in the range [0, 1000].
0 <= Node.val <= 1000
1 <= k <= 50
*/

class Solution {
    public int countNodes(ListNode head) {
        ListNode temp = head;
        int cnt = 0;
        
        while (temp != null) {
            cnt++;
            temp = temp.next;
        }
        return cnt;
    }
    public ListNode[] splitListToParts(ListNode head, int k) {
        int cnt = countNodes(head);
        double numberOfNodesInGroup = (double)(cnt) / (double)k;
        ListNode[] res = new ListNode[k];
        int curIndex = 0;
        ListNode temp = head;

        while (temp != null) {
            int curCnt = 0;
            if (cnt % k != 0) {
            // As long as cnt is not fully divisible we need to have 1 extra node in group
                curCnt = (int)(numberOfNodesInGroup + 1);
            } else {
                curCnt = (int)numberOfNodesInGroup;
            }
            res[curIndex++] = temp; // new group start
            ListNode prev = null;
            for (int i = 0; i < curCnt && temp != null; i++) {
                prev = temp;
                temp = temp.next;
            }
            prev.next = null; // Split into group
            cnt -= curCnt; // Update number of nodes left
            k--; // Update number of groups left
        }

        return res;
    }
}
