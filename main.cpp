#include "mainwindow.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QFile cssFile(":/stylesheets/blender.qss");
    if (cssFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug()<<application.styleSheet();
        a.setStyleSheet(cssFile.readAll());
    }

    a.setFont(QFont("Bavaria", 12, 14));
    return a.exec();
}
