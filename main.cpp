#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPixmap m("./Resource/fired.jpg");

        QFile file("./Resource/orange.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
    w.setStyleSheet(styleSheet);

QSplashScreen splash(m);
splash.show();


    w.show();
    return a.exec();
}
