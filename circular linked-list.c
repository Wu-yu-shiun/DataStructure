//circular linked-list ADT

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


struct Node{
    int data;
    struct Node* next;
}*head;     //create a global Node* "head"

int count(struct Node* p){
    int length=0;
    do {
        length++;
        p=p->next;
    }while(p!=head);   //第一次即是head，用do while先做一次，跳過第一次的p是head
    return length;
}

void create(int* arr, int num){

    head=(struct Node*)malloc(sizeof(struct Node));
    head->data=arr[0];
    head->next=head;
    struct Node* last=head;
    
    for(int i=1;i<num;++i){
        struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
        temp->data=arr[i];
        temp->next=last->next;
        last->next=temp;
        last=temp;
    }
}

void display(struct Node* p){
    do{
        printf("%d ",p->data);
        p=p->next;
    }while(p!=head);
    printf("\n");
    
}
void display_r(struct Node* p){
    static bool move=false;
    if(p!=head || move==false){
        move=true;
        printf("%d ",p->data);
        display_r(p->next);
    }
}

void insert(struct Node* p, int index,int num){
    if(index<0 || index>count(p)) return;
    
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=num;
    if(index==0){
        if(head){
            while(p->next!=head) p=p->next;
            p->next=temp;
            temp->next=head;
            head=temp;
        }
        else{
            head=temp;
            head->next=head;
        }
        
    }
    else{
        for(int i=0;i<index-1;++i) p=p->next; //p到要插入的前一個
        temp->next=p->next;
        p->next=temp;
    }
}

void remove(struct Node* p, int index){
    if(index<0 || index>count(p)) return;
    
    if(index==0){
        printf("remove %d !\n",head->data);
        while(p->next!=head) p=p->next; //p到最後一個元素
        if(head==p){  //原本就只有一個元素
            free(head);
            head=NULL;
        }
        else{
            p->next=head->next;
            free(head);
            head=p->next;
        }
    }
    else{
        for(int i=0;i<index-1;++i) p=p->next;  //p到要刪除的前一個
        struct Node* temp=p->next;  //temp為要刪的元素
        p->next=temp->next;
        printf("remove %d !\n",temp->data);
        free(temp);
    }
}

int main(){

    int A[]={2,3,4,5,6};
    create(A, 5);
    
    display(head);
    display_r(head);
    cout<<endl;
    
    insert(head, 4, 10);
    display(head);
    insert(head, 0, 1);
    display(head);
    
    remove(head,5);
    display(head);
    remove(head,0);
    display(head);
    
    return 0;
}
