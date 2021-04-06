#ifndef MAPWIDGET_HPP
#define MAPWIDGET_HPP

#include <QWidget>
#include <memory>
#include <QPainter>
#include <QPen>
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
    QPainter painter;
    QPen bluePen;
    QPen redPen;
    QPen blackPen;
    QPen greenPen;
    QFont textFont;

public:
    MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent = nullptr);
    virtual void paintEvent(QPaintEvent*) override;
    void UpdateMapUI();

    Direction directionBitfield;
    std::shared_ptr<Game::Zork> zork;
};

} //namespace Ui

#endif
