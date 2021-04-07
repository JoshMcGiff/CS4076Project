#ifndef SPECIALROOM_HPP
#define SPECIALROOM_HPP

#include "Room.hpp"
namespace Game {

class SpecialRoom : public Room {
protected:
    SpecialRoom();
public:
    ~SpecialRoom();
    static SpecialRoom* NewSpecialRoom();

    RoomType GetRoomType() override;
    void GenerateRoomDialogue() override;

    std::string ToString();
};

} //namespace Game

#endif