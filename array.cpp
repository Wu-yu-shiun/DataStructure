//array ADT

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Array{
    int *p; //不同於直接宣告陣列A[10],每次要用要先malloc一個空間
    int size;
    int length;
};

void swap (int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

//display()
void Display(struct Array arr){
    cout<<"display element:";
    for(int i=0;i<arr.length;++i)
        cout<<" "<<arr.p[i];
    cout<<", length: "<<arr.length<<endl;
}

//append(x)
void Append(struct Array *arr,int x){
    if(arr->length<arr->size){
        arr->p[arr->length]=x;
        arr->length++;
        cout<<"append "<<x<<"..."<<endl;
    }
}

//insert(index,x)
void Insert(struct Array *arr,int index,int x){
    if(index<=arr->length && index>=0){
        for(int i=arr->length;i>index;--i){
            arr->p[i]=arr->p[i-1];
        }
        arr->p[index]=x;
        arr->length++;
        cout<<"insert "<<x<<" at index "<<index<<"..."<<endl;
    }
}

//delete(index)
void Delete(struct Array *arr,int index){
    if(index<arr->length && index>=0){
        int x=arr->p[index];
        for(int i=index;i<arr->length;++i){
            arr->p[i]=arr->p[i+1];
        }
        arr->length--;
        cout<<"delete "<<x<<" at index "<<index<<"..."<<endl;
    }
}

//linear search(key) => index
int LinearSearch(struct Array *arr,int key){
    for(int i=0;i<arr->length;++i){
        if(arr->p[i]==key){
            swap(&arr->p[i],&arr->p[0]);  //move to head,for the benifit of searching next time
            return i;
         }
    }
    return NULL;
}

//binary search(key) => index
int BinarySearch(struct Array arr,int key){
    int low=0,high=arr.length-1,middle;
    while(low<=high){
        middle=(low+high)/2;
        if(key<arr.p[middle]) high=middle-1;
        else if(key>arr.p[middle]) low=middle+1;
        else return middle;
    }
    return NULL;
}

//max
int Max(struct Array arr){
    int max=arr.p[0];
    for(int i=0;i<arr.length;++i){
        if(arr.p[i]>max){
            max=arr.p[i];
        }
    }
    return max;
}

//min
int Min(struct Array arr){
    int min=arr.p[0];
    for(int i=0;i<arr.length;++i){
        if(arr.p[i]<min){
            min=arr.p[i];
        }
    }
    return min;
}

//sum
int Sum(struct Array arr){
    int sum=0;
    for(int i=0;i<arr.length;++i){
        sum+=arr.p[i];
    }
    return sum;
}

//avg
float Avg(struct Array arr){
    return (float)Sum(arr)/arr.length;
}

//get(index) => value
int Get(struct Array arr,int index){
    if(index>=0 && index<arr.length)
        return arr.p[index];
    return NULL;
}

//set(index,x)
void Set(struct Array *arr,int index,int x){
    if(index>=0 && index<arr->length)
        arr->p[index]=x;
}

//reverse
void Reverse(struct Array *arr){
    //method 1
    int *temp=(int*)malloc(arr->length*sizeof(int));
    for(int i=arr->length-1,j=0;i>=0;--i,++j){
        temp[j]=arr->p[i];
    }
    for(int i=0;i<arr->length;++i){
        arr->p[i]=temp[i];
    }
    free(temp);
    
    //method 2
//    for(int i=0,j=arr->length-1;i<j;++i,--j){
//       swap(&arr->p[i],&arr->p[j]);
//    }
}

//sort an array from small to big
void BubbleSort(struct Array *arr){
    for(int i=0;i<arr->length-1;++i){
        for(int j=0;j<arr->length-1;++j){
            if(arr->p[j]>arr->p[j+1]){
                swap(&arr->p[j],&arr->p[j+1]);
            }
        }
    }
}

//insert number in a sorted array
void SortedInsert(struct Array *arr,int x){
    int i=arr->length-1;
    if(arr->length==arr->size)
        return;
    while(i>=0 && arr->p[i]>x){
        arr->p[i+1]=arr->p[i];
        i--;
    }
    arr->p[i+1]=x;
    arr->length++;
}

//check if sorted
bool IsSorted(struct Array arr){
    for(int i=0;i<arr.length-1;++i){
        if(arr.p[i]>arr.p[i+1]){
            return false;
        }
    }
    return true;
}

//merge two sorted array
struct Array* SortedMerge(struct Array *arr,struct Array *arr2){
    
    struct Array *arr3=(struct Array *)malloc(sizeof(struct Array));
    arr3->size=20;
    arr3->length=arr->length+arr2->length;
    arr3->p=(int*)malloc(arr3->size*sizeof(int));
    
    int i=0,j=0,k=0; //i,j：兩陣列讀取端，k：合併陣列寫入端
    while(i<arr->length && j<arr2->length){
        if(arr->p[i]<arr2->p[j]){
            arr3->p[k++]=arr->p[i++];  // == arr3->p[k]=arr->p[i]; k++; i++;
        }
        else{
            arr3->p[k++]=arr2->p[j++];
        }
    }
    for(;i<arr->length;++i){
        arr3->p[k++]=arr->p[i];
    }
    for(;j<arr2->length;++j){
        arr3->p[k++]=arr2->p[j];
    }
    
    return arr3;
}

int main(){
    
    //initialize data
    struct Array arr;
    cout<<"Array size: ";
    cin>>arr.size;
    arr.p=(int*)malloc(arr.size*sizeof(int)); //this type of array size is dynamic
    arr.length=0;
    int num;
    cout<<"num: ";
    cin>>num;
    for(int i=0;i<num;++i)
        cin>>arr.p[i];
    arr.length=num;
    
    //operations
    Display(arr);

    Append(&arr,10);
    Display(arr);
    
    Insert(&arr, 3, 100);
    Display(arr);
    
    Delete(&arr, 0);
    Display(arr);
    
    cout<<"Search 3 at index : "<<LinearSearch(&arr, 3)<<endl;
    Display(arr);
    
    cout<<"get index 3: "<<Get(arr, 3)<<endl;
    cout<<"max value: "<<Max(arr)<<", min value: "<<Min(arr)<<", sum: "<<Sum(arr)<<", avg: "<<Avg(arr)<<endl;
    
    cout<<"set 999 at index 3..."<<endl;
    Set(&arr, 3, 999);
    Display(arr);
    
    cout<<"reverse array..."<<endl;
    Reverse(&arr);
    Display(arr);
    
    cout<<"bubble sort..."<<endl;
    BubbleSort(&arr);
    Display(arr);
    
    cout<<"Insert 77 in sorted array..."<<endl;
    SortedInsert(&arr, 77);
    Display(arr);
    
    cout<<"Is Sorted Array? "<<IsSorted(arr)<<endl;
    
    //initial arr2
    struct Array arr2;
    arr2.p=(int*)malloc(arr.size*sizeof(int));
    arr2.size=10;
    arr2.length=7;
    for(int i=0;i<arr2.length;++i)
        arr2.p[i]=i*5;
    Display(arr2);
    
    //merge arr and arr2
    struct Array *arr3=SortedMerge(&arr, &arr2);
    Display(*arr3);
    
    return 0;
}
