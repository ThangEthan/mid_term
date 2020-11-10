//
//  polynomial.cpp
//  mid
//
//  Created by Thang Vu on 10/11/2020.
//  Copyright © 2020 Thang Vu. All rights reserved.
//

#include "polynomial.hpp"
#include "term.hpp"
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

Polynomial::Polynomial() {}

Polynomial::Polynomial(string name)
{
    this->name = name;
    system("clear");
    cout << this->name << ": ";
    /* use system call to make terminal send all keystrokes directly to stdin */
    system("/bin/stty raw");
    while ((c = getchar()) != '.')  //type a period to break out of the loop
    {
        if (c == '^')   //next number will be superscript
        {
            f_r += '^';
            switch ((c = getchar()))
            {
            case '2':
                f += "\u00B2";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '3':
                f += "\u00B3";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '4':
                f += "\u2074";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '5':
                f += "\u2075";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '6':
                f += "\u2076";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '7':
                f += "\u2077";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '8':
                f += "\u2078";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            case '9':
                f += "\u2079";
                f_r += c;
                system("clear");
                cout << this->name << ": " << f;
                break;
            default:
                break;
            }
        }
        else if (c == '`')  //delete
        {
            f.pop_back();
            f_r.pop_back();
            if (f.back() == '\\')
            {
                f.pop_back();
                f_r.pop_back();
            }
            system("clear");
            cout << this->name << ": " << f;
        }
        else
        {
            f += c;
            f_r += c;
            system("clear");
            cout << this->name << ": " << f;
        }
    }
    /* split polynomial into terms */
    string term;
    for (int i = 0; i < f_r.size(); i++)
    {
        if (f_r[i] != '+' && f_r[i] != '-')
        {
            term += f_r[i];
        }
        else
        {
            t.push_back(Term(term));
            term = "";
            term += f_r[i]; //math operator of the next term
        }
    }
    t.push_back(Term(term));
    system("clear");
    /* use system call to set terminal behaviour to more normal behaviour */
    system("/bin/stty cooked");
}

Polynomial::Polynomial(vector<Term> ts)
{
    this->t.reserve(ts.size());
    this->t.insert(t.end(), ts.begin(), ts.end());
}

Polynomial operator*(Polynomial const &f1, Polynomial const &f2)
{
    vector<Term> new_terms;
    for (int i = 0; i < f1.t.size(); i++)
    {
        for (int j = 0; j < f2.t.size(); j++)
        {
            new_terms.push_back(f1.t[i] * f2.t[j]);
        }
    }
    Polynomial new_polynomial(new_terms);
    return new_polynomial;
}

ostream &operator<<(ostream &out, const Polynomial &f)
{
    int count = 0;
    for (int i = 0; i < f.t.size(); i++)
    {
        if (f.t[i].getConstant() < 0)
        {
            out << f.t[i].getConstant();
        }
        else if (f.t[i].getConstant() > 0 && count != 0)
        {
            out << "+" << f.t[i].getConstant(); 
        }
        else
        {
            out << f.t[i].getConstant();
            count = 1; 
        }

        for (int j = 0; j < f.t[i].getVar().size(); j++)
        {
            out << f.t[i].getVar()[j];
            switch (f.t[i].getPower()[j])
            {
            case 2:
                out << "\u00B2";
                break;
            case 3:
                out << "\u00B3";
                break;
            case 4:
                out << "\u2074";
                break;
            case 5:
                out << "\u2075";
                break;
            case 6:
                out << "\u2076";
                break;
            case 7:
                out << "\u2077";
                break;
            case 8:
                out << "\u2078";
                break;
            case 9:
                out << "\u2079";
                break;
            default:
                break;
            }
        }
    }
    return out;
}

int Polynomial::evaluate()
{
    vector<int> varValue;
    vector<char> var;   //hold distinct var in the polynomial
    int num;
    int result=0;
    for (int i = 0; i < this->t.size(); i++)
    {
        for (int j = 0; j < t[i].getVar().size(); j++)
        {
            if (find(var.begin(), var.end(), t[i].getVar()[j]) == var.end())    //found a distinct var
            {
                var.push_back(t[i].getVar()[j]);
                cout << t[i].getVar()[j] << " = ";  //ask for its value
                cin >> num;
                varValue.push_back(num);
            }
        }
    }
    for (int i = 0; i < this->t.size(); i++)
    {
        result += t[i].evaluate(var, varValue); //pass it to each term
    }
    return result;
}