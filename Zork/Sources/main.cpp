#include "ui_mainwindow.h"

#include <QApplication>
#include "mainwindow.h"
#include "Zork.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //Game::Zork zork;

    return 0;
}
