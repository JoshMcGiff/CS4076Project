#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "Item.hpp"
#include "RoomBase.hpp"

namespace Game {

enum class RoomAttribute { // Different room attributes. Using class to avoid conflicts
    CHILLY = 0,
    HOT = 1,
    DARK = 2,
    SUNNY = 3,
    EERIE = 4,
    CALM = 5,
    SLIPPY = 6,
    STICKY = 7,
    WET = 8,
    MUSIC = 9,
};

class Room : public RoomBase {
private:
    RoomAttribute roomAttribute;
    bool isLocked;
    std::vector<Item> roomItems; // Items in the room
    void GenerateRoomDialogue(RoomAttribute r);
public:
    Room();
    ~Room();

    virtual RoomType GetRoomType() override;
    std::string GetRoomDialogue() override;
    void SetRoomDialogue(const std::string& diag) override;
    std::vector<Item> GetRoomItems();
    std::size_t GetRoomItemAmount();
    bool AddItem(const Item& item);
    bool RemoveItem(const int index);
};

}; //namespace Game

#endif
