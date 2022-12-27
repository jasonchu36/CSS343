#include "classic.h"
#include "movie.h"

Classic::Classic(int stock, string title, string director, string actor,
                 int releaseYear, int monthReleased)
{
   this->movieCode = 'C';
   this->stock = stock;
   this->title = title;
   this->director = director;
   this->actor = actor;
   this->releaseYear = releaseYear;
   this->monthReleased = monthReleased;
}

Classic::~Classic()
= default;

int Classic::getMonth() const
{
   return monthReleased;
}

string Classic::getActor() const
{
   return actor;
}

string Classic::toString() const
{
   string str;
   str.push_back(movieCode);
   return to_string(monthReleased) + " " + to_string(releaseYear) + " " +
          actor + " " + to_string(stock) + " " + director + " " + title +
          " " + str;
}

bool Classic::operator==(const Movie& compare) const
{
   if(monthReleased == compare.getMonth() &&
      releaseYear == compare.getYear() &&
      getActor() == compare.getActor())
   {
      return true;
   } else
   {
      return false;
   }
}

bool Classic::operator>(const Movie& compare) const
{
   if(releaseYear > compare.getYear())
   {
      return true;
   } else if(releaseYear == compare.getYear())
   {
      if(monthReleased > compare.getMonth())
      {
         return true;
      }
   }

   return false;

}

bool Classic::operator<(const Classic& compare) const
{
   if(releaseYear < compare.getYear())
   {
      return true;
   } else if(releaseYear == compare.getYear())
   {    //If release year is the same:
      if(monthReleased < compare.getMonth())
      {
         return true;
      } else if(monthReleased == compare.getMonth())
      {

         return (actor.compare(compare.getActor()) < 0);

      }
   }
   return false;

}

std::ostream& operator<<(ostream& output, const Classic& movie)
{
   output << movie.toString();
   output << "\n";
   return output;
}
