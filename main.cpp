#include "mainwindow.h"
// #include <QFile>

#include <QApplication>
// QFile style(":/style.css");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
