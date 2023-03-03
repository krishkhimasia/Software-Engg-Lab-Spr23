//task 2
#include<iostream>
#include<vector>
#include<list>
#include<tuple>
#include"rdb.h"

Relation *naturaljoin(Relation *R1, Relation *R2, list<string> joinattr)
{
    Relation * d2 = new Relation(*R2);
    for(auto &s: joinattr)
    {
        rename(d2, "getRidOf" + s, s);              // d2 is copy of R2 with attributes common to R2 renamed
    }
    Relation * d3 = cartesianproduct(R1, d2);       // d3 is cartesian product of R1 and d2
    DNFformula * f = new DNFformula();
    Relation * d4 = projection(R1, joinattr);       // d4 is projection of R1 on join attributes, used to create DNFformula used for selection
    list <string>::iterator it = joinattr.begin();
    for(auto &rec: d4->recs)
    {
        it = joinattr.begin();
        list<tuple<string, char, Attr*>> clause;
        for(auto &attr: rec->getAttrptr())          // for each record in d4, create a clause for selection (corresponds to the attributes in joinattrs), which is pushed to DNFformula
        {
            clause.push_back(make_tuple(*it, '=', attr));
            clause.push_back(make_tuple("getRidOf"+*it, '=', attr));
            it++;
        }
        f->ops.push_back(clause);
    }
    Relation * d5 = selection(d3, f);           // d5 is selection of d3 on DNFformula
    list <string> finalAttrs;                   // finalAttrs is list of attributes in the natural join
    for (auto &s: R1->attrNames) {
        finalAttrs.push_back(s);
    }
    for (auto &s: R2->attrNames)
    {
        int f=1;
        for(auto &sj: joinattr)
        {
            if (s==sj)
            {
                f=0;
                break;
            }
        }
        if(f)
        {
            finalAttrs.push_back(s);
        }
    }
    Relation * nj = projection(d5, finalAttrs);         // nj is projection of d5 on finalAttrs, which is the natural join
    return nj;
}