#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <memory>
#include <array>
#include "Room.hpp"
#include "Item.hpp"
#include "SpecialRoom.hpp"
#include "Npc.hpp"

namespace Ui {
    class MapWidget; //predeclare MapWidget class. Can't use include here as it results in 'circular dependency'
}

namespace Game {
#define ROW_COUNT 7
#define COL_COUNT 7

#define START_ROW ROW_COUNT / 2
#define START_COL COL_COUNT / 2

class World {
    friend class Ui::MapWidget; //Friendship, to access the rooms (required by spec)
private:
    std::string worldName;
    std::string worldDescription;
    Game::Npc worldNpc;
    std::array<std::array<Room*, COL_COUNT>, ROW_COUNT> roomArray;
    std::vector<Item> worldItems; //Store items here
    Item specialItem; // special item in special room needed to finish the game
    int iRow;
    int jCol;
    bool hasCollectedKeyItem;

    void GenerateRooms(int row, int col, int chanceDecrease);
    void GenerateSpecialRoom(int row, int col);
    void GenerateItems();
    void GenerateNpc();

    template <typename Type> // Templates must be used in headers because the compiler needs to instantiate different versions of the code, depending on the parameters given/deduced for template parameters. 
    void PrintRoom(Type* room) {
        if (room) {
            printf("%s ", room->ToString().c_str());
        }
        else {
            printf("0 "); 
        }
    }

public:

    World(const char* name, const char* desc, Game::Npc& npc, Game::Item&& keyItem, std::vector<Item>& worldItems); //keyItem is pass by move as we construct it inline; pass in vector of world specific items to constructor
    ~World();
    Room* MoveNorth();
    Room* MoveSouth();
    Room* MoveEast();
    Room* MoveWest();
    void SetItems(std::vector<Item>& worldItems);
    Item GetItem(size_t index);
    void Generate();
    std::string GetWorldName() const;
    Room* GetCurrentRoom() const;
    void CollectKeyItem();
    bool HasCollectedKeyItem() const;
    Game::Npc GetNpc() const;

};

} //namespace Game

#endif
