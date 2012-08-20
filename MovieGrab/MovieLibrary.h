
#ifndef MOVIELIBRARY_H
#define MOVIELIBRARY_H
#include "Globals.h"
#include <QString>

struct MovieLibraryData;



class MovieLibrary
{
public:
    MovieLibrary();
    QList<Movie> selectMovies(QString);


   // bool MovieLibrary::less(Movie,Movie);
    ~MovieLibrary();

private:
    MovieLibraryData *d;
};

#endif // MOVIELIBRARY_H
