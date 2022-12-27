#include <string>
#include <iostream>
#include <fstream>
#include "customer.h"
#include "hashtable.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
#include "movie.h"
#include <memory>

#include <vector>

#include <algorithm>
#include <sstream>

using namespace std;

void fillCustomerData(ifstream& customerFile, HashTable<Customer>& customers)
{
   char nextLine[100];  //Size doesn't matter much, just needs to be big enough

   std::stringstream stream;

   string ID;
   string firstName;
   string lastName;

   while(!customerFile.eof())
   {
      //Get the next line, up to 100 chars, put in nextLine
      customerFile.getline(nextLine, 100);
      stream << nextLine;
      stream >> ID;
      stream >> lastName;
      stream >> firstName;
      customers.insertItem(ID, new Customer(ID, firstName, lastName));
      stream.clear();
   }
}


string removeSpaces(string input)
{
   string output;
   bool isStart = true;
   for(int i = 0; i < input.length(); i++)
   {
      if(!(isStart && input[i] == ' '))
      {
         isStart = false;
         output += input[i];
      }
   }
   return output;
}

void fillMovieData(ifstream& movieFile, vector<shared_ptr<Comedy>>& comedies,
                   vector<shared_ptr<Drama>>& dramas, vector<shared_ptr<Classic>>& classics)
{

   string token;

   std::stringstream stream;

   char code;
   string stock;
   string director;
   //string directorLastName;
   string title;

   //Everything but Classic year is next
   string year;

   //Only for classic
   string majorActorFirstName;
   string majorActorLastName;
   string month;

   while(!movieFile.eof())
   {
      char nextLine[200];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 999 chars, put in nextLine
      movieFile.getline(nextLine, 200);
      if(movieFile.eof())
      {
         break;
      }
      stream.str(nextLine);

      //string next(nextLine);
      //next.erase(remove(next.begin(), next.end(), ','), next.end());
      std::getline(stream, token, ',');
      token = removeSpaces(token);
      code = token[0];

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      stock = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      director = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      title = token;

      if(code == 'C')
      {
         stream >> majorActorFirstName;
         stream >> majorActorLastName;
         stream >> month;
         stream >> year;

         

         auto thing = shared_ptr<Classic> ( new Classic(stoi(stock), title, director,
                                        majorActorFirstName + " " +
                                        majorActorLastName, stoi(year),
                                        stoi(month)));
         classics.push_back(thing);
         
         
         //classics.push_back(new Classic(stoi(stock), title, director,
         //                               majorActorFirstName + " " +
         //                               majorActorLastName, stoi(year),
          //                              stoi(month)));
      } else if(code == 'F')
      {
         //getline(stream, token, ',');
         //year = token;
         stream >> year;
         auto thing2 = shared_ptr<Comedy> (new Comedy(stoi(stock), title, director, stoi(year)));
         comedies.push_back(thing2);
         
         //comedies
            //.push_back(new Comedy(stoi(stock), title, director, stoi(year)));
      } else if(code == 'D')
      {
         //getline(stream, token, ',');
         //year = token;
         stream >> year;
         auto thing3 = shared_ptr<Drama> (new Drama(stoi(stock), title, director, stoi(year)));
         dramas.push_back(thing3);
         
         //dramas.push_back(new Drama(stoi(stock), title, director, stoi(year)));
      } else
      {
         std::cout << "Invalid movie code in movie file\n\n";
      }
      stream.clear();

   }
   //Sort
   sort(classics.begin(), classics.end(), [](Classic* ptr_l, Classic* ptr_r)
   { return *ptr_l < *ptr_r; });
   sort(dramas.begin(), dramas.end(), [](Drama* ptr_l, Drama* ptr_r)
   { return *ptr_l < *ptr_r; });
   sort(comedies.begin(), comedies.end(), [](Comedy* ptr_l, Comedy* ptr_r)
   { return *ptr_l < *ptr_r; });
}


void outputInventory(vector<shared_ptr<Comedy>>& comedies, vector<shared_ptr<Drama>>& dramas,
                     vector<shared_ptr<Classic>>& classics)
{
   for(shared_ptr<Comedy> c: comedies)
   {
      std::cout << c->getStock() << ": ";
      std::cout << c->getTitle() << ", ";
      std::cout << c->getYear() << " " << c->getMovieCode() << "\n";
      //cout << *c;
   }
   for(shared_ptr<Drama> d: dramas)
   {
      std::cout << d->getStock() << ": ";
      std::cout << d->getDirector() << ", ";
      std::cout << d->getTitle() << " " << d->getMovieCode() << "\n";
      //cout << *d;
   }
   for(shared_ptr<Classic> c: classics)
   {
      std::cout << c->getStock() << ": ";
      std::cout << c->getMonth() << " ";
      std::cout << c->getYear() << ", ";
      std::cout << c->getActor() << " " << c->getMovieCode() << "\n";
      //cout << *c;
   }
   std::cout << "\n";
}

//R [ID] D [movie info]: Return
//B [ID] D [movie info]: Borrow
//I: Output inventory
//H [ID]: Output Customer history
void executeCommands(ifstream& commandFile, HashTable<Customer>& customers,
                     vector<shared_ptr<Comedy>>& comedies, vector<shared_ptr<Drama>>& dramas,
                     vector<shared_ptr<Classic>>& classics)
{
   string token;

   std::stringstream stream;

   char code;
   string stock;
   string director;
   //string directorLastName;
   string title;

   //Everything but Classic year is next
   string year;

   //Only for classic
   string majorActorFirstName;
   string majorActorLastName;
   string month;

   char commandCode;

   char media;

   string ID;

   while(!commandFile.eof())
   {
      stream.clear();
      char nextLine[200];  //Size doesn't matter much, just needs to be big enough

      //Get the next line, up to 999 chars, put in nextLine
      commandFile.getline(nextLine, 200);
      if(commandFile.eof())
      {
         break;
      }
      stream.str(nextLine);

      stream >> commandCode;

      if(commandCode == 'I')
      {
         outputInventory(comedies, dramas, classics);
      } else if(commandCode == 'H')
      {
         stream >> ID;
         customers.retrieve(ID)->outputHistory();
      } else if(commandCode == 'B')
      {
         //Borrow
         stream >> ID;
         stream >> media;
         if(media != 'D')
         {
            std::cout << "Invalid media type\n\n";
            continue;
         }
         stream >> code;
         if(code == 'D')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            director = token;
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            shared_ptr<Drama> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Drama> d: dramas)
            {
               if(d->getDirector() == director && d->getTitle() == title)
               {
                  movie = d;
               }
            }
            if(movie == nullptr) {
               std::cout << "No movie with title ";
               std::cout << title;
               std::cout << "\n\n";
               continue;
            }
            if(!movie->removeStock(1)) {
               std::cout << "Movie not in stock\n\n";
               continue;
            }
            customer = customers.retrieve(ID);
            if(customer == nullptr) {
               std::cout << "No customer with ID ";
               std::cout << ID;
               std::cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "borrow");
         } else if(code == 'C')
         {
            stream >> month;
            stream >> year;
            stream >> majorActorFirstName;
            stream >> majorActorLastName;
            shared_ptr<Classic> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Classic> c: classics)
            {
               if(c->getMonth() == stoi(month) && c->getYear() == stoi(year) &&
                  c->getActor() ==
                  majorActorFirstName + " " + majorActorLastName)
               {
                  movie = c;
               }
            }
            if(movie == nullptr) {
               cout << "No movie with title ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            if(!movie->removeStock(1)) {
               cout << "Movie not in stock\n\n";
               continue;
            }
            customer = customers.retrieve(ID);
            if(customer == nullptr) {
               cout << "No customer with ID ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "borrow");
         } else if(code == 'F')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            stream >> year;
            shared_ptr<Comedy> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Comedy> c : comedies) {
               if(c->getTitle() == title && c->getYear() == stoi(year)) {
                  movie = c;
               }
            }
            if(movie == nullptr) {
               cout << "No movie with title ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            if(!movie->removeStock(1)) {
               cout << "Movie not in stock\n\n";
               continue;
            }
            customer = customers.retrieve(ID);
            if(customer == nullptr) {
               cout << "No customer with ID ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "borrow");
         } else
         {
            cout << "Invalid movie code in command file\n\n";
            continue;
         }

      } else if(commandCode == 'R')
      {
         //Return
         stream >> ID;
         stream >> media;
         if(media != 'D')
         {
            cout << "Invalid media type\n\n";
            continue;
         }
         stream >> code;
         if(code == 'D')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            director = token;
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            shared_ptr<Drama> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Drama> d: dramas)
            {
               if(d->getDirector() == director && d->getTitle() == title)
               {
                  movie = d;
               }
            }
            if(movie == nullptr) {
               cout << "No movie with title ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            movie->addStock(1);
            customer = customers.retrieve(ID);
            if(customer == nullptr) {
               cout << "No customer with ID ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "return");
         } else if(code == 'C')
         {
            stream >> month;
            stream >> year;
            stream >> majorActorFirstName;
            stream >> majorActorLastName;
            shared_ptr<Classic> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Classic> c: classics)
            {
               if(c->getMonth() == stoi(month) && c->getYear() == stoi(year) &&
                  c->getActor() ==
                  majorActorFirstName + " " + majorActorLastName)
               {
                  movie = c;
               }
            }
            if(movie == nullptr) {
               cout << "No movie with title ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            movie->addStock(1);
            customer = customers.retrieve(ID);
            if(customer == nullptr) {
               cout << "No customer with ID ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "return");
         } else if(code == 'F')
         {
            std::getline(stream, token, ',');
            token = removeSpaces(token);
            title = token;
            stream >> year;
            shared_ptr<Comedy> movie = nullptr;
            Customer* customer = nullptr;
            for(shared_ptr<Comedy> c : comedies) {
               if(c->getTitle() == title && c->getYear() == stoi(year)) {
                  movie = c;
               }
            }
            if(movie == nullptr) {
               cout << "No movie with title ";
               cout << title;
               cout << "\n\n";
               continue;
            }
            movie->addStock(1);
            customer = customers.retrieve(ID);
            if(customer == nullptr) {
               cout << "No customer with ID ";
               cout << ID;
               cout << "\n\n";
               continue;
            }
            customer->addHistory(movie, "return");
         } else
         {
            cout << "Invalid movie code in command file\n\n";
            continue;
         }
      } else
      {
         cout << "Invalid command code\n\n";
      }

      /*
      //string next(nextLine);
      //next.erase(remove(next.begin(), next.end(), ','), next.end());
      std::getline(stream, token, ',');
      token = removeSpaces(token);
      code = token[0];

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      stock = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      director = token;

      std::getline(stream, token, ',');
      token = removeSpaces(token);
      title = token;
`     */
      stream.clear();
   }
}


int main()
{
   ifstream customerFile("data4customers.txt");
   ifstream moviesFile("data4movies.txt");
   ifstream transactionsFile("data4commands.txt");

   if(!customerFile)
      cout << "Customer file cannot be opened" << endl;
   if(!moviesFile)
      cout << "Movie file cannot be opened" << endl;
   if(!transactionsFile)
      cout << "Transaction file cannot be opened" << endl;

   HashTable<Customer> customers;

   vector<shared_ptr<Comedy>> comedies;
   vector<shared_ptr<Drama>> dramas;
   vector<shared_ptr<Classic>> classics;

   fillCustomerData(customerFile, customers);
   cout << "\n";
   fillMovieData(moviesFile, comedies, dramas, classics);
   //cout << "\n";
   //customers.printHash();
   executeCommands(transactionsFile, customers, comedies, dramas, classics); 

   return 0;
}