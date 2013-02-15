
#include <QtGui/QApplication>
//#include <QGeoServiceProvider>
#include <qgeoserviceprovider.h>
#include "mappingwidget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    MainWindow mainWindow;
//   mainWindow.setOrientation(MainWindow::ScreenOrientationLockLandscape);
//    mainWindow.showExpanded();

//    mainWindow.initialize();

    MappingWidget mapWidget;
    mapWidget.showMaximized();

    QGeoServiceProvider serviceProvider ("nokia");

    if (serviceProvider.error() == QGeoServiceProvider::NoError)
    {
        mapWidget.initialize(serviceProvider.mappingManager());
    }

    return app.exec();
}
