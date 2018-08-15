#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

typedef struct Node{//Structure of node
    long int data;
    struct Node* next;
} node;

node* alloc(long int val){//Allocate new node
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = val;
    newnode->next = NULL;
    return newnode;
}

void traverse(node* head){//Traverse and print the whole list
    if(head==NULL){
        cout<<"No nodes present"<<endl;
    }
    else{
        node* current = head;
        cout<<"Current list"<<endl;
        while(current!=NULL){
            cout<<current->data<<"->";
            current=current->next;
        }
        cout<<"NULL"<<endl;
    }
}

node* insertend(node* head,long int val){//Insert at end
    node* current=head;
    if(head==NULL){//If there is no node
        head=alloc(val);
        return head;
    }
    else{
        while(current->next!=NULL)//Traverse to end of list
            current=current->next;
        current->next=alloc(val);//Link new node at end
    }
    return head;
}

node* findend(node* head){
    node* current = head;
    if(head==NULL){
        cout<<"No nodes present"<<endl;
    }
    else{
        while(current->next!=NULL){
            current=current->next;
        }
    }
    return current;
}

node* findnode(node* head,int n){
    int i=1;
    node* current = head;
    while(i<n&&current!=NULL){
        current = current->next;
        i++;
    }
    if(current!=NULL)
        return current;
    else{
     cout<<"Underflow - no of nodes required is not present. Loop creation unsuccessful"<<endl;
     return current;
    }
}

void makeloop(node* head,int n){
    node* endlist = findend(head);
    if(endlist!=NULL){
        //cout<<"End found with node : "<<endlist->data<<endl;
        node* loopnode = findnode(head,n);
        //cout<<"Loop node : "<<loopnode->data<<endl;
        endlist->next = loopnode;
    }
}

void detectloop(node* head){
    node* fastptr = head;
    node* slowptr = head;
    while(fastptr&&slowptr&&fastptr->next){
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
        if(slowptr == fastptr){
            cout<<"Loop Detected"<<endl;
            return;
        }
    }
    cout<<"No loop present"<<endl;
}

int main(){
    cout<<"--------Create a linked list of at least 5 nodes and then create a loop with the last node pointing to the nth node-----------"<<endl;
    cout<<" 1. Insert at end "<<endl;
    cout<<" 2. Loop the List"<<endl;
    cout<<" 3. Detect presence of loop"<<endl;
    cout<<" 0. exit"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    int i,n;
    node* head = NULL;
    while(true){
        cout<<"Enter next choice : ";
        cin>>i;
        switch(i){
            case 0:
                break;
            case 1:
                cout<<" Enter a value to insert at end :";
                cin>>n;
                head = insertend(head,n);
                traverse(head);
                break;
            case 2:
                cout<<" Enter the node number where loop is to be made :";
                cin>>n;
                makeloop(head,n);
                break;
            case 3:
                detectloop(head);
                break;
        }
        if(i==0)
            break;
    }
return 0;
}
