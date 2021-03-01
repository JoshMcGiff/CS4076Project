#ifndef ZORK_HPP
#define ZORK_HPP

#include <vector>
#include <memory>
#include "World.hpp"
#include "Player.hpp"

#define WORLD_AMOUNT 10 //Pre-processor variable

class Zork {
private:
    std::vector<World> zorkWorlds;
    std::shared_ptr<Player> currentPlayer;


public:
    Zork();
    
    World* getCurrentWorld();
    std::shared_ptr<Player> getCurrentPlayer();


};


#endif