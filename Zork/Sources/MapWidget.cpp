#include "MapWidget.hpp"
#include <QPainter>
#include <QPen>

namespace Ui {

using namespace Game;

void MapWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setPen(QPen(Qt::blue, 3));
    int n = 8;
    p.drawRect(10, 10, 20, 20);

    Game::World* world = zork->getCurrentWorld();
    for(int i = 0; i <)
    world->roomArray[0][0] = new Room();
}

}