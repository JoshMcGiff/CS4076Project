#ifndef MAPWIDGET_HPP
#define MAPWIDGET_HPP

#include <QWidget>
#include <memory>
#include <QPainter>
#include <QPen>
#include "Zork.hpp"

namespace Ui {

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
    std::shared_ptr<Game::Zork> zork;

public:
    MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent = nullptr);
    virtual void paintEvent(QPaintEvent*) override;
    void UpdateMapUI();

};

} //namespace Ui

#endif
