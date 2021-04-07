#include "SpecialRoom.hpp"

namespace Game{

SpecialRoom::SpecialRoom() {
    #ifdef ZORK_DEBUG
    printf("Construting SpecialRoom Object!\n");
    #endif
}

SpecialRoom::~SpecialRoom() {

}
\
SpecialRoom* SpecialRoom::NewSpecialRoom() {
    SpecialRoom* room = new SpecialRoom();
    room->GenerateRoomDialogue();
    return room;
}

std::string SpecialRoom::ToString() {
    char str[50] = {0};
    snprintf(str, 50, "Type: Special\t%llX", (uint64_t)this);
    return std::string(str);
}

void SpecialRoom::GenerateRoomDialogue() {
    roomDialogue = "Special Room";
}

RoomType SpecialRoom::GetRoomType() {
    return RoomType::Special;
}

} //namespace Game
