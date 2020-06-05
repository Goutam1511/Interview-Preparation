/*
Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.

Solution : Maintain a hashmap where key is the sorted version of each string and value is the vector of anagrams.
Complexity : O(NMlogM) where N is number of strings and MlogM is the time to sort the largest string of length M.
*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> identity_count;
        int i = 0, j = 0;
        vector<vector<string>> result;
        
        for (i = 0; i < strs.size(); i++) {
        //Find the sorted version of string to check if anagram already exists. If yes group it, else enter a new entry in map
            string res = strs[i];
            sort(res.begin(), res.end());
            if (identity_count.count(res)) {
                identity_count[res].push_back(strs[i]);
            } else {
                identity_count.insert(make_pair(res, vector<string> {strs[i]}));
            }
        }
        map<string, vector<string>>::iterator itr;
        for (itr = identity_count.begin(); itr != identity_count.end(); ++itr) {
            vector<string> temp;
            for (i = 0; i < itr->second.size(); i++) {
                temp.push_back((itr->second)[i]);
            }
            result.push_back(temp);
        }
        return result;
    }
};
