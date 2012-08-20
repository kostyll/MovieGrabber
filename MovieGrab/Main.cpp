/*******************************************************************************
Author : Aneesh Muralidharan
E-Mail : aneesh@thegeek.in
*******************************************************************************/

#include "MovieGrabberDaemon.h"

#include <QApplication>
#include <QStringList>
#include <QDebug>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MovieGrabberDaemon daemon;
//    qDebug() << daemon.movieList();
//    qDebug() << daemon.movieList().count();

    return app.exec();
}
