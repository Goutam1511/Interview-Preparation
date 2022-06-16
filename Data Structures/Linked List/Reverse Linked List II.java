/*
Given the head of a singly linked list and two integers left and right where left <= right, 
reverse the nodes of the list from position left to position right, and return the reversed list.

Example 1:

Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n

Edge Cases :

1. [5] --> Only one node in list
    1
    1
2. [3,5] --> Reversing from head
    1
    2

Follow up: Could you do it in one pass?

Solution: Move till the starting point, make sure to store the previous node before starting point as it will be needed later to connect after reversing the
sublist. Reverse and make sure to attach the proper next node after reversing by start.next = next; Reattach connection by prev.next = reverse(temp, right - left + 1);

Time Complexity : O(n)
*/
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode reverse(ListNode start, int cnt) {
        ListNode next = null;
        ListNode prev = null;
        ListNode temp = start;
        
        while (cnt > 0 && temp != null) {//Reverse till counted nodes
            next = temp.next;
            temp.next = prev;
            prev = temp;
            temp = next;
            cnt--;
        }
        start.next = next; //Attach the next part of the remaining list to tail of the reversed list
        return prev; // Return new head of this sublist
    } 
    public ListNode reverseBetween(ListNode head, int left, int right) {
        ListNode temp = head;
        ListNode prev = null;

        //Move the pointer till starting point and also store previous. Also check if the list at all has that many nodes
        for (int i = 0; i < left - 1 && temp != null; i++) {
            prev = temp;
            temp = temp.next;
        }
        
        //If left == 1, that means we reverse from head node, hence just reverse and attach the next node and return new head
        if (left == 1) {
            return reverse(head, right - left + 1);
        }
        //If the list doesn't have that many nodes or only one node
        if (temp == null || temp == head) {
            return head;
        }
        
        /* Reverse from starting point and reverse the required number of nodes and attach the previous sublist with new head.
         * Note, we are alreading attaching the next part of the sublist while reversing only
         */
        prev.next = reverse(temp, right - left + 1);
        return head;
    }
}
