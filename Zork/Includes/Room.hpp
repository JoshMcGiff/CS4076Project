#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "Item.hpp"
#include "RoomBase.hpp"

namespace Game {

enum class RoomAttribute { // Different room attributes. Using class to avoid conflicts
    Ice = 0,
    Fire = 1,
};

class Room : public RoomBase {
private:
    RoomAttribute roomAttributes;
    bool isLocked;
    std::vector<Item> roomItems; // Items in the room

public:
    Room();
    ~Room();

    virtual RoomType GetRoomType() override;
    std::string GetRoomDialogue() override;
    std::vector<Item> GetRoomItems();
    bool AddItem(const Item& item);
};

}; //namespace Game

#endif
