#include<iostream>      //need to check for negative polynomials
#include<cmath>

using namespace std;

const int MAX=100;

typedef struct _node{
    int deg;
    double coeff;
    struct _node *next;
}node;

node *allocate()
{
    node *head = new node;
    head->next=NULL;
    return head;
}

typedef struct{
    int degree;
    node *c;
}Polyn;

void printPoly(Polyn p)
{
    node *h=p.c;
    if(h->deg!=0)
    printf("(%lf)x^%d",h->coeff,h->deg);
    else
    printf("(%lf)",h->coeff);
    h=h->next;
    while(h!=NULL)
    {
        printf("+(%lf)x^%d",h->coeff,h->deg);
        h=h->next;
    }
}

node *insert(node *h, node *head)
{
    node *prev=head;
    node *current=head->next;
    if(prev->deg>h->deg)
    {
        h->next=prev;
        head=h;
        return head;
    }
    while(current!=NULL)
    {
        if(current->deg>h->deg)
        {
            prev->next=h;
            h->next=current;
            break;
        }
        else if(current->deg==h->deg)
        {
            current->coeff=h->coeff;
            break;
        }
        prev=current;
        current=current->next;
    }
    if(current==NULL)
    {
        prev->next=h;
    }
    return head;
}

void addremoveterm(Polyn p1, int d, double c)
{
    // node *h=p1.c;
    // node *prev=h;
    // while(h!=NULL)
    // {
    //     if(h->deg==d)
    //     {
    //         h->coeff=c;
    //         break;
    //     }
    //     prev=h;
    //     h=h->next;
    // }
    // if(h==NULL)
    // {
    //     node *t=allocate();
    //     t->coeff=c;
    //     t->deg=d;
    //     prev->next=t;
    // }
    node *h=p1.c;
    node *t=allocate();
    t->deg=d;
    t->coeff=c;
    insert(t,h);
    cout<<"New polynomial is: ";
    printPoly(p1);
}

node *addremoveterm(Polyn p1, int d)
{
    // node *h=p1.c;
    // node *prev=h;
    // if(h->deg==d)
    // {
    //     p1.c=h->next;
    //     free(h);
    //     return;
    // }
    // h=h->next;
    // while(h!=NULL)
    // {
    //     if(h->deg==d)
    //     {
    //         prev->next=h->next;
    //         free(h);
    //     }
    //     prev=h;
    //     h=h->next;
    // }
    node *h=p1.c;
    node *prev=h;
    if(h->deg==d)
    {
        node *t=h;
        h=h->next;
        p1.c=h;
        prev=h;
        free(t);
        return p1.c;
    }
    while(h!=NULL)
    {
        if(h->deg==d)
        {
            prev->next=h->next;
            free(h);
        }
        prev=h;
        h=h->next;
    }
    cout<<"New polynomial is: ";
    printPoly(p1);
    return p1.c;
}

void addremoveterm(Polyn p1, int a, int b, double eps=1e-9)      //***not able to call it twice
{
    if(eps<1e-9)
    {
        return;
    }
    node *h=p1.c;
    node *prev=h;
    if(h->coeff<eps)
    {
        node *t=h;
        h=h->next;
        p1.c=h;
        prev=h;
        free(t);
    }
    while(h!=NULL)
    {
        if(h->coeff<eps)
        {
            prev->next=h->next;
            node *t=h;
            if(p1.c==h)
            {
                p1.c=p1.c->next;
            }
            h=h->next;
            free(t);
        }
        else
        {
            prev=h;
            h=h->next;
        }
    }
    cout<<"New polynomial is: ";
    printPoly(p1);
}

double evaluate(Polyn p, double x)
{
    node *h=p.c;
    double sum=0;
    while(h!=NULL)
    {
        sum+=h->coeff*pow(x,h->deg);
        h=h->next;
    }
    return sum;
}

Polyn add(Polyn p1, Polyn p2)
{
    Polyn p;
    p.c=allocate();
    node *h1=p1.c;
    node *h2=p2.c;
    node *h=p.c;
    if(h1->deg==h2->deg)
    {
        node *t=allocate();
        t->deg=h1->deg;
        t->coeff=h1->coeff+h2->coeff;
        p.c=t;
        h=t;
        h1=h1->next;
        h2=h2->next;
    }
    else if(h1->deg<h2->deg)
    {
        node *t=allocate();
        t->deg=h1->deg;
        t->coeff=h1->coeff;
        p.c=t;
        h=t;
        h1=h1->next;
    }
    else if(h1->deg>h2->deg)
    {
        node *t=allocate();
        t->deg=h2->deg;
        t->coeff=h2->coeff;
        p.c=t;
        h=t;
        h2=h2->next;
    }
    while(h1!=NULL && h2!=NULL)
    {
        if(h1->deg==h2->deg)
        {
            node *t=allocate();
            t->deg=h1->deg;
            t->coeff=h1->coeff+h2->coeff;
            h->next=t;
            h=h->next;
            h1=h1->next;
            h2=h2->next;
        }
        else if(h1->deg<h2->deg)
        {
            node *t=allocate();
            t->deg=h1->deg;
            t->coeff=h1->coeff;
            h->next=t;
            h=h->next;
            h1=h1->next;
        }
        else if(h1->deg>h2->deg)
        {
            node *t=allocate();
            t->deg=h2->deg;
            t->coeff=h2->coeff;
            h->next=t;
            h=h->next;
            h2=h2->next;
        }
    }
    while(h1!=NULL)
    {
        node *t=allocate();
        t->deg=h1->deg;
        t->coeff=h1->coeff;
        h->next=t;
        h=h->next;
        h1=h1->next;
    }
    while(h2!=NULL)
    {
        node *t=allocate();
        t->deg=h2->deg;
        t->coeff=h2->coeff;
        h->next=t;
        h=h->next;
        h2=h2->next;
    }
    return p;
}

Polyn differentiate(Polyn p)
{
    Polyn p1;
    p1.c=allocate();
    node *h=p.c;
    node *c=p1.c;
    if(h->deg==0)
    {
        h=h->next;
    }
    node *t=allocate();
    t->coeff=h->coeff*h->deg;
    t->deg=h->deg-1;
    p1.c=t;
    c=p1.c;
    h=h->next;
    while(h!=NULL)
    {
        node *t=allocate();
        t->coeff=h->coeff*h->deg;
        t->deg=h->deg-1;
        c->next=t;
        c=c->next;
        h=h->next;
    }
    return p1;
}

double zeroNewton(Polyn p, double x0, double eps=1e-9)
{
    Polyn pd=differentiate(p);
    double x1=x0-(evaluate(p,x0)/evaluate(pd,x0));
    while(abs(x1-x0)>eps)
    {
        x0=x1;
        x1=x0-(evaluate(p,x0)/evaluate(pd,x0));
    }

    return x1;
}

int main()
{   
    int f=1,choice,size=0;
    Polyn polys[MAX];
    while(f)
    {
        cout<<"\n\nWhat would you like to do?\n1)Create a polynomial.\n2)Add/replace a term to a polynomial.\n3)Remove a term of polynomial.\n4)Remove all terms with absolute coefficient values less than some epsilon.\n5)Evaluate a polynomial for some x\n6)Add 2 polynomials.\n7)Differentiate a polynomial.\n8)Calculate a root of polynomial.\n9)Print a polynomial.\n10)Exit.\n\n";
        cin>>choice;
        switch(choice)
        {
            case 1:     //choice to create a polynomial (works perfectly)
            {
                Polyn p;
                p.c=allocate();
                node *prev=p.c,*current=p.c;
                int n;
                cout<<"Enter number of terms in polynomial: ";
                cin>>n;
                cout<<"Enter degree of term and corresponding coefficient: ";
                cin>>current->deg>>current->coeff;
                prev=current;
                for(int i=1;i<n;i++)
                {
                    node *temp=allocate();
                    cout<<"Enter degree of term and corresponding coefficient: ";
                    cin>>temp->deg>>temp->coeff;
                    p.c=insert(temp,p.c);
                    // current->next=temp;
                    // prev=current;
                    // current=current->next;

                }
                cout<<"The polynomial "<<size+1<<" is: \n";
                printPoly(p);
                size++;
                polys[size]=p;
                break;
            }
            case 2:     //ADDS/REPLACES TERM, works perfectly
            {
                Polyn p;
                int c;
                printf("Which polynomial to change?(according to order of insertion)");
                cin>>c;
                p=polys[c];
                int d,coef;
                cout<<"Enter degree and coeff: ";
                cin>>d>>coef;
                addremoveterm(p,d,coef);
                break;
            }
            case 3:     //REMOVE TERM, works perfectly
            {
                Polyn p;
                int c;
                printf("Which polynomial to change?(according to order of insertion)");
                cin>>c;
                p=polys[c];
                int d;
                cout<<"Enter degree: ";
                cin>>d;
                p.c=addremoveterm(p,d);
                break;
            }
            case 4:     //REMOVE ALL <EPSILON, works perfectly
            {
                Polyn p;
                int c;
                printf("Which polynomial to change?(according to order of insertion)");
                cin>>c;
                p=polys[c];
                double eps;
                cout<<"Enter epsilon: ";
                cin>>eps;
                addremoveterm(p,0,0,eps);
                break;
            }
            case 5:     //EVALUATE POLYNOMIAL, works perfectly
            {
                Polyn p;
                int c;
                printf("Which polynomial to evaluate?(according to order of insertion)");
                cin>>c;
                p=polys[c];
                double x;
                cout<<"Enter x: ";
                cin>>x;
                cout<<"The value of the polynomial at x is: "<<evaluate(p,x);
                break;
            }
            case 6:     //ADDS TWO POLYNOMIALS, works perfectly
            {
                Polyn p1,p2;
                int c1,c2;
                printf("Which polynomials to add?(according to order of insertion)");
                cin>>c1>>c2;
                for(int i=1;i<=size;i++)
                {
                    if(i==c1)
                    {
                        p1=polys[i];
                    }
                    if(i==c2)
                    {
                        p2=polys[i];
                    }
                }
                Polyn p3=add(p1,p2);
                cout<<"The polynomial "<<size+1<<" after adding the chosen polynomials is: \n";
                printPoly(p3);
                size++;
                polys[size]=p3;
                break;
            }
            case 7:     //DIFFERENTIATES POLYNOMIAL, works perfectly
            {
                Polyn p;
                int c;
                printf("Which polynomial to differentiate?(according to order of insertion)");
                cin>>c;
                p=polys[c];
                Polyn p1=differentiate(p);
                cout<<"The polynomial "<<size+1<<" after adding the chosen polynomials is: \n";
                printPoly(p1);
                size++;
                polys[size]=p1;
                break;
            }
            case 8:     //FINDS ROOT OF POLYNOMIAL, not working for (x-0.5)^2
            {
                Polyn p;
                int c;
                printf("Which polynomial to find root of?(according to order of insertion)");
                cin>>c;
                p=polys[c];
                double x;
                cout<<"Enter x: ";
                cin>>x;
                cout<<"The root of the polynomial is: "<<zeroNewton(p,x);
                break;
            }
            case 9:     //PRINTS POLYNOMIAL, works perfectly
            {
                int c;
                cout<<"Which polynomial to print?(according to order of insertion)";
                cin>>c;
                printPoly(polys[c]);
                break;
            }
            case 10:     //choice to exit
            {
                f=0;
                break;
            }
        }
    }
    return 0;
}

