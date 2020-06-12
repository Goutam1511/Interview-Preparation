/*
Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.

Example: 
// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();

Solution : We would have used hash table/map to insert, delete and remove in O(1) in average case. Challenge here is to have the random 
operation. The trick is to use a resizable array or vector whose last element can be removed in O(1). The approach is to, maintain a hashtable 
with keys as the values in the set and the values of the hashtable will be index to the vector where the values of the set are stored. We will
always lookup the hashtable while inserting in O(1) and if value is not present then we will insert at the back of the vector and store 
the last index of the vector and the value in the hashtable, also keeping track of the size. The complex trick is remove operation. While
removing we will not directly remove the element from hashtable and vector as that will be costly. But what we will do is, retrieve the
index of the value in the vector if present in the hashtable and swap that element with the last element of the vector. Then remove the
last element of the vector and update the index of the swapped past last element in the hashtable accordingly. Finally, we will remove the
entry of the element to be deleted from hashtable and decrement the size. Random is easy now with the vector present. Just return a random
element from vector.
*/

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    int size; //Keep track of size
    vector<int> contents; // Vector to track the contents
    /* Key is values in the vector and Value of Hashtable is index of 
     * the vector where val is stored - {Value in vector, its index} */
    map<int, int> hashtable; 
    
    RandomizedSet() {
        size = 0;
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (hashtable.count(val)) { //If value present, no need to insert again
            return false;
        }
        hashtable.insert(make_pair(val, size)); //Insert the element as key and value will be last index of vector + 1
        contents.push_back(val); //Insert at back of vector
        size++;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        int temp = 0, index = 0;
        if (!hashtable.count(val)) { //If not present, return false
            return false;
        }
        temp  = contents[size - 1]; 
        index = hashtable[val]; //Lookup the hash table for index of the element to be removed in vector
        contents[index]  = temp; //Move the last element of vector in place of element to be removed
        hashtable[temp]  = index; //Update the value of the newly swapped element in the hashtable.
        hashtable.erase(val); //Remove the entry of the element removed from hash table
        contents.pop_back(); //Resize the vector
        size--;
        return true;
    }
    
    /** Get a random element from the set (Here a random element from current elements in vector). */
    int getRandom() {
        int rnd = rand() % size;
        return contents[rnd];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
