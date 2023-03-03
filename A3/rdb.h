using namespace std;

class Relation;

class Record;

class Attr
{
public:
    virtual bool operator==(const Attr &right) = 0;
    virtual bool operator!=(const Attr &right) = 0;
    virtual bool operator<=(const Attr &right) = 0;
    virtual bool operator>=(const Attr &right) = 0;
    virtual bool operator<(const Attr &right) = 0;
    virtual bool operator>(const Attr &right) = 0;
    virtual void printValue() = 0;
};

// derived classes of Attr
class integerAttribute : public Attr
{
    int value;

public:
    integerAttribute(int v);
    void setValue(int v);
    int getValue() const;
    void printValue();
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>=(const Attr &right);
    bool operator<(const Attr &right); 
    bool operator>(const Attr &right); 
};

class floatAttribute : public Attr
{
    float value;

public:
    floatAttribute(float v);
    void setValue(float v);
    float getValue() const;
    void printValue();
    bool operator==(const Attr &right); 
    bool operator!=(const Attr &right); 
    bool operator<=(const Attr &right); 
    bool operator>=(const Attr &right); 
    bool operator<(const Attr &right); 
    bool operator>(const Attr &right); 
};

class stringAttribute : public Attr
{
    string value;

public:
    stringAttribute(string v);
    void setValue(string v);
    string getValue() const;
    void printValue();
    bool operator==(const Attr &right);
    bool operator!=(const Attr &right);
    bool operator<=(const Attr &right);
    bool operator>=(const Attr &right);
    bool operator<(const Attr &right);
    bool operator>(const Attr &right);
};

// DNFformula is a list of lists of tuples
struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
};

// Record is a vector of Attr pointers
class Record
{
    vector<Attr *> attrptr;

public:
    Record();
    Record(const Record& r);
    Record& operator=(const Record& r);
    ~Record();
    bool operator==(const Record &right);
    vector<Attr *> getAttrptr() const;
    void pushToAttrptr(Attr *a);
};

// Relation
class Relation
{
    int nAttr, nRecs;
    vector<string> attrNames;
    vector<int> attrInds;
    list<Record *> recs;

public:
    Relation(vector<string> aN);
    Relation(vector<string> aN, vector<int> aI);
    Relation(const Relation &r);
    Relation &operator=(const Relation &r);
    ~Relation();
    int getnAttr() const;
    vector<string> getAttrNames() const;
    int doesRecExist(Record *r);
    void addRec(Record *r);
    vector<int> getAttrInds() const;
    void setAttrInds(vector<int> aI, vector<int> bI);
    int getAttrInd(string s) const;
    void print();
    friend int areCompatible(Relation *R1, Relation *R2);
    friend Relation* Union(Relation *R1, Relation *R2);
    friend Relation* difference(Relation *R1, Relation *R2);
    friend Relation *cartesianproduct(Relation *R1, Relation *R2);
    friend Relation *projection(Relation *R1, list<string> projectattrs);
    friend int eval(Relation *R, Record *rec, string attrName, char op, Attr *attrptr);
    friend Relation *selection(Relation *R1, DNFformula *f);
    friend void rename(Relation *R1, string s1, string s2);
    friend Relation *naturaljoin(Relation *R1, Relation *R2, list<string> joinattr);
};

// basic operations
int areCompatible(Relation *R1, Relation *R2);
Relation* Union(Relation *R1, Relation *R2);
Relation* difference(Relation *R1, Relation *R2);
Relation *cartesianproduct(Relation *R1, Relation *R2);
Relation *projection(Relation *R1, list<string> projectattrs);
int eval(Relation *R, Record *rec, string attrName, char op, Attr *attrptr);
Relation *selection(Relation *R1, DNFformula *f);
void rename(Relation *R1, string s1, string s2);
Relation *naturaljoin(Relation *R1, Relation *R2, list<string> joinattr);