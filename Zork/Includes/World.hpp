#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <memory>
#include <array>
#include "Room.hpp"
#include "Item.hpp"
#include "SpecialRoom.hpp"

namespace Ui {
    class MapWidget; //predeclare MapWidget class. Can't use include here as it results in 'circular dependency'
}

namespace Game {
#define ROW_COUNT 7
#define COL_COUNT 7

#define START_ROW ROW_COUNT / 2
#define START_COL COL_COUNT / 2

class World {
    friend class Ui::MapWidget;
private:
    std::string worldName;
    std::string worldDescription;
    std::vector<Item> worldItems; //Store items here
    Item keyItem; // key in special room needed to finish the game
    void GenerateRooms(int row, int col, int chanceDecrease);
    void GenerateSpecialRoom(int row, int col);
    void GenerateItems();
    int iRow;
    int jCol;

    std::array<std::array<Room*, COL_COUNT>, ROW_COUNT> roomArray;


public:

    World(const char* name, const char* desc, Game::Item&& keyItem, std::vector<Item>& worldItems); //pass in array of world specific items to constructor
    ~World();
    Room* MoveNorth();
    Room* MoveSouth();
    Room* MoveEast();
    Room* MoveWest();
    void SetItems(std::vector<Item>& worldItems);
    Item GetItem(size_t index);
    void Generate();
    int GetRow();
    int GetCol();
    Room* GetCurrentRoom();


};

} //namespace Game

#endif
