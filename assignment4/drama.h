/** drama.h
 * Defines a Drama class that describes a drama movie. Includes functions for
 *movie class *
 * Written by Aditya Duggirala
 *
 */

#ifndef ASSIGNMENT4_DRAMA_H
#define ASSIGNMENT4_DRAMA_H

#include <fstream>
#include "movie.h"
#include <iomanip>

using namespace std;

class Drama:public Movie {

   public:

   //Constructor set to default values
   Drama(int stock, string title, string director, int releaseYear);
   
   //default constructor from Movie
   Drama();
   
   //destructor
   ~Drama();

   string toString() const;

   bool operator<(const Drama &compare) const;

   //Extraction operator overload
   friend std::ostream& operator<<(std::ostream&, const Drama&);
   
};
#endif //ASSIGNMENT4_DRAMA_H
