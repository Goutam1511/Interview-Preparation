/*An element is leader if it is greater than all the elements to its right side.
And the rightmost element is always a leader.
For example in the array {16, 17, 4, 3, 5, 2}, leaders are 17, 5 and 2. */

#include <bits/stdc++.h>
using namespace std;

void leaders(long int arr[],long int n){
    set<long int> s;
    long int track[n];
    long int i,j;
    s.insert(arr[n-1]);
    track[n-1]=arr[n-1];
    for(i=n-2;i>=0;i--){
        j=track[i+1]>arr[i]?track[i+1]:arr[i];
        track[i] = j;
    }
    for(i=0;i<n;i++){
        s.insert(track[i]);
    }
    cout<<"The leaders in the array are : "<<endl;
    for (std::set<long int>::iterator it=s.begin(); it!=s.end(); ++it)
    std::cout << ' ' << *it;
    std::cout << '\n';

}

int main(){
    long int n,i,j;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"Enter any number other than 0 to find the leaders of an array"<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<"Enter your choice : ";
    cin>>j;
    while(j){
        cout<<"Enter the size of the array : ";
        cin>>n;
        long int arr[n];
        cout<<"Enter the elements of the array"<<endl;
        for(i=0;i<n;i++)
            cin>>arr[i];
        leaders(arr,n);
        cout<<"Enter your choice : ";
        cin>>j;
    }
}
