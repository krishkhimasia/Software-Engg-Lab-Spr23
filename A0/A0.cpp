#include<bits/stdc++.h>

using namespace std;

const int maxProd=6;

typedef struct _customer{
    int id;
    string name;
    int zip;
    vector <pair<int,int>> pList;
}customer;

typedef struct _prod{
    int id;
    string name;
}prod;

typedef struct _shop{
    int id;
    string name;
    int zip;
    vector <int> prodq;
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
        cout<<"1) Create entity\n2) Delete entity\n3) Print entities\n4) Add some amount of a product to a shop\n5) Place an order\n6) List my purchases\n7) List inventory of shop\n8) Exit\n\n";
        cin>>choice;
        switch(choice){
            case 1:
            {
                int c;
                cout<<"Enter the type of entity you wish to create:\n1)Customer\n2)Shop\n3)Delivery Agent\n\n";
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
                        s.prodq.resize(6);
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
                cout<<"Entity Created Successfully\n\n";
                break;
            }
            case 2:
            {
                cout<<"List of entities:\n";
                cout<<"Customers:\n";
                if(!custs.size())
                {
                    cout<<"No customers\n";
                }
                else
                {
                    for(auto &c : custs)
                    {
                        printf("id: %d    name: ",c.id);
                        cout<<c.name<<endl;
                    }
                }
                cout<<"\nShops:\n";
                if(!shops.size())
                {
                    cout<<"No shops\n";
                }
                else
                {
                    for(auto &s : shops)
                    {
                        printf("id: %d    name: ",s.id);
                        cout<<s.name<<endl;
                    }
                }
                cout<<"\nAgents:\n";
                if(!agents.size())
                {
                    cout<<"No agents\n";
                }
                else
                {
                for(auto &a : agents)
                    {
                        printf("id: %d    name: ",a.id);
                        cout<<a.name<<endl;
                    }
                }
                cout<<endl;
                int c,f=0;
                cout<<"Enter the type of entity you wish to delete:\n1)Customer\n2)Shop\n3)Delivery Agent\n4)Product\n\n";
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
                                f=1;
                                custs.erase(i);
                                break;
                            }
                        }
                        break;
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
                                f=1;
                                shops.erase(i);
                                break;
                            }
                        }
                        break;
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
                                f=1;
                                agents.erase(i);
                                break;
                            }
                        }
                        break;
                    }
                }
                if(f)
                cout<<"Deleted Successfully\n\n";
                else
                cout<<"Entity doesn't exist anyway\n\n";
                break;
            }
            case 3:
            {
                cout<<"Customers:\n";
                if(!custs.size())
                {
                    cout<<"No customers\n";
                }
                else
                {
                    for(auto &c : custs)
                    {
                        printf("id: %d    name: ",c.id);
                        cout<<c.name<<endl;
                    }
                }
                cout<<"\nShops:\n";
                if(!shops.size())
                {
                    cout<<"No shops\n";
                }
                else
                {
                    for(auto &s : shops)
                    {
                        printf("id: %d    name: ",s.id);
                        cout<<s.name<<endl;
                    }
                }
                cout<<"\nAgents:\n";
                if(!agents.size())
                {
                    cout<<"No agents\n";
                }
                else
                {
                for(auto &a : agents)
                    {
                        printf("id: %d    name: ",a.id);
                        cout<<a.name<<endl;
                    }
                }
                cout<<endl;
                break;
            }
            case 4:
            {
                int id;
                cout<<"Choose shop by entering id:\n";
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
                int cid,pid,q,zip,f=0;
                shop valids;
                agent valida;
                customer cust;
                cout<<"Enter your customer id: ";
                cin>>cid;
                for(auto &c: custs)
                {
                    if(c.id==cid)
                    {
                        cust=c;
                        break;
                    }
                }
                cout<<"Enter the product id (1-5) and quantity required of the same: ";
                cin>>pid>>q;
                for(auto &s: shops)
                {
                    if(s.zip==cust.zip)
                    {
                        if(q<=s.prodq[pid])
                        {
                            valids=s;
                            f=1;
                            s.prodq[pid]-=q;
                            break;
                        }
                    }
                }
                for(auto &a: agents)
                {
                    if(a.zip==cust.zip)
                    {
                        valida=a;
                        if(f==1)
                        {
                            f=2;
                        }
                        break;
                    }
                }
                if(f==0)
                {
                    cout<<"No shop in your area can meet your requirements.\n";
                }
                else if(f==1)
                {
                    cout<<"No delivery agent available.\n";
                }
                else
                {
                    cust.pList.push_back({pid,q});
                    cout<<"Order placed successfully.\n";
                }
                break;
            }
            case 6:
            {
                int cid;
                customer cust;
                cout<<"Enter your customer id: ";
                cin>>cid;
                for(auto &c: custs)
                {
                    if(c.id==cid)
                    {
                        cust=c;
                        break;
                    }
                }
                if(cust.pList.size())
                {
                    cout<<"List of purchases:\n";
                    for(auto &p:cust.pList)
                    {
                        cout<<"Product "<<p.first<<": "<<p.second<<endl;
                    }
                }
                else
                {
                    cout<<"No purchase made.\n\n";
                }
                break;
            }
            case 7:
            {
                int id;
                cout<<"Choose shop by entering id:\n";
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
                    printf("Product %d: %d\n",i,it->prodq[i]);
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