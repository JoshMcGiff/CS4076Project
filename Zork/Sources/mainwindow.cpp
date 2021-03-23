#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "MapWidget.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->zork = std::make_shared<Game::Zork>();
    ui->setupUi(this);

    Ui::MapWidget* map = new Ui::MapWidget(this->zork);
    ui->MAP_GRID->addWidget(map, 0, 0, 1, 1);
    
}

MainWindow::~MainWindow()
{
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
    try {
        this->zork->MoveWest();
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_DPAD_RIGHT_clicked() {
    try {
        this->zork->MoveEast();
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_DPAD_DOWN_clicked() {
    try {
        this->zork->MoveSouth();
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}
