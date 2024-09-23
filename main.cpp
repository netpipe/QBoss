#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#ifdef __APPLE__
    QPixmap m("/Applications/QBoss.app/Contents/MacOS/Resource/fired.jpg");

        QFile file("/Applications/QBoss.app/Contents/MacOS/Resource/orange.qss");
#else
        QPixmap m("./Resource/fired.jpg");

            QFile file("./Resource/orange.qss");
#endif


        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
    w.setStyleSheet(styleSheet);

QSplashScreen splash(m);
splash.show();


    w.show();
    return a.exec();
}
