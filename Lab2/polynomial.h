/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include "expression.h"

class Polynomial : public Expression {
public:
    
    Polynomial(double arg); //Klar
    Polynomial(const std::vector<double>& arg2); //Klar explicit?
    Polynomial(const Polynomial&) = default;//Copy constructor
    
    ~Polynomial() = default; 
    
    Polynomial* clone() const override;
    
    //Assignment operator
    Polynomial& operator=(const Polynomial&) = default; // P1 = P2;
    
    //an add-and-assignn operators
    Polynomial operator+=(const Polynomial& rhs); // p1+=p2 = p1=p1+p2
    
    //P3 = P1 + P2, addiation of two polynomials
    //we are not using *this, so not a member function, but we need to have access to private coeff
    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
        return (lhs += rhs); //using += operator
    }
    //P3 += P2
    //P3 = P2 + P1
    double operator()(double d) const override;
    double& operator[](int arg);
    double operator[](int arg) const;
    
private:
    std::vector<double> coeff;
    void display(std::ostream& os) const override;
};
