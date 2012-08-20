#include "Globals.h"
#include "MovieGrabberDaemon.h"
#include "MovieLibrary.h"
#include "MoodGenre.h"
#include <QString>


struct MovieLibraryData
{
    QMap<QString,QList<Movie> > movieLib;
    QList<Movie> selectedMovies;
    MovieGrabberDaemon *movieCollection;
    MoodGenre *moodToGenre;
};

bool less(Movie m1,Movie m2)
{
    if(m1.rating < m2.rating)
        return true;
    else if(m1.rating > m2.rating)
        return false;
    else
    {
        if(m1.title.toLower() < m2.title.toLower())
            return true;
        else
            return false;
    }
}


MovieLibrary::MovieLibrary()
{
    d = new MovieLibraryData;
    d->movieCollection = new MovieGrabberDaemon;
}

QList<Movie> MovieLibrary::selectMovies(QString mood)
{
    d->movieLib; // = d->movieCollection->movies();
    QList<QString> moodGenreList = d->moodToGenre->getGenre(mood);

    for(int i=0;i<moodGenreList.count();i++)
    {
        for(int j=0;j<d->movieLib.value(moodGenreList.at(i)).count();j++)
        {
            bool duplicate = false;
            Movie tempMovie = d->movieLib.value(moodGenreList.at(i)).at(j);
            for(int k=0;k<d->selectedMovies.count();k++)
            {
                if(tempMovie.title == d->selectedMovies.at(k).title)
                    duplicate = true;
            }
            if(!duplicate)
                d->selectedMovies.append(tempMovie);
        }
    }



    qSort(d->selectedMovies.begin(),d->selectedMovies.end(), less);



    return d->selectedMovies;
}

MovieLibrary::~MovieLibrary()
{
    delete d;
}









