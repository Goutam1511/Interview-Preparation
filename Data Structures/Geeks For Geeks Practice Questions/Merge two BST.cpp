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

void preorder(node* r){
    if(r!=NULL){
        cout<<r->data<<" ";
        preorder(r->left);
        preorder(r->right);
    }
}

void postorder(node* r){
    if(r!=NULL){
        postorder(r->left);
        postorder(r->right);
        cout<<r->data<<" ";
    }
}

node* insertnode(node* r,int val){
    if(r==NULL){
        r=alloc(val);
        return r;
    }
    else if(r->data>val){
        r->left = insertnode(r->left,val);
    }
    else{
        r->right = insertnode(r->right,val);
    }
    return r;
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

node* mergebst(node* r1,node* r2){
    int n = countnodes(r1);
    int storein[n];
    int i=0;
    binarytoarray(storein,r1,&i);
    for(i=0;i<n;i++){
        r2 = insertnode(r2,storein[i]);
    }
    return r2;
}

int main(){
    node* root1 = NULL;
    node* root2 = NULL;
    node* result = NULL;
    int i;
    cout<<"-----Create 1st binary tree-------"<<endl;
    cout<<"Press 0 to exit in case no child to be inserted"<<endl;
    cin>>i;
    if(i){
        root1 = createtree(root1,i);
    }
    cout<<"Inorder of Inserted Binary Tree"<<endl;
    inorder(root1);
    binarytobst(root1);
    cout<<endl;
    cout<<"Inorder of Converted Binary Search Tree"<<endl;
    inorder(root1);
    cout<<endl;
    cout<<"-----Create 2nd binary tree-------"<<endl;
    cout<<"Press 0 to exit in case no child to be inserted"<<endl;
    cin>>i;
    if(i){
        root2 = createtree(root2,i);
    }
    cout<<"Inorder of Inserted Binary Tree"<<endl;
    inorder(root2);
    binarytobst(root2);
    cout<<endl;
    cout<<"Inorder of Converted Binary Search Tree"<<endl;
    inorder(root2);
    result = mergebst(root1,root2);
    cout<<endl;
    cout<<"Inorder of Merged BST :"<<endl;
    inorder(result);
    cout<<endl;
    cout<<"Preorder of Merged BST :"<<endl;
    preorder(result);
    cout<<endl;
    cout<<"Postorder of Merged BST :"<<endl;
    postorder(result);
    return 0;
}
