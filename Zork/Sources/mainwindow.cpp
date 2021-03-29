#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "MapWidget.hpp"
#include "Zork.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->zork = std::make_shared<Game::Zork>();
    ui->setupUi(this);

    this->map = new Ui::MapWidget(this->zork, ui->PAINTWIDGET);
    //ui->MAP_GRID->addWidget(map, 0, 0, 1, 1);
    //ui->PAINTWIDGET = map;
    QLayoutItem* item = ui->MAPGRID->replaceWidget(ui->PAINTWIDGET, this->map);

    if (item == nullptr) {
        printf("replaceWidget failed\n");
    }
    else printf("replaceWidget success\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DPAD_UP_clicked() {
    try {
        this->zork->MoveNorth();
        this->map->MovePlayerNorth(); // NEED TO FIX THIS SO THAT IT IS CALLED IN MOVENORTH!! So it doesn't go out of bounds
    
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_DPAD_LEFT_clicked() {
    try {
        this->zork->MoveWest();
        this->map->MovePlayerWest();

    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_DPAD_RIGHT_clicked() {
    try {
        this->zork->MoveEast();
        this->map->MovePlayerEast();
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_DPAD_DOWN_clicked() {
    try {
        this->zork->MoveSouth();
        this->map->MovePlayerSouth();
    } catch (const Game::ZorkException& e) {
        std::cout << e.what() << std::endl;
    }
}

void MainWindow::on_WORLDLIST_currentRowChanged(int currentRow)
{
    this->zork->SetWorld(currentRow);
    update();
}
