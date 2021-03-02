#include "Room.hpp"
#include <cstdlib>

namespace Game{


Room::Room() {

}

Room::~Room() {

}

RoomType Room::GetRoomType() {
    return RoomType::Normal;
}

};
