//
// Created by zachc on 5/28/2022.
//

#include "customer.h"
#include <string>
#include "comedy.h"
#include "drama.h"
#include "classic.h"

using namespace std;

//Default constructor. Sets ID to 0000, firstName "Default", lastName "Default"
Customer::Customer()
{
   ID = "0000";
   firstName = "Default";
   lastName = "Default";
   numTransactions = 0;
}

Customer::~Customer()
{
   //for(int i = 0; i < MAXHISTORY; i++) {
   //   delete historyMovies[i];
   //}
}

Customer::Customer(string ID, std::string firstName, std::string lastName)
{
   this->ID = ID;
   this->firstName = firstName;
   this->lastName = lastName;
}

//Output the Customer's history to cout in chronological order.
//Format:
//typeOfHistory: movie.toString()
void Customer::outputHistory() const
{
   cout << "ID: " << ID << "\n";
   cout << lastName << ", ";
   cout << firstName;
   cout << "\n";
   for(int i = numTransactions - 1; i >= 0; i--) {
      cout << historyTypes[i];
      cout << ": ";
      cout << historyMovies[i]->toString();
      cout << "\n";
   }
   cout << "\n";
}

void Customer::addHistory(shared_ptr<Movie> movie, std::string type)
{
   if(numTransactions >= MAXHISTORY) {
      cout << "numTransactions cannot exceed MAXHISTORY";
      return;
   }
   //bool hasMovie = false;
   int numTimesBorrowed = 0;
   int numTimesReturned = 0;
   if(type == "return")
   {
      for(int i = 0; i < numTransactions; i++)
      {
         if(historyMovies[i] == movie)
         {
            if(historyTypes[i] == "borrow")
            {
               numTimesBorrowed++;
            } else if(historyTypes[i] == "return")
            {
               numTimesReturned++;
            }
         }
      }
      if(numTimesReturned == numTimesBorrowed) {
         cout << "Cannot return movie that has not been borrowed\n\n";
         return;
      }
   }
   historyMovies[numTransactions] = movie;
   historyTypes[numTransactions] = type;
   numTransactions++;
}

string Customer::getID() const
{
   return ID;
}

string Customer::getFirstName() const
{
   return firstName;
}

string Customer::getLastName() const
{
   return lastName;
}

std::ostream& operator<<(ostream& output, const Customer& customer)
{
   output << "ID: " << customer.ID << "\n";
   output << customer.lastName << " ";
   output << customer.firstName;

   return output;
}


