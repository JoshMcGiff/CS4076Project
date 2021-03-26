#include "MapWidget.hpp"
#include <QPainter>
#include <QPen>

namespace Ui {

using namespace Game;


void MapWidget::paintEvent(QPaintEvent*) {
    
    QPixmap pixmap = QPixmap(600,300);
    pixmap = pixmap.scaled(width(), height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    
    QPainter p(this);
    p.setPen(QPen(Qt::blue, 3));
    int n = 8;
    Game::World* world = zork->getCurrentWorld();
        for(int i = 0; i < ROW_COUNT; i++){
            for(int j = 0; j < COL_COUNT; j++){
                if(world->roomArray[i][j] != nullptr){
                    p.drawRect(10 + (j*75), 10 + (i*75), 50, 50);
                }
                if ((i+1 < ROW_COUNT) && (world->roomArray[i][j] != nullptr) && (world->roomArray[i+1][j]) != nullptr) { //North
                    p.drawLine  (10 + (j*75) +25, //x1
                                10 + (i*75)+ 50, //y1
                                10 + (j*75) + 25, //x2
                                10 + ((i+1)*75)); //y2
                }
                if ((j+1 < ROW_COUNT) && (world->roomArray[i][j] != nullptr) && (world->roomArray[i][j+1]) != nullptr) { //North
                    p.drawLine  (10 + (j*75) + 50, //x1
                                10 + ((i*75) + 25), //y1
                                10 + ((j+1)*75), //x2
                                10 + ((i*75) + 25)); //y2
                }
                
            }
        }
            p.setPen(QPen(Qt::red, 3));
            QRect test = QRect(QPoint(playerStartX, playerStartY), QSize(20, 20));
            if(directionBitfield.isNorth){
                this->playerStartY -= 75;
                playerRect = QRect(QPoint(playerStartX, playerStartY), QSize(20, 20));
                p.drawRect(playerRect);
                p.eraseRect(test);
                directionBitfield.isNorth = false;
            }else if(directionBitfield.isSouth){
                this->playerStartY += 75;
                playerRect = QRect(QPoint(playerStartX, playerStartY), QSize(20, 20));
                p.drawRect(playerRect);
                p.eraseRect(test);
                directionBitfield.isSouth = false;
            }else if(directionBitfield.isEast){
                this->playerStartX += 75;
                playerRect = QRect(QPoint(playerStartX, playerStartY), QSize(20, 20));
                p.drawRect(playerRect);
                p.eraseRect(test);
                directionBitfield.isEast = false;
            }else if(directionBitfield.isWest){
                this->playerStartX -= 75;
                playerRect = QRect(QPoint(playerStartX, playerStartY), QSize(20, 20));
                p.drawRect(playerRect);
                p.eraseRect(test);
                directionBitfield.isEast = false;
            }else{
                playerStartX = (START_COL*75)+25;
                playerStartY = (START_ROW*75)+25;
                p.fillRect(test, Qt::red);
            }
    }

void MapWidget::MovePlayerNorth(){
    directionBitfield.isNorth = true;
    update();
}
void MapWidget::MovePlayerSouth(){
    directionBitfield.isSouth = true;
    update();
}
void MapWidget::MovePlayerEast(){
    directionBitfield.isEast = true;
    update();
}
void MapWidget::MovePlayerWest(){
    directionBitfield.isWest = true;
    update();
}


    //world->roomArray[0][0] = new Room();
}

