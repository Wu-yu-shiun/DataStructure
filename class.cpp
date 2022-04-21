#include <iostream>
#include <stdio.h>

using namespace std;

//1.basic class
class Rectangle{
    private:
        int length;
        int breadth;
    public:
        //default construtor
        Rectangle(){
            this->length=0;
            this->breadth=0;
        }
        //customized constructor
        Rectangle(int l,int b){
            this->length=l;
            this->breadth=b;
        }

        int calculateArea(){
            return length*breadth;
        }
        int calculatePerimeter(){
            return 2*(length+breadth);
        }

        void setLength(int l){
            length=l;
        }

        //destructor
        ~Rectangle(){
            cout<<"destructor!"<<endl;
        }
};

//2.using template
template<class T>
class Arithmetic{
    private:
        T a;
        T b;
    public:
        Arithmetic(T a,T b);
        T add();
        T sub();
};

template<class T> //implement ouside class by scop resolution ::
Arithmetic<T>::Arithmetic(T a ,T b){
    this->a=a;
    this->b=b;
}

template<class T> 
T Arithmetic<T>:: add(){
    T c;
    c=a+b;
    return c;
}

template<class T> 
T Arithmetic<T>::sub(){
    return a-b;
}



int main() {

    //1.basic class
    int length,breadth;
    printf("basic class\nInput length and breadth:\n");
    cin>>length>>breadth;

    Rectangle r1(length,breadth);

    cout<<"output area: "<<r1.calculateArea()<<endl;
    cout<<"output perimeter: "<<r1.calculatePerimeter()<<endl;

    r1.setLength(99);
    cout<<"new output area: "<<r1.calculateArea()<<endl;
    cout<<"new output perimeter: "<<r1.calculatePerimeter()<<endl;

    //2.using template
    Arithmetic<int> ar1(10,5);
    Arithmetic<float> ar2(123.45,55.5);
    Arithmetic<char> ar3('A', 'B');

    cout<<"using template"<<endl;
    cout<<"ar1 Add: "<<ar1.add()<<" Sub: "<<ar1.sub()<<endl;
    cout<<"ar2 Add: "<<ar2.add()<<" Sub: "<<ar2.sub()<<endl;
    cout<<"ar3 Add: "<<(int)ar3.add()<<" Sub: "<<(int)ar2.sub()<<endl;

    return 0;
}
