#include <bits/stdc++.h>
using namespace std;

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
}node;

node* alloc(int val){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->key = val;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

int getHeight(node* r){
    if(r==NULL)
        return 0;
    return r->height;
}

int getBalance(node* r){
    return getHeight(r->left)-getHeight(r->right);
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

void postorder(node* r){
    if(r!=NULL){
        postorder(r->left);
        postorder(r->right);
        cout<<r->key<<" ";
    }
}

node* findmin(node* r){
    if(r->left==NULL)
        return r;
    else{
        while(r->left!=NULL)
            r=r->left;
        return r;
    }
}

node* rightrotate(node* y){
    node* x = y->left;
    node* t = x->right;

    x->right = y;
    y->left = t;
    //Update Heights
    y->height = 1+max(getHeight(y->left),getHeight(y->right));
    x->height = 1+max(getHeight(x->left),getHeight(x->right));
    return x;
}

node* leftrotate(node* x){
    node* y = x->right;
    node* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1+max(getHeight(x->left),getHeight(x->right));
    y->height = 1+max(getHeight(y->left),getHeight(y->right));
    return y;
}

node* insertkey(node* r,int val){
    if(r==NULL){
        r=alloc(val);
        return r;
    }
    else if(r->key<val){
        r->right = insertkey(r->right,val);
    }
    else{
        r->left = insertkey(r->left,val);
    }
    r->height = 1+max(getHeight(r->left),getHeight(r->right));
    int balance = getBalance(r);
    if(balance>1&&val<r->left->key){
        return rightrotate(r);
    }
    if(balance<-1&&val>r->right->key){
        return leftrotate(r);
    }
    if(balance>1&&val>r->left->key){
        r->left = leftrotate(r->left);
        return rightrotate(r);
    }
    if(balance<-1&&val<r->right->key){
        r->right = rightrotate(r->right);
        return leftrotate(r);
    }
    return r;
}

node* deletekey(node* r,int val){
    if(r==NULL)
        return r;
    else if(r->key<val){
        r->right = deletekey(r->right,val);
    }
    else if(val<r->key){
        r->left = deletekey(r->left,val);
    }
    else{
        if((r->left==NULL)||(r->right==NULL)){
            node* temp = r->left? r->left : r->right;
            if(temp==NULL){
                temp = r;
                r = NULL;
            }
            else{
                r = temp;
            }
            free(temp);
        }
        else{
            node* temp = findmin(r->right);
            r->key = temp->key;
            r->right = deletekey(r->right,temp->key);
            free(temp);
        }
    }
    r->height = 1+max(getHeight(r->left),getHeight(r->right));
    int balance = getBalance(r);
    if(balance>1&&getBalance(r->left)>=0){
        return rightrotate(r);
    }
    if(balance<-1&&getBalance(r->right)>=0){
        return leftrotate(r);
    }
    if(balance>1&&getBalance(r->left)<0){
        r->left = leftrotate(r->left);
        return rightrotate(r);
    }
    if(balance<-1&&getBalance(r->right)<0){
        r->right = rightrotate(r->right);
        return leftrotate(r);
    }
    return r;
}

int main(){//Insertion, Deletion and Traversal of a AVL Tree
    node* root=NULL;
    long int i,n,k;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Insert "<<endl;
    cout<<" 2. Deletion "<<endl;
    cout<<" 3. Traversal "<<endl;
    cout<<" 4. Find Height "<<endl;
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
                root = insertkey(root,n);
                break;
            case 2:
                cout<<" Enter a value to delete :";
                cin>>n;
                root = deletekey(root,n);
                break;
            case 3:
                inorder(root);
                cout<<endl;
                preorder(root);
                cout<<endl;
                postorder(root);
                cout<<endl;
                break;
            case 4:
                cout<<"The required height is "<<getHeight(root)<<endl;
                break;
        }
        if(i==0)
            break;
    }
    return 0;
}
