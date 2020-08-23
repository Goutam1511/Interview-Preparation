/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

Solution : The easiest approach might seem to be converting the linked list to numbers and then adding and converting back.
But the catch is once the number of nodes in the linkedlist exceeds 30+, soon all the normal data types like int, long int,etc will overflow.
So, we need to add the numbers as it is just like we add two numbers digitwise while traversing the two lists.

Corner Inputs :
[9]
[1,9,9,9,9,9,9,9,9,9]

Corner Cases:
1) The two lists might not be equal
2) There might be carry at the end of the sum (refer corner case)
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
    ListNode* createList(long long int num) {
        ListNode* head = new ListNode(num % 10);
        ListNode* temp = head;
        num = num/10;
        
        while (num) {
            temp->next = new ListNode(num % 10);
            temp = temp->next;
            num = num / 10;
        }
        
        return head;
    }
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int intermediatesum = l1->val + l2->val;
        int sum = intermediatesum % 10;
        int carry = intermediatesum / 10;
        ListNode* head = new ListNode(sum);
        ListNode* temp = head;
        l1 = l1->next;
        l2 = l2->next;
        
        while (l1 && l2) {
            intermediatesum = l1->val + l2->val + carry;
            sum = intermediatesum % 10;
            carry = intermediatesum / 10;
            temp->next = new ListNode(sum);
            temp = temp->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        
        while (l1) {
            intermediatesum = l1->val + carry;
            sum = intermediatesum % 10;
            carry = intermediatesum / 10;
            temp->next = new ListNode(sum);
            temp = temp->next;
            l1 = l1->next;
        }
        
        while (l2) {
            intermediatesum = l2->val + carry;
            sum = intermediatesum % 10;
            carry = intermediatesum / 10;
            temp->next = new ListNode(sum);
            temp = temp->next;
            l2 = l2->next;
        }
        
        if (carry) {
            temp->next = new ListNode(carry);
        }
        
        return head;
    }
};
