#include "SpecialRoom.hpp"

namespace Game{

SpecialRoom::SpecialRoom() {

}

SpecialRoom::~SpecialRoom() {

}

SpecialRoom* SpecialRoom::NewSpecialRoom() {
    SpecialRoom* room = new SpecialRoom();
    room->GenerateRoomDialogue();
    return room;
}

void SpecialRoom::GenerateRoomDialogue() {
    roomDialogue = "Special Room";
}

RoomType SpecialRoom::GetRoomType() {
    return RoomType::Special;
}

} //namespace Game
