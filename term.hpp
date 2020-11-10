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
        vector<char> var;
        vector<int> power;
    public:
        Term();
        Term(string t);
        Term(int cons, vector<char> v, vector<int> p);
        int getConstant() const;
        int evaluate(vector<char> var, vector<int> varVal) const;
        vector<char> getVar() const;
        vector<int> getPower() const;
        friend Term operator * (Term const &, Term const &);
};

#endif /* term_hpp */
