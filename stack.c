//stack ADT 

#include <stdio.h>
#include <stdlib.h>

//1. using array

struct Stack{
    int size;
    int top;
    int* arr;
};


void create(struct Stack* stack){
    printf("Enter Size: ");
    scanf("%d",&stack->size);
    stack->top=-1;
    stack->arr=(int*)malloc(sizeof(int)*stack->size);
}


void display(struct Stack stack){
    for(int i=stack.top;i>=0;--i) printf("%d ",stack.arr[i]); //由上而下
    printf("\n");
}

void push(struct Stack* stack,int num){
    if(stack->top==stack->size-1) printf("stack overflow!\n");
    else{
        stack->top++;
        stack->arr[stack->top]=num;
    }
}

int pop(struct Stack* stack){
    if(stack->top==-1){
        printf("stack underflow!\n");
        return -1;
    }
    
    return stack->arr[stack->top--];
}

int peek(struct Stack stack, int index){  //index[0]==top
    if(stack.top-index<0 || index<0){
        printf("invalid index! \n");
        return -1;
    }
    
    return stack.arr[stack.top-index];
}

bool isEmtpy(struct Stack stack){
    return stack.top==-1;
}

bool isFull(struct Stack stack){
    return stack.top==stack.size-1;
}

int peekTop(struct Stack stack){
    return isEmtpy(stack)?-1:stack.arr[stack.top];
}


int main(){
    struct Stack stack1;
    create(&stack1);
    
    push(&stack1,10);
    push(&stack1,20);
    push(&stack1,30);
    printf("pop %d\n",pop(&stack1));
    push(&stack1,30);
    push(&stack1,40);
    push(&stack1,50);
    push(&stack1,60);
    display(stack1);
    
    printf("%d\n",peekTop(stack1));
    printf("%d\n",peek(stack1,5));
    printf("%d\n",peek(stack1,1));
    display(stack1);
    
    return 0;
}

//-------------------------------------------------------------

//2. using linked-list

struct Node{
    int data;
    struct Node* next;
}*top=NULL;

//將新加進來的放在linked-list頭
void push(int num){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    if(!temp) printf("stack is full!\n");
    else{
        temp->data=num;
        temp->next=top;
        top=temp;
    }
}

//取出linked-list頭
int pop(){
    if(!top){
        printf("stack is empty!\n");
        return -1;
    }
    
    struct Node* temp=top;
    int topNum=temp->data;
    top=top->next;
    return topNum;
}

void display(){
    struct Node* p=top; //p == iter
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int main(){
    push(10);
    push(20);
    push(30);
    display();
    printf("%d \n",pop());
    display();
}



