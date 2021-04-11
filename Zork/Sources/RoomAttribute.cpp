#include "RoomAttribute.hpp"

namespace Game {

RoomAttribute::RoomAttribute() {
    
}

AttributeEnum RoomAttribute::GetAttribute() const {
    return roomAttribute;
}

void RoomAttribute::SetAttribute(AttributeEnum& attribute) {
    roomAttribute = attribute;
}

} //namespace Game

