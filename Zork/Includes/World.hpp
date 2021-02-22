#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
//#include <vector>
#include <memory>
#include "Room.hpp"

class World {
private:
    std::string worldName;
    std::string worldDescription;
    std::unique_ptr<Room> worldStartingRoom; //Rooms link themselves to other Rooms
    //Store items here

public:

    World(std::string name, std::string desc); //pass in array of world specific items to constructor
};

#endif