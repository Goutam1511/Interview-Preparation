/*
Design an Iterator class, which has:

A constructor that takes a string characters of sorted distinct lowercase English letters and a number combinationLength as arguments.
A function next() that returns the next combination of length combinationLength in lexicographical order.
A function hasNext() that returns True if and only if there exists a next combination.

Example:

CombinationIterator iterator = new CombinationIterator("abc", 2); // creates the iterator.

iterator.next(); // returns "ab"
iterator.hasNext(); // returns true
iterator.next(); // returns "ac"
iterator.hasNext(); // returns true
iterator.next(); // returns "bc"
iterator.hasNext(); // returns false

Constraints:
1 <= combinationLength <= characters.length <= 15
There will be at most 10^4 function calls per test.
It's guaranteed that all calls of the function next are valid.

Solution : Generate all combinations of provided length as a preprocessing and store them. Return them on next() call one by one and return true for
hasNext() until the last string is given away via next().
*/

class CombinationIterator {
    vector<string> temp;
    int i = 0;
public:
    CombinationIterator(string characters, int combinationLength) {
        backtrack(characters, combinationLength, 0, "");
    }
    
    void backtrack(string characters,int combinationlength,int idx,string ans){
        if(ans.size()==combinationlength){
            temp.push_back(ans);
            return;
        }
        for(int i=idx;i<characters.size();i++){
            ans.push_back(characters[i]);
            backtrack(characters,combinationlength,i+1,ans);
            ans.pop_back();
        }
    }
    
    string next() {
        return temp[i++];
    }
    
    bool hasNext() {
        if (i < temp.size())
            return true;
        return false;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
