//binary search tree

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}*root=NULL;

int height(struct Node* p){
    if(p==NULL) return -1;
        
    int leftH=height(p->left);
    int rightH=height(p->right);
    return leftH>rightH ? leftH+1 : rightH+1;
}

void insert(int key){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=key;
    temp->left=temp->right=NULL;
    
    if(root==NULL){ //第一個node
        root=temp;
        return;
    }

    struct Node* iter=root,* tail=NULL; //use tail follow behind p to get parent's address when connecting
    while(iter){
        tail=iter;
        if(iter->data>key) iter=iter->left;
        else if(iter->data<key) iter=iter->right;
        else return; //已存在此node,不做動作
    }
    if(tail->data>key) tail->left=temp;
    else tail->right=temp;
}

void inorder(struct Node* p){
    if(p==NULL) return;
    
    inorder(p->left);
    printf("%d ",p->data);
    inorder(p->right);
}

struct Node* search(int key){
    struct Node* iter=root;
    while(iter){
        if(iter->data>key) iter=iter->left;
        else if(iter->data<key) iter=iter->right;
        else{
            printf("Find %d in BST!!!\n",key);
            return iter;
        }
    }
    printf("Not find %d in BST!!!\n",key);
    return NULL;
}

struct Node* insert_recursive(struct Node* p,int key){
    if(p==NULL){
        struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
        temp->data=key;
        temp->left=temp->right=NULL;
        return temp;
    }
    
    if(p->data>key) p->left=insert_recursive(p->left,key);
    else if(p->data<key) p->right=insert_recursive(p->right, key);
    return p; //最後會回傳到root node
}

//About delete BST node
//case1:沒找到key
//case2:純去掉 (leaf node)
//case2:去掉後下面只有一個往上捕缺
//case3:去掉後要找到下面適合者往上捕(右半部找最左 或 左半部找最右)
//case4:去掉後要找到下面適合者往上捕，適合者的缺由下面只有一個往上捕缺 (3+2)
struct Node* remove(struct Node* p,int key){
    if(p==NULL){//cannot find that key, nothing to do (case1)
        printf("Cannot find %d in BST!!!\n",key);
        return NULL;
    }
    if(p->left==NULL && p->right==NULL && p->data==key){ //leaf node (case2)
        if(p==root) root=NULL;
        free(p);
        return NULL;
    }
    
    if(p->data>key) p->left=remove(p->left,key);
    else if(p->data<key) p->right=remove(p->right, key);
    else{ //p is the key must remove (case3+4+5)
        //choose left or right suitable node to replace the removed node
        if(height(p->left)>height(p->right)){
            struct Node* temp=p->left;
            while(temp&&temp->right) temp=temp->right; //temp is 左半部找最右
            p->data=temp->data;
            p->left=remove(p->left, temp->data); //用遞迴重複做(case4+5)
        }
        else{
            struct Node* temp=p->right;
            while(temp&&temp->left) temp=temp->left; //temp is 右半部找最左
            p->data=temp->data;
            p->right=remove(p->right, temp->data); //用遞迴重複做(case4+5)
        }
    }
    return  p;
}

void create_BST_from_preorder(int* arr,int size){
    root=(struct Node*)malloc(sizeof(struct Node));
    root->data=arr[0];
    root->left=root->right=NULL;
    
    struct Node* iter=root;
    Stack stack; //用stack存下長在左邊的node，也就是存下右邊有可能會再長出node的所有可能node的位址
    int index=1;
    while(index<size){
        if(iter->data>arr[index]){
            struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
            temp->data=arr[index];
            temp->right=temp->left=NULL;
            iter->left=temp;
            push(&stack, iter);
            iter=temp;
        }
        else{
            if(peekTop(stack)->data>arr[index]){
                struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
                temp->data=arr[index];
                temp->right=temp->left=NULL;
                iter->right=temp;
                iter=temp;
            }
            else{
                pop(&stack); //沒有用到後就再也用不到
            }
        }
    } 
}

int main(){
    insert(30);
    insert(5);
    insert(10);
    insert(20);
    insert(8);
    insert(5);
    insert_recursive(root, 50);
    
    
    printf("in-order traveral: ");
    inorder(root);
    printf("\n");
    
    search(5);
    search(13);
    struct Node* x=search(20);
    if(x)printf("%d\n",x->data);
    
    remove(root, 30);
    remove(root, 15);
    remove(root, 5);
    remove(root, 50);
    inorder(root);
    printf("\n");
    
    return 0;
}
