#ifndef ZORK_HPP
#define ZORK_HPP

#include <array>
#include <memory>
#include <vector>
#include "World.hpp"
#include "Item.hpp"
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
    World* curWorld;
    std::array<World*, WORLD_AMOUNT> zorkWorlds;
    std::vector<Game::Item> playerInventory;
    Ui::MapWidget* map;

public:
    Zork();
    ~Zork();
    
    World* GetCurrentWorld();
    Room* GetCurrentRoom();
    bool SetWorld(size_t index);
    int MoveNorth();
    void MoveSouth();
    void MoveEast();
    void MoveWest();
    
    std::vector<Game::Item>* GetInventoryItems();
    size_t GetInventoryItemAmount();

    bool AddItemToInventory(const Item& item); //Returns true if adding an item to the inventory is successful
    bool RemoveItemFromInventory(const size_t index); //Returns true if removing an item from the inventory is successful
    bool GetItemFromInventory(const size_t index, Game::Item& item); //Returns true if getting an item from the inventory is successful
    void ClearInventory();
};

} //namespace Game

#endif
