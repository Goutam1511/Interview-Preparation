#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	string s;
	cin>>t;
	while (t--) {
	    stack<char> st;
	    bool flag = true;
	    cin>>s;
	    for (long int i = 0; i < s.length(); i++) {
	        if (s[i] == '{' || s[i] == '(' || s[i] == '[')
	            st.push(s[i]);
	        else {
	            if (st.empty()) { //Number of pops cannot be greater than push
	                flag = false;
	                break;
	            }
	            char c = st.top();
	            if (c == '{' && s[i] != '}') { //Order of paranthesis must be same
	                flag = false;
	                break;
	            }
	            if (c == '(' && s[i] != ')') {
	                flag = false;
	                break;
	            }
	            if (c == '[' && s[i] != ']') {
	                flag = false;
	                break;
	            }
	            st.pop(); //Pop to close
	        }
	    }
	    if (flag && st.empty()) { //At the end stack should be empty
	        cout<<"balanced"<<endl;
	    } else {
	        cout<<"not balanced"<<endl;
	    }
	}
	return 0;
}
