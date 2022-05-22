//doubly linked-list ADT

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
}*first=NULL;

void create(int* arr, int num){
    first=(struct Node*)malloc(sizeof(struct Node));
    first->data=arr[0];
    first->prev=first->next=NULL;
    struct Node* last=first;
    
    for(int i=1;i<num;++i){
        struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
        temp->data=arr[i];
        temp->next=last->next;
        temp->prev=last;
        last->next=temp;
        last=temp;
    }
}

void display(struct Node* p){
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int count(struct Node* p){
    int length=0;
    while (p) {
        length++;
        p=p->next;
    }
    return length;
}

void insert(struct Node* p, int index,int num){
    if(index<0 || index>count(p)) return;
    
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=num;
    
    if(index==0){
        temp->prev=NULL;
        temp->next=first;
        first->prev=temp;
        first=temp;
    }
    else{
        for(int i=0;i<index-1;++i) p=p->next; //p到要插入的前一個
        temp->prev=p;
        temp->next=p->next;
        if(p->next) p->next->prev=temp;  //若要插入的位置非最後一個時(後面還有node)
        p->next=temp;
    }
}

void remove(struct Node* p, int index){
    if(index<0 || index>count(p)) return;
    
    if(index==0){
        first=first->next;
        if(first) first->prev=NULL;
    }
    else{
        for(int i=0;i<index;++i) p=p->next; //p移到要被刪掉的node
        p->prev->next=p->next;
        if(p->next) p->next->prev=p->prev;
    }
    printf("remove %d !\n",p->data);
    free(p);
}

void reverse(struct Node* p){
    while(p){
        struct Node* temp=p->next; //對每個p的prev和next做互換
        p->next=p->prev;
        p->prev=temp;
        
        p=p->prev;
        if(p && !(p->next)) first=p;  //p已到最後一個
    }
}

int main(){
    int A[]={10,20,30,40,50};
    create(A, 5);
    display(first);
    
    insert(first, 3, 7);
    display(first);
    insert(first, 0, 8);
    display(first);
    
    remove(first,0);
    display(first);
    remove(first,5);
    display(first);
        
    reverse(first);
    display(first);
    
    return 0;
}
