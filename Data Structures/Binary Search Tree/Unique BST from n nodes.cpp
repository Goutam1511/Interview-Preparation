/*
Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

Solution : Check out https://www.geeksforgeeks.org/total-number-of-possible-binary-search-trees-with-n-keys/
On a simpler note, the number of structurally unique BST possible with n nodes is : Catalan number(Cn) = (2n!)/((n + 1)! * n!).
While the number of structurally unique Binary Trees that can be possible with n nodes is : Catalan number(Cn) * n! = (2n!)/(n + 1)!.
*/

class Solution {
public:
    // A function to find factorial of a given number 
    long int factorial(int n) 
    { 
        unsigned long int res = 1; 

        // Calculate value of [1*(2)*---*(n-k+1)] / [k*(k-1)*---*1] 
        for (int i = 1; i <= n; ++i) 
        { 
            res *= i; 
        } 

        return res; 
    } 

    long int binomialCoeff(int n, int k) 
    { 
        unsigned long int res = 1; 

        // Since C(n, k) = C(n, n-k) 
        if (k > n - k) 
            k = n - k; 

        // Calculate value of [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1] 
        for (int i = 0; i < k; ++i) 
        { 
            res *= (n - i); 
            res /= (i + 1); 
        } 

        return res; 
    } 

    // A Binomial coefficient based function to find nth catalan 
    // number in O(n) time 
    long int catalan(int n) 
    { 
        // Calculate value of 2nCn 
        unsigned long int c = binomialCoeff(2*n, n); 

        // return 2nCn/(n+1) 
        return c/(n+1); 
    } 

    // A function to count number of BST with n nodes 
    // using catalan 
    long int countBST(int n) 
    { 
        // find nth catalan number 
        unsigned long int count = catalan(n); 

        // return nth catalan number 
        return count; 
    } 

    int numTrees(int n) {
        return countBST(n);
    }
};
