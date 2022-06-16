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
