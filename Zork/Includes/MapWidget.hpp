#ifndef MAPWIDGET_HPP
#define MAPWIDGET_HPP

#include <QWidget>
#include <memory>
#include "Zork.hpp"

namespace Ui {

struct Direction { //Bitfield of attributes
    /* data */
    bool isNorth : 1;
    bool isSouth : 1;
    bool isEast : 1;
    bool isWest : 1;
};

class MapWidget : public QWidget 
{
    Q_OBJECT
private:
QRect playerRect;
int playerStartX;
int playerStartY;
public:
    MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent = nullptr): zork(zorkInstance), QWidget(parent) {
        this->directionBitfield.isNorth = 0;
        this->directionBitfield.isSouth = 0;
        this->directionBitfield.isEast = 0;
        this->directionBitfield.isWest = 0;
    }
    Direction directionBitfield;
    virtual void paintEvent(QPaintEvent*) override;
    std::shared_ptr<Game::Zork> zork;
    void MovePlayerNorth();
    void MovePlayerSouth();
    void MovePlayerEast();
    void MovePlayerWest();

};

} //namespace Ui

#endif