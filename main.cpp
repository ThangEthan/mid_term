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

    Polynomial f1("f1");
    Polynomial f2("f2");
    Polynomial f3 = f1 * f2;

    cout << "f1 * f2 = " << f3 << endl;
    cout << f3.evaluate() << endl;
    return 0;
}
