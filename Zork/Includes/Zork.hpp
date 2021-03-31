#ifndef ZORK_HPP
#define ZORK_HPP

#include <array>
#include <memory>
#include "World.hpp"
#include "ZorkException.hpp"

namespace Game {

enum WORLDS : int {
    WORLD_1 = 0,
    WORLD_2 = 1,
    WORLD_3 = 2,
    WORLD_4 = 3,
    WORLD_5 = 4,

    WORLD_AMOUNT
};

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
    Room* GetCurrentRoom();
    void SetWorld(int index);
    int MoveNorth();
    void MoveSouth();
    void MoveEast();
    void MoveWest();

};

} //namespace Game

#endif