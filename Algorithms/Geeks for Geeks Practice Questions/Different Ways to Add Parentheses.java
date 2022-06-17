/*
Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators.
You may return the answer in any order.
The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.

Example 1:

Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0 
(2-(1-1)) = 2
Example 2:

Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10
 
Constraints:

1 <= expression.length <= 20
expression consists of digits and the operator '+', '-', and '*'.
All the integer values in the input expression are in the range [0, 99].

Solution : Divide and Conquer - we partition the main expression to subexpressions based on operators and do the same for subexpressions until we get only
operands. And then based on the results, we compute the bigger subexpressions. One thing to note that is for a subexpression, we are doing repeated calculations.
Hence we also store the result of a subexpression to avoid redundant calculations.
*/

class Solution {
    Map<String, List<Integer>> m = new HashMap<>();
    
    public int perform(int a, int b, char c) {
        if (c == '+') return a + b;
        if (c == '-') return a - b;
        return a * b;
    }
    
    public List<Integer> diffWayToCompute(String exp, int start, int end) {
        if (m.containsKey(String.valueOf(start) + String.valueOf(end))) { //If already calculated, find and return
            return m.get(String.valueOf(start) + String.valueOf(end));
        }
        boolean allDigits = true; //to track if it's only an operand
        List<Integer> res = new ArrayList<>();
        for (int i = start; i <= end; i++) {
            if (!Character.isDigit(exp.charAt(i))) {//for every operator, partition the expression in subexpression
                allDigits = false; //mark that expression is not a single operand
                List<Integer> list1 = diffWayToCompute(exp, start, i - 1); //compute subexpressions
                List<Integer> list2 = diffWayToCompute(exp, i + 1, end);
                
                for (int j = 0; j < list1.size(); j++) { //Compute the result of subexpression into result
                    for (int k = 0; k < list2.size(); k++) {
                        res.add(perform(list1.get(j), list2.get(k), exp.charAt(i)));
                    }
                }
            }
        }
        if (allDigits) { //if expression had no operator then it is a operand, add operand as a single element list
            res.add(Integer.valueOf(exp.substring(start, end + 1)));
        }
        m.put(String.valueOf(start) + String.valueOf(end), res); //store to avoid same recalculation - key - start + end : value -> list
        return res;
    }
    
    public List<Integer> diffWaysToCompute(String expression) {
        return diffWayToCompute(expression, 0, expression.length() - 1);
    }
}
