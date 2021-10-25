/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

Constraints:

-2^31 <= val <= 2^31 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 104 calls will be made to push, pop, top, and getMin.

Solution : Classic two stack solution, one stack storing the original values and the other maintaining the updated minimum at each point.
*/

class MinStack {
public:
    stack<int> st;
    stack<int> min;
    MinStack() {
        
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push(val);
            min.push(val);
        } else {
            if (val < min.top()) {
                min.push(val);
            } else {
                min.push(min.top());
            }
            st.push(val);
        }
    }
    
    void pop() {
        if (!st.empty()) {
            st.pop();
            min.pop();
        }
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return min.top();
    }
};
