#include<bits/stdc++.h>

using namespace std;

typedef struct _customer{
    int id;
    string name;
    int zip;
    vector <int> pList;
}customer;

typedef struct _prod{
    int id;
    string name;
}prod;

typedef struct _shop{
    int id;
    string name;
    int zip;
    vector <int> prodq(6);
}shop;

typedef struct _agent{
    int id;
    string name;
    int zip;
    int prodDelivered;
}agent;

int main()
{
    vector <customer> custs;
    vector <prod> prods(6);
    vector <shop> shops;
    vector <agent> agents;
    int choice,f=1;
    while (f){
        cout<<"What do you wanna do?"<<endl;
        cout<<"1) Create entity\n2) Delete entity\n3) Print entities\n4) Add some amount of a product to a shop\n5) Place an order\n6) List my purchases\n7) List inventory of shop\n8) Exit\n";
        cin>>choice;
        switch(choice){
            case 1:
            {
                int c;
                cout<<"Enter the type of entity you wish to create:\n1)Customer\n2)Shop\n3)Delivery Agent\n4)Product\n";
                cin>>c;
                switch(c){
                    case 1:
                    {
                        customer cust;
                        cout<<"Enter id: ";
                        cin>>cust.id;
                        cout<<"Enter name: ";
                        cin>>cust.name;
                        cout<<"Enter zipcode: ";
                        cin>>cust.zip;
                        custs.push_back(cust);
                        break;
                    }
                    case 2:
                    {
                        shop s;
                        cout<<"Enter id: ";
                        cin>>s.id;
                        cout<<"Enter name: ";
                        cin>>s.name;
                        cout<<"Enter zipcode: ";
                        cin>>s.zip;
                        for(int i=1;i<6;i++)
                        {
                            cout<<"Enter amount of product "<<i<<": ";
                            cin>>s.prodq[i];
                        }
                        shops.push_back(s);
                        break;
                    }
                    case 3:
                    {
                        agent a;
                        cout<<"Enter id: ";
                        cin>>a.id;
                        cout<<"Enter name: ";
                        cin>>a.name;
                        cout<<"Enter zipcode: ";
                        cin>>a.zip;
                        a.prodDelivered=0;
                        agents.push_back(a);
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                choice c;
                cout<<"Enter the type of entity you wish to delete:\n1)Customer\n2)Shop\n3)Delivery Agent\n4)Product\n";
                cin>>c;
                switch(c){
                    case 1:
                    {
                        int id;;
                        cout<<"Enter id: ";
                        cin>>id;
                        for(auto i = custs.begin(); i<custs.end();i++)
                        {
                            if(i->id==id)
                            {
                                custs.erase(i);
                                break;
                            }
                        }
                    }
                    case 2:
                    {
                        int id;;
                        cout<<"Enter id: ";
                        cin>>id;
                        for(auto i = shops.begin(); i<shops.end();i++)
                        {
                            if(i->id==id)
                            {
                                shops.erase(i);
                                break;
                            }
                        }
                    }
                    case 3:
                    {
                        int id;;
                        cout<<"Enter id: ";
                        cin>>id;
                        for(auto i = agents.begin(); i<agents.end();i++)
                        {
                            if(i->id==id)
                            {
                                agents.erase(i);
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 3:
            {
                cout<<"Customers:\n";
                for(auto &c : custs)
                {
                    printf("id: %d    name: %s\n",c.id,c.name);
                }
                cout<<"\nShops\n";
                for(auto &s : shops)
                {
                    printf("id: %d    name: %s\n",s.id,s.name);
                }
                cout<<"\nAgents\n";
                for(auto &a : agents)
                {
                    printf("id: %d    name: %s\n",s.id,s.name);
                }
                break;
            }
            case 4:
            {
                int id;
                cout<<"Choose shop by entering id:\n"
                for(auto &s : shops)
                {
                    printf("id: %d    name: %s\n",s.id,s.name);
                }
                cin>>id;
                auto it = shops.begin();
                for(it= shops.begin();it<shops.end();it++)
                {
                    if(it->id==id)
                    {
                        break;
                    }
                }
                int p,q;
                cout<<"Enter product id (1-5) and its amount: ";
                cin>>p>>q;
                it->prodq[p]+=q;
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
            case 7:
            {
                int id;
                cout<<"Choose shop by entering id:\n"
                for(auto &s : shops)
                {
                    printf("id: %d    name: %s\n",s.id,s.name);
                }
                cin>>id;
                auto it = shops.begin();
                for(it=shops.begin();it<shops.end();it++)
                {
                    if(it->id==id)
                    {
                        break;
                    }
                }
                for(int i=1;i<6;i++)
                {
                    printf("Product %d: %d",it->)
                }
                break;
            }
            case 8:
            {
                f=0;
                break;
            }
        }
    }
    return 0;
}