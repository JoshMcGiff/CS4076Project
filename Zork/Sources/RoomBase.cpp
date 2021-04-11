#include "RoomBase.hpp"

namespace Game {

RoomBase::RoomBase() {
    #ifdef ZORK_DEBUG
    printf("1: Construting RoomBase Object!\n");
    #endif
}

RoomBase::~RoomBase() { }

}
