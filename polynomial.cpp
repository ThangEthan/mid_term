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
    while ((c = getchar()) != '.') //type a period to break out of the loop
    {
        if (c == '^') //next number will be superscript
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
        else if (c == '`') //delete
        {
            f.pop_back();
            f_r.pop_back();
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
    string deli = ";";
    string f_d;
    string term;
    size_t pos = 0;
    for (int i = 0; i < f_r.size(); i++)
    {
        if (f_r[i] != '+' && f_r[i] != '-')
        {
            f_d += f_r[i];
        }
        else
        {
            f_d += deli;
            f_d += f_r[i];
        }
    }
    f_d += deli;
    while ((pos = f_d.find(";")) != string::npos)
    {
        term = f_d.substr(0, pos);
        if (term != "")
        {
            t.push_back(Term(term));
        }
        f_d.erase(0, pos + deli.length());
    }
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
    return Polynomial(new_terms);
}

ostream &operator<<(ostream &out, const Polynomial &f)
{
    for (int i = 0; i < f.t.size(); i++)
    {
        int c = f.t[i].getConstant();
        if (!f.t[i].getVar().empty())
        {

            if (c > 0)
            {
                if (c != 1 && i == 0)
                {
                    cout << c;
                }
                else
                {
                    if (c == 1)
                    {
                        cout << "+";
                    }
                    else
                    {
                        cout << "+" << c;
                    }
                }
            }
            else
            {
                if (c == -1)
                {
                    out << "-";
                }
                else
                {
                    out << c;
                }
            }
        }
        else 
        {
            if (c > 0)
            {
                if (i == 0)
                {
                    cout << c;
                }
                else
                {
                    cout << "+" << c;
                }
            }
            else
            {
                cout << c;
            }
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
    vector<char> var; //hold distinct var in the polynomial
    int num;
    int result = 0;
    for (int i = 0; i < this->t.size(); i++)
    {
        for (int j = 0; j < t[i].getVar().size(); j++)
        {
            if (find(var.begin(), var.end(), t[i].getVar()[j]) == var.end()) //found a distinct var
            {
                var.push_back(t[i].getVar()[j]);
                cout << t[i].getVar()[j] << " = "; //ask for its value
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