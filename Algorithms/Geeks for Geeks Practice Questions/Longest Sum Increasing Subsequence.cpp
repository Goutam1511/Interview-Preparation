/*
Given an array of n positive integers. Write a program to find the sum of maximum sum subsequence of the given array such that the integers in the subsequence are 
sorted in increasing order. For example, if input is {1, 101, 2, 3, 100, 4, 5}, then output should be 106 (1 + 2 + 3 + 100), if the input array is {3, 4, 5, 10},
then output should be 22 (3 + 4 + 5 + 10) and if the input array is {10, 5, 4, 3}, then output should be 10.

Solution Approach : Check https://www.youtube.com/watch?v=99ssGWhLPUE. This problem is a variation of standard Longest Increasing Subsequence (LIS) problem.
We need a slight change in the Dynamic Programming solution of LIS problem. All we need to change is to use sum as a criteria instead of length of increasing subsequence.
Also in order to find out elements of the longest sum increasing subsequence we are going to store the indexes of the array while finding out the subsequence. 
For that we are needing a vector of pair. Also a stack is used to store the indexes while backtracking the lsis vector and finally the stack is popped out to print the
indexed of lsis in sequential order.

Time Complexity : O(n^2)
Space Complexity : O(n)
*/

#include <bits/stdc++.h>
using namespace std;

void lsis(long int arr[],long int n){
    vector < pair<long int,long int> > res;
    long int i,j;
    /* We initialize the sums as array value itself as that is the minimum sum possible considering only value at arr[i]. *
     * Also there is no previous element to backtrack as sum is made from only that element, so -1 in index part of pair. */
    for(i=0;i<n;i++){
        res.push_back(make_pair(arr[i],-1));
    }
    
    /* For each element, we check from start of array till that point, if the sum of any element at j and the current element at i in consideration, is        *
     * greater than the sum at current place, we update the sum at current place i.e. res[i].first. We also update the index (res[i].second) for backtracking. */
    for(i=1;i<n;i++){
        for(j=0;j<i;j++){
            if(arr[i]>arr[j]&&res[i].first<(res[j].first+arr[i])){
                res[i].first = res[j].first+arr[i];
                res[i].second = j;
            }
        }
    }
    //Find the maximum sum and its index of occurance.
    long int maxm = INT_MIN,index=-1;
    for(i=0;i<n;i++){
        if(res[i].first>maxm){
            maxm = res[i].first;
            index = i;
        }
    }
    //Go on pushing the indexes through which the maximum sum is formed in a stack for easy backtracking
    stack<long int> track;
    track.push(index);
    while(res[index].second!=-1){
        track.push(res[index].second);
        index = res[index].second;
    }
    cout<<"The maximum sum increasing subsequence is : "<<maxm<<endl;
    cout<<"The contributing indices are : "<<endl;
    //Backtrack and print the sequence by popping the indexes from stack
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
