#include "World.hpp"

World::World(std::string name, std::string desc) {
    this->worldName = name;
    this->worldDescription = desc;

    this->worldStartingRoom = std::make_unique<Room>(this, nullptr, nullptr, nullptr, nullptr);
    this->worldStartingRoom->GenerateRooms();
}