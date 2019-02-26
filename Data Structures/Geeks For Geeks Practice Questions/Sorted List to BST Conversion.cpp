#include <bits/stdc++.h>
using namespace std;

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
}node;

typedef struct Block{
    int data;
    struct Block* next;
}block;

node* allocnode(int val){
    node* r = (node*)malloc(sizeof(node));
    r->left = NULL;
    r->right = NULL;
    r->key = val;
    return r;
}

block* allocblock(int val){
    block* newnode = (block*)malloc(sizeof(block));
    newnode->data = val;
    newnode->next = NULL;
    return newnode;
}

block* push(block* h,int val){
    if(h==NULL){
        h = allocblock(val);
    }
    else{
        block* b = allocblock(val);
        b->next = h;
        h = b;
    }
    return h;
}

void inorder(node* r){
    if(r!=NULL){
        inorder(r->left);
        cout<<r->key<<" ";
        inorder(r->right);
    }
}

void preorder(node* r){
    if(r!=NULL){
        cout<<r->key<<" ";
        preorder(r->left);
        preorder(r->right);
    }
}

void traverse(block* head){//Traverse and print the whole list
    if(head==NULL){
        cout<<"No nodes present"<<endl;
    }
    else{
        block* current = head;
        cout<<"Current list"<<endl;
        while(current!=NULL){
            cout<<current->data<<"->";
            current=current->next;
        }
        cout<<"NULL"<<endl;
    }
}


void postorder(node* r){
    if(r!=NULL){
        postorder(r->left);
        postorder(r->right);
        cout<<r->key<<" ";
    }
}

int countnodes(block* start,block* endlist){
    int i=0;
    block* ptr=start;
    while(ptr!=endlist){
        ptr=ptr->next;
        i++;
    }
    return i;
}

block* findmiddle(block* start,int n){
    block* ptr=start;
    int i=0;
    while(i<n){
        ptr=ptr->next;
        i++;
    }
    return ptr;
}

/*

Recursively build the BST by allocating the middle element as root and then going on building the BST by splitting the 
list into two. The smaller elements in left of list will be the left subtree and the bigger will be the right.

*/

node* convertlisttotree(block* start,block* endlist){
    int i;
    if(start!=endlist&&start->next!=endlist){
        i = countnodes(start,endlist);
        block* middle = findmiddle(start,i/2);
        node* r = allocnode(middle->data);
        r->left = convertlisttotree(start,middle);
        r->right = convertlisttotree(middle->next,endlist);
        return r;
    }
    else{
        node* r = allocnode(start->data);
        return r;
    }
}

int main(){//Conversion of a sorted linked list to a BST (Somehow works only for Odd number of nodes)
    node* root=NULL;
    block* head=NULL;
    long int i,n,k;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Insert a number "<<endl;
    cout<<" 3. Traversal of the BST "<<endl;
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
                head = push(head,n);
                traverse(head);
                break;
            case 2:
                root = convertlisttotree(head,NULL);
                inorder(root);
                cout<<endl;
                preorder(root);
                cout<<endl;
                postorder(root);
                cout<<endl;
                break;
        }
        if(i==0)
            break;
    }
    return 0;
}
