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

/* Recursive solution */
class Solution {
    public String count(String s, int n) {
        if (n == 0) return s;
        String res = "";
        int cnt = 1;
        char lastChar = s.charAt(0);
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) == lastChar) {
                cnt++;
            } else {
                res += Integer.toString(cnt) + lastChar;
                cnt = 1;
                lastChar = s.charAt(i);
            }
        }
        res += Integer.toString(cnt) + lastChar;
        return count(res, n - 1);
    }
    public String countAndSay(int n) {
        if (n == 1) return "1";
        return count("1", n - 1);
    }
}
