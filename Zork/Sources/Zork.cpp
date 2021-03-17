#include "Zork.hpp"
#include "Item.hpp"

__attribute__((unused)) bool thisIsAUsefulVariable = false; //Unused Global Variable, only here due to the spec 

namespace Game {

Zork::Zork() : curWorld(nullptr) {
    World* world1 = new World("World 1", "Description");

    std::vector<Item> items1 = {};
    world1->SetItems(std::move(items1));

    zorkWorlds[0] = world1;

    World* world2 = new World("World 2", "Description");

    std::vector<Item> items2 = {};
    world2->SetItems(std::move(items2));

    zorkWorlds[1] = world2;

    World* world3 = new World("World 3", "Description");

    std::vector<Item> items3 = {};
    world3->SetItems(std::move(items3));

    zorkWorlds[2] = world3;

    World* world4 = new World("World 4", "Description");

    std::vector<Item> items4 = {};
    world4->SetItems(std::move(items4));

    zorkWorlds[3] = world4;

    World* world5 = new World("World 5", "Description");

    std::vector<Item> items5 = {};
    world5->SetItems(std::move(items5));

    zorkWorlds[4] = world5;
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

void Zork::MoveNorth() {
    if (curWorld == nullptr) {
        return;
    }

    curRoom = curWorld->MoveNorth();
}
void Zork::MoveSouth() {
    if (curWorld == nullptr) {
        return;
    }

    curRoom = curWorld->MoveSouth();
}
void Zork::MoveEast() {
    if (curWorld == nullptr) {
        return;
    }

    curRoom = curWorld->MoveEast();
}
void Zork::MoveWest() {
    if (curWorld == nullptr) {
        return;
    }

    curRoom = curWorld->MoveWest();
}

} //namespace Game
