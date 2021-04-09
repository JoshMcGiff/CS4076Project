#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "Zork.hpp"
#include "Room.hpp"
#include "npcdialogui.hpp"
#include <QString>  
#include <QObject>
#include <QShortcut>

#define DIAG_FONT_SIZE 25

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->zork = std::make_shared<Game::Zork>();
    ui->setupUi(this);
    #ifndef ZORK_DEBUG //only fullscreen in non-debug mode
    this->setWindowState(Qt::WindowFullScreen);
    #endif
    ui->DIALOGUEBOX->setFontPointSize(DIAG_FONT_SIZE);

    ui->WORLDLIST->clear();
    for (size_t i = 0; i < zork->GetWorldAmount(); i++) {
        Game::World* world = zork->GetWorld(i);
        if (world) {
            ui->WORLDLIST->addItem(QString::fromStdString(world->GetWorldName()));
        }
    }

    this->Init();
    this->map = new Ui::MapWidget(this->zork, ui->PAINTWIDGET);
    ui->MAPGRID->replaceWidget(ui->PAINTWIDGET, this->map);
    ui->PAINTWIDGET->hide();

    this->roomItemsWidget = new Ui::QListStorageWidget<Game::Item>(ui->ROOMITEMS);
    this->roomItemsWidget->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    ui->gridLayout->replaceWidget(ui->ROOMITEMS, this->roomItemsWidget);
    ui->ROOMITEMS->hide();

    connect(this->roomItemsWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(roomItemsUI_DoubledClick(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init() {
    this->UpdateRoomDialogueUI();
    this->UpdateRoomItemsUI();
}

void MainWindow::UpdateRoomDialogueUI() {
    ui->DIALOGUEBOX->clear();

    Game::Room* curRoom = this->zork->GetCurrentRoom();
    if (!curRoom) {
        return;
    }
    ui->DIALOGUEBOX->textCursor().insertText(QString::fromStdString(curRoom->GetRoomDialogue()));
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

void MainWindow::UpdateInventoryUI() {
    ui->INVENTORYLIST->clear();
    for (size_t i = 0; i < zork->GetInventoryItemAmount(); i++) {
        Game::Item item;
        if (zork->GetItemFromInventory(i, item)) {
            ui->INVENTORYLIST->addItem(QString::fromStdString(item.GetName()));
        }
    }
}

//Advanced preprocessor - uses preprocessor for each of the move directions. Also uses custom exceptions
#define MOVE_FUNC(SLOT_NAME, MOVE_DIR) \
    void MainWindow::on_DPAD_##SLOT_NAME##_clicked() { \
        try { \
        this->zork->Move##MOVE_DIR(); \
        this->map->UpdateMapUI(); \
        this->UpdateRoomItemsUI(); \
        this->UpdateRoomDialogueUI(); \
        this->CheckNPC(); \
        \
        } catch (const Game::ZorkException& e) { \
            std::cout << e.what() << std::endl; \
        } \
    }

MOVE_FUNC(UP, North)
MOVE_FUNC(DOWN, South)
MOVE_FUNC(LEFT, West)
MOVE_FUNC(RIGHT, East)

void MainWindow::CheckNPC() {
    if (this->zork->GetCurrentWorld()->HasCollectedKeyItem()) {
        return;
    }

    Game::Room* room = this->zork->GetCurrentRoom();
    if (room) {
        if (room->HasNpc()) {
            Game::Npc npc = this->zork->GetCurrentWorld()->GetNpc();
            NpcDialogUI dialog(npc, this);
            dialog.exec();

            if (dialog.result() == NpcDialogUIResult_Yes) {
                zork->AddItemToInventory(npc.GetKeyItem());
                this->UpdateInventoryUI();
            }
        }
    }
}

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

    Game::Item newItem;
    if (roomItemsWidget->getItemFromStorage(item, newItem, false)) {
        for (size_t i = 0; i < room->GetRoomItemAmount(); i++) {
            Game::Item checkItem;
            if (room->GetItem(i, checkItem)) {
                if (checkItem == newItem) {
                    zork->AddItemToInventory(newItem);
                    roomItemsWidget->removeItemWithStorage(newItem);
                    room->RemoveItem(i);
                    break;
                }
            }
        }
    }

    this->UpdateRoomItemsUI();
    this->UpdateInventoryUI();
}

void MainWindow::on_QUITBUTTON_clicked()
{
    qApp->exit();
}
