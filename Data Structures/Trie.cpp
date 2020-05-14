#include <bits/stdc++.h>
using namespace std;

/*
  Implement a trie with insert, search, and startsWith methods.
	Example:
	Trie trie = new Trie();

	trie.insert("apple");
	trie.search("apple");   // returns true
	trie.search("app");     // returns false
	trie.startsWith("app"); // returns true
	trie.insert("app");   
	trie.search("app");     // returns true
 */

typedef struct TrieNode {
    map<char, struct TrieNode*> charset;
    bool endofword;
    /* When inserting a word, by default,
       end of word indicator will be false
       as new characters might be coming.
       This will be false even for an empty trie.
       It will be true only for the node containing
       the last character of a word to indicate END OF WORD.
     */
    TrieNode() {
        endofword = false;
    } 
} node;

class Trie {
public:
    /** Initialize your data structure here. */
    node* root = NULL;
    Trie() { //Only instantiate trie when a word is inserted
        root = NULL;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        int i = 0;
        if (isempty()) {
            root = new node();
        }
        node* ptr = root;
        for (i = 0; i < word.length(); i++) {
        	/* Check if character exists. If yes,
        	   then move to the next node following
        	   the character trail. If it is the last
        	   character, then mark the next node
        	   End of Word indicator as false to indicate
        	   a new word has been introduced which is the
        	   prefix of an existing word.
        	 */
            if ((ptr->charset).count(word[i])) {
                ptr = (ptr->charset)[word[i]];
                if (i == word.length() - 1) {
                    ptr->endofword = true;
                }
            } else {
            	/* Else insert the character into set and
            	   allocate a new node with End of Word as false
            	   if not the last character else mark true.
            	 */
                node* newnode = new node();
                (ptr->charset).insert(make_pair(word[i], newnode));
                if (i != word.length() - 1)
                    newnode->endofword = false;
                else
                    newnode->endofword = true;
                ptr = newnode;
            }
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        node* ptr = root;
        if (isempty())
            return false;
        for (int i = 0; i < word.length(); i++) {
        	/* Check if character exists. If yes,
        	   then move to the next node following
        	   the character trail. Else return false.
        	 */
            if ((ptr->charset).count(word[i])) {
                ptr = (ptr->charset)[word[i]];
            } else {
                return false;
            }
        }
        /* This is critical. A word might exist as a whole
           or another word might exist whose prefix is the
           word being searched. To avoid this ambiguity, the
           End Of Word flag is being used. Hence the below check
         */
        if (!ptr->endofword)
            return false;
        return true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        node* ptr = root;
        
        if (isempty())
            return false;
        for (int i = 0; i < prefix.length(); i++) {
            if ((ptr->charset).count(prefix[i])) {
                ptr = (ptr->charset)[prefix[i]];
            } else {
                return false;
            }
        }
        /* No need to check End of Word. Return */
        return true;
    }
    
    bool isempty() {
        return root == NULL? true : false; 
    }
};

int main() {
	Trie* obj = new Trie();
    obj->insert("apple");
    cout<<obj->search("apple")<<endl;
    cout<<obj->startsWith("app")<<endl;
	return 0;
}
