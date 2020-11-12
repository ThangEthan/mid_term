//
//  term.cpp
//  mid
//
//  Created by Thang Vu on 10/11/2020.
//  Copyright © 2020 Thang Vu. All rights reserved.
//

#include "term.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>
#include "helper.hpp"
using namespace std;

Term::Term() {}

Term::Term(string t)
{
    string parse;
    while (!isalpha(t[0])) //until encounter first variable
    {
        parse += t[0];
        t.erase(0, 1);
        if (t == "") //in case term has no variable
            break;
    }
    if (parse == "" || parse == "+")
    {
        this->constant = 1;
    }
    else if (parse == "-")
    {
        this->constant = -1;
    }
    else
    {
        this->constant = stoi(parse);
    }
    /* parsing variable and its power */
    parse = "";
    for (size_t i = 0; i < t.size(); i++)
    {
        if (isalpha(t[i]))
        {
            this->vars.push_back(t[i]);
            if (t[i + 1] == '^') //check if the variable has power
            {
                continue;
            }
            else
            {
                this->powers.push_back(1); //else power of 1
            }
        }
        else if (isnumber(t[i]))
        {
            this->powers.push_back(t[i] - '0'); //acsii code
        }
    }
}

Term::Term(int con, vector<char> vs, vector<int> ps)
{
    this->constant = con;
    this->vars.reserve(vs.size());
    this->vars.insert(this->vars.end(), vs.begin(), vs.end());
    this->powers.reserve(ps.size());
    this->powers.insert(this->powers.end(), ps.begin(), ps.end());
}
bool Term::simplifiable(Term const &t2)
{
    if (this->vars.size() != t2.getVar().size())
    {
        return false;
    }
    else
    {
        vector<pair<char,int> > t1Zipped, t2Zipped;
        vector<char> t1Vars, t2Vars;
        vector<int> t1Powers, t2Powers;
        zip(this->vars, this->powers, t1Zipped);
        zip(t2.getVar(), t2.getPower(), t2Zipped);
        sort(begin(t1Zipped), end(t1Zipped), [&](const auto& a, const auto& b)
            {
                return a.first < b.first;
            }
        );
        sort(begin(t2Zipped), end(t2Zipped), [&](const auto& a, const auto& b)
            {
                return a.first < b.first;
            }
        );
        return t1Zipped == t2Zipped ? true : false;
    }
}
Term Term::simplify(Term const &t2)
{
    int con = this->constant + t2.getConstant();
    vector<char> vars = this->vars;
    vector<int> powers = this->powers;
    return Term(con, vars, powers);
}

Term operator*(Term const &t1, Term const &t2)
{
    vector<char> new_var;
    vector<int> new_power;
    vector<char> common_var;
    vector<char> simplified_var;
    vector<int> simplified_power;

    int new_constant = t1.constant * t2.constant;
    new_var.reserve(t1.vars.size() + t2.vars.size());
    new_power.reserve(t1.powers.size() + t2.powers.size());
    new_var.insert(new_var.end(), t1.vars.begin(), t1.vars.end());
    new_var.insert(new_var.end(), t2.vars.begin(), t2.vars.end());
    new_power.insert(new_power.end(), t1.powers.begin(), t1.powers.end());
    new_power.insert(new_power.end(), t2.powers.begin(), t2.powers.end());
    /* Find common variable and add their power together */
    for (size_t i = 0; i < new_var.size(); i++)
    {
        for (size_t j = i + 1; j < new_var.size(); j++)
        {
            if (new_var[i] == new_var[j]) //found common var
            {
                simplified_var.push_back(new_var[i]);
                simplified_power.push_back(new_power[i] + new_power[j]); //add their power
                common_var.push_back(new_var[i]);                        //save found common var
            }
        }
        if (find(common_var.begin(), common_var.end(), new_var[i]) == common_var.end()) //avoid common var
        {
            simplified_var.push_back(new_var[i]);
            simplified_power.push_back(new_power[i]);
        }
    }
    return Term(new_constant, simplified_var, simplified_power);
}

int Term::getConstant() const
{
    return this->constant;
}

int Term::evaluate(vector<char> var, vector<int> varVal) const
{
    int result = this->constant;
    for (size_t i = 0; i < this->vars.size(); i++)
    {
        result *= pow(varVal[distance(var.begin(), find(var.begin(), var.end(), this->vars[i]))], this->powers[i]); //find the variable's value in given vector
    }
    return result;
}

vector<char> Term::getVar() const
{
    return this->vars;
}

vector<int> Term::getPower() const
{
    return this->powers;
}