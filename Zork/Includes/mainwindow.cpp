#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DPAD_UP_clicked()
{
    
}

void MainWindow::on_DPAD_LEFT_clicked()
{

}

void MainWindow::on_DPAD_RIGHT_clicked()
{

}

void MainWindow::on_DPAD_DOWN_clicked()
{

}
