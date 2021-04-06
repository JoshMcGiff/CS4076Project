#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "Item.hpp"
#include "RoomBase.hpp"

namespace Game {

enum class RoomAttribute : int { // Different room attributes. Using class to avoid conflicts
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

    ATTRIBUTE_MAX
};

class Room : public RoomBase {
private:
    RoomAttribute roomAttribute;
    bool isLocked;
    std::vector<Item>* roomItems; // Items in the room

protected:
    Room();
    Room(const Room* room);
public:
    virtual ~Room();
    static Room* NewRoom(Room* room = nullptr); //Used to create a new Room on heap

    virtual RoomType GetRoomType() override;
    std::string GetRoomDialogue() override;
    virtual void GenerateRoomDialogue() override; //Not called in ctor as virtual, wrong version may be called/considered bad practise


    std::vector<Item>* GetRoomItems();
    size_t GetRoomItemAmount();
    bool AddItem(const Item& item); //Returns true if adding an item to the room is successful
    bool RemoveItem(const size_t index); //Returns true if removing an item from the room is successful
    bool GetItem(const size_t index, Game::Item& item); //Returns true if getting an item from the room is successful
};

} //namespace Game

#endif
