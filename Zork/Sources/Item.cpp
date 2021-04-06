#include "Item.hpp"

namespace Game {

Item::Item() : Item("", ItemIDs::None, "", 0)
{

}

Item::Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const ItemAttributes& itemAttributes)
    : itemName(itemName), itemDescription(itemDescription), itemID(itemID), itemAttributes(itemAttributes)
{
    
}

Item::Item(const char* itemName, const uint8_t itemID, const char* itemDescription, const uint32_t itemAttributesRaw)
    : itemName(itemName), itemDescription(itemDescription), itemID(itemID), itemAttributesRaw(itemAttributesRaw)
{

}

bool Item::IsSpecial() const {
    return itemAttributes.isSpecial;
}

std::string Item::GetName() const {
    return itemName;
}

bool Item::operator==(const Item& rhs) {
    return this->itemID == rhs.itemID;
}

bool operator==(const Item& lhs, const Item& rhs) {
    return lhs.itemID == rhs.itemID;
}

} //namespace Game
