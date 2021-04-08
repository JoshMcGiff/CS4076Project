#include "Zork.hpp"
#include "Item.hpp"
#include <ctime>

__attribute__((unused)) bool thisIsAUsefulVariable = false; //Unused Global Variable, only here due to the spec 

namespace Game {

Zork::Zork() : curWorld(nullptr), playerInventory() {
    srand(time(NULL));

    Game::Npc npc1("Nicki Minaj", "I have the key item for this world! But first, you must answer one simple question! Is Nicki Minaj the Queen of Rap?", "Wrong!", "Yes, I am the Queen of Rap! Take this item!", true);
    std::vector<Item> items1 = {{"Nicki's Candle", NICKI_CANDLE, "Pray to Queen Nicki", ItemAttributesBitsEnum::Key}, {"Pink Friday Album", NICKI_ALBUM, "Stream Super Bass", 0}, 
                                {"Nicki's Barb Army", NICKI_BARBS, "The Army of Nicki", ItemAttributesBitsEnum::Weapon}, {"Nicki's Wig", NICKI_WIG, "A Pink and White Wig", 0}};
    World* world1 = new World("Nicki's Kingdom", "Description", npc1, Game::Item("Nicki's Crown", NICKI_CROWN, "The Queens Crown", ItemAttributesBitsEnum::Special), items1);
    zorkWorlds[0] = world1;

    Game::Npc npc2("Nicki Minaj", "I have the key item for this world! But first, you must answer one simple question! Is Nicki Minaj the Queen of Rap?", "Wrong!", "Yes, I am the Queen of Rap! Take this item!", true);
    std::vector<Item> items2 = {{"Grace's Cello", CB_CELLO, "Clean Bandit's cello", ItemAttributesBitsEnum::Key|ItemAttributesBitsEnum::Weapon}, {"Jack's Synth", CB_SYNTH, "Clean Bandit's synth", 0}, 
                                {"Luke's Drums", CB_DRUMS, "Clean Bandit's drums", 0}, {"What Is Love? The Album", CB_ALBUM, "Clean Bandit's sophmore album", 0}};
    World* world2 = new World("Clean Bandit Land", "Description", npc2, Game::Item("Grammy Award", CB_GRAMMY, "Clean Bandit's 2014 Grammy Award", ItemAttributesBitsEnum::Special), items2);
    zorkWorlds[1] = world2;

    Game::Npc npc3("Nicki Minaj", "I have the key item for this world! But first, you must answer one simple question! Is Nicki Minaj the Queen of Rap?", "Wrong!", "Yes, I am the Queen of Rap! Take this item!", true);
    std::vector<Item> items3 = {{"Viral Tweet", TWT_VIRAL, "A viral Tweet", ItemAttributesBitsEnum::Key}, {"K-Pop Fans", TWT_KPOP, "Be wary of the K-Pop stans", 0}, 
                                {"Donald Trump's Banned Account", TWT_TRUMP, "This is Donald Trump's virtual graveyard", 0}, {"Cancelled User", TWT_CANCELLED, "You're cancelled!", ItemAttributesBitsEnum::Weapon}};
    World* world3 = new World("Twitterverse", "Description", npc3, Game::Item("Verification", TWT_VERIFY, "You got verified on Twitter!", ItemAttributesBitsEnum::Special), items3);
    zorkWorlds[2] = world3;

    Game::Npc npc4("Nicki Minaj", "I have the key item for this world! But first, you must answer one simple question! Is Nicki Minaj the Queen of Rap?", "Wrong!", "Yes, I am the Queen of Rap! Take this item!", true);
    std::vector<Item> items4 = {{"Golden Joystick", GAMER_JOYSTICK, "The best joystick ever", ItemAttributesBitsEnum::Key}, {"Animal Crossing Fans", GAMER_ANIMAL, "The best kind of fans", 0}, 
                                {"Candy Crush Parents", GAMER_PARENTS, "All parents are professionals at the point", ItemAttributesBitsEnum::Weapon}, {"iPad Kids", GAMER_KID, "\"Do you have any games? Have you Fortnite?\"", 0}};
    World* world4 = new World("Gamer Globe", "Description", npc4, Game::Item("RGB Keyboard", GAMER_KEYBOARD, "Do you even game bro?", ItemAttributesBitsEnum::Special), items4);
    zorkWorlds[3] = world4;

    Game::Npc npc5("Nicki Minaj", "I have the key item for this world! But first, you must answer one simple question! Is Nicki Minaj the Queen of Rap?", "Wrong!", "Yes, I am the Queen of Rap! Take this item!", true);
    std::vector<Item> items5 = {{"Skype", CODE_SKYPE, "Skype walked so Microsoft Teams could run", ItemAttributesBitsEnum::Key}, {"Viber", CODE_VIBER, "Remember Viber?", 0}, 
                                {"Internet Explorer", CODE_IE, "R.I.P Internet Explorer 2020", ItemAttributesBitsEnum::Weapon}, {"Nokia Snake", CODE_SNAKE, "Where is the snake now?", 0}};
    World* world5 = new World("Code Graveyard", "Description", npc5, Game::Item("Zork", CODE_ZORK, "Replaced by a Brand New and Exciting Game: Pork!", ItemAttributesBitsEnum::Special), items5);
    zorkWorlds[4] = world5;
}

Zork::~Zork() {
    for (size_t i = 0; i < zorkWorlds.size(); i++) {
        World* world = zorkWorlds[i];
        if (world != nullptr) {
            delete world;
        }
        zorkWorlds[i] = nullptr;
    }
}

World* Zork::GetCurrentWorld() {
    return curWorld;
}

int Zork::MoveNorth() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveNorth: World does not exist");
        return 1;
    }

    curWorld->MoveNorth();
    return 0;
}

void Zork::MoveSouth() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveSouth: World does not exist");
        return;
    }

    curWorld->MoveSouth();
}

void Zork::MoveEast() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveEast: World does not exist");
        return;
    }

    curWorld->MoveEast();
}

void Zork::MoveWest() {
    if (curWorld == nullptr) {
        throw ZorkException("MoveWest: World does not exist");
        return;
    }

    curWorld->MoveWest();
}

bool Zork::SetWorld(size_t index) {
    if (index <= zorkWorlds.size()) {
        this->curWorld = zorkWorlds[index];
        return true;
    }
    return false;
}

World* Zork::GetWorld(size_t index) {
    if (index >= this->zorkWorlds.size()) {
        return nullptr;
    }

    return zorkWorlds[index];
}

size_t Zork::GetWorldAmount() {
    return zorkWorlds.size();
}

Room* Zork::GetCurrentRoom() {
    if (this->curWorld) {
        return this->curWorld->GetCurrentRoom();
    }
    return nullptr;
}

std::vector<Game::Item>* Zork::GetInventoryItems() {
    return &this->playerInventory;
}

size_t Zork::GetInventoryItemAmount() {
    return this->playerInventory.size();
}

bool Zork::AddItemToInventory(const Item& item) {
    this->playerInventory.push_back(item);
    if (this->curWorld && item.IsKey()) {
        this->curWorld->CollectedKeyItem();
    }

    return true;
}

bool Zork::RemoveItemFromInventory(const size_t index) {
    if (index >= this->playerInventory.size()) {
        return false;
    }

    this->playerInventory.erase(this->playerInventory.begin()+index);
    return true;
}

bool Zork::GetItemFromInventory(const size_t index, Game::Item& item) {
    if (index >= this->playerInventory.size()) {
        return false;
    }

    item = this->playerInventory[index];
    return true;
}

void Zork::ClearInventory() {
    this->playerInventory.clear();
}

} //namespace Game
