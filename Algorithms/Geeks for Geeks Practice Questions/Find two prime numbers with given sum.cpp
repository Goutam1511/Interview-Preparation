/*
Given an even number (greater than 2 ), print two prime numbers whose sum will be equal to given number.
There may be several combinations possible. Print only first such pair.
An interesting point is, a solution always exist according to Goldbach’s conjecture.

Examples :

Input: n = 74
Output: 3 71

Input : n = 1024
Output: 3 1021

Input: n = 66
Output: 5 61

Input: n = 9990
Output: 17 9973

Solution : The idea is to find all the primes less than or equal to the given number N using Sieve of Eratosthenes.
Once we have an array that tells all primes, we can traverse through this array to find pair with given sum.
*/

// C++ program to find a prime number pair whose 
// sum is equal to given number 
// C++ program to print super primes less than 
// or equal to n. 
#include<bits/stdc++.h> 
using namespace std; 

// Generate all prime numbers less than n. 
bool SieveOfEratosthenes(int n, bool isPrime[]) 
{ 
	// Initialize all entries of boolean array 
	// as true. A value in isPrime[i] will finally 
	// be false if i is Not a prime, else true 
	// bool isPrime[n+1]; 
	isPrime[0] = isPrime[1] = false; 
	for (int i=2; i<=n; i++) 
		isPrime[i] = true; 

	for (int p=2; p*p<=n; p++) 
	{ 
		// If isPrime[p] is not changed, then it is 
		// a prime 
		if (isPrime[p] == true) 
		{ 
			// Update all multiples of p 
			for (int i=p*p; i<=n; i += p) 
				isPrime[i] = false; 
		} 
	} 
} 

// Prints a prime pair with given sum 
void findPrimePair(int n) 
{ 
	// Generating primes using Sieve 
	bool isPrime[n+1]; 
	SieveOfEratosthenes(n, isPrime); 

	// Traversing all numbers to find first 
	// pair 
	for (int i=0; i<n; i++) 
	{ 
		if (isPrime[i] && isPrime[n-i]) 
		{ 
			cout << i << " " << (n-i); 
			return; 
		} 
	} 
} 

// Driven program 
int main() 
{ 
	int n = 74; 
	findPrimePair(n); 
	return 0; 
} 
