#include "MapWidget.hpp"

namespace Ui {

using namespace Game;

#define PEN_THICKNESS 3
#define MW_FONT_SIZE 50

MapWidget::MapWidget(std::shared_ptr<Game::Zork> zorkInstance, QWidget* parent)
    : QWidget(parent), painter(), bluePen(Qt::blue, PEN_THICKNESS), redPen(Qt::red, PEN_THICKNESS),
        blackPen(Qt::black, PEN_THICKNESS), greenPen(Qt::green, PEN_THICKNESS), textFont(), zork(zorkInstance)
{
    this->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
    textFont.setPixelSize(MW_FONT_SIZE);
}

void MapWidget::paintEvent(QPaintEvent*) { //overridden function from QWidget
    constexpr int squareSize = 58;
    constexpr int lineLength = 30;
    constexpr int spacing = squareSize + lineLength;

   
    float centerXConstant = (width() / 2) - (((COL_COUNT * squareSize) + ((COL_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);
    float centerYConstant = (height() / 2) - (((ROW_COUNT * squareSize) + ((ROW_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);

    painter.begin(this);
    painter.setPen(bluePen);

    Game::World* world = zork->GetCurrentWorld();
    if (world == nullptr) { //At start player is not in a world
        painter.setFont(textFont);
        painter.drawText(this->rect(), Qt::AlignCenter, "Pork - The Pop Culture Zork\n\nChoose a world!"); //this->rect() returns a QRect of x,y,width and height of MapWidget
    }

    else { //When in a world
        for(int i = 0; i < ROW_COUNT; i++){
            for(int j = 0; j < COL_COUNT; j++){
                Room* room = world->roomArray[i][j];
                //Room drawing (sqaures) + items
                if(room != nullptr){
                    painter.setPen(bluePen);

                    if(room == world->roomArray[START_ROW][START_COL] ){
                            painter.setPen(redPen);
                    }

                    if(room->GetRoomItemAmount() > 0 ){
                        if((room->GetRoomType() == RoomType::Special) && world->hasCollectedKeyItem){
                           painter.drawImage(QRectF(centerXConstant + (j*spacing)+4,centerYConstant + (i*spacing)+4, squareSize, squareSize)
                                            ,QImage(":/new/Images/Images/CHEST.png"), QRectF(0,0,squareSize,squareSize)); 
                        }else if (room->GetRoomType() != RoomType::Special){
                            painter.drawImage(QRectF(centerXConstant + (j*spacing)+4,centerYConstant + (i*spacing)+4, squareSize, squareSize)
                                            ,QImage(":/new/Images/Images/STAR.png"), QRectF(0,0,squareSize,squareSize));
                            painter.setPen(greenPen);

                        }
                    }

                    if(room->GetRoomType() == RoomType::Special){
                        if(world->hasCollectedKeyItem == false){
                            
                            painter.drawImage(QRectF(centerXConstant + (j*spacing)+4,centerYConstant + (i*spacing)+4, squareSize, squareSize)
                                            ,QImage(":/new/Images/Images/LOCK.png"), QRectF(0,0,squareSize,squareSize));
                        }
                            painter.setPen(blackPen);
                            painter.drawEllipse(centerXConstant + (j*spacing),centerYConstant + (i*spacing), squareSize, squareSize);
                    }else{
                        painter.drawRect(centerXConstant + (j*spacing),centerYConstant + (i*spacing), squareSize, squareSize);
                    }   
                }
                //Paths between squares
                painter.setPen(blackPen);
                if ((i+1 < ROW_COUNT) && (room != nullptr) && (world->roomArray[i+1][j]) != nullptr) { //Verical
                    painter.drawLine  (centerXConstant + (j*spacing) + lineLength, //x1
                                centerYConstant + (i*spacing)+ squareSize + PEN_THICKNESS, //y1
                                centerXConstant + (j*spacing) + lineLength, //x2
                                centerYConstant + ((i+1)*spacing) - PEN_THICKNESS); //y2
                }
                if ((j+1 < ROW_COUNT) && (room != nullptr) && (world->roomArray[i][j+1]) != nullptr) { //Horizontal
                    painter.drawLine  (centerXConstant + (j*spacing) + squareSize + PEN_THICKNESS, //x1
                                centerYConstant + ((i*spacing) + lineLength), //y1
                                centerXConstant + ((j+1)*spacing) - PEN_THICKNESS, //x2
                                centerYConstant + ((i*spacing) + lineLength)); //y2
                }
            }
        }

        painter.setPen(QPen(Qt::red, PEN_THICKNESS));
        QRect playerRect = QRect(QPoint(centerXConstant + (world->jCol*spacing) + (squareSize/4), centerYConstant +(world->iRow*spacing)+(squareSize/4)), QSize(30, 30));
        painter.drawEllipse(playerRect);
    }
    painter.end();
}

void MapWidget::UpdateMapUI() {
    this->update();
}

}

