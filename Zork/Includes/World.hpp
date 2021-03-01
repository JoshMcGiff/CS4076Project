#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
//#include <vector>
#include <memory>
#include "Room.hpp"
#include "Item.hpp"

class World {
private:
    std::string worldName;
    std::string worldDescription;
    std::unique_ptr<Room> worldStartingRoom; //Rooms link themselves to other Rooms
    std::vector<Item> worldItems; //Store items here

public:
    int itemIndex; //Used by rooms to access the worldItems vector

    World(const char* name, const char* desc); //pass in array of world specific items to constructor
    void SetItems(std::vector<Item>&& worldItems);
    Item GetItem(int index);


};

#endif