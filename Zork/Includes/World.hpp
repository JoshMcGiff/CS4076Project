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
};

#endif