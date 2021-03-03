#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
//#include <vector>
#include <memory>
#include <array>
#include "Room.hpp"
#include "Item.hpp"
#include "SpecialRoom.hpp"


namespace Game {
#define ROW_COUNT 7
#define COL_COUNT 7

class World {
private:
    std::string worldName;
    std::string worldDescription;
    std::vector<Item> worldItems; //Store items here
    Item keyItem; // key in special room needed to finish the game
    void GenerateRooms(int row, int col, int chanceDecrease);
    void GenerateSpecialRoom(int row, int col);
    void GenerateItems(int row, int col);


public:
    std::array<std::array<Room*, COL_COUNT>, ROW_COUNT> roomArray;

    World(const char* name, const char* desc); //pass in array of world specific items to constructor

    void SetItems(std::vector<Item>&& worldItems);
    Item GetItem(int index);
    void Generate();

};

} //namespace Game

#endif
