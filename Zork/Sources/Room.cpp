#include "Room.hpp"
#include <cstdlib>

namespace Game {

Room::Room() : hasNpc(false) {
    #ifdef ZORK_DEBUG
    printf("2: Construting Room Object!\n");
    #endif

    roomItems = new std::vector<Game::Item>();
}

Room::Room(const Room* room) { //Deep Copy
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

std::string Room::ToString() {
    char str[50] = {0};
    snprintf(str, 50, "Type: Normal\t%llX", (uint64_t)this);
    return std::string(str);
}

void Room::GenerateRoomDialogue() {
    this->roomAttribute = (AttributeEnum)(rand() % (int)AttributeEnum::ATTRIBUTE_MAX);

    switch(this->roomAttribute) {
        case AttributeEnum::CHILLY:
            roomDialogue = "You can see your breath appear in the air as you enter the room 🥶🧊🥶";
            break;
        case AttributeEnum::HOT:
            roomDialogue = "The heat hits you like a ton of bricks as you enter the room 🥵";
            break;
        case AttributeEnum::DARK:
            roomDialogue = "The room is barely lit as you enter the room 🌚🌚";
            break;
        case AttributeEnum::SUNNY:
            roomDialogue = "The beams of sunlight take you by surprise as you step into the room 🌞😎";
            break;
        case AttributeEnum::EERIE:
            roomDialogue = "You are suddenly on edge as you enter the room 😖👻";
            break;
        case AttributeEnum::CALM:
            roomDialogue = "You instantly feel safe when you find yourself standing in the room 🌱✌😄";
            break;
        case AttributeEnum::SLIPPY:
            roomDialogue = "You feel yourself losing your grip as you slide into the room 🛹🧊";
            break;
        case AttributeEnum::STICKY:
            roomDialogue = "You trudge into the room as the ground is covered in a sticky substance 😖😖😖";
            break;
        case AttributeEnum::WET:
            roomDialogue = "You can see your reflection in a giant puddle spanning the entire room 🌊😳";
            break;
        case AttributeEnum::MUSIC:
            roomDialogue = "Faint voices chirping in the distance hit you as you step inside the room 👂🎶";
            break;
        default:
            roomDialogue = "Bad roomAttribute enum value 😜✌";
    }
}

std::string Room::GetRoomDialogue() {
    return this->roomDialogue;
}

RoomType Room::GetRoomType() {
    return RoomType::Normal;
}

bool Room::SetNpc(bool npc) {
    if (this->hasNpc) { //if already set
        return false;
    }

    this->hasNpc = npc;
    return true;
}

bool Room::HasNpc() {
    return this->hasNpc;
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

void Room::SetRoomDialogue(const std::string& dialogue, const std::string& itemName) {
    (void)dialogue; (void)itemName; //not unused, supress warnings
    return;
}

size_t Room::GetRoomItemAmount() { //returns std::size_t as it's the return type from std::vector::size
    return this->roomItems->size();
}

}; //namespace Game
