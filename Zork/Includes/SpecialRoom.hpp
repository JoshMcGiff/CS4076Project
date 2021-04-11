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
    void GenerateRoomDialogue() override; //Not called in ctor as virtual, wrong version may be called/considered bad practise
    void SetRoomDialogue(const std::string& dialogue, const std::string& itemName) override;

    std::string ToString();
};

} //namespace Game

#endif
