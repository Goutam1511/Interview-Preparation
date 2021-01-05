/*
Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
Return the linked list sorted as well.

Example 1:

Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]
Example 2:

Input: head = [1,1,1,2,3]
Output: [2,3]

Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.
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
    ListNode* deleteDuplicates(ListNode* start) {
        // create a dummy node 
        // that acts like a fake 
        // head of list pointing 
        // to the original head 
        ListNode* dummy = new ListNode; 

        // dummy node points 
        // to the original head 
        dummy -> next = start; 

        // Node pointing to last 
        // node which has no duplicate. 
        ListNode* prev = dummy; 

        // Node used to traverse 
        // the linked list. 
        ListNode* current = start; 

        while(current != NULL) 
        { 
            // Until the current and 
            // previous values are 
            // same, keep updating current 
            while(current -> next != NULL && 
                prev -> next -> val == current -> next -> val) 
                current = current -> next; 

            // if current has unique value 
            // i.e current is not updated, 
            // Move the prev pointer to 
            // next node 
            if (prev -> next == current) 
                prev = prev -> next; 

            // when current is updated 
            // to the last duplicate 
            // value of that segment, 
            // make prev the next of current 
            else
                prev -> next = current -> next; 

            current = current -> next; 
        } 

        // update original head to 
        // the next of dummy node 
        start = dummy -> next; 
        return start;
    }
};
