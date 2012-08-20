/*******************************************************************************
Author : Aneesh Muralidharan
E-Mail : aneesh@thegeek.in
*******************************************************************************/

#ifndef MOVIEGRABBERDAEMON_H
#define MOVIEGRABBERDAEMON_H

#include "Globals.h"

#include <QObject>
#include <QStringList>

struct MovieGrabberDaemonData;
class MovieGrabberDaemon : public QObject
{
    Q_OBJECT
public:
    MovieGrabberDaemon(QObject *parent = 0);
    ~MovieGrabberDaemon();

    void refresh();
    QStringList movieList() const;

    QMap<QString, QList<Movie> > movies() const;

signals:
    void populatingDone();

protected slots:
    void movieInfoUpdated(const QString& url);

protected:
    void populateMovieList();
    void populateMovieInfo();

private:
    MovieGrabberDaemonData* d;
};

#endif // MOVIEGRABBERDAEMON_H
