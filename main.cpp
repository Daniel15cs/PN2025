#include "mainwindow.h"
#include "stackedwidget.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug()<<"start start";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
