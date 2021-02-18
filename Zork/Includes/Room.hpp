#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "Item.hpp"

enum class RoomAttribute { // Different room attributes. Using class to avoid conflicts
    ICE = 0,
    FIRE = 1,
};

class Room;

struct Doors { // Bitfield to know which directions have doors and whether they are locked or not
    Room* North;
    Room* East;
    Room* South;
    Room* West;

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
    uint8_t roomType;
    Doors roomExits; //Directions (Locked/Unlocked, can go, etc)
    RoomAttribute roomAttributes;
    std::vector<Item> roomItems; // Items in the room
    
    // 


public:

    Room(/* args */);
    ~Room();
};

#endif
