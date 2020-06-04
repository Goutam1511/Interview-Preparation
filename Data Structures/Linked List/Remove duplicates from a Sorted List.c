/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 
/* 
Given a sorted linked list, delete all duplicates such that each element appear only once.

Example 1:

Input: 1->1->2
Output: 1->2

Example 2:

Input: 1->1->2->3->3
Output: 1->2->3

Solution : The idea is to maintain two pointers - one pointer will hold its position and the other will move until 1st 
pointer->value == 2nd pointer->value. While moving we will go on deleting these duplicate values and reassigning the next 
pointer of 1st pointer to current 2nd pointer.If not 1st pointer->value == 2nd pointer->value then, 1st pointer = current
2nd pointer & 2nd pointer = current 2nd pointer->next

VISUAL DRY RUN

Input: 1->1->2->3->3

1)         2nd ptr                                     
              | 
           1->1->1->2->3->3->NULL
           |
         1st ptr
2)         2nd ptr
              | 
           1->2->3->3->NULL
           |
         1st ptr
3)             2nd ptr
                 | 
           1->2->3->3->NULL
              |
            1st ptr
4)                2nd ptr
                    | 
           1->2->3->3->NULL
                 |
              1st ptr   
5)                2nd ptr
                    | 
           1->2->3->NULL
                 |
              1st ptr  
Output: 1->2->3
*/



struct ListNode* deleteDuplicates(struct ListNode* head){
    if (head == NULL || head->next == NULL)
        return head;
    struct ListNode* prevnode = head;
    struct ListNode* nextnode = head->next;
    struct ListNode* tempnode = NULL;
    
    while (nextnode != NULL) {
        while (nextnode && prevnode->val == nextnode->val) {
            tempnode       = nextnode;
            nextnode       = nextnode->next;
            prevnode->next = nextnode;
            free(tempnode);
        }
        if (nextnode) {
            prevnode = nextnode;
            nextnode = nextnode->next;
        }
    }
    return head;
}
