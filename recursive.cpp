//recursive practice

#include <iostream>
#include <stdio.h>

using namespace std;

//1.sum (1+2+3...)

int SumOfN (int n){
    if(n<=0)
        return 0;
    return SumOfN(n-1)+n;
}

//2.factorial (5! = 1*2*3*4*5)

double FactarialOfN(int n){
    if(n<=0)
        return 1;
    return FactarialOfN(n-1)*n;
}

//3. power (2^3 = 2*2*2)

//basic
double PowerOfMN1(int m,int n){
    if(n==0)
        return 1;
    return PowerOfMN1(m,n-1)*m;
}

//faster
int PowerOfMN2(int m,int n){
    if(n==0)
        return 1;
    if(n%2==0)  //even number
        return PowerOfMN2(m*m,n/2);
    return m*PowerOfMN2(m*m,(n-1)/2);  //odd number
}

//4. Taylor series

//basic, e^x = 1+ x/1 + x^2/2! + x^3/3! + ... n terms => O(n^2)
double Taylor(int x,int n){
    static double num=1,den=1;
    double temp;
    
    if(n==0)
        return 1;
    temp=Taylor(x, n-1);
    num*=x;
    den*=n;
    return temp+num/den;
}


//--------------------------------------------------------------------
//方法可行，若使用上面函式的型態是int，會導致泰勒展開式分數的分子分母太大時數字會跑掉
double Taylor1(int x,int n){
    static int num=0,den=0;
    double fraction;
    
    if(n==0)
        return 1;
    num++;
    den++;

    //compute fraction instead of putting all in return,because of static variable exist...
    fraction=(double)PowerOfMN1(x,num)/(double)FactarialOfN(den);

    return Taylor1(x,n-1)+fraction;
}
//--------------------------------------------------------------------

//by Horner's rule(using multiplication reduced)
//e^x = 1 + x/1( 1 + x/2( 1 + x/3( 1 + x/4...))) => O(n)
double Taylor2(int x,int n){
    static int i=n+1;
    double temp;
    
    if(n==0)
        return 1;
    temp=Taylor2(x,n-1);
    
    i--;
    return 1+temp*x/i;
}

//5. Fabonacci series ( 0 1 1 2 3 5 8 13... )

//basic, call the same function multiple times, O(2^n)
int Fibonacci1(int n){
    if(n<=1)
        return n;
    return Fibonacci1(n-1)+Fibonacci1(n-2);
}

//fast, store value as an array(memorization), O(n)
int Fib[100];
int Fibonacci2(int n){
    if(n<=1){
        Fib[n]=n;
        return n;
    }
    if(Fib[n-1]==-1)
        Fib[n-1]=Fibonacci2(n-1);
    if(Fib[n-2]==-1)
        Fib[n-2]=Fibonacci2(n-2);
    return Fib[n-1]+Fib[n-2];
}

//6. Combination Formula nCr ( n!/r!(n-r)! )
int nCr1(int n,int r){
    return FactarialOfN(n)/(FactarialOfN(r)*FactarialOfN(n-r));
}

int nCr2(int n,int r){
    if (r==0 || r==n){
        return 1;
    }
    return nCr2(n-1, r-1)+nCr2(n-1, r);
}

//7. Tower of Hanoi => O(2^n)
int Hanoi(int num,char start,char pass,char end){
    static int steps=0;
    if(num>0){
        Hanoi(num-1, start, end, pass);
        printf("Move %d from %c to %c...\n",num,start,end);
        steps++;
        Hanoi(num-1, pass, start, end);
    }
    return steps;
}

int main(){
    //1.sum 2.factorial 3.power
    int n,m;
    cout<<"n= ";
    cin>>n;
    cout<<"m= ";
    cin>>m;
    cout<<"sum of "<<n<<": "<<SumOfN(n)<<endl;
    cout<<"factorial of "<<n<<": "<<FactarialOfN(n)<<endl;
    cout<<"(double)power of "<<m<<"^"<<n<<": "<<PowerOfMN1(m,n)<<endl;
    cout<<"(int)power of "<<m<<"^"<<n<<": "<<PowerOfMN2(m,n)<<endl;
    cout<<"----------------"<<endl;

    //4.taylor series
    int e,terms;
    cout<<"e: ";
    cin>>e;
    cout<<"terms: ";
    cin>>terms;
    cout<<"e^"<<e<<" by Taylor Series 1-1: "<<Taylor(e, terms)<<endl;
    cout<<"e^"<<e<<" by Taylor Series 1-2: "<<Taylor1(e, terms)<<endl;
    cout<<"e^"<<e<<" by Taylor Series 2: "<<Taylor2(e, terms)<<endl;
    cout<<"----------------"<<endl;

    //5.Fabonacci series
    int f;
    cout<<"Index of Fabonacci Series (0~99): ";
    cin>>f;
    cout<<"basic recursion: "<<Fibonacci1(f)<<endl;
    memset(Fib, -1, sizeof(Fib));
    cout<<"memorizaton: "<<Fibonacci2(f)<<endl;
    cout<<"----------------"<<endl;
    
    //6.Combination Formula nCr
    int C_n, C_r;
    cout<<"C_n= ";
    cin>>C_n;
    cout<<"C_r= ";
    cin>>C_r;
    cout<<"nCr by formula: "<<nCr1(C_n,C_r)<<endl;
    cout<<"nCr by Pascal's triangle: "<<nCr1(C_n,C_r)<<endl;
    cout<<"----------------"<<endl;
    
    //7.Tower of Hanoi
    int num;
    cout<<"Num of Hanoi Tower: ";
    cin>>num;
    cout<<Hanoi(num,'A','B','C')<<" steps to solve."<<endl;
    
    return 0;
}
