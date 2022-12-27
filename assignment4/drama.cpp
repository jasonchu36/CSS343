/** drama.h
 * Defines a Drama class that describes a drama movie. Includes functions for
 *movie class *
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_DRAMA_CPP
#define ASSIGNMENT4_DRAMA_CPP

#include <fstream>
#include "movie.h"
#include "drama.h"
#include <iomanip>

using namespace std;


//Constructor set to default values
Drama::Drama(int stock, string title, string director, int releaseYear)
{
   this->movieCode = 'D';
   this->stock = stock;
   this->title = title;
   this->director = director;
   this->releaseYear = releaseYear;
}

//default constructor from Movie
Drama::Drama()
{
   movieCode = 'D';
   stock = 0;
   releaseYear = 0;
   title = "";
   director = "";

}

//destructor
Drama::~Drama()
   = default;


string Drama::toString() const
{
   string str;
   str.push_back(movieCode);
   return director + " " + title + " " + to_string(releaseYear) + " " +
          to_string(stock) + " " + str;
}

bool Drama::operator<(const Drama& compare) const
{
   if(director.compare(compare.getDirector()) < 0)
   {
      return true;
   } else if(director.compare(compare.getDirector()) == 0)
   {
      if(title.compare(compare.getTitle()) < 0)
      {
         return true;
      }
   }
   return false;
}

std::ostream& operator<<(ostream& output, const Drama& movie)
{
   output << movie.toString();
   output << "\n";
   return output;
}

#endif //ASSIGNMENT4_DRAMA_H
