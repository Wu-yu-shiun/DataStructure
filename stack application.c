//stack application

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char data;
    struct Node* next;
}*top=NULL;


void push(char ch){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    if(!temp) printf("stack is full!\n");
    else{
        temp->data=ch;
        temp->next=top;
        top=temp; //將新加進來的放在linked-list頭
    }
}

char pop(){
    if(!top){
        printf("stack is empty!\n");
        return NULL;
    }
    
    struct Node* temp=top;
    char topCh=temp->data;
    top=top->next; //取出linked-list頭
    return topCh;
}

void display(){
    struct Node* p=top; //p == iter
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

//1. parenthesis matching
bool isBalanced(char* exp){
    for(int i=0;exp[i]!='\0';++i){
        if(exp[i]=='(') push(exp[i]);
        else if(exp[i]==')'){
            if(top==NULL) return false;
            pop();
        }
    }
    
    if(top==NULL) return true;
    else return false;
}

//2. infix to postfix conversion
int operatorLevel(char ch){
    if(ch=='+' || ch=='-') return 1;
    else if (ch=='*' || ch=='/') return 2;
    else return 0;
}

bool isOperand(char ch){
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/') return false;
    else return true;
}
               
char* infixToPostfix(char* infix){
    char* postfix=(char*)malloc(sizeof(char)*(strlen(infix)+2)); //one more for '#'mark

    int i=0,j=0;
    while(infix[i]!='\0'){
        if(isOperand(infix[i])) postfix[j++]=infix[i++];
        else{
            if(operatorLevel(infix[i])>operatorLevel(top->data)) push(infix[i++]);
            else postfix[j++]=pop(); //此時i位置不變，會再次進入while迴圈檢查level
        }
    }
    
    while(top!=NULL) postfix[j++]=pop(); //stack內所剩operator全部pop出來
    postfix[j]='\0';
    return postfix;
}

//3. calculate postfix expression  restriction: unsuitable for multiple digits
int postfixCalculate(char* postfix){
    for(int i=0;postfix[i]!='\0';++i){
        if(isOperand(postfix[i])) push(postfix[i]-'0'); //turn char operand into int before putting into stack
        else{
            int b=pop(), a=pop(), result=0; // a (+,-,*,/) b
            switch (postfix[i]) {
                case '+':
                    result=a+b;
                    break;
                case '-':
                    result=a-b;
                    break;
                case '*':
                    result=a*b;
                    break;
                case '/':
                    result=a/b;
                    break;
            }
            push(result);
        }
    }
    return pop();
}

int main(){
    char* exp=(char*)"((a+b))*(c-d)";
    printf("%d\n",isBalanced(exp));           //true(1)
    
    
    char* infix=(char*)"a+b*c-d/e";
    push('#');
    printf("%s\n",infixToPostfix(infix));     //abc*+de/-#
    
    
    char* postfix=(char*)"453*+62/-";
    printf("%d\n",postfixCalculate(postfix)); //4+5*3-6/2=16
    
    return 0;
}
