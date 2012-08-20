#ifndef APPFUNCTIONALITIES_H
#define APPFUNCTIONALITIES_H

#include <QObject>

class AppFunctionalities : public QObject
{
    Q_OBJECT

public:
    static AppFunctionalities& instance();
    AppFunctionalities(QObject* parent = 0);
    ~AppFunctionalities();

    Q_INVOKABLE void showMovieDescription();
};

#endif // APPFUNCTIONALITIES_H
