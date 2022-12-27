#ifndef CLASSIC_H
#define CLASSIC_H

#include "movie.h"
#include <string>

class Classic : public Movie
{
    public:
        // constructor
        Classic(int stock, std::string title, std::string director, std::string actor, int releaseYear, int monthReleased);

        // destructor
        ~Classic();

        // accessors
        int getMonth() const;
        std::string getActor() const;
        string toString() const;

        // operator overloads
        bool operator==(const Movie &compare) const;
        bool operator>(const Movie &compare) const;
        bool operator<(const Classic &compare) const;

      //Extraction operator overload
      friend std::ostream& operator<<(std::ostream&, const Classic&);

    private:
        int monthReleased;
        std::string actor;
};

#endif //CLASSIC_H
