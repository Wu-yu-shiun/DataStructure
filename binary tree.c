//header1:Queue ADT

#include <stdio.h>
#include <stdlib.h>

#ifndef Queue_h
#define Queue_h

struct Node{
    struct Node* left;
    struct Node* right;
    int data;
};

struct Queue{
    int size;
    int front; //移出端(第一個的前一個)
    int rear;  //放入端(最後一個)
    Node** container; //** => for Node + for array
};

void createQueue(struct Queue* queue, int size){
    queue->size=size;
    queue->front=queue->rear=0;
    queue->container=(Node**)malloc(sizeof(Node*)*size);
}

void enqueue(struct Queue* queue, Node* num){
    if((queue->rear+1)%queue->size == queue->front) printf("Queue is full!\n");
    else{
        queue->rear=(queue->rear+1)%queue->size;
        queue->container[queue->rear]=num;
    }
}

Node* dequeue(struct Queue* queue){
    if(queue->front==queue->rear){
        printf("Queue is empty!\n");
        return NULL;
    }
    else{
        queue->front=(queue->front+1)%queue->size;
        return queue->container[queue->front];
    }
}

bool isEmptyQueue(struct Queue q){
    return q.front==q.rear;
}

#endif /* Queue_h */

//------------------------------------------------------------

//header2:Stack ADT
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#ifndef Stack_h
#define Stack_h

struct Stack{
    int size;
    int top;
    struct Node** container;
};

void createStack(struct Stack* stack,int size){
    stack->size=size;
    stack->top=-1;
    stack->container=(struct Node**)malloc(sizeof(struct Node*)*stack->size);
}

void push(struct Stack* stack,struct Node* num){
    if(stack->top==stack->size-1) printf("stack overflow!\n");
    else{
        stack->top++;
        stack->container[stack->top]=num;
    }
}

struct Node* pop(struct Stack* stack){
    if(stack->top==-1){
        printf("stack underflow!\n");
        return NULL;
    }
    
    return stack->container[stack->top--];
}

bool isEmtpyStack(struct Stack stack){
    return stack.top==-1;
}

#endif /* Stack_h */

//------------------------------------------------------------

//binary tree

#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"
#include "Stack.h"

struct Node *root=NULL;

void createTree(){
    struct Queue q;
    createQueue(&q,100);
    
    int x;
    printf("Enter root value: ");
    scanf("%d",&x);
    root=(struct Node*)malloc(sizeof(Node));
    root->data=x;
    root->left=root->right=NULL;
    enqueue(&q,root);
    
    while(!isEmptyQueue(q)){
        struct Node* p=dequeue(&q);
        
        printf("Enter %d's left child: ",p->data);
        scanf("%d",&x);
        if(x!=-1){
            struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
            temp->data=x;
            temp->left=temp->right=NULL;
            
            p->left=temp;
            enqueue(&q, temp);
        }
        
        printf("Enter %d's right child: ",p->data);
        scanf("%d",&x);
        if(x!=-1){  //-1 means NULL
            struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
            temp->data=x;
            temp->left=temp->right=NULL;
            
            p->right=temp;
            enqueue(&q, temp);
        }
    }
}

int height(struct Node* p){
    if(p==NULL) return -1; //空node的地方放-1，開始往上+1+1剛好符合height定義
    
    int leftH=height(p->left);
    int rightH=height(p->right);
    return leftH>rightH ? leftH+1 : rightH+1;
}

int count(struct Node* p){
    if(p==NULL) return 0;
    
    int leftN=count(p->left);
    int rightN=count(p->right);
    return leftN+rightN+1; //count all nodes
    
    //return (p->right==NULL && p->left==NULL) ? leftN+rightN+1 : leftN+rightN   //count degree 0 nodes(leaf)
    //return (p->right ^ p->left) ？ leftN+rightN+1 : leftN+rightN   //count degree 1 nodes (^ XOR)
    //return (p->right && p->left) ？ leftN+rightN+1 : leftN+rightN   //count degree 2 nodes
}

//1.traverse tree by recursion
void pre_order_recursive(struct Node* p){
    if(p){
        printf("%d ",p->data);
        pre_order_recursive(p->left);
        pre_order_recursive(p->right);
    }
}
void in_order_recursive(struct Node* p){
    if(p){
        in_order_recursive(p->left);
        printf("%d ",p->data);
        in_order_recursive(p->right);
    }
}
void post_order_recursive(struct Node* p){
    if(p){
        post_order_recursive(p->left);
        post_order_recursive(p->right);
        printf("%d ",p->data);
    }
}

//2.traverse tree by iterative (using stack,queue)

void pre_order_iterative(struct Node* p){
    struct Stack stack;
    createStack(&stack, 100);
    
    while(p || !isEmtpyStack(stack)){
        if(p){
            printf("%d ",p->data);
            push(&stack, p);
            p=p->left;
        }
        else{
            p=pop(&stack);
            p=p->right;
        }
    }
}
void in_order_iterative(struct Node* p){
    struct Stack stack;
    createStack(&stack, 100);
    
    while(p || !isEmtpyStack(stack)){
        if(p){
            push(&stack, p);
            p=p->left;
        }
        else{
            p=pop(&stack);
            printf("%d ",p->data);
            p=p->right;
        }
    }
}
void post_order_iterative(struct Node* p){ //Warning! not suitable for negative data except -1
    struct Stack stack;
    createStack(&stack, 100);
    
    while(p || !isEmtpyStack(stack)){
        if(p){
            push(&stack, p);
            p=p->left;
        }
        else{
            struct Node* temp=pop(&stack);
            
            //distinguish popping out first time or second time by using negative number
            if(temp->data>0){ //pop out first time
                temp->data*=-1;
                push(&stack,temp); //push that node into stack again
                p=temp->right; //check for the right node
            }
            else{ //pop out second time
                temp->data*=-1;
                printf("%d ",temp->data); //already check right child, then print
                p=NULL; //
            }
        }
    }
}
void level_order_iterative(struct Node* p){
    struct Queue queue;
    createQueue(&queue, 100);
    
    //print root
    printf("%d ",p->data);
    enqueue(&queue,p);
    
    while(!isEmptyQueue(queue)){
        p=dequeue(&queue);
        if(p->left){
            printf("%d ",p->left->data);
            enqueue(&queue, p->left);
        }
        if(p->right){
            printf("%d ",p->right->data);
            enqueue(&queue, p->right);
        }
    }
}

int main(){
    
    createTree();
    printf("\n");
    printf("Height of tree: %d\n",height(root));
    printf("Nodes of tree: %d\n\n",count(root));
    
    printf("1.traverse tree by recursive\n");
    printf("pre-order: ");
    pre_order_recursive(root);
    printf("\n");
    printf("in-order: ");
    in_order_recursive(root);
    printf("\n");
    printf("post-order: ");
    post_order_recursive(root);
    printf("\n\n");
    
    printf("2.traverse tree by iterative\n");
    printf("pre-order: ");
    pre_order_iterative(root);
    printf("\n");
    printf("in-order: ");
    in_order_iterative(root);
    printf("\n");
    printf("post-order: ");
    post_order_iterative(root);
    printf("\n");
    printf("level-order: ");
    level_order_iterative(root);
    printf("\n");
    
    return 0;
}
