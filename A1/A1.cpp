#include<iostream>

using namespace std;

const int MAX=20;

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
    printf("(%lf)x^%d",h->coeff,h->deg);
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
    cout<<"New polynomial is: ";
    printPoly(p1);
}

void addremoveterm(Polyn p1, int a, int b, double eps)      //***not able to call it twice
{
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

//function to insert node h in sorted list based on degree

int main()
{   
    int f=1,choice,size=0;
    Polyn polys[MAX];
    while(f)
    {
        cout<<"\n\nWhat would you like to do?\n1)Create a polynomial.\n2)Add/replace a term to a polynomial.\n3)Remove a term of polynomial.\n4)Remove all terms with absolute coefficient values less than some epsilon.\n5)Add 2 polynomials.\n6)Differentiate a polynomial.\n6)Calculate a root of polynomial.\n7)Print a polynomial.\n8)Exit.\n\n";
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
            case 3:     //REMOVE TERM, got issues
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
            case 4:     //REMOVE ALL <EPSILON, got issues
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
            case 5:
            {

                break;
            }
            case 6:
            {

                break;
            }
            case 7:     //PRINTS POLYNOMIAL, works perfectly
            {
                int c;
                cout<<"Which polynomial to print?(according to order of insertion)";
                cin>>c;
                printPoly(polys[c]);
                break;
            }
            case 8:     //choice to exit
            {
                f=0;
                break;
            }
        }
    }
    return 0;
}

