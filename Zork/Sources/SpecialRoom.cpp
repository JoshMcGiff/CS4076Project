#include "SpecialRoom.hpp"

namespace Game{

SpecialRoom::SpecialRoom() {
    #ifdef ZORK_DEBUG
    printf("3: Construting SpecialRoom Object!\n");
    #endif
}

SpecialRoom::~SpecialRoom() {

}

SpecialRoom* SpecialRoom::NewSpecialRoom() { //static setup function, wrapper used to create a SpecialRoom + ensure it is set up
    SpecialRoom* room = new SpecialRoom();
    room->GenerateRoomDialogue();
    return room;
}

std::string SpecialRoom::ToString() { // Needed for "PrintRoom()" virtual function
    char str[50] = {0};
    snprintf(str, 50, "Type: Special\t%llX", (uint64_t)this);
    return std::string(str);
}

void SpecialRoom::GenerateRoomDialogue() {
    roomDialogue = "Special Room";
}

void SpecialRoom::SetRoomDialogue(const std::string& dialogue, const std::string& itemName){
    this->roomDialogue = "World Treasure: " + itemName + " (" + dialogue + ")";
}

RoomType SpecialRoom::GetRoomType() {
    return RoomType::Special;
}

} //namespace Game
