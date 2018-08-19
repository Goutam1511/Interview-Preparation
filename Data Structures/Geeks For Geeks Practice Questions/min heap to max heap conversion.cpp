/*
The simplest approach possible followed here is to take every element from Min heap and Insert it to another max heap.
However this is not time and space efficient.
A better approach would be to start from the bottommost and rightmost element of the heap and convert the min heap to max heap in place.
*/
#include<bits/stdc++.h>
using namespace std;

void swap(int *a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int heap[100];
int maxheap[100];
int heapsize=0;
int maxheapsize = 0;

int left(int i){
    return (2*i+1);
}

int right(int i){
    return (2*i+2);
}

int parent(int i){
    return i/2;
}

void buildminheap(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l<heapsize&&heap[l]<heap[smallest])
        smallest = l;
    if(r<heapsize&&heap[r]<heap[smallest])
        smallest = r;
    if(smallest!=i){
        swap(&heap[i],&heap[smallest]);
        buildminheap(smallest);
    }
}

void insertkey(int val){
    int i;
    heapsize++;
    if(heapsize>100){
        cout<<"Overflow"<<endl;
        return;
    }
    heap[heapsize-1]=val;
    i=heapsize-1;
    while(i!=0&&heap[parent(i)]>heap[i]){
        swap(&heap[parent(i)],&heap[i]);
        i=parent(i);
    }
}

void insertkeymax(int val){//Insert to another max heap
    int i;
    maxheapsize++;
    if(maxheapsize>100){
        cout<<"Overflow"<<endl;
        return;
    }
    maxheap[maxheapsize-1]=val;
    i=maxheapsize-1;
    while(i!=0&&maxheap[parent(i)]<maxheap[i]){
        swap(&maxheap[parent(i)],&maxheap[i]);
        i=parent(i);
    }
}


int extractmin(){
    int val = heap[0];
    swap(&heap[0],&heap[heapsize-1]);
    heapsize--;
    //cout<<"Returned val : "<<val<<endl;
    buildminheap(0);
    return val;
}

void converttomaxheap(){//Helper function to insert every element of min heap to max heap
    int k;
    while(heapsize){//While the min heap is not empty
        k = extractmin();//Extract the minimum from min heap
        //cout<<"Extracted min : "<<k<<endl;
        insertkeymax(k);//Insert the element into the max heap
        //cout<<"Inserted : "<<k<<endl;
    }
}

int main(){
long int i,n,k;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Insert into heap"<<endl;
    cout<<" 2. Convert to max heap "<<endl;
    cout<<" 0. exit"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Enter next choice : ";
        cin>>i;
        switch(i){
            case 0:
                break;
            case 1:
                cout<<" Enter a value to insert :";
                cin>>n;
                insertkey(n);
                cout<<"Present min heap : "<<endl;
                for(int j=0;j<heapsize;j++)
                    cout<<heap[j]<<" ";
                cout<<endl;
                break;
            case 2:
                converttomaxheap();
                cout<<"The max heap is "<<endl;
                for(int j=0;j<maxheapsize;j++)
                    cout<<maxheap[j]<<" ";
                cout<<endl;
                break;
        }
        if(i==0)
            break;
    }
    return 0;

}
