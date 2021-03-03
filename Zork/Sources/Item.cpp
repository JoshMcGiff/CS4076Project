#include "Item.hpp"

namespace Game {

Item::Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const ItemAttributes& itemAttributes)
    : itemName(itemName), itemID(itemID), itemDescription(itemDescription), itemAttributes(itemAttributes)
{
    
}

Item::Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const uint32_t itemAttributesRaw)
    : itemName(itemName), itemID(itemID), itemDescription(itemDescription), itemAttributesRaw(itemAttributesRaw)
{
    
}

bool Item::IsSpecial() {
    return itemAttributes.isSpecial;
}

} //namespace Game
