//
//  term.hpp
//  mid
//
//  Created by Thang Vu on 10/11/2020.
//  Copyright © 2020 Thang Vu. All rights reserved.
//

#ifndef term_hpp
#define term_hpp

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
class Term
{
    private:
        int constant;
        vector<char> vars;
        vector<int> powers;
    public:
        Term();
        Term(string t);
        Term(int con, vector<char> vs, vector<int> ps);
        int getConstant() const;
        int evaluate(vector<char> vars, vector<int> varVals) const;
        bool simplifiable(Term const &);
        void orderVariable();
        vector<char> getVar() const;
        vector<int> getPower() const;
        Term simplify(Term const &);
        friend Term operator * (Term const &, Term const &);
};

#endif /* term_hpp */
