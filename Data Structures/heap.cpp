#include <bits/stdc++.h>
using namespace std;

void swap(int *a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int heap[100];
int heapsize=0;

int left(int i){
    return (2*i+1);
}

int right(int i){
    return (2*i+2);
}

int parent(int i){
    return i/2;
}

void buildheap(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l<heapsize&&heap[l]<heap[smallest])
        smallest = l;
    if(r<heapsize&&heap[r]<heap[smallest])
        smallest = r;
    if(smallest!=i){
        swap(&heap[i],&heap[smallest]);
        buildheap(smallest);
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

int extractmin(){
    int val = heap[0];
    swap(&heap[0],&heap[heapsize-1]);
    heapsize--;
    cout<<heapsize<<endl;
    buildheap(0);
    return val;
}

void decreasekey(int i,int val){
    heap[i] = val;
    while(i!=0&&heap[parent(i)]>heap[i]){
        swap(&heap[parent(i)],&heap[i]);
        i=parent(i);
    }
}

int main(){
long int i,n,k,j;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Insert into heap"<<endl;
    cout<<" 2. Extract the minimum value from heap "<<endl;
    cout<<" 3. Decrease a key in heap "<<endl;
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
                break;
            case 2:
                cout<<"The minimum value of the heap is "<<extractmin()<<endl;
                break;
            case 3:
                cout<<"Enter the value of the index whose key to be decreased and also the decreased key value :"<<endl;
                cin>>k>>n;
                decreasekey(k,n);
                break;
        }
        if(heapsize){
            cout<<"Present min heap is :"<<endl;
            for(j=0;j<heapsize;j++){
                cout<<heap[j]<<" ";
            }
            cout<<endl;
        }
        if(i==0)
            break;
    }
    return 0;

}
