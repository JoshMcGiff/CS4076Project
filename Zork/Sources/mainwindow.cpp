#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "Zork.hpp"
#include "Room.hpp"
#include <QString>  
#include <QObject>

#define DIAG_FONT_SIZE 25

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->zork = std::make_shared<Game::Zork>();
    ui->setupUi(this);
    ui->DIALOGUEBOX->setFontPointSize(DIAG_FONT_SIZE);
    Init();
    this->map = new Ui::MapWidget(this->zork, ui->PAINTWIDGET);
    this->roomItemsWidget = new Ui::QListStorageWidget(ui->ROOMITEMS);
    ui->MAPGRID->replaceWidget(ui->PAINTWIDGET, this->map);
    ui->gridLayout->replaceWidget(ui->ROOMITEMS, this->roomItemsWidget);
    ui->ROOMITEMS->hide();
    ui->PAINTWIDGET->hide();

    connect(this->roomItemsWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(roomItemsUI_DoubledClick(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateRoomDialogueUI() {
    ui->DIALOGUEBOX->clear();

    Game::Room* curRoom = this->zork->GetCurrentRoom();
    if (!curRoom) {
        return;
    }
    ui->DIALOGUEBOX->textCursor().insertText(QString::fromStdString(curRoom->GetRoomDialogue()));
}

void MainWindow::Init() {
    this->UpdateRoomDialogueUI();
    this->UpdateRoomItemsUI();
}

void MainWindow::UpdateRoomItemsUI() {
    Game::Room* curRoom = this->zork->GetCurrentRoom();
    if (!curRoom) {
        return;
    }

    this->roomItemsWidget->clear();
    for (size_t i = 0; i < curRoom->GetRoomItemAmount(); i++) {
        Game::Item item;
        if (curRoom->GetItem(i, item)) {
            this->roomItemsWidget->addItemWithStorage(item); 
        }
    }
    this->map->UpdateMapUI();
}

//Advanced preprocessor - uses preprocessor for each of the move directions. Also uses custom exceptions
#define MOVE_FUNC(SLOT_NAME, MOVE_DIR) \
    void MainWindow::on_DPAD_##SLOT_NAME##_clicked() { \
        try { \
        this->zork->Move##MOVE_DIR(); \
        this->map->UpdateMapUI(); \
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
        this->map->UpdateMapUI();
        UpdateRoomItemsUI();
        UpdateRoomDialogueUI();
    }

    ui->WORLDLIST->setCurrentRow(ui->WORLDLIST->currentRow(), QItemSelectionModel::Deselect|QItemSelectionModel::Clear);
}

void MainWindow::roomItemsUI_DoubledClick(QListWidgetItem *item) {
    Game::Room* room = this->zork->GetCurrentRoom();
    if (room == nullptr)
        return;


    printf("tryign to take %s\n", item->text().toStdString().c_str());
    Game::Item newItem;
    if (roomItemsWidget->getItemFromStorage(item, newItem, false)) {
        printf("Item gotten from storage: %s\n", newItem.GetName().c_str());
        for (size_t i = 0; i < room->GetRoomItemAmount(); i++) {
            Game::Item checkItem;
            if (room->GetItem(i, checkItem)) {
                printf("Item gotten from Room: %s\n", checkItem.GetName().c_str());
                if (checkItem == newItem)
                {
                    ui->INVENTORYLIST->addItem(item->text());
                    roomItemsWidget->removeItemWithStorage(newItem);
                    room->RemoveItem(i);
                    break;
                }
            }
        }
    }

    this->UpdateRoomItemsUI();
}
