#ifndef ZORK_HPP
#define ZORK_HPP

#include <array>
#include <memory>
#include "World.hpp"
#include "ZorkException.hpp"

namespace Game {
#define WORLD_AMOUNT 5 //Pre-processor variable

class Zork {
private:
    std::array<World*, WORLD_AMOUNT> zorkWorlds;
    Ui::MapWidget* map;

    World* curWorld;
    Room* curRoom;
public:
    Zork();
    ~Zork();
    
    World* getCurrentWorld();

    int MoveNorth();
    void MoveSouth();
    void MoveEast();
    void MoveWest();

};

} //namespace Game

#endif