/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 
 /*
 Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.
Example 1:
Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL
Example 2:
Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL
Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...


SOLUTION :

We will have four pointers - 2 pointing to head of odd and even nodes starting. 2 pointers to relink the odd nodes and even nodes as
we traverse the list. We will start traversing the list and go on relinking the odd and even nodes to each other until one of the both
pointers reach the end of the list. Evidently, at the end of traversing in case the list contains odd number of nodes, the even_cur pointing relinking the even
nodes will reach NULL and odd_cur will reach the last node of the list and in case the list contain even number of nodes, the even_cur
will reach the last node and odd_cur will reach the node before the last node. In either case, if we link the odd_cur to the even head,
our job will be done. This is the approach.

VISUAL DRY RUN :

In Case of Odd Number of Nodes:
At beginning:
odd_head/odd_cur
        |
        v
        1->2->3->4->5->NULL
           ^
           |
           even_head/even_cur
           
At end of traversal:
odd_head        odd_cur                                              Odd List :
        |           |                                                1->3>5->NULL
        v           v                                                
        1  2  3  4  5  NULL     //The links have been changed         Even List:
           ^             ^                                            2->4->NULL
           |             |
           even_head    even_cur
Now link odd_cur->next to even_head.  Result : 1->3->5->2->4->NULL
 
In Case of Even Number of Nodes:
At beginning:
odd_head/odd_cur
        |
        v
        1->2->3->4->5->6->NULL
           ^
           |
           even_head/even_cur
           
At end of traversal:
odd_head        odd_cur                                              Odd List :
        |           |                                                1->3>5->6->NULL
        v           v                                                
        1  2  3  4  5  6  NULL     //The links have been changed     Even List:
           ^           ^                                            2->4->6->NULL
           |           |
           even_head  even_cur
Now link odd_cur->next to even_head.  Result : 1->3->5->2->4->NULL
*/

struct ListNode* oddEvenList(struct ListNode* head){
    struct ListNode* odd_head  = head;
    struct ListNode* even_head = NULL;
    
    struct ListNode* odd_cur  = head;
    struct ListNode* even_cur = NULL;
    
    struct ListNode* temp = NULL;
    
    if (head == NULL) { //If list is empty
        return head;
    } else {
        even_head = head->next;
        even_cur  = head->next;
    }
    
    if (even_head == NULL) { //List contains only one node
        return odd_head;
    }
    
    //Traverse the list and relink the even and odd nodes while traversing.
    while (odd_cur && even_cur && odd_cur->next && even_cur->next) {
        odd_cur->next  = odd_cur->next->next;
        even_cur->next = even_cur->next->next;
        odd_cur  = odd_cur->next;
        even_cur = even_cur->next;
    }
    //Relink the odd_cur->next to even_head to complete the merging of odd and even list
    odd_cur->next = even_head;
        
    return odd_head;
}
