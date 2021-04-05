#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "MapWidget.hpp"
#include "Zork.hpp"
#include "Room.hpp"
#include <QString>  
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->zork = std::make_shared<Game::Zork>();
    ui->setupUi(this);
    // ui->DIALOGUEBOX->textCursor().insertText(QString::fromStdString(zork->GetCurrentRoom));
    Init();
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



void MainWindow::UpdateRoomDialogue(){

    ui->DIALOGUEBOX->clear();
    ui->DIALOGUEBOX->setFontPointSize(25);
    ui->DIALOGUEBOX->textCursor().insertText(QString::fromStdString(zork->GetCurrentRoom()->GetRoomDialogue()));
}

void MainWindow::Init()
{
    this->UpdateRoomDialogue();
}

void MainWindow::RefreshRoomItemsUI() {
    ui->ROOMITEMS->clear();
    for(int i =0; i < this->zork->GetCurrentRoom()->GetRoomItemAmount(); i++){
       ui->ROOMITEMS->addItem(QString::fromStdString(zork->GetCurrentRoom()->GetRoomItems()[i].GetItemName())); //TODO: Custom Widget to add Item IDs, so we can compare by item ID instead of string
    }
    this->map->MovePlayer();
}

//Advanced preprocessor - uses preprocessor for each of the move directions. Also uses custom exceptions
#define MOVE_FUNC(SLOT_NAME, MOVE_DIR) \
    void MainWindow::on_DPAD_##SLOT_NAME##_clicked() { \
        try { \
        this->zork->Move##MOVE_DIR(); \
        this->map->MovePlayer(); \
        this->RefreshRoomItemsUI(); \
        this->UpdateRoomDialogue(); \
        \
        } catch (const Game::ZorkException& e) { \
            std::cout << e.what() << std::endl; \
        } \
    }

MOVE_FUNC(UP, North)
MOVE_FUNC(DOWN, South)
MOVE_FUNC(LEFT, West)
MOVE_FUNC(RIGHT, East)

void MainWindow::on_WORLDLIST_currentRowChanged(int currentRow)
{
    this->zork->SetWorld(currentRow);
    this->zork->SetCurrentRoom(this->zork->GetCurrentWorld()->GetCurrentRoom());

    UpdateRoomDialogue();
    update();
}

void MainWindow::on_ROOMITEMS_itemDoubleClicked(QListWidgetItem *item)
{
    printf("yo yoy yo\n");
    printf("Item: %s\n", item->text().toStdString().c_str());

    ui->INVENTORYLIST->addItem(item->text());
    Game::Room* room = zork->GetCurrentRoom();

    for (std::size_t i = 0; i < room->GetRoomItemAmount(); i++) {
        if (room->GetRoomItems()[i].GetItemName() == item->text().toStdString()) {
            room->RemoveItem(i);
            break;
        }
    }

    this->RefreshRoomItemsUI();
}
