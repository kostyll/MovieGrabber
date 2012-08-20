/*******************************************************************************
Author : Aneesh Muralidharan
E-Mail : aneesh@thegeek.in
*******************************************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QImage>
#include <QStringList>

struct Movie
{
    Movie() :
        rating(0)
    {
    }

    QString title;
    QString plot;
    qreal rating;
    QImage poster;
    QStringList genreList;
};

#endif // GLOBALS_H
