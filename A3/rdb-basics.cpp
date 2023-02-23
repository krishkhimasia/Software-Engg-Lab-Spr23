//task 1
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Attr{

    public: virtual bool operator==(const Attr& right) = 0;
};

class Record{
    vector <Attr*> attrptr;

};

class Relation{
    int nattr, nrecs;
    vector <string> attrinds;
    list <Record*> recs;
};