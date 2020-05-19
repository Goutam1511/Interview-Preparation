#include <bits/stdc++.h>
using namespace std;

/*
Write a class StockSpanner which collects daily price quotes for some stock, and returns the span of that stock's price for the current day.
The span of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backwards) for which the price of the stock was less than or equal to today's price.
For example, if the price of a stock over the next 7 days were [100, 80, 60, 70, 60, 75, 85], then the stock spans would be [1, 1, 1, 2, 1, 4, 6].

Example 1:

Input: ["StockSpanner","next","next","next","next","next","next","next"], [[],[100],[80],[60],[70],[60],[75],[85]]
Output: [null,1,1,1,2,1,4,6]
Explanation: 
First, S = StockSpanner() is initialized.  Then:
S.next(100) is called and returns 1,
S.next(80) is called and returns 1,
S.next(60) is called and returns 1,
S.next(70) is called and returns 2,
S.next(60) is called and returns 1,
S.next(75) is called and returns 4,
S.next(85) is called and returns 6.

Note that (for example) S.next(75) returned 4, because the last 4 prices
(including today's price of 75) were less than or equal to today's price.

Note:
    Calls to StockSpanner.next(int price) will have 1 <= price <= 10^5.
    There will be at most 10000 calls to StockSpanner.next per test case.
    There will be at most 150000 calls to StockSpanner.next across all test cases.
    The total time limit for this problem has been reduced by 75% for C++, and 50% for all other languages.

Solution Approach : Have a stack that will always store the last element processed
and its index as an pair. At any point, whenever an element is processed, the stack
is popped until the top of the stack contains an element greater than the current 
element being processed. If the stack becomes empty, we store the current element
and its index as a pair and return the currentIndex as the duration of stock span
else we return the difference between the top element index at stack and the current
index being processed and store the last element processed and its index in stack.

VISUAL DRY RUN :
Input : 100, 80, 60, 70, 60, 75, 85.

Processing 100:
Stack : EMPTY
Insert 100 in Stack : 100, Return 1 (CurrentIndex + 1) as duration.
Processing 80:
Stack : 100
Insert 80 in Stack : 100 80, Return 1 - 0 (Stack top index = 0, currentIndex = 1).
Processing 60:
Stack : 100 80
Insert 60 in Stack : 100 80 60, Return 2 - 1 (Stack top index = 1, currentIndex = 2).
Processing 70
Stack : 100 80 60
After pop : 100 80
Insert 70 in Stack : 100 80 70, Return 3 - 1 (Stack top index = 0, currentIndex = 3).
Processing 60:
Stack : 100 80 70
Insert 60 in Stack : 100 80 70 60, Return 4 - 3 (Stack top index = 3, currentIndex = 4).
Processing 75:
Stack : 100 80 70 60
After pop : 100 80
Insert 75 in Stack : 100 80 75, Return 5 - 1 (Stack top index = 1, currentIndex = 5).
..................
And so on
*/

class StockSpanner {
public:
    stack<pair<long int, long int> > s;
    long int currentindex = -1;
    StockSpanner() {
        
    }
    
    int next(int price) {
        long int count = 0;
        while (!s.empty() && s.top().first <= price) {
            s.pop();
        }
        s.empty() ? count = (++currentindex) + 1 : count = (++currentindex) - s.top().second;
        /*if (!s.empty())
        cout<<"Top : "<<s.top().second<<" Count : "<<count<<endl;*/
        s.push(make_pair(price, currentindex));
        return count;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

int main() {
	// Online Stock Plan LeetCode May Challenge 2020
	return 0;
}
