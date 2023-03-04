#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <iomanip>
#include "rdb.h"

// Record
Record::Record() {} // default constructor

Record::Record(const Record &r) // copy constructor
{
    vector<Attr *> temp;
    for (int i = 0; i < r.attrptr.size(); i++)
    {
        if (r.attrptr[i]->getType() == 1)
        {
            Attr *a = new integerAttribute(*((integerAttribute *)r.attrptr[i]));
            temp.push_back(a);
        }
        else if (r.attrptr[i]->getType() == 2)
        {
            Attr *a = new stringAttribute(*((stringAttribute *)r.attrptr[i]));
            temp.push_back(a);
        }
        else if (r.attrptr[i]->getType() == 3)
        {
            Attr *a = new floatAttribute(*((floatAttribute *)r.attrptr[i]));
            temp.push_back(a);
        }
    }
    attrptr = temp;
}

Record &Record::operator=(const Record &r) // assignment operator
{
    if (this != &r)
    {
        for (auto attr : attrptr)
        {
            delete attr;
        }
        attrptr.clear();
        vector<Attr *> temp;
        for (int i = 0; i < r.attrptr.size(); i++)
        {
            if (r.attrptr[i]->getType() == 1)
            {
                Attr *a = new integerAttribute(*((integerAttribute *)r.attrptr[i]));
                temp.push_back(a);
            }
            else if (r.attrptr[i]->getType() == 2)
            {
                Attr *a = new stringAttribute(*((stringAttribute *)r.attrptr[i]));
                temp.push_back(a);
            }
            else if (r.attrptr[i]->getType() == 3)
            {
                Attr *a = new floatAttribute(*((floatAttribute *)r.attrptr[i]));
                temp.push_back(a);
            }
        }
        attrptr = temp;
    }
    return *this;
}

Record::~Record() // destructor
{
    for (int i = 0; i < attrptr.size(); i++)
    {
        delete attrptr[i];
    }
}

bool Record::operator==(const Record &right) // equality operator
{
    if (attrptr.size() != right.attrptr.size())
    {
        return false;
    }
    for (int i = 0; i < attrptr.size(); i++)
    {
        if (*attrptr[i] != *right.attrptr[i])
        {
            return false;
        }
    }
    return true;
}

vector<Attr *> Record::getAttrptr() const { return attrptr; }

void Record::pushToAttrptr(Attr *a) { attrptr.push_back(a); }

// Relation
Relation::Relation(vector<string> aN) // constructor
{
    attrNames = aN;
}

Relation::Relation(vector<string> aN, vector<int> aI) // constructor
{
    attrNames = aN;
    attrInds = aI;
    nAttr = aN.size();
}

Relation::Relation(const Relation &r) // copy constructor
{
    nAttr = r.nAttr;
    nRecs = r.nRecs;
    attrNames = r.attrNames;
    list<Record *> temprecs;
    for (auto rec : r.recs)
    {
        Record *temp = new Record(*rec);
        temprecs.push_back(temp);
    }
    recs = temprecs;
    attrInds = r.attrInds;
}

Relation &Relation::operator=(const Relation &r) // assignment operator
{
    if (this != &r)
    {
        nAttr = r.nAttr;
        nRecs = r.nRecs;
        attrNames = r.attrNames;
        list<Record *> temprecs;
        for (auto rec : r.recs)
        {
            Record *temp = new Record(*rec);
            temprecs.push_back(temp);
        }
        recs = temprecs;
        attrInds = r.attrInds;
    }
    return *this;
}

Relation::~Relation() // destructor
{
    for (list<Record *>::iterator it = recs.begin(); it != recs.end(); it++)
    {
        delete *it;
    }
}
int Relation::getnAttr() const { return nAttr; }

vector<string> Relation::getAttrNames() const { return attrNames; }

int Relation::doesRecExist(Record *r) // returns 1 if record already exists in given relation, 0 otherwise
{
    int i = 1;
    for (auto &rec : recs)
    {
        if (*rec == *r)
        {
            return 1;
        }
    }
    return 0;
}

void Relation::addRec(Record *r)
{
    Record *temp = new Record(*r);
    recs.push_back(temp);
    nRecs++;
}

vector<int> Relation::getAttrInds() const { return attrInds; }

void Relation::setAttrInds(vector<int> aI, vector<int> bI)
{
    attrInds.clear();
    for (int i = 0; i < aI.size(); i++)
    {
        attrInds.push_back(aI[i]);
    }
    for (int i = 0; i < bI.size(); i++)
    {
        attrInds.push_back(bI[i]);
    }
}

int Relation::getAttrInd(string s) const
{
    int i = 0;
    for (auto &str : attrNames)
    {
        if (str == s)
        {
            break;
        }
        i++;
    }
    return attrInds[i];
}

void Relation::print()
{
    for (int i = 0; i < nAttr * 20 + 2; ++i)
    {
        cout << "-"; // Horizontal Rule
    }
    cout << endl;

    cout << "| ";
    for (auto &attrs : attrNames)
    {
        cout << left << setw(17) << attrs << " | "; // Attribute Names
    }
    cout << endl;

    for (int i = 0; i < nAttr * 20 + 2; ++i)
    {
        cout << "-"; // Horizontal Rule
    }
    cout << endl;

    // Printing the records
    for (list<Record *>::iterator it = recs.begin(); it != recs.end(); ++it)
    {
        Record *rec = *it;
        cout << "| ";
        for (size_t i = 0; i < rec->getAttrptr().size(); ++i)
        {

            if (attrInds[i] == 1)
            {
                integerAttribute *intAttr = dynamic_cast<integerAttribute *>(rec->getAttrptr()[i]);
                cout << right << setw(17) << intAttr->getValue() << " | ";
            }
            else if (attrInds[i] == 2)
            {
                stringAttribute *stringAttr = dynamic_cast<stringAttribute *>(rec->getAttrptr()[i]);
                cout << right << setw(17) << stringAttr->getValue() << " | ";
            }
            else if (attrInds[i] == 3)
            {
                floatAttribute *floatAttr = dynamic_cast<floatAttribute *>(rec->getAttrptr()[i]);
                cout << right << setw(17) << floatAttr->getValue() << " | ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < nAttr * 20 + 2; ++i)
    {
        cout << "-"; // Horizontal Rule
    }
    cout << endl;
}

int isIndexValid(int relInd, vector<int> deletedInds, vector<Relation *> relations)
{
    int f = 1;
    int size = relations.size();
    for (int i = 0; i < deletedInds.size(); i++)
    {
        if (relInd == deletedInds[i])
        {
            f = 0;
            break;
        }
    }
    if ((relInd > size - 1) || (relInd < 0) || !f)
    {
        return 0;
    }
    return 1;
}

int areCompatible(Relation *R1, Relation *R2) // returns 1 if relations are compatible for union/difference, 0 otherwise
{
    if (R1->getnAttr() != R2->getnAttr())
    {
        return 0;
    }
    for (int i = 0; i < R1->getnAttr(); i++)
    {
        if ((R1->getAttrNames()[i] != R2->getAttrNames()[i]) || (R1->getAttrInds()[i] != R2->getAttrInds()[i]))
        {
            return 0;
        }
    }
    return 1;
}

Relation *Union(Relation *R1, Relation *R2) // returns relation with all records in R1 and R2 without repetition
{
    Relation *R3 = new Relation(R1->attrNames);
    R3->nAttr = R1->nAttr;
    R3->attrInds = R1->attrInds;
    for (auto &rec1 : R1->recs)
    {
        R3->addRec(rec1);
    }
    for (auto &rec2 : R2->recs)
    {
        int f = 1;
        for (auto &rec1 : R1->recs)
        {
            if (*rec1 == *rec2) // if record already exists in R1, don't add it to R3
            {
                f = 0;
                break;
            }
        }
        if (f)
        {
            R3->addRec(rec2);
        }
    }
    R3->nRecs = R3->recs.size();
    return R3;
}

Relation *difference(Relation *R1, Relation *R2) // returns relation with records in R1 but not in R2
{
    Relation *R3 = new Relation(R1->attrNames);
    R3->nAttr = R1->nAttr;
    R3->attrInds = R1->attrInds;
    for (auto &rec1 : R1->recs)
    {
        int f = 1;
        for (auto &rec2 : R2->recs) // if a record in R1 exists in R2, don't add it to R3
        {
            if (*rec1 == *rec2)
            {
                f = 0;
                break;
            }
        }
        if (f)
        {
            R3->addRec(rec1);
        }
    }
    R3->nRecs = R3->recs.size();
    return R3;
}

Relation *cartesianproduct(Relation *R1, Relation *R2) // returns cartesian product of two relations
{
    Relation *R3 = new Relation(R1->attrNames);
    R3->nAttr = R1->nAttr + R2->nAttr;
    R3->setAttrInds(R1->attrInds, R2->attrInds);
    for (auto &s : R2->attrNames) // R3 has attributes of R1 and R2 both
    {
        R3->attrNames.push_back(s);
    }
    for (auto &rec1 : R1->recs)
    {
        for (auto &rec2 : R2->recs)
        {
            vector<Attr *> attrptr;
            Record *rec3 = new Record; // create new record with attributes of R1 and R2 both and add to R3
            for (auto &attr1 : rec1->getAttrptr())
            {
                rec3->pushToAttrptr(attr1);
            }
            for (auto &attr2 : rec2->getAttrptr())
            {
                rec3->pushToAttrptr(attr2);
            }
            R3->addRec(rec3);
        }
    }
    R3->nRecs = R3->recs.size();
    return R3;
}

Relation *projection(Relation *R1, list<string> projectattrs) // relation with only attributes in projectattrs
{
    vector<string> attrs;
    vector<int> attrInds;
    for (auto &s : projectattrs)
    {
        attrs.push_back(s);
        attrInds.push_back(R1->getAttrInd(s));
    }
    Relation *R3 = new Relation(attrs);
    R3->nAttr = projectattrs.size();
    R3->attrInds = attrInds;
    for (auto &rec1 : R1->recs)
    {
        vector<Attr *> attrptr;
        Record *rec3 = new Record;
        for (auto &s : projectattrs)
        {
            for (int i = 0; i < R1->nAttr; i++)
            {
                if (s == R1->attrNames[i])
                {
                    rec3->pushToAttrptr(rec1->getAttrptr()[i]); // creat and add records only with attributes in projectattrs to R3
                    break;
                }
            }
        }
        R3->addRec(rec3);
    }
    R3->nRecs = R3->recs.size();
    return R3;
}

int eval(Relation *R, Record *rec, string attrName, char op, Attr *attrptr) // evaluates condition held by the tuple <attrName,op,attrptr> for the record rec
{
    int i1, i2;
    for (i1 = 0; i1 < R->nAttr; i1++)
    {
        if (attrName == R->attrNames[i1])
        {
            break;
        }
    }
    if (op == '=')
    {
        if (*rec->getAttrptr()[i1] == *attrptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (op == '<')
    {
        if (*rec->getAttrptr()[i1] < *attrptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (op == '>')
    {
        if (*rec->getAttrptr()[i1] > *attrptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (op == '!')
    {
        if (*rec->getAttrptr()[i1] != *attrptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

Relation *selection(Relation *R1, DNFformula *f)
{
    Relation *R3 = new Relation(R1->attrNames);
    R3->nAttr = R1->nAttr;
    for (auto &rec1 : R1->recs) // iterating thru recs
    {
        for (auto &l : f->ops) // iterating thru list of list of tuples, l is list of tuples, each tuple in l should be true (AND), and atleast one of the l's should be true (OR)
        {
            int f = 1;
            for (auto &t : l) // iterating thru list of tuples, t is a tuple
            {
                string attrName = get<0>(t);
                char op = get<1>(t);
                Attr *attrptr = get<2>(t);
                if (!eval(R1, rec1, attrName, op, attrptr))
                {
                    f = 0;
                    break;
                }
            }
            if (f)
            {
                R3->addRec(rec1);
                break;
            }
        }
    }
    R3->nRecs = R3->recs.size();
    R3->attrInds = R1->attrInds;
    return R3;
}

void rename(Relation *R1, string s1, string s2) // attribute name changed from s2 to s1
{
    for (int i = 0; i < R1->getnAttr(); i++)
    {
        string s = R1->attrNames[i];
        if (s == s2)
        {
            R1->attrNames[i] = s1;
        }
    }
}