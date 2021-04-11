#include <cstdio>
#include "World.hpp"
#include <math.h>
#include <iostream>

namespace Game {

#define BASE_ROOM_CHANCE 100
#define CHANCE_DECREASE 55
#define ITEM_CHANCE 75
#define SPECIAL_ROOM_CHANCE 100

#if __cplusplus >= 201703L //'register' keyword was removed in C++17 (not in spec, but asked to do it in the lectures)
    #define REGISTER 
#else 
    #define REGISTER register
#endif

    World::World(const char *name, const char *desc, Game::Npc& npc, Game::Item&& specialItem, std::vector<Item>& worldItems)
        : worldName(name), worldDescription(desc), worldNpc(npc), specialItem(specialItem), iRow(START_ROW), jCol(START_COL), hasCollectedKeyItem(false)
    {
        this->SetItems(worldItems);
        this->Generate();
}

World::~World() {
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
                delete roomArray[i][j]; //delete each room. if room is a nullptr, delete is unaffected as per the C++ standard.
                roomArray[i][j] = nullptr;
        }
    }
}

void World::SetItems(std::vector<Item>& worldItems) {
    this->worldItems = worldItems;
}

Item World::GetItem(size_t index) {
    if (index >= worldItems.size()) {
        index = 0;
    }

    return worldItems[index];
}

Room* World::MoveNorth(){
    if(roomArray[iRow-1][jCol] != nullptr) { //if exists, move row before return. Otherwise return current room
        RoomType roomtype = roomArray[iRow-1][jCol]->GetRoomType();
        if((hasCollectedKeyItem && (roomtype == RoomType::Special)) || roomtype == RoomType::Normal) { 
            iRow -= 1;
        }
    }
    return roomArray[iRow][jCol];
}

Room* World::MoveSouth(){
    if(roomArray[iRow+1][jCol] != nullptr) { //if exists, move row before return. Otherwise return current room
        RoomType roomtype = roomArray[iRow+1][jCol]->GetRoomType();
        if((hasCollectedKeyItem && (roomtype == RoomType::Special)) || roomtype == RoomType::Normal) {
            iRow += 1;
        }
    }
    return roomArray[iRow][jCol];
}

Room* World::MoveEast(){
    if(roomArray[iRow][jCol+1] != nullptr) { //if exists, move col before return. Otherwise return current room
        RoomType roomtype = roomArray[iRow][jCol+1]->GetRoomType();
        if((hasCollectedKeyItem && (roomtype == RoomType::Special)) || roomtype == RoomType::Normal) { 
            jCol += 1;
        }
    }
    return roomArray[iRow][jCol];
}

Room* World::MoveWest(){
    if(roomArray[iRow][jCol-1] != nullptr) { //if exists, move col before return. Otherwise return current room
        RoomType roomtype = roomArray[iRow][jCol-1]->GetRoomType();
        if((hasCollectedKeyItem && (roomtype == RoomType::Special)) || roomtype == RoomType::Normal) { 
            jCol -= 1;
        }
    }
    return roomArray[iRow][jCol];
}

void World::GenerateRooms(int row, int col, int roomChance) {
    if ((roomChance <= 0) || (row >= ROW_COUNT) || (col >= COL_COUNT)) { //Setting the bounds of the room generation recursion
        return;
    }

    REGISTER int random = 0; //use register keyword here (not in spec, but asked to do it in the lectures)
    if ((row+1 < ROW_COUNT) && this->roomArray[row+1][col] == nullptr) { //North
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row+1][col] = Room::NewRoom();
            GenerateRooms(row+1, col, roomChance-CHANCE_DECREASE);
        }
    }

    if ((row-1 >= 0) && this->roomArray[row-1][col] == nullptr) { //South
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row-1][col] = Room::NewRoom();
            GenerateRooms(row-1, col, roomChance-CHANCE_DECREASE);
        }
    }

    if ((col+1 < COL_COUNT) && this->roomArray[row][col+1] == nullptr) { //East
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row][col+1] = Room::NewRoom();
            GenerateRooms(row, col+1, roomChance-CHANCE_DECREASE);
        }
    }
    
    if ((col-1 >= 0) && this->roomArray[row][col-1] == nullptr) { //West
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row][col-1] = Room::NewRoom();
            GenerateRooms(row, col-1, roomChance-CHANCE_DECREASE);
        }
    }
}

void World::GenerateSpecialRoom(int row, int col){
    REGISTER int random = rand() % 4; //use register keyword here (not in spec, but asked to do it in the lectures)

    switch(random){
        case 0:
            for(int i = row-1; i < ROW_COUNT; i++){
                if(roomArray[row+i][col] == nullptr){
                    roomArray[row+i][col] = dynamic_cast<Room*>(SpecialRoom::NewSpecialRoom()); //uses dynamic_cast here for casting Special Room to Room
                    roomArray[row+i][col]->AddItem(specialItem);
                    roomArray[row+i][col]->SetRoomDialogue(specialItem.GetItemDescription(), specialItem.GetName());
                    return;
                }
            }
            break;
        case 1:
            for(int i = row-1; i < ROW_COUNT; i++){
                if(roomArray[row + (row - i - 1)][col] == nullptr){
                    roomArray[row + (row - i - 1)][col] = dynamic_cast<Room*>(SpecialRoom::NewSpecialRoom()); //uses dynamic_cast here for casting Special Room to Room
                    roomArray[row + (row - i - 1)][col]->AddItem(specialItem);
                    roomArray[row + (row - i - 1)][col]->SetRoomDialogue(specialItem.GetItemDescription(), specialItem.GetName());
                    return;
                }       
            }
            break;
        case 2: 
            for(int j = col-1; j < COL_COUNT; j++){
                if(roomArray[row][col+j] == nullptr){
                    roomArray[row][col+j] = dynamic_cast<Room*>(SpecialRoom::NewSpecialRoom()); //uses dynamic_cast here for casting Special Room to Room
                    roomArray[row][col+j]->AddItem(specialItem);
                    roomArray[row][col+j]->SetRoomDialogue(specialItem.GetItemDescription(), specialItem.GetName());
                    return;
                }
            }
            break;
        case 3:
            for(int j = col-1; j < COL_COUNT; j++){
                if(roomArray[row][col + (col - j - 1)] == nullptr){
                    roomArray[row][col + (col - j - 1)] = dynamic_cast<Room*>(SpecialRoom::NewSpecialRoom()); //uses dynamic_cast here for casting Special Room to Room
                    roomArray[row][col + (col - j - 1)]->AddItem(specialItem);
                    roomArray[row][col + (col - j - 1)]->SetRoomDialogue(specialItem.GetItemDescription(), specialItem.GetName());
                    return;
                }
            }
            break;
    }
}

void World::GenerateNpc() { // add the npc to a single room in the world
    bool setNpc = false;
    while (!setNpc) {
        REGISTER int col = rand() % COL_COUNT; //Gen number between 0 to COL_COUNT
        REGISTER int row = rand() % ROW_COUNT; //Gen number between 0 to ROW_COUNT

        Room* room = roomArray[row][col];
        if (room != nullptr) {
            if (room->GetRoomType() != Game::RoomType::Special && room->GetRoomItemAmount() == 0) { //NPC can't be in a special room + room must have 0 items
                setNpc = room->SetNpc(true);
            }
        }
    }
}

void World::GenerateItems() { // call generate items after generate rooms
    if (worldItems.empty()) {
        return;
    }

    uint32_t itemIndex = 0;
    while (itemIndex < worldItems.size()) {
        REGISTER int col = rand() % COL_COUNT; //Gen number between 0 to COL_COUNT
        REGISTER int row = rand() % ROW_COUNT; //Gen number between 0 to ROW_COUNT

        Room* room = roomArray[row][col];
        if (room != nullptr) {
            if (room->GetRoomType() != Game::RoomType::Special) {
                room->AddItem(GetItem(itemIndex));
                itemIndex++;
            }
        }
    }
}

Room* World::GetCurrentRoom() const {
    return roomArray[iRow][jCol];
}

void World::CollectKeyItem() {
    hasCollectedKeyItem = true;
}

bool World::HasCollectedKeyItem() const {
    return hasCollectedKeyItem;
}

std::string World::GetWorldName() const {
    return this->worldName;
}

Game::Npc World::GetNpc() const {
    return this->worldNpc;
}

void World::Generate() {
    for (auto& array : roomArray) {
        array.fill(nullptr); //Set everything in 2D array to nullptr
    }

    this->roomArray[START_ROW][START_COL] = Room::NewRoom(); //Generate starting room
    this->GenerateRooms(START_ROW, START_COL, BASE_ROOM_CHANCE); //Start in middle of array
    this->GenerateSpecialRoom(START_ROW, START_COL);
    this->GenerateItems();
    this->GenerateNpc();

    #ifdef ZORK_DEBUG //print rooms only in debug mode (uses preprocessors)
    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COL_COUNT; j++) {
            Room* room = roomArray[i][j];
            if ((!room) || room->GetRoomType() != RoomType::Special) {
                this->PrintRoom<Game::Room>(room); //template function
            }
            else this->PrintRoom<Game::SpecialRoom>(dynamic_cast<Game::SpecialRoom*>(room)); //template function
        }
        printf("\n");
    }   
    printf("\n\n");
    #endif
}

} //namespace Game
