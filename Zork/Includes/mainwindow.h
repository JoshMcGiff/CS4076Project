#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DPAD_UP_clicked();

    void on_DPAD_LEFT_clicked();

    void on_DPAD_RIGHT_clicked();


    void on_DPAD_DOWN_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H