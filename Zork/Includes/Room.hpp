#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "Item.hpp"

enum class RoomAttribute { // Different room attributes. Using class to avoid conflicts
    Ice = 0,
    Fire = 1,
};

enum class RoomType {
    Normal = 0,
    Special = 1,
};



class Room; //pre-declare Room so it can be used in Doors traversal
struct Doors { // Bitfield to know which directions have doors and whether they are locked or not
    bool NorthLocked : 1;
    bool EastLocked : 1;
    bool SouthLocked : 1;
    bool WestLocked : 1; 
};

class Room {
private:
    /* data */
    std::string roomName;
    //uint32_t roomID; probably not needed
    //World* world;
    Doors roomExits; //Directions (Locked/Unlocked, can go, etc)
    RoomAttribute roomAttributes;
    std::vector<Item> roomItems; // Items in the room

public:
    Room();
    ~Room();
    
    virtual RoomType GetRoomType();
};

#endif
