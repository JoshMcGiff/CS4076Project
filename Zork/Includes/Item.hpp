#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

namespace Game {

enum ItemIDs {
    None = 0,
    Torch = 1,



    //Pink World stuffs
    PINK_MIN = 2,
    PINK_WAND = 2,




    NICKIS_WIG,
    PINK_MAX,


    //Badnit World
    Fiddle = 11,



    Album = 17,

};

struct ItemAttributes { //Bitfield of attributes
    /* data */
    bool isSpecial : 1;
    bool isWeapon : 1;
    bool isTorch : 1;

};

class Item {
private:
    /* data */
    std::string itemName;
    std::string itemDescription;
    uint16_t itemID;
    union {
        ItemAttributes itemAttributes;
        uint32_t itemAttributesRaw;
    };

public:
    Item();
    Item(const Item& item);
    Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const ItemAttributes& itemAttributes);
    Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const uint32_t itemAttributesRaw);
    std::string GetName() const;
    bool IsSpecial() const;

    bool operator==(const Item& rhs);
    friend bool operator==(const Item& lhs, const Item& rhs);
};

} //namespace Game

#endif
