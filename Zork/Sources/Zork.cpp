#include "Zork.hpp"
#include "Item.hpp"

Zork::Zork() {
    World world1("Name", "Description");

    std::vector<Item> items = {};
    world1.SetItems(std::move(items));

    zorkWorlds.push_back(world1);
}