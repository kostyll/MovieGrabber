/*******************************************************************************
Author : Aneesh Muralidharan
E-Mail : aneesh@thegeek.in
*******************************************************************************/

#include "MovieGrabberDaemon.h"
#include "JSON.h"

#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QDirIterator>

struct MovieGrabberDaemonData
{
    MovieGrabberDaemonData()
    {
        rottenTomatoAPIKey = "y9smu3eu7w4jyb2ux9csb66k";
        rottenTomatoMListURL = "http://api.rottentomatoes.com/api/public/v1.0/movies.json?apikey=" +
                          rottenTomatoAPIKey +
                          "&q=";
        rottenTomatoMInfoURL = "http://api.rottentomatoes.com/api/public/v1.0/movies/[ID].json?apikey=" +
                               rottenTomatoAPIKey;
        movieUpdaterIndex = 0;
    }

    QString rottenTomatoMListURL;
    QString rottenTomatoMInfoURL;
    QString rottenTomatoAPIKey;
    QStringList movieList;

    QMap<QString, QList<Movie> > movies;
    int movieUpdaterIndex;
};

MovieGrabberDaemon::MovieGrabberDaemon(QObject *parent) :
    QObject(parent)
{
    d = new MovieGrabberDaemonData;

    connect(&JSON::instance(), SIGNAL(parseDone(QString)), this, SLOT(movieInfoUpdated(QString)));

    this->refresh();
}

MovieGrabberDaemon::~MovieGrabberDaemon()
{
    delete d;
}

void MovieGrabberDaemon::refresh()
{
    d->movieUpdaterIndex = 0;
    this->populateMovieList();
}

QStringList MovieGrabberDaemon::movieList() const
{
    return d->movieList;
}

QMap<QString, QList<Movie> > MovieGrabberDaemon::movies() const
{
    return d->movies;
}

void MovieGrabberDaemon::movieInfoUpdated(const QString& url)
{
    // qDebug() << url;
    // qDebug() << JSON::instance().valueCount() << " results found";
    if(JSON::instance().valueCount() == 0)
        return this->populateMovieInfo();

    if(JSON::instance().valueCount() == 1/* &&
            JSON::instance().value(0, "total").isEmpty()*/)
    {
        QString title = JSON::instance().value(1, "title");
        QString criticsRating = JSON::instance().value(1, "critics_score");
        QString criticsConsensus = JSON::instance().value(1, "critics_consensus");
        QString genres = JSON::instance().value(1, "genres");
        QString synopsis = JSON::instance().value(1, "synopsis");
        Movie movie;
        movie.title = title;
        movie.rating = (criticsRating.toInt() > 0) ? criticsRating.toInt() / 10 : 0;
        movie.plot = synopsis + criticsConsensus;

        if(!genres.isEmpty())
        {
            genres.replace('\"', "");
            genres.replace("[", "");
            genres.replace("]", "");

            movie.genreList = genres.split(',');
            Q_FOREACH(QString genre, movie.genreList)
            {
                if(genre.isEmpty())
                    continue;
                if(!d->movies.contains(genre))
                    d->movies.insert(genre, QList<Movie>());
                d->movies[genre].append(movie);
            }
            return this->populateMovieInfo();
        }
    }

    for(int i=0; i<JSON::instance().valueCount(); ++i)
    {
        QString title = JSON::instance().value(i, "title");
        if(title.isEmpty())
            continue;

        // Hopefully here we get the right one
        QString id = JSON::instance().value(i, "id");
        QString url = d->rottenTomatoMInfoURL;
        url.replace("[ID]", id);
        JSON::instance().parse(url);

        return;
    }

    this->populateMovieInfo();
}

void MovieGrabberDaemon::populateMovieList()
{
    qDebug() << "Populating movies STARTED";
    QFileInfoList fList = QDir::drives();
    fList.removeFirst();
    int dirFilters = QDir::Files |
                          QDir::NoDot |
                          QDir::NoDotDot |
                          QDir::NoSymLinks;
    QStringList fileFilters = QStringList() << "*.avi" << "*.mkv" << "*.mp4";
    Q_FOREACH(QFileInfo fi, fList)
    {
        // qDebug() << "In IT";
        QDirIterator dIterator(fi.dir().absolutePath(), fileFilters, (QDir::Filter)dirFilters, QDirIterator::Subdirectories);
        // qDebug() << "Out IT";
        // qDebug() << "In while";
        while(dIterator.hasNext())
        {
            QFileInfo f = dIterator.fileInfo();
            // qDebug() << "SIZE : " << f.size();
            if(f.size() > (600*1024*1024))
                d->movieList << f.fileName();
            dIterator.next();
        }
        // qDebug() << "Out while";
    }
    qDebug() << "Populating movies [DONE]";
    // d->movieList << "dictator.avi" << "IAmNumberFour.avi" << "ThickAsThieves.avi";
    this->populateMovieInfo();
}

void MovieGrabberDaemon::populateMovieInfo()
{
    if(d->movieUpdaterIndex == d->movieList.count())
    {
        qDebug() << "Done";
        emit populatingDone();
        Q_FOREACH(QString genre, d->movies.keys())
        {
            qDebug() << "GENRE : " << genre;
            Q_FOREACH(Movie movie, d->movies.value(genre))
                qDebug() << "---- " << movie.title;
        }

        return;
    }

    // if(d->movieUpdaterIndex < 3)
    {
        QString movieName = d->movieList.at(d->movieUpdaterIndex);
        movieName = movieName.split('.').at(0);
        movieName.replace(' ', '+');
        // qDebug() << "+++Movie++++[" << movieName << "]";
        QString url = d->rottenTomatoMListURL;
        url += movieName;
        JSON::instance().parse(url);
    }
    d->movieUpdaterIndex++;
}
