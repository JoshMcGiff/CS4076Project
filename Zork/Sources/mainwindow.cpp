#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->zork = new Game::Zork();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete this->zork;
    delete ui;
}

void MainWindow::on_DPAD_UP_clicked() {
    try {
        this->zork->MoveNorth();
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_DPAD_LEFT_clicked() {
    this->zork->MoveWest();
}

void MainWindow::on_DPAD_RIGHT_clicked() {
    this->zork->MoveEast();
}

void MainWindow::on_DPAD_DOWN_clicked() {
    this->zork->MoveSouth();
}
