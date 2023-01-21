/*
A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading
zeros.

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to
reorder or remove any digits in s. You may return the valid IP addresses in any order. 

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

Constraints:

1 <= s.length <= 20
s consists of digits only.

Solution : Try introducing dot at each point of the number and whenever we are done traversing the whole string and used up all the dots, check if IP formed
is valid, if valid add it into a list. Other base case is to check if we traversed the whole string and didn't use all dots, then it would be invalid. While
backtracking, at each point we have to check by inserting the dot and not inserting the dot.

Optimised solution : https://leetcode.com/problems/restore-ip-addresses/solution/
*/

class Solution {
    
    Set<String> ips = new HashSet<>();
    
    public boolean checkIfValidIP(String ip) {
        String[] quads = ip.split("\\.");
        for (String q : quads) {
            if (q.length() > 1 && q.charAt(0) == '0') return false;
            long num = Long.parseLong(q);
            //System.out.println(num);
            if (num < 0 || num > 255) return false;
        }
        return true;
    }
    
    public void generateIps(String s, StringBuilder sb, int index, int count) {
        if (index == 0 && count == 0) {
            sb.append(s.charAt(index));
            sb.reverse();
            //System.out.println(sb.toString());
            if (checkIfValidIP(sb.toString()))
                ips.add(sb.toString());
            return;
        }
        if (index < 0) return;
        
        sb.append(s.charAt(index));
        StringBuilder newSb = new StringBuilder(sb);
        newSb.append(".");
        generateIps(s, new StringBuilder(newSb), index - 1, count - 1);
        generateIps(s, new StringBuilder(sb), index - 1, count);
    }
    public List<String> restoreIpAddresses(String s) {
        generateIps(s, new StringBuilder(), s.length() - 1, 3);
        return new ArrayList<>(ips);
    }
}
