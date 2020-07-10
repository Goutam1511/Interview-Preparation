// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

/*
Problem Link : https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

You are given a doubly linked list which in addition to the next and previous pointers, it could have a child pointer, 
which may or may not point to a separate doubly linked list. These child lists may have one or more children of their own, 
and so on, to produce a multilevel data structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given the head of the first level of the list.

Example 1:

Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
Output: [1,2,3,7,8,11,12,9,10,4,5,6]
Explanation:

We use the multilevel linked list from Example 1 above:

 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL
The serialization of each level is as follows:

[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]
To serialize all levels together we will add nulls in each level to signify no node connects to the upper node of the previous level. The serialization becomes:

[1,2,3,4,5,6,null]
[null,null,7,8,9,10,null]
[null,11,12,null]
Merging the serialization of each level and removing trailing nulls we obtain:

[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
 
Output : 1--2--3--7--8--11--12--9--10

Example 2:

Input: head = [1,2,null,3]
Output: [1,3,2]
Explanation:

The input multilevel linked list is as follows:

  1---2---NULL
  |
  3---NULL
  
 Output : 
 
 1--3--2--NULL
 
Example 3:

Input: head = []
Output: []

Constraints:
Number of Nodes will not exceed 1000.
1 <= Node.val <= 10^5

Corner Case : 
 
 1--NULL
 |
 2--NULL
 |
 3--NULL
 |
 ....

Solution : Use recursion and go on iterating, if a child is found, store the next node in that level and recursively flatten the child.
The recursive function returns the last node of the child level, so append the next node stored to the last node returned from the recursion.
Do this recursively until the last node of the first level is reached. The lastnode of the first level can again contain child so that needs
to be handled seperately using the same logic again.

Time Complexity : O(n) as all nodes are visited only once.
*/

class Solution {
public:
    Node* flattenlist(Node* cur) {
        Node* current  = cur;
        Node* nextnode = NULL;
        Node* lastnode = NULL;
        
        while (current->next != NULL) { //Until the last node of the current level is reached
            if (current->child) { //If child exists flatten it recursively
                nextnode             = current->next; //Store the next node before entering the recursion
                current->next        = current->child; //Append the child to the current level to flatten the child level
                lastnode             = flattenlist(current->child); //Get the lastnode of the child level
                current->child->prev = current; //Reset the prev pointer of the child node
                current->child       = NULL; //Current now has no child as the child level has been flattened
                lastnode->next       = nextnode; //Append the stored next node to the last node of the child level
                nextnode->prev       = lastnode; //Set the prev pointer of the stored next node to point to lastnode of child level
                current              = nextnode; //Continue with the iteration from next node
            } else {
                current = current->next; //Go on iterating until last node
            }
        }
        
        return current;
    }
    
    Node* flatten(Node* head) {
        Node* nextnode = NULL;
        Node* lastnode = NULL;
        Node* current  = NULL;
        
        if (!head) {
            return NULL;
        }
        
        lastnode = flattenlist(head); The multi-level list is flattened till the last node of first level
        
        while (lastnode->child) { //The last node of first level needs to be handled seperately to counter the corner case mentioned above
            current         = lastnode->child; 
            current->prev   = lastnode; 
            lastnode->next  = current; //Append the child to the last node
            lastnode->child = NULL; //Set the child of the last node to NULL
            lastnode        = current; //Now last node is the appended child
        } 
        return head; //Return the head of the newly flattened list
    }
};
