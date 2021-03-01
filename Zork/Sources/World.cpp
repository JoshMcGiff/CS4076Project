#include "World.hpp"

World::World(const char* name, const char* desc) : worldName(name), worldDescription(desc) {
    this->worldStartingRoom = std::make_unique<Room>(this, nullptr, nullptr, nullptr, nullptr);
    this->worldStartingRoom->Generate();
}

void World::SetItems(std::vector<Item>&& worldItems) {
    this->worldItems = worldItems;

    //TODO: randomise order
}

Item World::GetItem(int index) {
    //TODO: check index in bounds, make items shared pointer

    return worldItems[index];
}