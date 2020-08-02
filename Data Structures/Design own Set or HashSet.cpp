/*
Design a HashSet without using any built-in hash table libraries.

To be specific, your design should include these functions:

add(value): Insert a value into the HashSet. 
contains(value) : Return whether the value exists in the HashSet or not.
remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.

Example:

MyHashSet hashSet = new MyHashSet();
hashSet.add(1);         
hashSet.add(2);         
hashSet.contains(1);    // returns true
hashSet.contains(3);    // returns false (not found)
hashSet.add(2);          
hashSet.contains(2);    // returns true
hashSet.remove(2);          
hashSet.contains(2);    // returns false (already removed)

Note:

All values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashSet library.

Solution : As we know HashSet or Set performs insert, delete and search in O(1).
This design uses 3 lists and a hash function. The hash function is simple, we choose a random large prime here 13001 and mod the
key to obtain the hashvalue. Essentially this hashvalue can range from 0 - 13000. Now the 3 lists are - one is a list of size 13001
where each element points to a linked list storing the values that has the same hashvalue. This list is the main hashset or hashlist.
Second is a boolean list of size 13001 to indicate whether that the bucket at ith position of hashlist has been occupied or not. This
will be predominantly used by add() or contains() to determine in O(1) to understand the possibility of occurance of a key. If the bucket
at ith position is empty, then the key corresponding to hashvalue of i can never be present in the set. So, we can immediately return
false to contains() or just add the key initializing the bucket at ith position to perform contains() and add() in O(1). The 3rd list is
a list of pointers containing the address to the last node of the linked list at each bucket position i of hashlist. This is used to retrieve
the last node of the linked list of any bucket in the hashlist so that any key corresponding to that hashvalue can be inserted in O(1) and we
don't need to traverse the whole linkedlist corresponding to that bucket.

contains() - We check if the position at key % hashprime in boolean list is true, if not we immediately return false. Else, we search the whole
linked list/bucket corresponding to that position to find out the key.

add() - We check if the key is already present or not using contains(). If the key is already present, we don't add else, we retrieve the last
node corresponding to the bucket using the hashvalue and lastnodelist. Add the key in a new node and update the lastnode to be the new node in 
that list. While doing this, we also need to check if the bucket was empty, that is no key corresponding to the hashvalue is present currently
in the hashset, in that case we have to initialise the bucket accordingly and update lastnode accordingly.

remove() - We check if the key is present using contains(). If not present, do nothing. Else, traverse the bucket/linked list corresponding to
the hashvalue of the key and remove the key just like how a node is deleted in a linkedlist. Two special points to be noded here, if the key is
the only element in that bucket or whether it is the head node of the linked list. If it is the only node in that bucket, we have to set the bucket
to be NULL and set ifpresent boolean list position corresponding to that hashvalue to be false after removing the node to maintain consistency.

TIME COMPLEXITY : Although the search and removal operation doesn't seem to be O(1) as we have to traverse a linked list in case of collision,
but if we do easy calculation, we can see that our given key range is [0, 100000] hence using a hashprime of 13001, the maximum number of collision,
that can occur at each position is 8. So, traversing a list of size 8 is constant. We can avoid collisions using a greater hashprime but that increases
the space complexity which is inefficient. So overall, all operations are being performed in O(1). Insert is truly O(1) because even if collision occurs
we are inserting the key just after the lastnode retrieving the last node of the bucket using the lastnodelist.

SPACE COMPLEXITY : We are using 3 lists - 2 having fixed size of hashprime - 13001 (boolean ifpresent and lastnode list). So they take O(1).
The actual space is occupied by hashlist which is actually a list of list. The number of bucket it can contain is 13001 and each bucket can
again contain upto 8 nodes when key range varies from [0, 100000]. So, the size depends on number of keys and hence O(n).
*/

//Linked List node structure for bucket
typedef struct Node{
    long int val;
    struct Node* next;
} node;

class MyHashSet {
public:
    int hashprime;
    node* hashlist[13001]  = {NULL};  //Actual hashset containing (hashprime - 1) buckets/linked list 
    bool  ifpresent[13001] = {false}; //Boolean list to track if a bucket at ith position of hashlist is empty or not
    node* lastnodelist[13001] = {NULL}; //List storing the lastnode of each bucket of hashlist for insertion in O(1)
    
    node* newnode(long int value) { //Utility function to create a new node in the bucket/linked list
        node* newn = (node*)malloc(sizeof(node));
        newn->val  = value;
        newn->next = NULL;
        return newn;
    }
    
    MyHashSet() {
        hashprime    = 13001; //The larger the hashprime, lesser collision, more time efficient but more bulky/space inefficient.
    }
    
    void add(int key) {
        int hashval = key % hashprime; //Hash function to determine which bucket key will be stored
        if (contains(key)) { //If already key present, no need to add
            return;
        }
        if (ifpresent[hashval]) { //If bucket is already present, that means there is a collision
            node* lastn = lastnodelist[hashval]; //Retrieve the last node of the bucket/linked list
            node* newn  = newnode(key); //create the new node
            lastn->next = newn; //Insert it at the end of that bucket
            lastnodelist[hashval] = newn; //Update the last node of that bucket/linked list to track the new last node
        } else { //Bucket is not initialised
            ifpresent[hashval] = true; //Update the presence of the new bucket being created at that hashvalue
            hashlist[hashval] = newnode(key); //The new node is the head of the bucket at that hashvalue position
            lastnodelist[hashval] = hashlist[hashval]; //Also track the new node to be the last node at that bucket
        }
    }
    
    void remove(int key) {
        int hashval = key % hashprime;
        node* temp  = hashlist[hashval];
        
        if(!contains(key)) { //If doesn't contain, no question of removal
            return;
        }
        if (hashlist[hashval]->val == key) { //If the key is the head node of that bucket 
            hashlist[hashval] = temp->next; //Update the head node to be the next node in that bucket
            free(temp); //Free the node and remove the key from set.
            if (!hashlist[hashval]) { //But if the node was the only node in that bucket
                ifpresent[hashval]    = false; //Update that the bucket is now empty
                lastnodelist[hashval] = NULL; //Update that there is no last node as the bucket is empty
            }
        } else { //Delete the node with that key value from the bucket/linked list
            node* prev = NULL;
            
            while (temp->val != key) {
                prev = temp;
                temp = temp->next;
            }
            /* If the node/key to be removed is the last node, update    *
             * the last node to track the previous node as the last node */
            if (temp == lastnodelist[hashval]) {
                lastnodelist[hashval] = prev;
            }
            prev->next = temp->next;
            free(temp);
        }
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int hashval = key % hashprime;
        /* Check if the bucket corresponding to that hashvalue is empty, *
         * if not then traverse the bucket to find the node with the key */
        if (ifpresent[hashval]) {
            node* temp = hashlist[hashval];
            
            while (temp != NULL) {
                if (temp->val == key) {
                    return true;
                }
                temp = temp->next;
            }
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
