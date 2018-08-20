#include <bits/stdc++.h>
using namespace std;

long int* halfsort(long int arr[],long int n){
    sort(arr,arr+n);
    long int i,j=n-1;
    long int* p = (long int*)malloc(n*sizeof(long int));
    for(i=0;i<n/2;i++){
        p[i] = arr[i];
    }
    for(i=n/2;i<n;i++){
        p[i] = arr[j];
        j--;
    }
    return p;
}

int main(){
    long int i,k,n;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Sort an array with first half in ascending order and the second half in descending order"<<endl;
    cout<<" 0. exit"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Enter next choice : ";
        cin>>i;
        switch(i){
            case 0:
                break;
            case 1:
                cout<<"Enter the size of array : "<<endl;
                cin>>n;
                long int arr[n];
                cout<<"Enter the numbers of the array :"<<endl;
                for(k=0;k<n;k++)
                    cin>>arr[k];
                long int* res = halfsort(arr,n);
                cout<<"The resultant array after the required sort is :"<<endl;
                for(k=0;k<n;k++)
                    cout<<res[k]<<" ";
                cout<<endl;
                free(res);
                break;
        }
        if(i==0)
            break;
    }
    return 0;
}
