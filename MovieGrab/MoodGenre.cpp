#include "MoodGenre.h"
#include "Globals.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QMap>
#include <QString>
#include <QList>

struct moodGenreData
{
    QMap<QString,QList<QString> > map;
    QList<QString> listOfGenre;
};

MoodGenre::MoodGenre()
{
    qDebug() << "this is start ";
    d = new moodGenreData;

    QDomDocument doc("mydocument");
    QFile file("moodGenre.xml");

    qDebug() << file.readAll();

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

 //   qDebug() << "file" << file.readAll();
    doc.setContent(&file);

    file.close();

    QDomElement element = doc.documentElement();
    QDomElement moodE = element.firstChildElement("mood");

    while(!moodE.isNull())
    {
        QDomElement genreE = moodE.firstChildElement("genre");
        QList<QString> genreList;
        while(!genreE.isNull())
        {
            qDebug() << genreE.attributes().namedItem("name").nodeValue() ;
            genreList.append(genreE.attributes().namedItem("name").nodeValue());

            genreE = genreE.nextSiblingElement();
        }
        qDebug() << moodE.attributes().namedItem("name").nodeValue() ;
        d->map.insert(QString(moodE.attributes().namedItem("name").nodeValue()),genreList);
   //     qDebug() << "map has been inserted ";
        moodE = moodE.nextSiblingElement("mood");
     //   d->map[list.at(i).attributes().namedItem("name").nodeValue()] = genList;
    }
}

QMap<QString,QList<QString> > MoodGenre::getMap()
{
    return d->map;
}


QList<QString> MoodGenre::getGenre(QString mood)
{
    return d->map.value(mood);
}

MoodGenre::~MoodGenre()
{
    delete d;
}


QList<QString> MoodGenre::genreList()
{
    d->listOfGenre.append("Action");
    d->listOfGenre.append("Adventure");
    d->listOfGenre.append("Animation");
    d->listOfGenre.append("Biography");
    d->listOfGenre.append("Comedy");
    d->listOfGenre.append("Crime");
    d->listOfGenre.append("Documentry");
    d->listOfGenre.append("Drama");
    d->listOfGenre.append("Family");
    d->listOfGenre.append("Fantasy");
    d->listOfGenre.append("Film-Noir");
    d->listOfGenre.append("Game-Show");
    d->listOfGenre.append("History");
    d->listOfGenre.append("Horror");
    d->listOfGenre.append("Music");
    d->listOfGenre.append("Musical");
    d->listOfGenre.append("Mystery");
    d->listOfGenre.append("News");
    d->listOfGenre.append("Reality-TV");
    d->listOfGenre.append("Romance");
    d->listOfGenre.append("Sci-Fi");
    d->listOfGenre.append("Sport");
    d->listOfGenre.append("Talk-Show");
    d->listOfGenre.append("Thriller");
    d->listOfGenre.append("War");
    d->listOfGenre.append("Western");

    return d->listOfGenre;
}

