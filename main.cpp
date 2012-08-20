#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "AppFunctionalities.h"

#include <QDesktopWidget>
#include <QDebug>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/MovieGrabber/main.qml"));
    viewer.showMaximized();

    QDesktopWidget* desktopWidget = QApplication::desktop();
    qDebug() << desktopWidget->screenGeometry().width();
    qDebug() << desktopWidget->screenGeometry().height();

    return app->exec();
}
