#ifndef MAPWIDGET_HPP
#define MAPWIDGET_HPP

#include <QWidget>
#include <memory>
#include "Zork.hpp"

namespace Ui {

class MapWidget : public QWidget 
{
    Q_OBJECT
private:
QRect playerRect;
int playerStartX;
int playerStartY;
public:
    MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent = nullptr): zork(zorkInstance), QWidget(parent) {}

    virtual void paintEvent(QPaintEvent*) override;
    std::shared_ptr<Game::Zork> zork;
    void MovePlayerNorth();

};

} //namespace Ui

#endif