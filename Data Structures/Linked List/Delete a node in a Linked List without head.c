/*
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Given linked list -- head = [4,5,1,9], which looks like following:


4 -> 5 -> 1 -> 9 -> NULL
 

Example 1:

Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.
Example 2:

Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.
 

Note:

The linked list will have at least two elements.
All of the nodes' values will be unique.
The given node will not be the tail and it will always be a valid node of the linked list.
Do not return anything from your function.

Personal Note : This question was asked to me at F5 Networks interview.

Solution Approach : The key to solve this problem is to consider the hint (This hint was given to me during the interview by Vamshi)
- "Do we at all need the previous node references?". Then consider, "Does deleting a node only means freeing that exact node?".
The trick is instead of freeing that very node, we will go on copying every values after that node to it's previous node and then 
ultimately delete the last node and set the penultimate node as last node, thus decreasing the linked list size by 1. It will look
as if the node was never there. But instead the given node address still remains with it's value changed. Ultimately the last node
is actually freed.

Time Complexity : O(n). In Worst Case, if the head node is to be deleted, we end up iterating the whole list.
*/

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};

void deleteNode(struct ListNode* node) {
    struct ListNode* temp = NULL;
    //Go on copying all the values until penultimate node reached
    while (node->next->next != NULL) {
        node->val = node->next->val;
        node      = node->next;
    }
    //Now node points to last before one node
    node->val  = node->next->val; //Copy last node value
    temp       = node->next; //Store last node address
    node->next = NULL; //Set the penultimate node as last node
    free(temp); //Free last node
}

/*
Optimisation : No need to copy whole list after the given node. Just copying the next node is enough.
LeetCode : 237. Delete Node in a Linked List
class Solution {
    public void deleteNode(ListNode node) {
        node.val = node.next.val;
        node.next = node.next.next;
    }
}

Time : O(1)
*/
