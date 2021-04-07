#include "RoomBase.hpp"

namespace Game {

RoomBase::RoomBase() {
    #ifdef ZORK_DEBUG
    printf("Construting RoomBase Object!\n");
    #endif
}

RoomBase::~RoomBase() { }

}
