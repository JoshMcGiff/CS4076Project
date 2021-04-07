#include "Zork.hpp"
#include "Item.hpp"
#include <ctime>

__attribute__((unused)) bool thisIsAUsefulVariable = false; //Unused Global Variable, only here due to the spec 

namespace Game {

Zork::Zork() : curWorld(nullptr) {
    srand(time(NULL));

    std::vector<Item> playerInventory = {}; 
    std::vector<Item> items1 = {{"Nicki's Candle", PINK_WAND, "Best candle eva", 8}};
    
    World* world1 = new World("World 1", "Description", Game::Item("Nicki's Crown1", 4, "Queen Shit", 0), items1, playerInventory);
    zorkWorlds[0] = world1;

    std::vector<Item> items2 = {};
    World* world2 = new World("World 2", "Description", Game::Item("Nicki's Crown2", 5, "Queen Shit", 0), items2, playerInventory);
    zorkWorlds[1] = world2;

    std::vector<Item> items3 = {};
    World *world3 = new World("World 3", "Description", Game::Item("Nicki's Crown3", 6, "Queen Shit", 0), items3, playerInventory);
    zorkWorlds[2] = world3;

    std::vector<Item> items4 = {};
    World* world4 = new World("World 4", "Description", Game::Item("Nicki's Crown4", 7, "Queen Shit", 0), items4, playerInventory);
    zorkWorlds[3] = world4;
    
    std::vector<Item> items5 = {};
    World *world5 = new World("World 5", "Description", Game::Item("Nicki's Crown5", 8, "Queen Shit", 0), items5, playerInventory);
    zorkWorlds[4] = world5;
}

Zork::~Zork() {
    for (size_t i = 0; i < zorkWorlds.size(); i++) {
        World* world = zorkWorlds[i];
        if (world != nullptr) {
            delete world;
        }
        zorkWorlds[i] = nullptr;
    }
}

World* Zork::GetCurrentWorld() {
    return curWorld;
}

int Zork::MoveNorth() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveNorth: World does not exist");
        return 1;
    }

    curWorld->MoveNorth();
    return 0;
}
void Zork::MoveSouth() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveSouth: World does not exist");
        return;
    }

    curWorld->MoveSouth();
}
void Zork::MoveEast() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveEast: World does not exist");
        return;
    }

    curWorld->MoveEast();
}
void Zork::MoveWest() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveWest: World does not exist");
        return;
    }

    curWorld->MoveWest();
}

bool Zork::SetWorld(size_t index) {
    if (index <= zorkWorlds.size()) {
        this->curWorld = zorkWorlds[index];
        return true;
    }
    return false;
}

Room* Zork::GetCurrentRoom() {
    if (this->curWorld) {
        return this->curWorld->GetCurrentRoom();
    }
    return nullptr;
}

} //namespace Game
