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
using namespace std;

Term::Term(){}

Term::Term(string t)
{
    string parse;
    while (!isalpha(t[0]))  //until encounter first variable
    {
        parse += t[0];
        t.erase(0,1);
        if (t == "")    //in case term has no variable
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
    for (int i = 0; i < t.size(); i++)
    {
        if (isalpha(t[i]))
        {
            this->var.push_back(t[i]);
            if (t[i+1] == '^')  //check if the variable has power
            {
                continue;
            }
            else
            {
                this->power.push_back(1); //else power of 1
            }
        }
        else if (isnumber(t[i]))
        {
            this->power.push_back(t[i]-'0');    //acsii code
        }
    }
}

Term::Term(int cons, vector<char> v, vector<int> p)
{
    this->constant = cons;
    this->var.reserve(v.size());
    this->var.insert(this->var.end(), v.begin(), v.end());
    this->power.reserve(p.size());
    this->power.insert(this->power.end(), p.begin(), p.end());
}

Term operator * (Term const &t1, Term const &t2)
{
    vector<char> new_var;
    vector<int> new_power;
    vector<char> common_var;
    vector<char> simplified_var;
    vector<int> simplified_power;

    int new_constant = t1.constant * t2.constant;
    new_var.reserve(t1.var.size() + t2.var.size());
    new_power.reserve(t1.power.size() + t2.power.size());
    new_var.insert(new_var.end(), t1.var.begin(), t1.var.end());
    new_var.insert(new_var.end(), t2.var.begin(), t2.var.end());
    new_power.insert(new_power.end(), t1.power.begin(), t1.power.end());
    new_power.insert(new_power.end(), t2.power.begin(), t2.power.end());
    /* Find common variable and add their power together */
    for (int i = 0; i < new_var.size(); i++)    
    {
        for (int j = i+1; j < new_var.size(); j++)
        {
            if (new_var[i] == new_var[j])   //found common var
            {
                simplified_var.push_back(new_var[i]);
                simplified_power.push_back(new_power[i] + new_power[j]);    //add their power
                common_var.push_back(new_var[i]);   //save found common var
            }
        }
        if (find(common_var.begin(), common_var.end(), new_var[i]) == common_var.end())     //avoid common var
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
    for (int i = 0; i < this->var.size(); i++)
    {
        result *= pow(varVal[distance(var.begin(), find(var.begin(), var.end(), this->var[i]))], this->power[i]);   //find the variable's value in given vector
    }
    return result;
}

vector<char> Term::getVar() const
{
    return this->var;
}

vector<int> Term::getPower() const
{
    return this->power;
}