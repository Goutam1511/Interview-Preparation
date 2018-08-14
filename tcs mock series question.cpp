/*A program to print the pattern : 1 2 1 3 2 5 3 7 5 11 8 13 13 17 .....
Note : The series is a dual series where the odd terms are actually the next fibonacci number and the even terms are just prime numbers
Approach : The prime numbers upto a large number are first generated using sieve of eratosthenes and stored in queue.
A vector is initialized with first 4 indexes filled with 0,1,2,1.The queue is dequeued to remove the first prime 2 as it is already
pushed into the vector. Then the vector is iteratively filled with a loop running from 4 to n following the below algo :
If index is even then dequeue a prime number from the queue and push back into the vector
Else push back the sum of the last two fibonacci.
*/

#include <bits/stdc++.h>
using namespace std;

queue <int> q;

void sieve(int n){
    bool prime[n+1];
    memset(prime, true, sizeof(prime));

    for (int p=2; p*p<=n; p++)
    {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples of p
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }
    // Print all prime numbers
    for (int p=2; p<=n; p++)
       if (prime[p])
          q.push(p);
}

int main(){
    vector<int> v;
    int i,n;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    sieve(65000);
    q.pop();
    cout<<"Enter the number of terms you want :";
    cin>>n;
    for(i=4;i<=n;i++){
        if(i%2!=0){
            v.push_back(v[i-2]+v[i-4]);
        }
        else{
            v.push_back(q.front());
            q.pop();
        }
    }
    cout<<"The required series is :"<<endl;
    for(i=1;i<=n;i++){
        cout<<v[i]<<" ";
    }
}
