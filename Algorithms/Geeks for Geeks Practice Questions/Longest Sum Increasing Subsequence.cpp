/*
This problem is a variation of standard Longest Increasing Subsequence (LIS) problem.
We need a slight change in the Dynamic Programming solution of LIS problem.
All we need to change is to use sum as a criteria instead of length of increasing subsequence.
Also in order to find out elements of the longest sum increasing subsequence we are going to store the indexes of the array
while finding out the subsequence. For that we are needing a vector of pair. Also a stack is used to store the indexes while backtracking the
lsis vector and finally the stack is popped out to print the indexed of lsis in sequential order.
*/

#include <bits/stdc++.h>
using namespace std;

void lsis(long int arr[],long int n){
    vector < pair<long int,long int> > res;
    long int i,j;
    for(i=0;i<n;i++){
        res.push_back(make_pair(arr[i],-1));
    }
    for(i=1;i<n;i++){
        for(j=0;j<i;j++){
            if(arr[i]>arr[j]&&res[i].first<(res[j].first+arr[i])){
                res[i].first = res[j].first+arr[i];
                res[i].second = j;
            }
        }
    }
    long int maxm = INT_MIN,index=-1;
    for(i=0;i<n;i++){
        if(res[i].first>maxm){
            maxm = res[i].first;
            index = i;
        }
    }
    stack<long int> track;
    track.push(index);
    while(res[index].second!=-1){
        track.push(res[index].second);
        index = res[index].second;
    }
    cout<<"The maximum sum increasing subsequence is : "<<maxm<<endl;
    cout<<"The contributing indices are : "<<endl;
    while(!track.empty()){
        cout<<track.top()<<" ";
        track.pop();
    }
    cout<<endl;
}

int main(){
    long int n,i,j;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"Enter any number other than 0 to find the longest sum increasing subsequence of an array"<<endl;
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
        lsis(arr,n);
        cout<<"Enter your choice : ";
        cin>>j;
    }
}
