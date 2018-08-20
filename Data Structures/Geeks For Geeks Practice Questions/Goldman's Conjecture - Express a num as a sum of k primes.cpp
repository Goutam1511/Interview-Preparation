/*
The famous Goldman's conjencture says any number n can be expressed as a sum of k prime numbers iff -
1. The number n = 2k and k = 1 then the number n itself must be a prime number
2. The number n >= 2k and k = 2 then if n is even then n can always be expressed as sum of 2 primes
else the number n-2 must be prime as n = 2 + (n-2)
3. If n>=2k and k>=3 then n can always be expressed as sum of k primes.
*/
#include <bits/stdc++.h>
using namespace std;

bool isprime(long int n){
    long int i=2;
    for(i=2;i*i<=n;i++)
        if(n%i==0)
        return false;
    return true;
}

bool ispossible(long int n,long int k){
    if(n<2*k)//If n<2k never possible
        return false;
    if(k==1)//if k = 1 and n>=2k then n itself must be prime
        return isprime(n);
    if(k==2){
        if(n%2==0)//if n is even and k = 2 always possible by Goldman's Conjecture
            return true;
        return isprime(n-2);//Else if n is odd and k = 2 then n-2 must be prime as one number must be 2.
    }
    return true;//For n>=2k and k>=3 n can always be expressed as sum of k primes
}

int main(){
    long int i,k,n;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Check if a given number can be expressed as a sum of k primes "<<endl;
    cout<<" 0. exit"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Enter next choice : ";
        cin>>i;
        switch(i){
            case 0:
                break;
            case 1:
                cout<<"Enter the value of k : "<<endl;
                cin>>k;
                cout<<"Enter a number to check if it can be expressed as sum of k primes :";
                cin>>n;
                if(ispossible(n,k))
                    cout<<"YES possible"<<endl;
                else
                    cout<<"NOT possible"<<endl;
                break;
        }
        if(i==0)
            break;
    }
    return 0;
}
