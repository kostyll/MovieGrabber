#include "AppFunctionalities.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

AppFunctionalities& AppFunctionalities::instance()
{
    static AppFunctionalities theInstance;
    return theInstance;
}

AppFunctionalities::AppFunctionalities(QObject *parent)
{

}

AppFunctionalities::~AppFunctionalities()
{

}

int AppFunctionalities::grabDesktopWidth()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    return desktopWidget->screenGeometry().width();
}

int AppFunctionalities::grabDesktopHeight()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    return desktopWidget->screenGeometry().height();
}

void AppFunctionalities::showMovieDescription()
{
    qDebug() << "Movie Description";
}
