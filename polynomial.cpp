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
        else if (c == ']') //delete
        {
            f.pop_back();
            f_r.pop_back();
            system("clear");
            cout << this->name << ": " << f;
        }
        else if (isalpha(c) || isdigit(c) || c == '-' || c == '+')
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
    for (size_t i = 0; i < f_r.size(); i++)
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
            this->terms.push_back(Term(term));
        }
        f_d.erase(0, pos + deli.length());
    }
    system("clear");
    /* use system call to set terminal behaviour to more normal behaviour */
    system("/bin/stty cooked");
}

Polynomial::Polynomial(vector<Term> ts)
{
    this->terms.reserve(ts.size());
    this->terms.insert(terms.end(), ts.begin(), ts.end());
}

Polynomial operator*(Polynomial const &f1, Polynomial const &f2)
{
    vector<Term> new_terms;

    for (size_t i = 0; i < f1.terms.size(); i++)
    {
        for (size_t j = 0; j < f2.terms.size(); j++)
        {
            new_terms.push_back(f1.terms[i] * f2.terms[j]);
        }
    }
    return Polynomial(new_terms).simplify();
}

Polynomial Polynomial::simplify()
{
    vector<Term> new_simplifiedd_terms;
    vector<int> index;
    Term temp;

    for (size_t i = 0; i < this->terms.size(); i++)
    {
        if (find(index.begin(), index.end(), i) != index.end())
        {
            continue; 
        }
        else
        {
            temp = this->terms[i];
        }
        for (size_t j = i + 1; j < this->terms.size(); j++)
        {
            if (this->terms[i].simplifiable(this->terms[j]))
            {
                index.push_back(j);
                temp = temp.simplify(this->terms[j]);
            }
        }
        if (temp.getConstant() != 0)
        {
            new_simplifiedd_terms.push_back(temp);
        }
    }
    return Polynomial(new_simplifiedd_terms);
}

ostream &operator<<(ostream &out, const Polynomial &f)
{
    for (size_t i = 0; i < f.terms.size(); i++)
    {
        int c = f.terms[i].getConstant();
        if (!f.terms[i].getVar().empty())
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
                        if (i == 0){}
                        else
                        {
                            cout << "+";
                        }
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

        for (size_t j = 0; j < f.terms[i].getVar().size(); j++)
        {
            out << f.terms[i].getVar()[j];
            switch (f.terms[i].getPower()[j])
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
    vector<char> vars; //hold distinct var in the polynomial
    vector<int> varVals;
    int num;
    int result = 0;
    for (size_t i = 0; i < this->terms.size(); i++)
    {
        for (size_t j = 0; j < this->terms[i].getVar().size(); j++)
        {
            if (find(vars.begin(), vars.end(), this->terms[i].getVar()[j]) == vars.end()) //found a distinct var
            {
                vars.push_back(this->terms[i].getVar()[j]);
                cout << this->terms[i].getVar()[j] << " = "; //ask for its value
                cin >> num;
                varVals.push_back(num);
            }
        }
    }
    for (size_t i = 0; i < this->terms.size(); i++)
    {
        result += this->terms[i].evaluate(vars, varVals); //pass it to each term
    }
    cout << "Result: ";
    return result;
}