#include "Item.hpp"

Item::Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const ItemAttributes &itemAttributes)
    : itemName(itemName), itemID(itemID), itemDescription(itemDescription), itemAttributes(itemAttributes)
{
    
}

bool Item::IsSpecial() {
    return itemAttributes.isSpecial;
}