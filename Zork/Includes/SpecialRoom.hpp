#ifndef SPECIALROOM_HPP
#define SPECIALROOM_HPP

#include "Room.hpp"

class SpecialRoom : public Room {


public:
    SpecialRoom();
    RoomType GetRoomType() override;
};

#endif