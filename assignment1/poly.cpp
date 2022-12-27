// ------------------------------------------------ poly.cpp ----------------------------------------------------------
//
// Jason Chu CSS 343
// Created on 4/1/2022
// Last modification made on 4/8/2022
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To create an abstract data type (ADT) for polynomial Poly.
// --------------------------------------------------------------------------------------------------------------------
// Does not handle data type errors.
// --------------------------------------------------------------------------------------------------------------------

#include "poly.h"

using namespace std;

// --------------------- Overloaded >> --------------------------
// Takes two ints from the console 
// --------------------------------------------------------------
istream &operator>>(istream &in, Poly &sourceCoefficient)
{
    int coefficient;
    int power;

    while (true)
    {
        in >> coefficient >> power;

        if ((coefficient == -1) && (power == -1))
        {
            break;
        }

        sourceCoefficient.setCoeff(coefficient, power);
    }
    return in;
} // end of operator>> overload function

// --------------------- Overloaded << --------------------------
// Outputs the Poly object
// --------------------------------------------------------------
ostream &operator<<(ostream &out, const Poly &sourcePoly)
{
    bool allZeroes = true;
    bool firstPoly = true;

    for (int i = sourcePoly.size - 1; i >= 0; i--) // iterates through the array from the last index
    {
        if (sourcePoly.coeffecientPtr[i] != 0)
        {
            allZeroes = false;

            if (!firstPoly)
            {
                out << " ";
            }
            else
            {
                firstPoly = false;
            }

            if (sourcePoly.coeffecientPtr[i] > 0)
            {
                out << "+";
            }

            out << sourcePoly.coeffecientPtr[i];

            if (i != 0 && i != 1)
            {
                out << "x^" << i;
            }

            if (i == 1)
            {
                out << "x";
            }
        }
    }

    if (allZeroes == false)
    {
        return out;
    }
    else
    {
        return out << "0";
    }
} // end of operator<< overload function

// ------------------ Default constructor------------------------
// Creates Poly object. Setting array size to 1 and value to 0.
// --------------------------------------------------------------
Poly::Poly()
{
    this->size = 1;
    coeffecientPtr = new int[this->size];
    coeffecientPtr[0] = 0;
} // end of default constructor

// --------------- Parameterized constructor --------------------
// Creates Poly object. Sets array size to 1 and value to 
// coefficient.
// --------------------------------------------------------------
Poly::Poly(int coefficient)
{
    this->size = 1;
    coeffecientPtr = new int[this->size];
    coeffecientPtr[0] = coefficient;
} // end of parameterized constructor

// ---------------- Paramaterized Constructor -------------------
// Overloaded constructor that takes two parameters and creates a
// Poly object.
// Array size is set to power + 1. Coefficient is placed to the
// end of the array.
// --------------------------------------------------------------
Poly::Poly(int coefficient, int power)
{
    this->size = power + 1;
    coeffecientPtr = new int[this->size];

    for (int i = 0; i < this->size; i++) // Initializes each element in array to 0
    {
        coeffecientPtr[i] = 0;
    }

    coeffecientPtr[power] = coefficient;
} // end of parameterized constructor

// ------------------ Copy Constructor --------------------------
// Assigns one Poly object value to another Poly object
// --------------------------------------------------------------
Poly::Poly(const Poly &source)
{
    this->size = source.size;
    coeffecientPtr = new int[size];

    for (int i = 0; i < size; i++)
    {
        coeffecientPtr[i] = source.coeffecientPtr[i];
    }
} // end of copy constructor

// --------------------- Destructor -----------------------------
// Deletes array and sets pointer to NULL
// --------------------------------------------------------------
Poly::~Poly()
{
    delete[] coeffecientPtr;
    coeffecientPtr = NULL;
} // end of destructor

// ----------------------- getCoeff -----------------------------
// Getter for Poly object.
// Returns the coefficient only if the power is positive and if
// power is within the array based on size of the array.
// Otherwise, returns 0.
// --------------------------------------------------------------
int Poly::getCoeff(int power) const
{
    if ((power >= 0) && (power < this->size))
    {
        return coeffecientPtr[power];
    }
    else
    {
        return 0;
    }
} // end of getCoeff(int power) function

// ----------------------- setCoeff -----------------------------
// setter for Poly object.
// Sets coefficient in the array based on index power.
// If power exceeds the current array size then create a new temp
// array to fill and replace current array.
// --------------------------------------------------------------
void Poly::setCoeff(int coefficient, int power)
{
    if (power >= 0) // Checks for positive number
    {
        if (power < this->size) // Checks if power is in range
        {
            coeffecientPtr[power] = coefficient;
        }
        else
        {
            int *tempArray = new int[power + 1];

            for (int i = 0; i < this->size; i++)
            {
                tempArray[i] = coeffecientPtr[i]; // Places values from original array to temp array
            }

            for (int j = this->size; j < power + 1; j++) // Fills remaining indexes to 0
            {
                tempArray[j] = 0;
            }

            delete[] coeffecientPtr;    // deletes old array
            coeffecientPtr = NULL;      // set current pointer to NULL
            coeffecientPtr = tempArray; // set pointer to temp array
            tempArray = NULL;           // set temp array pointer to NULL
            this->size = power + 1;     // sets size of the array to the size of temp array
        }
    }
} // end of setCoeff(int coefficient, int power) function

// --------------------- Overloaded + ---------------------------
// Adds two polynomials together
// Returns the sum of two Poly objects
// --------------------------------------------------------------
Poly Poly::operator+(const Poly &p) const
{
    if (this->size > p.size)
    {
        Poly sum(0, this->size);

        for (int i = 0; i < this->size; i++)
        {
            sum.coeffecientPtr[i] = this->coeffecientPtr[i];
        }

        for (int i = 0; i < p.size; i++)
        {
            sum.coeffecientPtr[i] += p.coeffecientPtr[i];
        }

        return sum;
    }
    else
    {
        Poly sum(0, p.size);

        for (int i = 0; i < p.size; i++)
        {
            sum.coeffecientPtr[i] = p.coeffecientPtr[i];
        }

        for (int i = 0; i < this->size; i++)
        {
            sum.coeffecientPtr[i] += this->coeffecientPtr[i];
        }

        return sum;
    }
} // end of overloaded operator+ function

// --------------------- Overloaded - ---------------------------
// Subtracts one polynomial from another
// Returns the difference between two Poly objects
// --------------------------------------------------------------
Poly Poly::operator-(const Poly &p) const
{
    if (this->size > p.size)
    {
        Poly difference(0, this->size);

        for (int i = 0; i < this->size; i++)
        {
            difference.coeffecientPtr[i] = this->coeffecientPtr[i];
        }

        for (int i = 0; i < p.size; i++)
        {
            difference.coeffecientPtr[i] -= p.coeffecientPtr[i];
        }

        return difference;
    }
    else
    {
        Poly difference(0, p.size);

        for (int i = 0; i < p.size; i++)
        {
            difference.coeffecientPtr[i] = this->coeffecientPtr[i];
        }

        for (int i = 0; i < this->size; i++)
        {
            difference.coeffecientPtr[i] -= p.coeffecientPtr[i];
        }

        return difference;
    }

} // end of overloaded operator- function

// --------------------- Overloaded * ---------------------------
// Multiplies two polynomails together
// Returns the product of two Poly objects
// --------------------------------------------------------------
Poly Poly::operator*(const Poly &p) const
{
    int tempInt;
    tempInt = (this->size + p.size - 2);

    Poly tempArray(0, tempInt);

    for (int i = 0; i < this->size; i++)
    {
        if (this->coeffecientPtr[i] != 0)
        {
            for (int j = 0; j < p.size; j++)
            {
                tempArray.coeffecientPtr[i + j] += (this->coeffecientPtr[i] * p.coeffecientPtr[j]);
            }
        }
    }

    return tempArray;
} // end of overloaded operator* function

// --------------------- Overloaded += --------------------------
// Adds two polynomials together and assigns the sum to the left 
// side of the operator
// --------------------------------------------------------------
Poly &Poly::operator+=(const Poly &p)
{
    *this = *this + p;
    return *this;
} // end of overloaded operator+= function

// --------------------- Overloaded -= --------------------------
// Subtracts two polynomials together and assigns the difference
// to the left side of the operator
// --------------------------------------------------------------
Poly &Poly::operator-=(const Poly &p)
{
    *this = *this - p;
    return *this;
} // end of overloaded operator-= function

// --------------------- Overloaded *= --------------------------
// Multiplies two polynomials together and assigns the product
// to the left side of the operator
// --------------------------------------------------------------
Poly &Poly::operator*=(const Poly &p)
{
    *this = *this * p;
    return *this;
} // end of overloaded operator*= function

// --------------------- Overloaded == --------------------------
// Checks two polynomials if they are the same
// Returns true if two polynomials are the same. Otherwise, return false.
// --------------------------------------------------------------
bool Poly::operator==(const Poly &p) const
{
    if (this->size == p.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (coeffecientPtr[i] != p.coeffecientPtr[i])
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        int bigger;
        int smaller;

        if (this->size < p.size)
        {
            smaller = this->size;
            bigger = p.size;

            for (int i = 0; i < smaller; i++)
            {
                if (coeffecientPtr[i] != p.coeffecientPtr[i])
                {
                    return false;
                }
            }

            for (int j = smaller; j < bigger; j++)
            {
                if (p.coeffecientPtr[j] != 0)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            smaller = p.size;
            bigger = this->size;

            for (int i = 0; i < smaller; i++)
            {
                if (coeffecientPtr[i] != p.coeffecientPtr[i])
                {
                    return false;
                }
            }

            for (int j = smaller; j < bigger; j++)
            {
                if (coeffecientPtr != 0)
                {
                    return false;
                }
            }

            return true;
        }
    }

} // end of overloaded operator== function

// --------------------- Overloaded != --------------------------
// Checks two polynomials if they are not the same
// Returns true if two polynomials are different. Otherwise,
// return false.
// --------------------------------------------------------------
bool Poly::operator!=(const Poly &p) const
{
    return !(*this == p); // calls overloaded== function and returns the opposite.
} // end of overloaded operator!= function

// --------------------- Overloaded = ---------------------------
// Assigns one Poly object value to another Poly object
// --------------------------------------------------------------
Poly &Poly::operator=(const Poly &p)
{
    if (this->coeffecientPtr == p.coeffecientPtr)
    {
        return *this;
    }

    if (this->size < p.size)
    {
        delete[] this->coeffecientPtr;
        coeffecientPtr = NULL;
        this->size = p.size;
        this->coeffecientPtr = new int[this->size];

        for (int i = 0; i < this->size; i++)
        {
            this->coeffecientPtr[i] = p.coeffecientPtr[i];
        }
    }

    if (this->size > p.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coeffecientPtr[i] = 0;
        }

        for (int j = 0; j < p.size; j++)
        {
            this->coeffecientPtr[j] = p.coeffecientPtr[j];
        }
    }

    if (this->size == p.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coeffecientPtr[i] = p.coeffecientPtr[i];
        }
    }

    return *this;
} // end of overloaded operator= function