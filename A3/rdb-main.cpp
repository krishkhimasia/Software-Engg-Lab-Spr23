#include<iostream>      //just need to print as proper table
#include<vector>
#include<list>
#include<tuple>
#include<iomanip>
#include"rdb.h"

int main()
{
    vector<Relation *> relations;
    vector<int> deletedInds;
    int choice;
    while (true)
    {
        cout << "Enter your choice?\n1. Create a relation.\n2. Add a record.\n3. Print Relation.\n4. Union of two relations.\n5. Difference of two relations.\n6. Cartesian Product of two relations.\n7. Selection of a relation.\n8. Projection of a relation.\n9. Rename an attribute of a relation.\n10. Natural Join of two relations.\n11. Delete a relation.\n12. Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:         //create relation
        {
            vector<string> attrNames;
            int nAttr;
            cout << "Enter number of attributes: ";
            cin >> nAttr;
            vector<int> type;
            for (int i = 0; i < nAttr; i++)
            {
                cout << "Enter name of attribute " << i + 1 << ": ";
                string s;
                cin >> s;
                attrNames.push_back(s);
                cout << "Enter type of attribute " << i + 1 << "(1 for int, 2 for string, 3 for float): ";
                int x;
                cin >> x;
                type.push_back(x);
            }
            Relation *r = new Relation(attrNames,type);
            relations.push_back(r);
            cout << "Relation "<<relations.size()-1<<" created successfully!\n\n";
            break;
        }
        case 2:         //add record
        {
            int relInd;
            cout << "Enter index of relation: ";
            cin >> relInd;
            if(!isIndexValid(relInd,deletedInds,relations))
            {
                cout<<"Relation "<<relInd<<" does not exist!\n\n";
                break;
            }
            Record *rec = new Record();
            for (int i = 0; i < relations[relInd]->getnAttr(); i++)
            {
                cout << "Enter value for " << relations[relInd]->getAttrNames()[i] << ": ";
                if (relations[relInd]->getAttrInds()[i] == 1)
                {
                    int x;
                    cin >> x;
                    Attr *a = new integerAttribute(x);
                    rec->pushToAttrptr(a);
                }
                else if (relations[relInd]->getAttrInds()[i] == 2)
                {
                    string s;
                    cin >> s;
                    Attr *a = new stringAttribute(s);
                    rec->pushToAttrptr(a);
                }
                else if (relations[relInd]->getAttrInds()[i] == 3)
                {
                    float f;
                    cin >> f;
                    Attr *a = new floatAttribute(f);
                    rec->pushToAttrptr(a);
                }
            }
            if(relations[relInd]->doesRecExist(rec))
            {
                cout<<"Record already exists!\n\n";
                break;
            }
            else
            {
                relations[relInd]->addRec(rec);
                cout << "Record added successfully!\n\n";
            }
            break;
        }
        case 3:         //print relation
        {
            int relInd;
            cout << "Enter index of relation: ";
            cin >> relInd;
            if(!isIndexValid(relInd,deletedInds,relations))
            {
                cout<<"Relation "<<relInd<<" does not exist!\n\n";
                break;
            }
            relations[relInd]->print();
            break;
        }
        case 4:         // union
        {
            Relation *r1, *r2;
            int relInd1, relInd2;
            cout << "Enter index of first relation: ";
            cin >> relInd1;
            cout << "Enter index of second relation: ";
            cin >> relInd2;
            if(!isIndexValid(relInd1,deletedInds,relations))
            {
                cout<<"Relation "<<relInd1<<" does not exist!\n\n";
                break;
            }
            if(!isIndexValid(relInd2,deletedInds,relations))
            {
                cout<<"Relation "<<relInd2<<" does not exist!\n\n";
                break;
            }
            r1 = relations[relInd1];
            r2 = relations[relInd2];
            if(areCompatible(r1,r2))
            {
                Relation *r = Union(r1, r2);
                relations.push_back(r);
                cout<<"Union of relations "<<relInd1<<" and "<<relInd2<<" is relation "<<relations.size()-1<<".\n\n";
            }
            else
            {
                cout<<"Relations are not compatible!\n\n";
            }
            break;
        }
        case 5:         // difference
        {
            Relation *r1, *r2;
            int relInd1, relInd2;
            cout << "Enter index of first relation: ";
            cin >> relInd1;
            cout << "Enter index of second relation: ";
            cin >> relInd2;
            if(!isIndexValid(relInd1,deletedInds,relations))
            {
                cout<<"Relation "<<relInd1<<" does not exist!\n\n";
                break;
            }
            if(!isIndexValid(relInd2,deletedInds,relations))
            {
                cout<<"Relation "<<relInd2<<" does not exist!\n\n";
                break;
            }
            r1 = relations[relInd1];
            r2 = relations[relInd2];
            if(areCompatible(r1,r2))
            {
                Relation *r = difference(r1, r2);
                relations.push_back(r);
                cout<<"Difference of relations "<<relInd1<<" and "<<relInd2<<" is relation "<<relations.size()-1<<".\n\n";
            }
            else
            {
                cout<<"Relations are not compatible!\n\n";
            }
            break;
        }
        case 6:         // cartesian product
        {
            Relation *r1, *r2;
            int relInd1, relInd2;
            cout << "Enter index of first relation: ";
            cin >> relInd1;
            cout << "Enter index of second relation: ";
            cin >> relInd2;
            if(!isIndexValid(relInd1,deletedInds,relations))
            {
                cout<<"Relation "<<relInd1<<" does not exist!\n\n";
                break;
            }
            if(!isIndexValid(relInd2,deletedInds,relations))
            {
                cout<<"Relation "<<relInd2<<" does not exist!\n\n";
                break;
            }
            r1 = relations[relInd1];
            r2 = relations[relInd2];
            Relation *r = cartesianproduct(r1, r2);
            relations.push_back(r);
            cout<<"Cartesian product of relations "<<relInd1<<" and "<<relInd2<<" is relation "<<relations.size()-1<<".\n\n";
            break;
        }
        case 7:         // selection
        {
            Relation *r;
            int relInd;
            cout << "Enter index of relation: ";
            cin >> relInd;
            if(!isIndexValid(relInd,deletedInds,relations))
            {
                cout<<"Relation "<<relInd<<" does not exist!\n\n";
                break;
            }
            r = relations[relInd];
            DNFformula *f;
            f = new DNFformula();
            int n;
            cout << "Enter number of OR clauses: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                list<tuple<string, char, Attr *>> l;
                int m;
                cout << "Enter number of AND clauses in OR clause " << i + 1 << ": ";
                cin >> m;
                for (int j = 0; j < m; j++)
                {
                    string attrName;
                    char op;
                    Attr *a;
                    cout << "Enter attribute name: ";
                    cin >> attrName;
                    cout << "Enter operator: ";
                    cin >> op;
                    cout << "Enter value: ";
                    if (r->getAttrInd(attrName) == 1)
                    {
                        int x;
                        cin >> x;
                        a = new integerAttribute(x);
                    }
                    else if (r->getAttrInd(attrName) == 2)
                    {
                        string s;
                        cin >> s;
                        a = new stringAttribute(s);
                    }
                    else if (r->getAttrInd(attrName) == 3)
                    {
                        float f;
                        cin >> f;
                        a = new floatAttribute(f);
                    }
                    tuple<string, char, Attr *> t(attrName, op, a);
                    l.push_back(t);
                }
                f->ops.push_back(l);
            }
            Relation *r1 = selection(r, f);
            relations.push_back(r1);
            delete f;
            cout<<"Selection of relation "<<relInd<<" is relation "<<relations.size()-1<<".\n\n";
            break;
        }
        case 8:         // projection
        {
            Relation *r;
            int relInd;
            cout << "Enter index of relation: ";
            cin >> relInd;
            if(!isIndexValid(relInd,deletedInds,relations))
            {
                cout<<"Relation "<<relInd<<" does not exist!\n\n";
                break;
            }
            r = relations[relInd];
            list<string> attrNames;
            int n;
            cout << "Enter number of attributes to project: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                string s;
                cout << "Enter attribute name: ";
                cin >> s;
                attrNames.push_back(s);
            }
            Relation *r1 = projection(r, attrNames);
            relations.push_back(r1);
            cout<<"Projection of relation "<<relInd<<" is relation "<<relations.size()-1<<".\n\n";
            break;
        }
        case 9:         // rename
        {
            Relation *r;
            int relInd;
            cout << "Enter index of relation: ";
            cin >> relInd;
            if(!isIndexValid(relInd,deletedInds,relations))
            {
                cout<<"Relation "<<relInd<<" does not exist!\n\n";
                break;
            }
            r = relations[relInd];
            string attr;
            string newName;
            cout << "Enter attribute name to rename: ";
            cin >> attr;
            cout << "Enter new name: ";
            cin >> newName;
            rename(r, newName, attr);
            cout<<"Renamed attribute of relation "<<relInd<<".\n\n";
            break;
        }
        case 10:        // natural join
        {
            Relation *r1, *r2;
            int relInd1, relInd2;
            cout << "Enter index of first relation: ";
            cin >> relInd1;
            cout << "Enter index of second relation: ";
            cin >> relInd2;
            if(!isIndexValid(relInd1,deletedInds,relations))
            {
                cout<<"Relation "<<relInd1<<" does not exist!\n\n";
                break;
            }
            if(!isIndexValid(relInd2,deletedInds,relations))
            {
                cout<<"Relation "<<relInd2<<" does not exist!\n\n";
                break;
            }
            r1 = relations[relInd1];
            r2 = relations[relInd2];
            list<string> joinattr;
            int n;
            cout << "Enter number of attributes to join on: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                string s;
                cout << "Enter attribute name: ";
                cin >> s;
                joinattr.push_back(s);
            }
            Relation *r = naturaljoin(r1, r2, joinattr);
            relations.push_back(r);
            cout<<"Natural join of relations "<<relInd1<<" and "<<relInd2<<" is relation "<<relations.size()-1<<".\n\n";
            break;
        }
        case 11:            //delete a relation
        {
            int relInd;
            cout << "Enter index of relation to delete: ";
            cin >> relInd;
            if(!isIndexValid(relInd,deletedInds,relations))
            {
                cout<<"Relation "<<relInd<<" does not exist!\n\n";
                break;
            }
            delete relations[relInd];
            cout<<"Relation "<<relInd<<" deleted.\n\n";
            deletedInds.push_back(relInd);
            break;
        }
        case 12:            //exit
        {
            cout << "Thanks for using this program!\n";
            for (int i = 0; i < relations.size(); i++)
            {
                int f=1;
                for(int j=0;j<deletedInds.size();j++)
                {
                    if(i==deletedInds[j])
                        f=0;
                }
                if(f)
                    delete relations[i];
            }
            return 0;
        }
        }
    }
    return 0;
}