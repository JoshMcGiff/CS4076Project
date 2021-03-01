#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

//Could be done at compile time


enum ItemIDs {
    Torch = 0,



    //Pink World stuffs
    PINK_MIN = 1,
    PINK_WAND = 1,




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
    uint8_t itemID;
    std::string itemDescription;
    ItemAttributes itemAttributes;

public:
    Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const ItemAttributes& itemAttributes);

    bool IsSpecial();
};

#endif