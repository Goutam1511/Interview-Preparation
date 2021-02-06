/*
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.
In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes 
(i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')
Return the simplified canonical path.

Example 1:

Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
Example 2:

Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
Example 3:

Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
Example 4:

Input: path = "/a/./b/../../c/"
Output: "/c"

Constraints:

1 <= path.length <= 3000
path consists of English letters, digits, period '.', slash '/' or '_'.
path is a valid absolute Unix path.

Solution : First make sure the given path starts and ends with '/' if not so then append a '/' at the end of path.
Create a stack of string.
Initialize ans string to "" and start iterating the path string from '1' index as path[0] will always be '/'.
Create a temp variable which will keep substrings upto '/', after that it will be checked with some conditions and then reset it back to "".
In each iteration check whether path[i] == '/', if true then check our temp string on the basis of below conditions (according to question ) :
If temp=="" || temp=="." then ignore.
If temp==".." then pop the top element from stack if it exists.
If non of above matches then push temp to stack.
After checking the above conditions, reset temp to ""
Finally, after the above loop ends, pop all the elements of the stack and store it in ans with a '/' in front, shown as follows : ans="/"+s.top()+ans.
Return ans
Complexity : O(n)
*/

class Solution {
public:
    string simplifyPath(string path) {
        int n=path.length();
        stack<string>s;
                
        if(path[n-1]!='/') // so that initially path always ends with '/'
            path+="/", ++n;
            
        int i=1; // since path always starts from '/'
        string ans="";
        string temp="";
        while(i<n){
            
            if(path[i]=='/'){ // check only if we encounter '/'
                
                if(temp=="" || temp=="."){
                    // ignore
                }
                else if(temp==".."){
                    if(!s.empty()) s.pop(); // pop the top element from stack if exists
                }
                else{
                    s.push(temp); //push the directory or file name to stack
                }
                
                temp=""; // reset temp
            }
            else{
                temp.push_back(path[i]); // else append to temp
            }
            
            ++i; // increment index
        }
        
        while(!s.empty()){ // add all the stack elements
            ans="/"+s.top()+ans;
            s.pop();
        }
        
        if(ans.length()==0) // if no directory or file is present
            ans="/"; // minimum root directory must be present in ans
        
        return ans;
    }
};
