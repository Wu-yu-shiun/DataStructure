//AVL tree

#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int nodeHeight;
}*root=NULL;

int height(struct Node* p){ //from BST
    if(p==NULL) return -1;

    int leftH=height(p->left);
    int rightH=height(p->right);
    return leftH>rightH ? leftH+1 : rightH+1;
}

int balanceFactor(struct Node* p){
    return height(p->left)-height(p->right);
}

struct Node* rotationLL(struct Node* p){
    printf("execute LL rotaion\n");
    struct Node* pl=p->left, * plr=pl->right;

    pl->right=p;
    p->left=plr;
    p->nodeHeight=height(p);
    pl->nodeHeight=height(pl);

    if(root==p) root=pl;
    return pl;  //return new root of this subtree
}

struct Node* rotationLR(struct Node* p){
    printf("execute LR rotaion\n");
    struct Node* pl=p->left, * plr=pl->right;

    p->left=plr->right;
    pl->right=plr->left;
    plr->left=pl;
    plr->right=p;
    p->nodeHeight=height(p);
    pl->nodeHeight=height(pl);
    plr->nodeHeight=height(plr);

    if(root==p) root=plr;
    return plr;  //return new root of this subtree
}

struct Node* rotationRR(struct Node* p){
    printf("execute RR rotaion\n");
    struct Node* pr=p->right, * prl=pr->left;

    pr->left=p;
    p->right=prl;
    p->nodeHeight=height(p);
    pr->nodeHeight=height(pr);

    if(root==p) root=pr;
    return pr;  //return new root of this subtree
}

struct Node* rotationRL(struct Node* p){
    printf("execute RL rotaion\n");
    struct Node* pr=p->right, * prl=pr->left;

    p->right=prl->left;
    pr->left=prl->right;
    prl->right=pr;
    prl->left=p;
    p->nodeHeight=height(p);
    pr->nodeHeight=height(pr);
    prl->nodeHeight=height(prl);

    if(root==p) root=prl;
    return prl;  //return new root of this subtree
}


struct Node* insert_recursive(struct Node* p,int key){ //from BST, we need to use recursive to trace every parent node
    if(p==NULL){
        struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
        temp->data=key;
        temp->nodeHeight=1;
        temp->left=temp->right=NULL;
        return temp;
    }

    if(p->data>key) p->left=insert_recursive(p->left,key);
    else if(p->data<key) p->right=insert_recursive(p->right, key);
  
    //avl--------
    p->nodeHeight=height(p); //at returning time,update the height of the node
    if(balanceFactor(p)==2 && balanceFactor(p->left)==1) return rotationLL(p);
    else if(balanceFactor(p)==2 && balanceFactor(p->left)==-1) return rotationLR(p);
    else if(balanceFactor(p)==-2 && balanceFactor(p->right)==-1) return rotationRR(p);
    else if(balanceFactor(p)==-2 && balanceFactor(p->right)==1)  return rotationRL(p);
    //-----------
    else return p;
}

struct Node* remove_recursive(struct Node* p,int key){ //from BST, we need to use recursive to trace every parent node
    if(p==NULL){
        printf("Cannot find %d in BST!!!\n",key);
        return NULL;
    }
    if(p->left==NULL && p->right==NULL && p->data==key){
        if(p==root) root=NULL;
        free(p);
        return NULL;
    }

    if(p->data>key) p->left=remove_recursive(p->left,key);
    else if(p->data<key) p->right=remove_recursive(p->right, key);
    else{
        if(height(p->left)>height(p->right)){
            struct Node* temp=p->left;
            while(temp&&temp->right) temp=temp->right;
            p->data=temp->data;
            p->left=remove_recursive(p->left, temp->data);
        }
        else{
            struct Node* temp=p->right;
            while(temp&&temp->left) temp=temp->left;
            p->data=temp->data;
            p->right=remove_recursive(p->right, temp->data);
        }
    }
  
    //avl--------
    p->nodeHeight=height(p);
    if(balanceFactor(p)==2 && balanceFactor(p->left)==1) return rotationLL(p);
    else if(balanceFactor(p)==2 && balanceFactor(p->left)==-1) return rotationLR(p);
    else if(balanceFactor(p)==-2 && balanceFactor(p->right)==-1) return rotationRR(p);
    else if(balanceFactor(p)==-2 && balanceFactor(p->right)==1) return rotationRL(p);
    else if(balanceFactor(p)==2 && balanceFactor(p->left)==0) return rotationLL(p); //or rotationLR(p)
    else if(balanceFactor(p)==-2 && balanceFactor(p->right)==0) return rotationRR(p); //or rotationRL(p)
    //-----------
    else return p;
}

void inorder(struct Node* p){
    if(p==NULL) return;

    inorder(p->left);
    printf("%d ",p->data);
    inorder(p->right);
}

void preorder(struct Node* p){
    if(p==NULL) return;

    printf("%d ",p->data);
    preorder(p->left);
    preorder(p->right);
}

int main(){
    printf("1.insert\n");
    root=insert_recursive(root, 10);
    insert_recursive(root, 20);
    insert_recursive(root, 30);
    insert_recursive(root, 25);
    insert_recursive(root, 28);
    insert_recursive(root, 27);
    insert_recursive(root, 5);
    
    printf("root:%d, tree height:%d\n",root->data,height(root));
    printf("pre-order: ");
    preorder(root);
    printf("\n");
    printf("in-order: ");
    inorder(root);
    printf("\n\n");
    
    printf("2.delete\n");
    remove_recursive(root, 5);
    remove_recursive(root, 20);
    remove_recursive(root, 10);
    remove_recursive(root, 30);
    
    printf("root:%d, tree height:%d\n",root->data,height(root));
    printf("pre-order: ");
    preorder(root);
    printf("\n");
    printf("in-order: ");
    inorder(root);
    printf("\n\n");
    
    return 0;
}
