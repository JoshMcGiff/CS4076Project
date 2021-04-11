#include "Item.hpp"

namespace Game {

Item::Item() : Item("", ItemIDs::None, "", 0)
{

}

Item::Item(const Item& item) { //Shallow copy
    this->itemName = item.itemName;
    this->itemDescription = item.itemDescription;
    this->itemID = item.itemID;
    this->itemAttributesRaw = item.itemAttributesRaw;
}

Item::Item(const char *itemName, const uint8_t itemID, const char *itemDescription, const ItemAttributes &itemAttributes)
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
bool Item::IsKey() const {
    return itemAttributes.isKey;
}

std::string Item::GetItemDescription() const {
    return itemDescription;
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
