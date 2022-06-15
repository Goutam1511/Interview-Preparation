/*
https://leetcode.com/problems/count-and-say/

Solution : Just repeatedly follow the procedure.
Complexity : O(n!)
*/

class Solution {
    String count(char[] arr) {
        int i = 0;
        String res = "";
        while (i < arr.length) {
            int cnt = 1;
            while (i < arr.length - 1 && arr[i] == arr[i + 1]) {
                i++;
                cnt++;
            }
            res = res + String.valueOf(cnt) + String.valueOf(arr[i]);
            i++;
        }
        return res;
    }
    public String countAndSay(int n) {
        String last = "1";
        if (n == 1) {
            return last;
        }
        
        for (int i = 2; i <= n; i++) {
            last = count(last.toCharArray());
        }
        
        return last;
    }
}
