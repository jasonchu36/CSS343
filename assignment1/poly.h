// ------------------------------------------------ poly.h ------------------------------------------------------------
//
// Jason Chu CSS 343
// Created on 4/1/2022
// Last modification made on 4/8/2022
// --------------------------------------------------------------------------------------------------------------------
// Purpose - a brief statement of the program's function
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
// --------------------------------------------------------------------------------------------------------------------


#ifndef POLY_H
#define POLY_H

#include <iostream>

using namespace std;

class Poly 
{

    friend istream& operator>>(istream &in, Poly &sourceCoefficient);

    friend ostream& operator<<(ostream &out, const Poly &sourcePoly);

    public:
    // Constructors
    Poly();
    Poly(int coefficient);
    Poly(int coefficient, int power);
    Poly(const Poly &source);

    // Destructor
    ~Poly();

    // Getter and setter
    int getCoeff(int power) const;
    void setCoeff(int coefficient, int power);

    // Overloaded arithmetic operators
    Poly operator+(const Poly &p) const;
    Poly operator-(const Poly &p) const;
    Poly operator*(const Poly &p) const;

    
    Poly& operator+=(const Poly &p);
    Poly& operator-=(const Poly &p);
    Poly& operator*=(const Poly &p);


    bool operator==(const Poly &p) const;
    bool operator!=(const Poly &p) const;

    Poly& operator=(const Poly &p);

    private:
        int* coeffecientPtr; // Pointer to array
        int size; // Size of array
};

#endif //POLY_H