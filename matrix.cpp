//matrix in C++

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Diogonal{
private:
    int *A;
    int n;
public:
    Diogonal(){
        A=new int[2];
        for(int i=0;i<2;++i){
            A[i]=0;
        }
        n=2;
    }
    Diogonal(int n){
        A=new int[n];
        for(int i=0;i<n;++i){
            A[i]=0;
        }
        this->n=n;
    }
    ~Diogonal(){
        delete []A;
    }
    
    void set(int i,int j,int x){
        if(i==j) A[i-1]=x;
    }
    int get(int i,int j){
        if(i==j) return A[i-1];
        else return 0;
    }
    void display(){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(i==j) cout<<A[i]<<" ";
                else cout<<"0 ";
            }
            cout<<endl;
        }
    }
};


class LowTri{
private:
    int *A;
    int n;
public:
    LowTri(){
        A=new int[3];
        for(int i=0;i<2;++i){
            A[i]=0;
        }
        n=2;
    }
    LowTri(int n){
        A=new int[n*(n+1)/2];
        for(int i=0;i<n;++i){
            A[i]=0;
        }
        this->n=n;
    }
    ~LowTri(){
        delete []A;
    }
    
    void set(int i,int j,int x){
        if(i>=j) A[i*(i-1)/2+j-1]=x;  //row-major
        //if(i>=j) A[n*(j-1)-(j-2)*(j-1)/2/2+i-j]=x;  //column-major
    }
    int get(int i,int j){
        if(i>=j) return A[i*(i-1)/2+j-1]; //row-major
        //if(i>=j) return A[n*(j-1)-(j-2)*(j-1)/2/2+i-j]; //column-major
        else return 0;
    }
    void display(){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(i>=j) cout<<A[i*(i-1)/2+j-1]<<" "; //row-major
                //if(i>=j) cout<<A[n*(j-1)-(j-2)*(j-1)/2/2+i-j]<<" "; //column-major
                else cout<<"0 ";
            }
            cout<<endl;
        }
    }
};

class Element{
public:
    int x;
    int y;
    int val;
};

class Sparse{
private:
    int m;
    int n;
    int num; //number of non-zero element
    Element* e;
public:
    Sparse(int m,int n,int num){
        this->m=m;
        this->n=n;
        this->num=num;
        this->e=new Element[this->num];
    }
    ~Sparse(){
        delete [] e;
    }
    
    //operator "+" directly syntax
    Sparse operator+ (Sparse &s){
        if(this->m!=s.m || this->n!=s.n) return Sparse(0,0,0);
        
        int i=0,j=0,k=0;
        Sparse *sum=new Sparse(m,n,this->num+s.num);
        
        while(i<num && j<s.num){
            if(this->e[i].x < s.e[j].x) sum->e[k++]=this->e[i++];
            else if(this->e[i].x > s.e[j].x) sum->e[k++]=s.e[j++];
            else{
                if(this->e[i].y < s.e[j].y) sum->e[k++]=this->e[i++];
                else if(this->e[i].y > s.e[j].y) sum->e[k++]=s.e[j++];
                else{
                    sum->e[k]=this->e[i]; //copy x,j,val
                    sum->e[k++].val=e[i++].val+s.e[j++].val;
                }
            }
        }
        for(;i<this->num;i++) sum->e[k++]=e[i];
        for(;j<s.num;j++) sum->e[k++]=s.e[j];
        sum->num=k;
        
        return *sum;
        
    }
    
    //cin,cout directly syntax
    friend istream & operator>>(istream &is,Sparse &s);
    friend ostream & operator<<(ostream &os,Sparse &s);
    
};

istream & operator>>(istream &is,Sparse &s){
    cout<<"input non-zero elements in order..."<<endl; //照row,column的大小順序輸入，以免讀不到
    for(int i=0;i<s.num;++i){
        cin>>s.e[i].x>>s.e[i].y>>s.e[i].val;
    }
    return is;
}

ostream & operator<<(ostream &os,Sparse &s){
    int k=0;
    for(int i=0;i<s.m;++i){
        for(int j=0;j<s.n;++j){
            if(s.e[k].x==i && s.e[k].y==j) cout<<s.e[k++].val<<" ";
            else cout<<"0 ";
        }
        cout<<endl;
    }
    return os;
}



int main(){

    cout<<"Diogonal Matrix (4*4)"<<endl;
    Diogonal d(4);
    d.set(1, 2, 3);
    d.set(2, 2, 5);
    d.set(4, 4, 10);
    d.display();
    cout<<"---------------"<<endl;
    
    cout<<"Lower Triangular Matrix (4*4)"<<endl;
    LowTri l(4);
    cout<<"set all elements"<<endl;
    for(int i=1;i<=4;++i){
        for(int j=1;j<=4;++j){
            int x;
            cin>>x;
            l.set(i, j, x);
        }
    }
    l.display();
    cout<<"---------------"<<endl;
    
    cout<<"Sparse Matrix (4*4)"<<endl;
    Sparse s1(4,4,4),s2(4,4,4);
    cin>>s1>>s2;
    Sparse sum=s1+s2;
    cout<<"output sparse matrix1..."<<endl<<s1;
    cout<<"output sparse matrix2..."<<endl<<s2;
    cout<<"output sparse matrix1+2..."<<endl<<sum;
    cout<<"---------------"<<endl;

    return 0;
}
