/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <cmath>
#include <iomanip>

// Default constructor
Logarithm::Logarithm() {
    c1 = 0.0; c2 = 1.0; b = 2;
    std::vector<double> coeff{0,1};
    E = new Polynomial{coeff};
}

//Constructor for log expression
Logarithm::Logarithm(const Expression& arg1, double arg2, double arg3, int arg4) {
    E = arg1.clone(); 
    c1 = arg2; c2 = arg3; b = arg4;
}

//Copy constructor
Logarithm::Logarithm(const Logarithm& arg1) {
    c1 = arg1.c1; c2 = arg1.c2; b = arg1.b;
    E = arg1.E -> clone();
}

//Destructor
Logarithm::~Logarithm(){
    delete E;
    E = nullptr;
    b = 0; c1 = 0; c2 = 0;
}

//Clone Logarithm
Logarithm* Logarithm::clone() const{
    return new Logarithm(*this);
}

//Set log base
Logarithm Logarithm::set_base(int arg) {
    b = arg;
    return *this;
}

Logarithm& Logarithm::operator=(const Logarithm& rhs) {
    b = rhs.b; c1 = rhs.c1; c2 = rhs.c2;
    delete E;
    E = rhs.E->clone();
    
    return *this;
}

//Display logarithm
void Logarithm::display(std::ostream& os) const {
    
    std::string s = " + ";
    if(c2 < 0) s = " - ";
    
    os << std::fixed << std::setprecision(2) << c1 << s << abs(c2) << " * Log_" << abs(b) << "( " << *E << " )";
}

//Oklart
double Logarithm::operator()(double d) const {
    double sum{0};
    double e = E -> operator()(d);
    
    sum += c1 + (c2 * (log(e)/log(b)));
    
    return sum;
}

//bool Logarithm::isRoot(double x) const {
//    return (operator()(x) == 0);
//}
