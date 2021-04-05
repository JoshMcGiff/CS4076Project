#include "Room.hpp"
#include <cstdlib>

namespace Game {


Room::Room() {
    //this->roomDialogue = desc;
}

Room::~Room() {

}

std::string Room::GetRoomDialogue() {
    return this->roomDialogue;
}

void Room::SetRoomDialogue(const std::string& diag) {
    this->roomDialogue = diag;
}

RoomType Room::GetRoomType() {
    return RoomType::Normal;
}

std::vector<Item> Room::GetRoomItems(){
    return this->roomItems;
}

bool Room::AddItem(const Item& item) {
    this->roomItems.push_back(item);
    return true;
}

bool Room::RemoveItem(const int index) {
    if (index < 0 && index >= this->roomItems.size()) {
        return false;
    }


    this->roomItems.erase(this->roomItems.begin()+index);
    return true;
}

std::size_t Room::GetRoomItemAmount() { //returns std::size_t as it's the return trype from std::vector::size
    return this->roomItems.size();
}

}; //namespace Game
