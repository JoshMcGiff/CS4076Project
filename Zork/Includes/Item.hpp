#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

struct ItemAttributes {
    /* data */
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
    
};

#endif