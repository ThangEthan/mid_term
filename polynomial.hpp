//
//  polynomial.hpp
//  mid
//
//  Created by Thang Vu on 10/11/2020.
//  Copyright © 2020 Thang Vu. All rights reserved.
//

#ifndef polynomial_hpp
#define polynomial_hpp

#include <iostream>
#include <string.h>
#include <vector>
#include "term.hpp"

using namespace std;

class Polynomial
{
    private:
        string name;
        string f; // displaying readable format
        string f_r; // raw input
        char c;
        vector<Term> terms;
    public:
        Polynomial();
        Polynomial(string name);
        Polynomial(vector<Term> ts);
        int evaluate();
    friend Polynomial operator * (Polynomial const &, Polynomial const &);
    friend ostream& operator << (ostream& os, const Polynomial &f);
};
#endif /* polynomial_hpp */
