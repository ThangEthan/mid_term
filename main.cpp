//
//  main.cpp
//  mid
//
//  Created by Thang Vu on 10/11/2020.
//  Copyright © 2020 Thang Vu. All rights reserved.
//

#include <iostream>
#include "polynomial.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    char c;
    system("echo \"              WELCOME TO THE POLYNOMIAL CALCULATOR\n\n--INSTRUCTION--\nSyntax: You can use any character from the alphabet for a variable,\nenter its exponent (2-9) by pressing '^' followed by a number.\nDelete by pressing ']'. To finish entering press '.'.\nEach term in the polynomial should follow this form\n[coefficient][variable][exponent]...\nEx: -3x²y²z\n\n--Press ENTER to continue--\" | cowsay -n -f tux");
    c = getchar();
    Polynomial f1("f1");
    Polynomial f2("f2");
    Polynomial f3 = f1 * f2;

    cout << "f1 * f2 = " << f3 << endl;
    cout << "Evaluate please use integer only" << endl;
    cout << f3.evaluate() << endl;
    return 0;
}
