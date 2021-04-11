#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <memory>
#include "Zork.hpp"
#include "MapWidget.hpp"
#include "QListStorageWidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateRoomItemsUI();
    void UpdateRoomDialogueUI();
    void UpdateInventoryUI();
    void CheckNPC();

private slots: //QT slots
    void on_DPAD_UP_clicked();
    void on_DPAD_LEFT_clicked();
    void on_DPAD_RIGHT_clicked();
    void on_DPAD_DOWN_clicked();
    void on_WORLDLIST_currentRowChanged(int currentRow);
    void roomItemsUI_DoubledClick(QListWidgetItem *item);
    void on_QUITBUTTON_clicked();

private:
    Ui::MapWidget* map;
    Ui::QListStorageWidget<Game::Item>* roomItemsWidget;
    Ui::MainWindow *ui;
    std::shared_ptr<Game::Zork> zork; //using shared pointer as the pointer is passed to multiple objects, therefore we dont want the memory to be deleted until the last insstance using it is deleted
};

#endif // MAINWINDOW_H
