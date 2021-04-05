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
    void SetRoomDialogue(const std::string& diag) override;
    std::vector<Item> GetRoomItems();
    std::size_t GetRoomItemAmount();
    bool AddItem(const Item& item);
    bool RemoveItem(const int index);
};

}; //namespace Game

#endif
