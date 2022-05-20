//linked-list ADT

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Node{
    int data;
    struct Node* next;
}*first=NULL;     //create a global Node* "first"


void create(int* arr, int size){
    struct Node* p,* last;
    
    //init linked-list head
    first=(struct Node*)malloc(sizeof(struct Node));
    first->data=arr[0];
    first->next=NULL;
    last=first;
    
    //connect others
    for(int i=1;i<size;++i){
        
        //先用一個暫時的p串上新的內容
        p=(struct Node*)malloc(sizeof(struct Node));
        p->data=arr[i];
        p->next=NULL;
        
        last->next=p; //將現在最後一個Node的next指向"p指向的新Node"
        last=p; //p這個位址指向的Node變成新的last
    }
}

void display(struct Node* p){
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
void display_r(struct Node* p){
    if(p==NULL) return;
    
    display_r(p->next);
    printf("%d ",p->data); //先進入下個遞迴，returning phase才印，結果會倒過來
}

int count(struct Node* p){
    int length=0;
    while (p) {
        length++;
        p=p->next;
    }
    return length;
}
int count_r(struct Node* p){
    if(p) return count_r(p->next)+1;
    else return 0;
}


int sum(struct Node* p){
    int sum=0;
    while (p) {
        sum+=p->data;
        p=p->next;
    }
    return sum;
}
int sum_r(struct Node* p){
    if(p) return sum_r(p->next)+p->data;
    else return 0;
}

int max(struct Node* p){ //由第一個向後比
    int maxNum=INT_MIN;
    while(p){
        if(p->data>maxNum) maxNum=p->data;
        p=p->next;
    }
    return maxNum;
}
int max_r(struct Node* p){ //由最後一個向前比
    if(p){
        int x=max_r(p->next);
        return x>p->data?x:p->data;
    }
    else return INT_MIN;
}

Node* search(struct Node* p, int key){ //linear search
    struct Node* last=NULL; //linear search improvement: move to head, use "last" to record last Node
    while(p){
        if(p->data==key){
            last->next=p->next;
            p->next=first;
            first=p;
            return p;
        }
        last=p;
        p=p->next;
    }
    return NULL;
}
Node* search_r(struct Node* p, int key){
    if(!p) return NULL;
    else if(p->data==key) return p;
    else return search_r(p->next, key);
}

void insert(struct Node* p,int index,int num){
    if(index<0 || index>count(p)) return;
    
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=num;
    
    if(index==0){
        temp->next=first;
        first=temp;
    }
    else{
        for(int i=0;i<index-1;++i) p=p->next; //p跑到要被插入的前一個
        temp->next=p->next;
        p->next=temp;
    }
}

void sortedInsert(struct Node* p, int num){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node)),* last=NULL;
    temp->data=num;
    temp->next=NULL;
    
    if(first==NULL) first=temp; //case1:空linked list
    else{
        while(p && p->data<num){ //p跑到要被插入的後一個,用q紀錄last的前一個
            last=p;
            p=p->next;
        }
        if(p==first){ //case2:插入位置在index 0
            temp->next=first;
            first=temp;
        }
        else{ //case3:其他插入位置
            temp->next=last->next;
            last->next=temp;
        }
    }
}

void remove(struct Node* p, int index){
    if(index<0 || index>=count(p)) return;
    else if(index==0){
        struct Node* temp=first;
        first=first->next;
        printf("remove %d!\n",temp->data);
        free(temp);
    }
    else{
        for(int i=0;i<index-1;++i) p=p->next; //p跑到要被插入的前一個
        struct Node* temp=p->next;
        p->next=temp->next; //若刪除的是最後一個，p->nexte剛好接上NULL
        printf("remove %d!\n",temp->data);
        free(temp);
    }
}

bool isSorted(struct Node* p){
    int minNum=INT_MIN;
    while(p){
        if(p->data>=minNum) minNum=p->data;
        else return false;
        p=p->next;
    }
    return true;
}

void sortedRemoveDuplicate(struct Node* p){
    if(p->next==NULL) return;
    
    struct Node* temp1=p, * temp2=p->next;
    while(temp2){
        if(temp1->data == temp2->data){
            temp1->next=temp2->next;
            free(temp2);
            temp2=temp1->next;
        }
        else{
            temp1=temp2;
            temp2=temp2->next;
        }
    }
    
}

void reverse_element(struct Node* p){
    int* temp=(int*)malloc(sizeof(int)*count(p));
    int i=0;
    struct Node* q=p;  //複製一份做遍歷
    while(q){    //遍歷一次後將值紀錄到array
        temp[i]=q->data;
        q=q->next;
        i++;
    }
    q=p;
    i--;
    while(q){    //更改linked list值
        q->data=temp[i];
        q=q->next;
        i--;
    }
}

void reverse_link(struct Node* p){  //sliding pointer
    struct Node* q=NULL,* r=NULL;   //q在p前一個,r在p後一個
    while(p){
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    first=q; //此時p在null,q在最後一個node
}

void reverse_link_r(struct Node* q,struct Node* p){ //q在p前一個
    if(p==NULL) first=q;
    else{
        reverse_link_r(p, p->next);  //先用遞迴遍歷到底
        p->next=q; //在returning phase做換箭頭方向
    }
}

//concat,sortedMerge需要不只一個linked list,跳過不寫

bool isLoop(struct Node* p){
    struct Node* fast=p,* slow=p;
    do{
        slow=slow->next;
        fast=fast->next;
        if(fast) fast=fast->next;
    }while(fast && slow && fast!=slow);
    
    return (fast==slow) ? true : false;
}

int main(){
    /*
    int a[]={1,2,3,4,5,10,1,4};
    create(a,8);
    display(first);
    display_r(first);
    cout<<endl;
    cout<<"length: "<<count(first)<<endl;
    cout<<"length: "<<count_r(first)<<endl;
    cout<<"sum: "<<sum(first)<<endl;
    cout<<"sum: "<<sum_r(first)<<endl;
    cout<<"max: "<<max(first)<<endl;
    cout<<"max: "<<max_r(first)<<endl;
    
    int key;
    cout<<"search for...";
    cin>>key;
    if(search(first,key) && search_r(first,key)) cout<<"found!"<<endl;
    else cout<<"Not found"<<endl;
    display(first);

    
    insert(first,4,100);
    display(first);
    insert(first,0,-100);
    display(first);
    */
    
    //sorted linked-list------------------------------------
    sortedInsert(first, 50);
    display(first);
    sortedInsert(first, 30);
    display(first);
    sortedInsert(first, 40);
    display(first);
    sortedInsert(first, 100);
    display(first);
    
    remove(first,3);
    display(first);
    remove(first,1);
    display(first);

    printf("Is sorted linked-list? %d\n",isSorted(first));
    insert(first, 1, 60);
    display(first);
    printf("Is sorted linked-list? %d\n",isSorted(first));
    
    remove(first,1);
    sortedInsert(first, 100);
    sortedInsert(first, 70);
    sortedInsert(first, 80);
    sortedInsert(first, 30);
    sortedInsert(first, 30);
    display(first);
    sortedRemoveDuplicate(first);
    display(first);
    
    reverse_element(first);
    display(first);
    reverse_link(first);
    display(first);
    reverse_link_r(NULL, first);
    display(first);
    
    printf("is loop? %d\n",isLoop(first));
    struct Node* a=first->next;
    struct Node* b=first->next->next->next;
    b->next=a;                              //make a loop
    printf("is loop? %d\n",isLoop(first));
    
    return 0;
}
