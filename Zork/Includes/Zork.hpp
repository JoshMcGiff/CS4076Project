#ifndef ZORK_HPP
#define ZORK_HPP

#include <array>
#include <memory>
#include "World.hpp"
#include "Player.hpp"

#define WORLD_AMOUNT 10 //Pre-processor variable

class Zork {
private:
    std::array<World, WORLD_AMOUNT> zorkWorlds;
    std::shared_ptr<Player> currentPlayer;


public:
    World* getCurrentWorld();
    std::shared_ptr<Player> getCurrentPlayer();
};


#endif