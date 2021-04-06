#include "Room.hpp"
#include <cstdlib>

namespace Game {

Room::Room() {
    roomItems = new std::vector<Game::Item>();
}

Room::Room(const Room* room) { //Deep 🌹🌹🔪💀🔪🖤 Copy
    roomAttribute = room->roomAttribute;
    isLocked = room->isLocked;
    roomDialogue = room->roomDialogue;

    roomItems = new std::vector<Game::Item>(*room->roomItems); //uses deep copy 
}

Room::~Room() {
    delete roomItems;
}

Room* Room::NewRoom(Room* room) {
    if (room) {
       Room* newroom = new Room(room); //deep copy
       return newroom;
    }

    Room* newroom = new Room();
    newroom->GenerateRoomDialogue();
    return newroom;
}

void Room::GenerateRoomDialogue() {
    this->roomAttribute = (RoomAttribute)(rand() % (int)RoomAttribute::ATTRIBUTE_MAX);

    switch(this->roomAttribute) {
        case RoomAttribute::CHILLY:
            roomDialogue = "You can see your breath appear in the air as you enter the room";
            break;
        case RoomAttribute::HOT:
            roomDialogue = "The heat hits you like a ton of bricks as you enter the room";
            break;
        case RoomAttribute::DARK:
            roomDialogue = "The room is barely lit as you enter the room";
            break;
        case RoomAttribute::SUNNY:
            roomDialogue = "The beams of sunlight take you by surprise as you step into the room";
            break;
        case RoomAttribute::EERIE:
            roomDialogue = "You are suddenly on edge as you enter the room";
            break;
        case RoomAttribute::CALM:
            roomDialogue = "You instantly feel safe when you find yourself standing in the room";
            break;
        case RoomAttribute::SLIPPY:
            roomDialogue = "You feel yourself losing your grip as you slide into the room";
            break;
        case RoomAttribute::STICKY:
            roomDialogue = "You trudge into the room as the ground is covered in a sticky substance";
            break;
        case RoomAttribute::WET:
            roomDialogue = "You can see your reflection in a giant puddle spanning the entire room";
            break;
        case RoomAttribute::MUSIC:
            roomDialogue = "Faint voices chirping in the distance hit you as you step inside the room";
            break;
        default:
            roomDialogue = "Bad roomAttribute enum value";
    }
}

std::string Room::GetRoomDialogue() {
    return this->roomDialogue;
}

RoomType Room::GetRoomType() {
    return RoomType::Normal;
}

std::vector<Item>* Room::GetRoomItems() {
    return this->roomItems;
}

bool Room::AddItem(const Item& item) {
    this->roomItems->push_back(item);
    return true;
}

bool Room::RemoveItem(const size_t index) {
    if (index >= this->roomItems->size()) {
        return false;
    }

    this->roomItems->erase(this->roomItems->begin()+index);
    return true;
}

bool Room::GetItem(const size_t index, Game::Item& item) {
    if (index >= this->roomItems->size()) {
        return false;
    }

    item = (*this->roomItems)[index];
    return true;
}

size_t Room::GetRoomItemAmount() { //returns std::size_t as it's the return trype from std::vector::size
    return this->roomItems->size();
}

}; //namespace Game
