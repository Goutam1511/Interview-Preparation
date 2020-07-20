/*
Remove all elements from a linked list of integers that have value val.

Example:

Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5

Time Complexity  : O(n)
Space Complexity : O(1)

Corner Cases : 
1) List : 1->NULL, Value : 1
2) List : [] (NULL)
3) List : 6->6->1->2->6->3->4->5->6->NULL, Value : 6
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int value) {
        ListNode* tempnode = NULL;
        ListNode* prevnode = NULL;
        ListNode* nextnode = NULL;
        
        if (!head) { //If head is NULL, return
            return head;
        }
        
        /* While the value is in head, move the head and delete the nodes. Also   *
         * the list might just end while deleting head so check if head is valid. */ 
        while (head && head->val == value) {
            tempnode = head;
            head     = head->next;
            delete tempnode;
        }
        
        tempnode = head;
        prevnode = head;
        
        /* While traversing the remaining list, maintain 3 pointers, one pointing current node,       *
         * one pointing next node and lastly one pointing previous node. Check the value of current   *
         * node, if it is equal to the value to be deleted, then link the previous and the next node. *
         * Delete the current node, assign the current node to be the next node and continue.         */
        while (tempnode != NULL) {
            nextnode = tempnode->next;
            if (tempnode->val == value) {
                prevnode->next = nextnode;
                delete tempnode;
                tempnode = nextnode;
            } else {
                prevnode = tempnode;
                tempnode = tempnode->next;
            }
        }
        
        return head;
    }
};
