/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 
 /*
  Given a linked list, remove the n-th node from the end of list and return its head.
  Example:
  Given linked list: 1->2->3->4->5, and n = 2.

  After removing the second node from the end, the linked list becomes 1->2->3->5.
  Note:
  Given n will always be valid.
  Follow up:
  Could you do this in one pass?
 */

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *ptr1 = head;
    struct ListNode *ptr2 = head;
    struct ListNode *temp = NULL;
    
    //If only one node present
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return head;
    }

    /* The eminent two-pointer approach!                *
     * While one pointer keeps pointing to the head,    *
     * the other pointer is moved till the gap between  *
     * pointer1 and pointer2 is n.                      */
    while (n--) {
        ptr2 = ptr2->next;
    }
    
    /* If ptr2 has reached end of list, that means the size of the list was n only. *
     * That implies we have to remove the head.                                     */
    if (!ptr2) {
        temp = ptr1->next;
        free(ptr1);
        head = temp;
        return head;
    }

    /* Now when ptr2 reaches to the last node,   *
     * ptr1 will be pointing to the NODE BEFORE  *
     * the nth node from last. Relink the list   *
     * appropriately through ptr1 and remove the *
     * nth node from last.                       */
    while (ptr2->next != NULL) {
        ptr2 = ptr2->next;
        ptr1 = ptr1->next;
    }
    temp = ptr1->next;
    ptr1->next = temp->next;
    free(temp);
    return head;
}
