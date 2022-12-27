/**         comedy.h
 *
 * Created by Zachary Clow
 *
 * Defines a Comedy class that inherits from Movie.
 *
 */

#ifndef ASSIGNMENT4_COMEDY_H
#define ASSIGNMENT4_COMEDY_H

#include "movie.h"
#include <string>

class Comedy: public Movie {
public:
   //Default constructor. Defined in Movie.h
   Comedy();
    
   // Destructor
   ~Comedy();

   //Constructor to set default values
   Comedy(int stock, std::string title, std::string director, int releaseYear);

   string toString() const;

   bool operator<(const Comedy &compare) const;

   int getYear() const;

   //Extraction operator overload
   friend std::ostream& operator<<(std::ostream&, const Comedy&);
};

#endif //ASSIGNMENT4_COMEDY_H

