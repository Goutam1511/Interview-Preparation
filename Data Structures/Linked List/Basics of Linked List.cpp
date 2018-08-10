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

node* insertbeg(node* head,long int val){//Insert at beginning
    node* newnode = alloc(val);
    newnode->next = head;
    head = newnode;
    return head;
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

bool insertafterkthnode(node* head,long int k,long int val){//Insert after Kth Node
    long int cnt=0;
    node* current = head;
    if(head==NULL){//If there is no node
        cout<<"Underflow"<<endl;
        return false;
    }
    while(cnt<k&&current!=NULL){
        cnt++;
        current=current->next;
    }
    if(current==NULL){//If no of nodes less than given k
        cout<<"Number of nodes lesser than given k="<<k<<" -Underflow"<<endl;
        return false;
    }
    else{
        node* temp=current->next;//Store next node
        node* newnode=alloc(val);
        newnode->next=temp;//Link the next of new node to next of current
        current->next=newnode;//Link the next of kth node to newnode
        return true;
    }
}

bool insertbeforekthnode(node* head,long int k,long int val){//Insert before Kth Node
    long int cnt=0;
    node* current = head;
    node* preptr=head;//Store previous node pointer
    if(head==NULL){
        cout<<"Underflow"<<endl;
        return false;
    }
    while(cnt<k&&current!=NULL){
        cnt++;
        preptr=current;//Store previous node
        current=current->next;
    }
    if(current==NULL){//If no of nodes is less than k
        cout<<"Number of nodes lesser than given k="<<k<<" -Underflow"<<endl;
        return false;
    }
    else{
        node* newnode=alloc(val);
        newnode->next=current;//Link next of newnode to kth node
        preptr->next=newnode;//Link next of previous of kth node to newnode
        return true;
    }
}

node* deletefrombeg(node* head){//Delete from Beginning
    if(head==NULL){//Base Underflow case
        cout<<"Underflow"<<endl;
        return head;
    }
    else{
        node* temp = head;//Store first node
        head = head->next;//Move ahead the head
        free(temp);//Free the first node
        return head;
    }
}

node* deletefromend(node* head){//Delete from end
    if(head==NULL){//Base underflow case
        cout<<"Underflow"<<endl;
    }
    else if(head->next==NULL){//If there is only one node
        head = NULL;
    }
    else{
        node* current = head;
        node* preptr = head;//Pointer for Previous node
        while(current->next!=NULL){//Traverse till end of list
            preptr=current;//Store the previous node
            current=current->next;//Move on to next
        }
        node* temp=current;
        preptr->next=NULL;//Jump the link from previous to NULL
        free(temp);//Free the last node
    }
    return head;
}

bool deletekthnode(node* head,long int k){//Insert after Kth Node
    long int cnt=0;
    node* current = head;
    node* preptr = head;//Pointer for previous
    if(head==NULL){//Handle the base underflow case
        cout<<"Underflow"<<endl;
        return false;
    }
    while(cnt<k&&current!=NULL){
        cnt++;
        preptr=current;
        current=current->next;
    }
    if(current==NULL){//handle the case if nodes are lesser than k
        cout<<"Number of nodes lesser than given k="<<k<<" -Underflow"<<endl;
        return false;
    }
    else{
        node* temp=current->next;//Store the next node
        preptr->next=temp;//Jump the link of previous to next node
        free(current);//Free the current
        return true;
    }
}

node* reverselist(node* head){//Reverse the list
    node* prev=NULL;
    node* next=NULL;
    node* current=head;
    while(current!=NULL){
        next=current->next;//Store the next node
        current->next=prev;//Change the next node of current to previous
        prev=current;//Change the previous to current
        current=next;//Move on to the next node
    }
    return prev;
}

int main(){//Insertion, Deletion and Reversal of a Linked List
    node* head=NULL;
    long int i,n,k;
    cout<<"-------- Choose any number from the below sequence -------------"<<endl;
    cout<<" 1. Insert at beginning "<<endl;
    cout<<" 2. Insert at end "<<endl;
    cout<<" 3. Insert after kth node "<<endl;
    cout<<" 4. Insert before kth node "<<endl;
    cout<<" 5. Delete from beginning "<<endl;
    cout<<" 6. Delete from end "<<endl;
    cout<<" 7. Delete kth node "<<endl;
    cout<<" 8. Reverse the List"<<endl;
    cout<<" 0. exit"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    while(true){
        cout<<"Enter next choice : ";
        cin>>i;
        switch(i){
            case 0:
                break;
            case 1:
                cout<<" Enter a value to insert at beginning :";
                cin>>n;
                head = insertbeg(head,n);
                traverse(head);
                break;
            case 2:
                cout<<" Enter a value to insert at end :";
                cin>>n;
                head = insertend(head,n);
                traverse(head);
                break;
            case 3:
                cout<<" Enter a value of k and the value to be inserted :"<<endl;
                cin>>k>>n;
                if(insertafterkthnode(head,k,n))
                    traverse(head);
                else
                    cout<<"Insert unsuccessful"<<endl;
                break;
            case 4:
                cout<<" Enter a value of k and the value to be inserted :"<<endl;
                cin>>k>>n;
                if(insertbeforekthnode(head,k,n))
                    traverse(head);
                else
                    cout<<"Insertion unsuccessful"<<endl;
                break;
            case 5:
                head = deletefrombeg(head);
                traverse(head);
                break;
            case 6:
                head=deletefromend(head);
                traverse(head);
                break;
            case 7:
                cout<<"Enter the value of k :";
                cin>>k;
                if(deletekthnode(head,k))
                    traverse(head);
                else
                    cout<<"Deletion Unsuccessful"<<endl;
                break;
            case 8:
                head = reverselist(head);
                traverse(head);
        }
        if(i==0)
            break;
    }
    return 0;
}
