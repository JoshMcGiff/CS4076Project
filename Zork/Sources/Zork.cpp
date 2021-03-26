#include "Zork.hpp"
#include "Item.hpp"
#include <ctime>

__attribute__((unused)) bool thisIsAUsefulVariable = false; //Unused Global Variable, only here due to the spec 

namespace Game {

Zork::Zork() : curWorld(nullptr) {
    srand(time(NULL));

    std::vector<Item> items1 = {};
    World* world1 = new World("World 1", "Description", items1);
    zorkWorlds[0] = world1;

    std::vector<Item> items2 = {};
    World* world2 = new World("World 2", "Description", items2);
    zorkWorlds[1] = world2;

    std::vector<Item> items3 = {};
    World* world3 = new World("World 3", "Description", items3);
    zorkWorlds[2] = world3;

    std::vector<Item> items4 = {};
    World* world4 = new World("World 4", "Description", items4);
    zorkWorlds[3] = world4;
    
    std::vector<Item> items5 = {};
    World* world5 = new World("World 5", "Description", items5);
    zorkWorlds[4] = world5;

    curWorld = world1;
}

Zork::~Zork() {
    for (int i = 0; i < zorkWorlds.size(); i++) {
        World* world = zorkWorlds[i];

        if (world != nullptr) {
            delete world;
        }
        zorkWorlds[i] = nullptr;
    }
}

World* Zork::getCurrentWorld() {
    return curWorld;
}

int Zork::MoveNorth() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveNorth: World does not exist");
        return 1;
    }

    curRoom = curWorld->MoveNorth();
    return 0;
}
void Zork::MoveSouth() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveSouth: World does not exist");
        return;
    }

    curRoom = curWorld->MoveSouth();
}
void Zork::MoveEast() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveEast: World does not exist");
        return;
    }

    curRoom = curWorld->MoveEast();
}
void Zork::MoveWest() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveWest: World does not exist");
        return;
    }

    curRoom = curWorld->MoveWest();
}

} //namespace Game
