/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "expression.h"

class Logarithm : public Expression {
    
public:
    Logarithm(); //default creat log2(x)
    Logarithm(const Expression& arg1, double arg2, double arg3, int arg4); //Klar
    Logarithm(const Logarithm& arg1);//Copy constructor
    
    ~Logarithm(); //destructor
    
    Logarithm* clone() const override;
    Logarithm set_base(int arg);
    
    //Assignment operator
    Logarithm& operator=(const Logarithm& rhs); // P1 = P2;
    
    double operator()(double d) const override;
    //bool isRoot(double x) const override;
    
private:
    Expression* E;
    int b;
    double c1,c2;
    
    void display(std::ostream& os) const override;
};
