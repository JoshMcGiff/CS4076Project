#include "MapWidget.hpp"
#include <QPainter>
#include <QPen>
#include <stdio.h>

namespace Ui {

using namespace Game;


void MapWidget::paintEvent(QPaintEvent*) {
    
    QPixmap pixmap = QPixmap(600,300);
    pixmap = pixmap.scaled(width(), height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    
    QPainter p(this);
    p.setPen(QPen(Qt::blue, 3));
    p.drawRect(width()/2, height()/2, 20, 20);

    //int n = 8;
    int squareSize = 50;
    int lineLength = 25;
    int spacing = squareSize + lineLength;
    float centerXConstant = (width() / 2) - (((COL_COUNT * squareSize) + ((COL_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);
    float centerYConstant = (height() / 2) - (((ROW_COUNT * squareSize) + ((ROW_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);

    Game::World* world = zork->getCurrentWorld();
        for(int i = 0; i < ROW_COUNT; i++){
            for(int j = 0; j < COL_COUNT; j++){
                Room* room = world->roomArray[i][j]; 
                if(room != nullptr){
                    if(room == world->roomArray[START_ROW][START_COL] ){
                            p.setPen(QPen(Qt::red, 3));
                    }
                    if(room->GetRoomType() == RoomType::Special){
                            p.setPen(QPen(Qt::black, 3));
                    }
                    if(room->GetRoomItemAmount() > 0){
                            p.setPen(QPen(Qt::green, 3));
                    }
                    p.drawRect(centerXConstant + (j*spacing),centerYConstant + (i*spacing), squareSize, squareSize);
                    p.setPen(QPen(Qt::blue, 3));
                }
                if ((i+1 < ROW_COUNT) && (room != nullptr) && (world->roomArray[i+1][j]) != nullptr) { //Verical
                    p.drawLine  (centerXConstant + (j*spacing) + lineLength, //x1
                                centerYConstant + (i*spacing)+ squareSize, //y1
                                centerXConstant + (j*spacing) + lineLength, //x2
                                centerYConstant + ((i+1)*spacing)); //y2
                }
                if ((j+1 < ROW_COUNT) && (room != nullptr) && (world->roomArray[i][j+1]) != nullptr) { //Horizontal
                    p.drawLine  (centerXConstant + (j*spacing) + squareSize, //x1
                                centerYConstant + ((i*spacing) + lineLength), //y1
                                centerXConstant + ((j+1)*spacing), //x2
                                centerYConstant + ((i*spacing) + lineLength)); //y2
                }
                
            }
        }
            p.setPen(QPen(Qt::red, 3));
            QRect test = QRect(QPoint(playerStartX, playerStartY), QSize(20, 20));
            if(directionBitfield.isNorth || directionBitfield.isSouth){
                printf("%d rowww\n", world->iRow);
                printf("%d col\n", world->jCol);
                playerStartX = (START_COL*75)+25;

                playerStartY = (START_ROW*75)+25;//(centerXConstant + world->jCol*75)+25;
                //playerRect = QRect(QPoint(centerXConstant + (START_COL*75)+25, centerYConstant +((ROW_COUNT - world->iRow)*75)+25), QSize(20, 20));
                playerRect = QRect(QPoint(centerXConstant + (START_COL*75)+25, centerYConstant +((ROW_COUNT - world->iRow)*75)+25), QSize(20, 20));

                
                p.fillRect(playerRect, Qt::red);
                p.eraseRect(test);
                directionBitfield.isNorth = false;
                directionBitfield.isSouth = false;
                
            }else if(directionBitfield.isEast || directionBitfield.isWest){
                printf("%d rowww\n", world->jCol);
                printf("%d col\n", world->iRow);
                this->playerStartX += 75;
                playerRect = QRect(QPoint(centerXConstant + ( world->jCol*75)+25, centerYConstant +(START_ROW*75)+25), QSize(20, 20));
                p.fillRect(playerRect, Qt::red);
                p.eraseRect(test);
                directionBitfield.isEast = false;
                directionBitfield.isWest = false;
            }else{
                playerStartX = (START_COL*75)+25;
                playerStartY = (START_ROW*75)+25;
                //p.fillRect(test, Qt::red);
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
