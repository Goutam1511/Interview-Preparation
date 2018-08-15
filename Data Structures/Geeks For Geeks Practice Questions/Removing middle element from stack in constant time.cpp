/*The idea is to implement the stack using Doubly Linked List so as to perform the deletion in  constant time as using linked list removing an item from middle takes constant time compared to array.*/
#include <bits/stdc++.h>
using namespace std;

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}node;

node* alloc(int val){//Allocate node for Doubly Linked List
    node* newnode = (node*)malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->data = val;
    return newnode;
}

node* push(node* head,int val){//Push in to the front of list
    if(head == NULL){//Handle case for first insertion
        node* newnode = alloc(val);
        head = newnode;
    }
    else{//Push into the front and readjust head after pointing previous of head to newnode
        node* newnode = alloc(val);
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    return head;
}

void traverse(node* head){//Traverse the list until NULL
    node* current = head;
    if(head==NULL){//If no node present
        cout<<"Underflow - no nodes present"<<endl;
        return;
    }
    cout<<"The current stack is "<<endl;
    while(current!=NULL){//While not NULL traverse the list
        cout<<current->data<<" ";
        current = current->next;
    }
    cout<<endl;
}

node* findmiddle(node* head){//Find the middle node using hare and tortoise pointer approach
    node* fastptr = head;
    node* slowptr = head;
    while(fastptr!=NULL&&fastptr->next!=NULL){//Jump the fast pointer by 2 while move the slow pointer by 1
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
    }
    return slowptr;
}

void removemiddle(node* head){
    if(head==NULL||head->next==NULL){//For 1 or no nodes write underflow
        cout<<"Underflow - Number of nodes is less than required"<<endl;
    }
    else if(head->next->next==NULL){//For two nodes in the stack free the second and readjust head
        node* temp = head->next;
        head->next = NULL;
        free(temp);
    }
    else{//Find the middle node and delete it
        node* middle = findmiddle(head);
        node* prevptr = middle->prev;
        node* nextptr = middle->next;
        prevptr->next = nextptr;
        nextptr->prev = prevptr;
        free(middle);
    }
}

int main(){
    node* head=NULL;
    long int i,n,k;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Insert into stack "<<endl;
    cout<<" 2. Delete from stack "<<endl;
    cout<<" 0. exit"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Enter next choice : ";
        cin>>i;
        switch(i){
            case 0:
                break;
            case 1:
                cout<<" Enter a value to push into stack : ";
                cin>>n;
                head = push(head,n);
                traverse(head);
                break;
            case 2:
                removemiddle(head);
                traverse(head);
                break;
            default:
                cout<<"Enter a valid choice"<<endl;
        }
        if(i==0)
            break;
    }
return 0;
}

