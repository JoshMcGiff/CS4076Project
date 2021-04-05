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
    ui->MAPGRID->replaceWidget(ui->PAINTWIDGET, this->map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateRoomDialogueUI() {

    ui->DIALOGUEBOX->clear();
    ui->DIALOGUEBOX->setFontPointSize(25);
    ui->DIALOGUEBOX->textCursor().insertText(QString::fromStdString(zork->GetCurrentRoom()->GetRoomDialogue()));
}

void MainWindow::Init() {
    this->UpdateRoomDialogueUI();
}

void MainWindow::UpdateRoomItemsUI() {
    ui->ROOMITEMS->clear();
    Game::Room* curRoom = this->zork->GetCurrentRoom();
    for (size_t i = 0; i < curRoom->GetRoomItemAmount(); i++) {
       ui->ROOMITEMS->addItem(QString::fromStdString(curRoom->GetRoomItems()[i].GetItemName())); //TODO: Custom Widget to add Item IDs, so we can compare by item ID instead of string
    }
    this->map->MovePlayer();
}

//Advanced preprocessor - uses preprocessor for each of the move directions. Also uses custom exceptions
#define MOVE_FUNC(SLOT_NAME, MOVE_DIR) \
    void MainWindow::on_DPAD_##SLOT_NAME##_clicked() { \
        try { \
        this->zork->Move##MOVE_DIR(); \
        this->map->MovePlayer(); \
        this->UpdateRoomItemsUI(); \
        this->UpdateRoomDialogueUI(); \
        \
        } catch (const Game::ZorkException& e) { \
            std::cout << e.what() << std::endl; \
        } \
    }

MOVE_FUNC(UP, North)
MOVE_FUNC(DOWN, South)
MOVE_FUNC(LEFT, West)
MOVE_FUNC(RIGHT, East)

void MainWindow::on_WORLDLIST_currentRowChanged(int currentRow) {
    if (this->zork->SetWorld(currentRow)) {
        UpdateRoomDialogueUI();
        update();
    }
}

void MainWindow::on_ROOMITEMS_itemDoubleClicked(QListWidgetItem *item) {
    ui->INVENTORYLIST->addItem(item->text());
    Game::Room* room = this->zork->GetCurrentRoom();

    for (size_t i = 0; i < room->GetRoomItemAmount(); i++) {
        if (room->GetRoomItems()[i].GetItemName() == item->text().toStdString()) {
            room->RemoveItem(i);
            break;
        }
    }

    this->UpdateRoomItemsUI();
}
