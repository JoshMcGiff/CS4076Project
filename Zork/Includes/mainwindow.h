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

private slots:
    void on_DPAD_UP_clicked();
    void on_DPAD_LEFT_clicked();
    void on_DPAD_RIGHT_clicked();
    void on_DPAD_DOWN_clicked();
    void on_WORLDLIST_currentRowChanged(int currentRow);
    void roomItemsUI_DoubledClick(QListWidgetItem *item);

private:
    void Init();
    Ui::MapWidget* map;
    Ui::QListStorageWidget* roomItemsWidget;
    Ui::MainWindow *ui;
    std::shared_ptr<Game::Zork> zork;
};

#endif // MAINWINDOW_H
