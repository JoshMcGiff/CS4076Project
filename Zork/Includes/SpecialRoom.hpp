#ifndef SPECIALROOM_HPP
#define SPECIALROOM_HPP

#include "Room.hpp"
namespace Game {

class SpecialRoom : public Room {
protected:
    SpecialRoom();
private:

public:
    ~SpecialRoom();
    static SpecialRoom* NewSpecialRoom();

    RoomType GetRoomType() override;
    void GenerateRoomDialogue() override;
    void SetRoomDialogue(std::string dialogue,std::string itemName) override;

    std::string ToString();
};

} //namespace Game

#endif