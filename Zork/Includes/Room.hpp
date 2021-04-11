#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "Item.hpp"
#include "RoomBase.hpp"
#include "RoomAttribute.hpp"
#include "Npc.hpp"

namespace Game {

class Room : public RoomBase, public RoomAttribute { //Multiple Inheritance, as asked for on the spec
private:
    bool isLocked;
    std::vector<Item>* roomItems; // Items in the room
    bool hasNpc;

protected:
    Room();
    Room(const Room* room);
public:
    virtual ~Room();
    static Room* NewRoom(Room* room = nullptr); //Used to create a new Room on heap

    virtual RoomType GetRoomType() override;
    std::string GetRoomDialogue() override;
    virtual void GenerateRoomDialogue() override; //Not called in ctor as virtual, wrong version may be called/considered bad practise
    virtual void SetRoomDialogue(const std::string& dialogue, const std::string& itemName) override;

    bool SetNpc(bool hasNpc);
    bool HasNpc();

    std::vector<Item>* GetRoomItems();
    size_t GetRoomItemAmount();
    std::string ToString();
    bool AddItem(const Item& item); //Returns true if adding an item to the room is successful
    bool RemoveItem(const size_t index); //Returns true if removing an item from the room is successful
    bool GetItem(const size_t index, Game::Item& item); //Returns true if getting an item from the room is successful
};

} //namespace Game

#endif
