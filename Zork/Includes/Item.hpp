#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

namespace Game {

enum ItemIDs {
    None = 0,
    //Nicki's Kingdom
    NICKI_START = 1,
    NICKI_CROWN = 1, //Special Item
    NICKI_CANDLE,
    NICKI_ALBUM,
    NICKI_BARBS,
    NICKI_WIG, //Key Item
    NICKI_MAX,

    //Bandit World
    CB_START = NICKI_MAX+1,
    CB_CELLO = CB_START, //Key Item
    CB_SYNTH,
    CB_DRUMS,
    CB_ALBUM,
    CB_GRAMMY, //Special Item
    CB_MAX,

    //Twitter World
    TWT_START = CB_MAX+1,
    TWT_VIRAL = TWT_START, //Key Item
    TWT_KPOP,
    TWT_TRUMP,
    TWT_CANCELLED,
    TWT_VERIFY, //Special ITem
    TWT_MAX,

    //Gamer Globe
    GAMER_START = TWT_MAX+1,
    GAMER_JOYSTICK = GAMER_START, //Key Item
    GAMER_ANIMAL,
    GAMER_PARENTS,
    GAMER_KID,
    GAMER_KEYBOARD, //Special Item
    GAMER_MAX,

    //Code Graveyard
    CODE_START = GAMER_MAX+1,
    CODE_SKYPE,
    CODE_VIBER,
    CODE_IE,
    CODE_SNAKE,
    CODE_ZORK,

    CODE_MAX

};

enum ItemAttributesBitsEnum {
    Special = 1,
    Weapon = 2,
    Torch = 4,
    Key = 8
};

struct ItemAttributes { //Bitfield of attributes
    /* data */
    bool isSpecial : 1;
    bool isWeapon : 1;
    bool isTorch : 1;
    bool isKey : 1;
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
    bool IsKey() const;

    bool operator==(const Item& rhs);
    friend bool operator==(const Item& lhs, const Item& rhs);
};

} //namespace Game

#endif
