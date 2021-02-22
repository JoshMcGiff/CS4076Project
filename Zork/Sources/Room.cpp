#include "Room.hpp"
#include <cstdlib>

#define DEFAULT_DEPTH 6
#define ROOM_CHANCE 50

Room::Room(World* world, Room* North, Room* South, Room* East, Room* West) {
    this->world = world;
    roomExits.North = North;
    roomExits.East = East;
    roomExits.South = South;
    roomExits.West = West;
}

Room::~Room() {

}

void Room::GenerateItems() {

}

void Room::GenerateRooms() {
    static uint32_t depthCount = 0;
    if (depthCount >= DEFAULT_DEPTH) {
        return;
    }

    //Generate Items

    depthCount++;

    register int random = 0;
    if (this->roomExits.North == nullptr) {
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomExits.North = new Room(this->world, nullptr, this, nullptr, nullptr);
            this->roomExits.North->GenerateRooms();
        }
    }

    if (this->roomExits.South == nullptr) {
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomExits.South = new Room(this->world, this, nullptr, nullptr, nullptr);
            this->roomExits.South->GenerateRooms();
        }
    }

    if (this->roomExits.East == nullptr) {
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomExits.East = new Room(this->world, nullptr, nullptr, nullptr, this);
            this->roomExits.East->GenerateRooms();
        }
    }
    
    if (this->roomExits.West == nullptr) {
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomExits.West = new Room(this->world, nullptr, nullptr, this, nullptr);
            this->roomExits.West->GenerateRooms();
        }
    }

    depthCount--;
}
