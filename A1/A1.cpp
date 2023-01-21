#include<iostream>      //need to check for negative polynomials
#include<cmath>

using namespace std;

const int MAX=100;
const int fail=-1e9;

typedef struct _node{
    int deg;
    double coeff;
    struct _node *next;
}node;

node *allocate()        //allocates memory for a new node
{
    node *head = new node;
    head->next=NULL;
    return head;
}

typedef struct{
    node *c;
}Polyn;


node *insert(node *h, node *head)       //code to insert node in sorted order based on degree of term
{
    node *prev=head;
    node *current=head->next;
    if(prev->deg>h->deg)        //if degree of new term if less than degree of first term, head is changed
    {
        h->next=prev;
        head=h;
        return head;
    }
    while(current!=NULL)        //loop though nodes and insert new node in sorted order
    {
        if(current->deg>h->deg)
        {
            prev->next=h;
            h->next=current;
            break;
        }
        else if(current->deg==h->deg)
        {
            current->coeff+=h->coeff;
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


Polyn createPoly()      //creates polynomial according to user input
{
    Polyn p;
    p.c=allocate();
    node *prev=p.c,*current=p.c;
    int n;
    cout<<"Enter number of terms in polynomial: ";
    cin>>n;
    cout<<"Enter "<<n<<" pairs of degree of term (power of x) and corresponding coefficient: \n";
    cin>>current->deg>>current->coeff;
    prev=current;
    for(int i=1;i<n;i++)
    {
        node *temp=allocate();
        cin>>temp->deg>>temp->coeff;
        p.c=insert(temp,p.c);
    }
    return p;
}


void printPoly(Polyn p)     //prints chosen polynomial
{
    node *h=p.c;
    if(h->deg!=0)
    {
        printf("(%lf)x^%d",h->coeff,h->deg);
    }
    else
    {
        printf("(%lf)",h->coeff);
    }
    h=h->next;
    while(h!=NULL)
    {
        printf("+(%lf)x^%d",h->coeff,h->deg);
        h=h->next;
    }
}


void printAllPolys(Polyn polys[], int size)     //lists all the polynomials present in polys[]
{
    if(size)
    {
        for(int i=1;i<=size;i++)
        {
            cout<<i<<": ";
            printPoly(polys[i]);
            cout<<endl;
        }
    }
    else
    {
        cout<<"No polynomials present.\n";
    }
}

void deletePoly(Polyn polys[], int &size)        //deletes chosen polynomial from polys[]
{
    int c;
    printf("Which polynomial to delete?\n");
    printAllPolys(polys,size);
    cout<<"Enter your choice: ";
    cin>>c;
    for(int i=c;i<size;i++)
    {
        polys[i]=polys[i+1];
    }
    size--;
    cout<<"Polynomial deleted.\n";
}



void addremoveterm(Polyn &p1, int d, double c)       //adds new term of chosen degree 'd' and coeff 'c' to polynomial 'p1'
{
    node *h=p1.c;
    node *t=allocate();
    t->deg=d;
    t->coeff=c;
    p1.c=insert(t,h);       //inserts new term in sorted order
    cout<<"New polynomial is: ";
    printPoly(p1);
}

void addremoveterm(Polyn &p1, int d)        //removes term of chosen degree 'd' from polynomial 'p1'
{
    node *h=p1.c;
    node *prev=h;
    if(h->deg==d)       //if first term has degree 'd', then it is removed and head is changed to next element
    {
        node *t=h;
        h=h->next;
        p1.c=h;
        prev=h;
        free(t);
    }
    while(h!=NULL)      //if any other term has degree 'd', then it is removed
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
}

void addremoveterm(Polyn &p1, int a, int b, double eps)      //removes all terms in p1 with |coeff| < eps
{
    node *h=p1.c;
    node *prev=h;
    if(abs(h->coeff)<eps)
    {
        node *t=h;
        h=h->next;
        p1.c=h;
        prev=h;
        free(t);
    }
    while(h!=NULL)
    {
        if(abs(h->coeff)<eps)
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

double evaluate(Polyn p, double x)      //evaluates value of polynomial 'p' at given 'x'
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

Polyn add(Polyn p1, Polyn p2)       //adds polynomials 'p1' and 'p2'
{
    Polyn p;
    p.c=allocate();
    node *h1=p1.c;
    node *h2=p2.c;
    node *h=p.c;
    if(h1->deg==h2->deg)        //add coeffs of terms with same degree
    {
        node *t=allocate();
        t->deg=h1->deg;
        t->coeff=h1->coeff+h2->coeff;
        p.c=t;
        h=t;
        h1=h1->next;
        h2=h2->next;
    }
    else if(h1->deg<h2->deg)        //add term with degree only in p1
    {
        node *t=allocate();
        t->deg=h1->deg;
        t->coeff=h1->coeff;
        p.c=t;
        h=t;
        h1=h1->next;
    }
    else if(h1->deg>h2->deg)        //add term with degree only in p2
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
        if(h1->deg==h2->deg)        //add coeffs of terms with same degree
        {
            node *t=allocate();
            t->deg=h1->deg;
            t->coeff=h1->coeff+h2->coeff;
            h->next=t;
            h=h->next;
            h1=h1->next;
            h2=h2->next;
        }
        else if(h1->deg<h2->deg)        //add term with degree only in p1
        {
            node *t=allocate();
            t->deg=h1->deg;
            t->coeff=h1->coeff;
            h->next=t;
            h=h->next;
            h1=h1->next;
        }
        else if(h1->deg>h2->deg)        //add term with degree only in p2
        {
            node *t=allocate();
            t->deg=h2->deg;
            t->coeff=h2->coeff;
            h->next=t;
            h=h->next;
            h2=h2->next;
        }
    }
    while(h1!=NULL)         //add remaining terms in p1
    {
        node *t=allocate();
        t->deg=h1->deg;
        t->coeff=h1->coeff;
        h->next=t;
        h=h->next;
        h1=h1->next;
    }
    while(h2!=NULL)         //add remaining terms in p2
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

Polyn differentiate(Polyn p)        //differentiates polynomial 'p'
{
    Polyn p1;
    p1.c=allocate();
    node *h=p.c;
    node *c=p1.c;
    node *te=h;
    int cnt=0;
    while(te!=NULL)
    {
        cnt++;
        te=te->next;
    }
    if(cnt==1 && h->deg==0)      //if only constant term is present
    {
        node *temp=allocate();
        temp->coeff=0;
        temp->deg=0;
        p1.c=temp;
        return p1;
    }
    else
    {
        if(h->deg==0)
        {
            h=h->next;
        }
        node *t=allocate();
        t->coeff=h->coeff*h->deg;       //standard differentiation
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
    }
    return p1;
}

double zeroNewton(Polyn p, double x0, double eps=1e-9)      //finds root of polynomial 'p' using Newton's method
{
    Polyn pd=differentiate(p);
    if(evaluate(p,x0)==0)
    {
        return x0;
    }
    if(evaluate(pd,x0)==0)      //newtons method wont work
    {
        return fail;
    }
    double x1=x0-(evaluate(p,x0)/evaluate(pd,x0));
    while(abs(x1-x0)>eps)
    {
        x0=x1;
        if(evaluate(p,x0)==0)
        {
            return x0;
        }
        if(evaluate(pd,x0)==0)      //newtons method wont work
        {
            return fail;
        }
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
        cout<<"\n\nWhat would you like to do?\n1)Create a polynomial.\n2)Delete a polynomial.\n3)Add a term to a polynomial.\n4)Remove a term of polynomial.\n5)Remove all terms with absolute coefficient values less than some epsilon.\n6)Evaluate a polynomial for some x\n7)Add 2 polynomials.\n8)Differentiate a polynomial.\n9)Calculate a root of polynomial.\n10)Print all polynomials.\n11)Exit.\n\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:     //choice to create a polynomial
            {
                Polyn p=createPoly();
                cout<<"Polynomial "<<size+1<<" is: \n";
                printPoly(p);
                size++;
                polys[size]=p;
                break;
            }
            case 2:     //DELETE POLYNOMIAL
            {
                if(size)
                deletePoly(polys,size);
                else
                cout<<"No polynomials to delete.\n";
                break;
            }
            case 3:     //ADDS TERM
            {
                int c;
                printf("Add a new term to which polynomial?\n");
                printAllPolys(polys,size);
                cout<<"Enter your choice: ";
                cin>>c;
                Polyn &p=polys[c];
                int d,coef;
                cout<<"Enter degree and coeff: ";
                cin>>d>>coef;
                addremoveterm(p,d,coef);
                break;
            }
            case 4:     //REMOVES TERM
            {
                int c;
                printf("Remove a term from which polynomial?\n");
                printAllPolys(polys,size);
                cout<<"Enter your choice: ";
                cin>>c;
                Polyn &p=polys[c];
                int d;
                cout<<"Enter degree: ";
                cin>>d;
                addremoveterm(p,d);
                break;
            }
            case 5:     //REMOVE ALL TERMS WITH COEFF<EPSILON
            {
                int c;
                printf("Which polynomial to change?\n");
                printAllPolys(polys,size);
                cout<<"Enter your choice: ";
                cin>>c;
                Polyn &p=polys[c];
                double eps;
                cout<<"Enter epsilon: ";
                cin>>eps;
                addremoveterm(p,0,0,eps);
                break;
            }
            case 6:     //EVALUATE POLYNOMIAL
            {
                Polyn p;
                int c;
                printf("Evaluate which polynomial?\n");
                printAllPolys(polys,size);
                cout<<"Enter your choice: ";
                cin>>c;
                p=polys[c];
                double x;
                cout<<"Enter x: ";
                cin>>x;
                cout<<"The value of the polynomial at x is: "<<evaluate(p,x);
                break;
            }
            case 7:     //ADDS TWO POLYNOMIALS
            {
                Polyn p1,p2;
                int c1,c2;
                printf("Choose the polynomials that you wish to add.\n");
                printAllPolys(polys,size);
                cout<<"Enter your choices: ";
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
                cout<<"Polynomial "<<size+1<<" after adding the chosen polynomials is: \n";
                printPoly(p3);
                size++;
                polys[size]=p3;
                break;
            }
            case 8:     //DIFFERENTIATES POLYNOMIAL
            {
                Polyn p;
                int c;
                printf("Choose the polynomial that you wish to differentiate.\n");
                printAllPolys(polys,size);
                cout<<"Enter your choice: ";
                cin>>c;
                p=polys[c];
                Polyn p1=differentiate(p);
                cout<<"The polynomial "<<size+1<<" after differentiating the chosen polynomials is: \n";
                printPoly(p1);
                size++;
                polys[size]=p1;
                break;
            }
            case 9:     //FINDS ROOT OF POLYNOMIAL
            {
                Polyn p;
                int c;
                printf("Which polynomial to find root of?:\n");
                printAllPolys(polys,size);
                cin>>c;
                p=polys[c];
                double x;
                cout<<"Enter initial guess (x0): ";
                cin>>x;
                double root=zeroNewton(p,x);
                if(root!=fail)
                cout<<"The root of the polynomial is: "<<root;
                else
                cout<<"The root could not be found using Newton's method.\n";
                break;
            }
            case 10:     //PRINTS ALL POLYNOMIALS
            {
                cout<<"List of all polynomials:\n";
                printAllPolys(polys,size);
                break;
            }
            case 11:     //EXIT
            {
                f=0;
                cout<<"\nThank you for using the program!\n";
                break;
            }
        }
    }
    return 0;
}