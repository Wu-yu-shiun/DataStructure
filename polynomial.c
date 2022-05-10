//Polynomial in C

struct Term{
    int coeff;
    int exp;
};

struct Polynomial{
    int num;
    struct Term* t;
};

void create(struct Polynomial* p){
    printf("Number of terms:\n");
    scanf("%d",&p->num);
    p->t=(struct Term*)malloc(sizeof(struct Term)*p->num);
    printf("Terms:\n");
    for(int i=0;i<p->num;++i) scanf("%d%d",&p->t[i].coeff,&p->t[i].exp);
}

void display(struct Polynomial p){
    for(int i=0;i<p.num;++i){
        printf("%dx^%d",p.t[i].coeff,p.t[i].coeff);
        if(i!=p.num-1) printf("+");
    }
    printf("\n");
}
struct Polynomial* add(struct Polynomial* p1,struct Polynomial* p2){
    int i=0,j=0,k=0;
    struct Polynomial* sum;
    sum=(struct Polynomial*)malloc(sizeof(struct Polynomial));
    sum->t=(struct Term*)malloc(sizeof(struct Term)*(p1->num+p2->num));
    
    while(i<p1->num && j<p2->num){
        if(p1->t[i].exp > p2->t[j].exp) sum->t[k++]=p1->t[i++];
        else if(p2->t[j].exp > p1->t[i].exp) sum->t[k++]=p2->t[j++];
        else{
            sum->t[k].exp=p1->t[i].exp;
            sum->t[k++].coeff=p1->t[i++].coeff+p2->t[j++].coeff;
        }
    }
    
    for(;i<p1->num;++i) sum->t[k++]=p1->t[i];
    for(;j<p2->num;++j) sum->t[k++]=p2->t[j];
    
    sum->num=k;
    return sum;
}

int main(){
    cout<<"Polynomial"<<endl;
    struct Polynomial p1,p2,*p3;
    create(&p1);
    printf("p1=\n");
    display(p1);
    create(&p2);
    printf("p2=\n");
    display(p2);
    p3=add(&p1,&p2);
    printf("p1+p2=\n");
    display(*p3);
    cout<<"---------------"<<endl;
    
    return 0;
}
