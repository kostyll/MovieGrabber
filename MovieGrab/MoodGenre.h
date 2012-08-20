#ifndef MOODGENRE_H
#define MOODGENRE_H

#include <QString>
#include <QList>
#include <QMap>



struct moodGenreData;


class MoodGenre
{
public:
    MoodGenre();
    QMap<QString,QList<QString> > getMap();
    QList<QString> genreList();
    QList<QString> getGenre(QString);


    ~MoodGenre();

private:
    moodGenreData* d;

};

#endif // MOODGENRE_H
