/*
Design a stack-like data structure to push elements to the stack and pop the most frequent element from the stack.

Implement the FreqStack class:

FreqStack() constructs an empty frequency stack.
void push(int val) pushes an integer val onto the top of the stack.
int pop() removes and returns the most frequent element in the stack.
If there is a tie for the most frequent element, the element closest to the stack's top is removed and returned.

Example 1:

Input
["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
[[], [5], [7], [5], [7], [4], [5], [], [], [], []]
Output
[null, null, null, null, null, null, null, 5, 7, 5, 4]

Explanation
FreqStack freqStack = new FreqStack();
freqStack.push(5); // The stack is [5]
freqStack.push(7); // The stack is [5,7]
freqStack.push(5); // The stack is [5,7,5]
freqStack.push(7); // The stack is [5,7,5,7]
freqStack.push(4); // The stack is [5,7,5,7,4]
freqStack.push(5); // The stack is [5,7,5,7,4,5]
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].

Constraints:

0 <= val <= 109
At most 2 * 104 calls will be made to push and pop.
It is guaranteed that there will be at least one element in the stack before calling pop.

Solution : 
Intuition

Evidently, we care about the frequency of an element. Let freq be a Map from xx to the number of occurrences of xx.
Also, we (probably) care about maxfreq, the current maximum frequency of any element in the stack. This is clear because we must pop 
the element with the maximum frequency. The main question then becomes: among elements with the same (maximum) frequency, 
how do we know which element is most recent? We can use a stack to query this information: the top of the stack is the most recent.
To this end, let group be a map from frequency to a stack of elements with that frequency. We now have all the required components to implement FreqStack.

Algorithm

Actually, as an implementation level detail, if x has frequency f, then we'll have x in all group[i] (i <= f), not just the top. This is because each group[i]
will store information related to the ith copy of x. Afterwards, our goal is just to maintain freq, group, and maxfreq as described above.
*/

class FreqStack {
    Map<Integer, Integer> freqMap; //Frequency of a number
    Map<Integer, Stack<Integer>> mostFreqElemSt; //Frequency wise Storing number occurences in Stack
    int maxFreq; // Track maximum freq so far
    public FreqStack() {
        freqMap = new HashMap<Integer, Integer>();
        mostFreqElemSt = new HashMap<Integer, Stack<Integer>>();
        maxFreq = 0;
    }
    
    public void push(int val) {
        int currentFreq = freqMap.getOrDefault(val, 0);
        freqMap.put(val, currentFreq + 1); //Update frequency of a number
        mostFreqElemSt.putIfAbsent(currentFreq + 1, new Stack<Integer>());
        mostFreqElemSt.get(currentFreq + 1).push(val); //Put the number in corresponding frequency stack
        maxFreq = Math.max(maxFreq, currentFreq + 1); //Update maximum frequency
        //System.out.println("Push : " + maxFreq);
    }
    
    public int pop() {
        int val = mostFreqElemSt.get(maxFreq).pop(); //Take the last occured number from the mostFrequent stack
        int freq = freqMap.get(val);
        /* Check if that number frequency is 1, that is now maxfrequency is 1 and the number has also occured once.
         * If that's the case, then remove the number from frequency map, else update the frequency of number.
         */
        if (freq > 1) { 
            freq--;
            freqMap.put(val, freq);
        } else {
            freqMap.remove(val);
        }
        //Check if for the maximum frequency, that was the last number with that frequency, if so remove stack and update maxFreq
        if (mostFreqElemSt.get(maxFreq).isEmpty()) {
            mostFreqElemSt.remove(maxFreq);
            maxFreq--;
        }
        //System.out.println("Pop : " + maxFreq + " Val : " + val);
        return val;
    }
}
