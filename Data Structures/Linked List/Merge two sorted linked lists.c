/*
Merge two sorted linked lists and return it as a sorted list.
The list should be made by splicing together the nodes of the first two lists.

Example 1:

Input: l1 = [1,2,4], l2 = [1,3,4]
Output: [1,1,2,3,4,4]
Example 2:

Input: l1 = [], l2 = []
Output: []
Example 3:

Input: l1 = [], l2 = [0]
Output: [0]

Solution : We recursively compare each node and arrange them
Time & Space Complexity : O(n). [For recursion, recursion stack is being used hence O(n)]
*/
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        ListNode* result = NULL; 

        /* Base cases */
        if (a == NULL) 
            return(b); 
        else if (b == NULL) 
            return(a); 

        /* Pick either a or b, and recur */
        if (a->val <= b->val) 
        { 
            result = a; 
            result->next = mergeTwoLists(a->next, b); 
        } 
        else
        { 
            result = b; 
            result->next = mergeTwoLists(a, b->next); 
        } 
        return(result);
    }
};
