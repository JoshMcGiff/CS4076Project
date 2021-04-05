#include "MapWidget.hpp"
#include <QPainter>
#include <QPen>

namespace Ui {

using namespace Game;

MapWidget::MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent)
    : QWidget(parent), zork(zorkInstance)
{
    this->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
}

void MapWidget::paintEvent(QPaintEvent*) {
    
    QPixmap pixmap = QPixmap(600,300);
    pixmap = pixmap.scaled(width(), height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    
    QPainter p(this);
    p.setPen(QPen(Qt::blue, 3));

    constexpr int squareSize = 50;
    constexpr int lineLength = 25;
    constexpr int penThickness = 3;
    constexpr int spacing = squareSize + lineLength;

    float centerXConstant = (width() / 2) - (((COL_COUNT * squareSize) + ((COL_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);
    float centerYConstant = (height() / 2) - (((ROW_COUNT * squareSize) + ((ROW_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);

    world = zork->GetCurrentWorld();
    
        for(int i = 0; i < ROW_COUNT; i++){
            for(int j = 0; j < COL_COUNT; j++){
                Room* room = world->roomArray[i][j]; 
                if(room != nullptr){
                    if(room == world->roomArray[START_ROW][START_COL] ){
                            p.setPen(QPen(Qt::red, penThickness));
                    }
                    if(room->GetRoomType() == RoomType::Special){
                            p.setPen(QPen(Qt::black, penThickness));
                    }
                    if(room->GetRoomItemAmount() > 0){
                            p.setPen(QPen(Qt::green, penThickness));
                    }
                    p.drawRect(centerXConstant + (j*spacing),centerYConstant + (i*spacing), squareSize, squareSize);
                    p.setPen(QPen(Qt::blue, penThickness));
                }
                if ((i+1 < ROW_COUNT) && (room != nullptr) && (world->roomArray[i+1][j]) != nullptr) { //Verical
                    p.drawLine  (centerXConstant + (j*spacing) + lineLength, //x1
                                centerYConstant + (i*spacing)+ squareSize + penThickness, //y1
                                centerXConstant + (j*spacing) + lineLength, //x2
                                centerYConstant + ((i+1)*spacing) - penThickness); //y2
                }
                if ((j+1 < ROW_COUNT) && (room != nullptr) && (world->roomArray[i][j+1]) != nullptr) { //Horizontal
                    p.drawLine  (centerXConstant + (j*spacing) + squareSize + penThickness, //x1
                                centerYConstant + ((i*spacing) + lineLength), //y1
                                centerXConstant + ((j+1)*spacing) - penThickness, //x2
                                centerYConstant + ((i*spacing) + lineLength)); //y2
                }
                
            }
        }
            p.setPen(QPen(Qt::red, penThickness));
            playerRect = QRect(QPoint(centerXConstant + ( world->jCol*spacing)+15, centerYConstant +(world->iRow*spacing)+15), QSize(20, 20));
            p.fillRect(playerRect, Qt::red);
    }

void MapWidget::MovePlayer() {
    update();
}


}

