#ifndef ROOMATTRIBUTE_HPP
#define ROOMATTRIBUTE_HPP

namespace Game {

enum class AttributeEnum : int { // Different room attributes. Using class to avoid conflicts
    CHILLY = 0,
    HOT = 1,
    DARK = 2,
    SUNNY = 3,
    EERIE = 4,
    CALM = 5,
    SLIPPY = 6,
    STICKY = 7,
    WET = 8,
    MUSIC = 9,

    ATTRIBUTE_MAX
};

class RoomAttribute {
    protected:
        RoomAttribute();
        AttributeEnum roomAttribute;
    public:
        AttributeEnum GetAttribute() const;
        void SetAttribute(AttributeEnum& attribute);
};

} //namespace Game

#endif
