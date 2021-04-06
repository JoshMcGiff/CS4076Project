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

void MapWidget::paintEvent(QPaintEvent*) {
    constexpr int squareSize = 50;
    constexpr int lineLength = 25;
    constexpr int spacing = squareSize + lineLength;

    float centerXConstant = (width() / 2) - (((COL_COUNT * squareSize) + ((COL_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);
    float centerYConstant = (height() / 2) - (((ROW_COUNT * squareSize) + ((ROW_COUNT-1) * lineLength))/2); //+ squareSize + (squareSize/2);

    painter.begin(this);
    painter.setPen(bluePen);

    Game::World* world = zork->GetCurrentWorld();
    if (world == nullptr) { //At start player is not in a world
        painter.setFont(textFont);
        painter.drawText(this->rect(), Qt::AlignCenter, "Choose a world!"); //this->rect() returns a QRect of x,y,width and height of MapWidget
    }

    else { //When in a world
        for(int i = 0; i < ROW_COUNT; i++){
            for(int j = 0; j < COL_COUNT; j++){
                Room* room = world->roomArray[i][j];
                if(room != nullptr){
                    painter.setPen(bluePen);
                    if(room == world->roomArray[START_ROW][START_COL] ){
                            painter.setPen(redPen);
                    }
                    if(room->GetRoomType() == RoomType::Special){
                            painter.setPen(blackPen);
                    }
                    if(room->GetRoomItemAmount() > 0){
                            painter.setPen(greenPen);
                    }
                    painter.drawRect(centerXConstant + (j*spacing),centerYConstant + (i*spacing), squareSize, squareSize);
                    painter.setPen(bluePen);
                }
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
        QRect playerRect = QRect(QPoint(centerXConstant + (world->jCol*spacing)+15, centerYConstant +(world->iRow*spacing)+15), QSize(20, 20));
        painter.fillRect(playerRect, Qt::red);
    }
    painter.end();
}

void MapWidget::UpdateMapUI() {
    this->update();
}

}

