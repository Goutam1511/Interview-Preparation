/*
    The solution is a 3-step solution that does the following -
    1. First stores the BST traversing in-order wise in an array.
    2. Sorts the array.
    3. Copies the sorted array back to BST in-order wise.
    The logic is that copying the sorted array while traversing in-orderwise will automatically form the BST 
     as in-order traversal of a BST is always a sorted array.
*/
#include <bits/stdc++.h>
using namespace std;

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}node;

node* alloc(int k){
    node* r = (node*)malloc(sizeof(node));
    r->data = k;
    r->left = NULL;
    r->right = NULL;
    return r;
}

node* createtree(node* r,int n){
    if(n==0)
        return r;
    else{
        int i;
        r = alloc(n);
        cout<<"Enter left child of "<<n<<" :"<<endl;
        cin>>i;
        r->left = createtree(r->left,i);
        cout<<"Enter right child of "<<n<<" :"<<endl;
        cin>>i;
        r->right = createtree(r->right,i);
        return r;
    }
}

int countnodes(node* r){
    if(r==NULL)
        return 0;
    else
        return countnodes(r->left)+countnodes(r->right)+1;
}

void inorder(node* r){
    if(r!=NULL){
        inorder(r->left);
        cout<<r->data<<" ";
        inorder(r->right);
    }
}

void binarytoarray(int *arr,node* r,int* index){
    if(r==NULL)
        return;
    binarytoarray(arr,r->left,index);
    arr[*index]=r->data;
    (*index)++;
    binarytoarray(arr,r->right,index);
}

void arraytobst(int *arr,node* r,int* index){
    if(r==NULL)
        return;
    arraytobst(arr,r->left,index);
    r->data = arr[*index];
    (*index)++;
    arraytobst(arr,r->right,index);
}

void binarytobst(node* r){
    int n = countnodes(r);
    int storein[n];
    int i=0;
    binarytoarray(storein,r,&i);
    sort(storein,storein+n);
    i=0;
    arraytobst(storein,r,&i);
}

int main(){
    node* root = NULL;
    int i;
    cout<<"-----Create a binary tree-------"<<endl;
    cout<<"Press 0 to exit in case no child to be inserted"<<endl;
    cin>>i;
    if(i){
        root = createtree(root,i);
    }
    cout<<"Inorder of Inserted Binary Tree"<<endl;
    inorder(root);
    binarytobst(root);
    cout<<endl;
    cout<<"Inorder of Converted Binary Search Tree"<<endl;
    inorder(root);
    return 0;
}


