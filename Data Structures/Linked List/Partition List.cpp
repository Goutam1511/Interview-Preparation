/*
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example 1:

Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Example 2:

Input: head = [2,1], x = 2
Output: [1,2]

Constraints:
The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200

Solution : Maintain 4 pointers - head_smaller, head_greater, current_greater, current_smaller. Line up all the smaller nodes side by side
and all the greater nodes side by side then link the last smaller node with the greater node.
Time & Space Complexity : O(n) & O(1).

Edge cases :
 1. Empty List
 2. All greater than x
 3. All smaller than x
 4. Single node list
*/

/* Definition for singly-linked list. */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* head_greater = new ListNode(); //Dummy head node to point to all values greater than x
        ListNode* head_smaller = new ListNode(); //Dummy head node to point to all values smaller than 
        ListNode* temp = head;
        //ListNode* debug = NULL;
        ListNode* current_greater = NULL;
        ListNode* current_smaller = NULL;
        
        if (!head) // List empty scenario
            return head;
        
        while (temp) {
            if (temp->val < x) {
               /* If value of current node is less than x, then check if the head_smaller is already      *
                * pointing to something or not, if not then this is the first node smaller than x. Also   *
                * keep on tracking the current_smaller to always point the last node visited smaller than *
                * x. If head_smaller was already populated, then line up the node next to last smaller.   */
                if (!head_smaller->next) {
                    head_smaller->next = temp;
                } else {
                    current_smaller->next = temp;
                }
                current_smaller = temp;
            } else {
                if (!head_greater->next) {
                    head_greater->next = temp;
                } else {
                    current_greater->next = temp;
                }
                current_greater = temp;
            }
            temp = temp->next;
        }
        
        if (current_greater)
          //Make sure that the last greater node now points to NULL to avoid making a circular list
            current_greater->next = NULL;
        
        if (!current_smaller) { //If there is no current_smaller means all nodes were greater than/equal x
            return head_greater->next;
        }
        current_smaller->next = head_greater->next; //Link up last smaller node with the first greater
        
        /*debug = head_smaller->next;
        cout<<endl;
        while (debug) {
            cout<< debug->val <<" ";
            debug = debug->next;
        }*/
        
        return head_smaller->next; //Return the first smaller node
    }
};
