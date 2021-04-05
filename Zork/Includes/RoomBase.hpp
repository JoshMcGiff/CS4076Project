#ifndef ROOMBASE_HPP
#define ROOMBASE_HPP

#include <string>

namespace Game {

enum class RoomType {
    Normal = 0,
    Special = 1,
};

class RoomBase { //Abstract class for Room base
protected:
    RoomBase(); //protected constructor as RoomBase shouldn't be used as a class
    virtual ~RoomBase();
    std::string roomDialogue;

public:
    virtual RoomType GetRoomType() = 0;
    virtual std::string GetRoomDialogue() = 0;
    virtual void GenerateRoomDialogue() = 0;
};

} //namespace Game

#endif
