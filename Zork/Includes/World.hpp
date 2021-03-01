#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
//#include <vector>
#include <memory>
#include "Room.hpp"
#include "Item.hpp"
#include <array>

#define ROWS 12
#define COLS 12
class World {
private:
    std::string worldName;
    std::string worldDescription;
    std::vector<Item> worldItems; //Store items here

    void GenerateItems();
    void GenerateRooms();
    void GenerateSpecialRoom();

public:
    int itemIndex; //Used by rooms to access the worldItems vector
    std::array<std::array<Room*, COLS>, ROWS> roomArray;
    World(const char* name, const char* desc); //pass in array of world specific items to constructor
    void SetItems(std::vector<Item>&& worldItems);
    Item GetItem(int index);

    void Generate();

};

#endif