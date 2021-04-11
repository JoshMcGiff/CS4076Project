#include "ui_mainwindow.h"

#include <QApplication>
#include "mainwindow.h"
#include "Zork.hpp"

int main(int argc, char *argv[]) //main entrypoint
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show(); //show main window
    return a.exec();

    return 0;
}
