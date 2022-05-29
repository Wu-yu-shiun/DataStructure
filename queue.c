#include <stdio.h>
#include <stdlib.h>

//circular queue ADT using array

struct Queue{
    int size;
    int front; //移出端(第一個的前一個)
    int rear;  //放入端(最後一個)
    int* container;
};

void create(struct Queue* queue, int size){
    queue->size=size;
    queue->front=queue->rear=0;
    queue->container=(int*)malloc(sizeof(int)*size);
}

void enqueue(struct Queue* queue, int num){
    if((queue->rear+1)%queue->size == queue->front) printf("Queue is full!\n");
    else{
        queue->rear=(queue->rear+1)%queue->size;
        queue->container[queue->rear]=num;
    }
}

int dequeue(struct Queue* queue){
    if(queue->front==queue->rear){
        printf("Queue is empty!\n");
        return -1;
    }
    else{
        queue->front=(queue->front+1)%queue->size;
        return queue->container[queue->front];
    }
}

void display(struct Queue queue){
    int index=(queue.front+1)%queue.size;
    while(index!=(queue.rear+1)%queue.size){
        printf("%d ",queue.container[index]);
        index=(index+1)%queue.size;
    }
    printf("\n");
    //for(int i=queue.front+1;i<=queue.rear;++i) printf("%d ",queue.container[i]); //non-circular
}


int main(){
    struct Queue q;
    create(&q, 5);
    
    enqueue(&q, 5);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40); //Queue is full! circular queue only can use size-1
    display(q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    display(q);
    enqueue(&q, 50);
    enqueue(&q, 60);
    enqueue(&q, 70);
    display(q);
    
    return 0;
}

//----------------------------------------------------------------

//queue ADT using linked-list

struct Node{
    int data;
    struct Node* next;
}* front=NULL,* rear=NULL;

void enqueue(int num){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    if(temp==NULL) printf("Queue is full!\n");
    else{
        temp->data=num;
        temp->next=NULL;
        if(front==NULL) front=rear=temp;  //first element
        else{
            rear->next=temp;
            rear=temp;
        }
    }
}

int dequeue(){
    if(front==NULL){
        printf("Queue is empty!\n");
        return -1;
    }
    else{
        struct Node* temp=front;
        int num=temp->data;
        front=front->next;
        free(temp);
        return num;
    }
}

void display(){
    struct Node* iter=front;
    while(iter){
        printf("%d ",iter->data);
        iter=iter->next;
    }
    printf("\n");
}

int main(){
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display();
    printf("%d\n",dequeue());
    printf("%d\n",dequeue());
    printf("%d\n",dequeue());
    display();
    printf("%d\n",dequeue());
    printf("%d\n",dequeue());
    printf("%d\n",dequeue());
    
    return 0;
}


