/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <vector>
#include <iomanip>
#include <cmath>


// ADD implementation of the member functions for class Polynomial
Polynomial::Polynomial(const std::vector<double>& arg2) {
    for(double i : arg2){
        coeff.push_back(i);
    }
}
Polynomial::Polynomial(double arg) {
    coeff.push_back(arg);
}

Polynomial* Polynomial::clone() const {
    return new Polynomial(*this);
}

void Polynomial::display(std::ostream& os) const {
    
    for (std::size_t i = 0; i < coeff.size(); i++){
        if(i == 0){
            os << std::fixed << std::setprecision(2) <<coeff[i];
        }
        else if(coeff[i] < 0){
            os << std::fixed << std::setprecision(2) << " - " << abs(coeff[i]) << " * X^" << i;
        }
        else{
            os << std::fixed << std::setprecision(2) << " + " << abs(coeff[i])  << " * X^" << i;
        }
    }
}

Polynomial Polynomial::operator+=(const Polynomial& rhs){
    
    for(std::size_t i = 0; i < rhs.coeff.size(); i++){
        if(i >= coeff.size()){
            coeff.push_back(rhs.coeff[i]); 
        }
        else coeff[i] += rhs.coeff[i];
    }
    return *this;
}

double Polynomial::operator()(double d) const {
    
    double sum{0};
    
    for (std::size_t i = 0; i < coeff.size(); i++){
        if(i==0) sum += coeff[i];
        else {
            sum += coeff[i] * (pow(d, i));
        }
    }
    return sum;
}

double& Polynomial::operator[](int arg){
    return coeff[arg];
}

double Polynomial::operator[](int arg) const{
    return coeff[arg];
}
