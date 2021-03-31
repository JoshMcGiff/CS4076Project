#ifndef MAPWIDGET_HPP
#define MAPWIDGET_HPP

#include <QWidget>
#include <memory>
#include "Zork.hpp"
#include <QListWidget>

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
Game::World* world;
public:
    MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent = nullptr): zork(zorkInstance), QWidget(parent){
        
        this->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
    }
    Direction directionBitfield;
    virtual void paintEvent(QPaintEvent*) override;
    std::shared_ptr<Game::Zork> zork;
    void MovePlayer();

};

} //namespace Ui

#endif