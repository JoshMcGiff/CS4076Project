#include <cstdio>
#include "World.hpp"
#include <math.h>
#include <iostream>

namespace Game {

#define BASE_ROOM_CHANCE 100
#define CHANCE_DECREASE 55
#define ITEM_CHANCE 75
#define SPECIAL_ROOM_CHANCE 100

#if __cplusplus >= 201703L //'register' keyword was removed in C++17
    #define REGISTER 
#else 
    #define REGISTER register
#endif

World::World(const char* name, const char* desc, Game::Item&& keyItem, std::vector<Item>& worldItems) 
    : worldName(name), worldDescription(desc), keyItem(keyItem), iRow(START_ROW), jCol(START_COL)
{
    this->SetItems(worldItems);
    this->Generate();
}

World::~World() {
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            if (roomArray[i][j] != nullptr) {
                delete roomArray[i][j];
                roomArray[i][j] = nullptr;
            }
        }
    }
}

void World::SetItems(std::vector<Item>& worldItems) {
    this->worldItems = worldItems;

    //TODO: randomise order
}

Item World::GetItem(int index) {
    if (worldItems.empty()) {
        return Item("Empty", 0xFF, "Empty Item", 0);
    }

    if (index < 0 || index >= worldItems.size()) {
        index = 0;
    }

    return worldItems[index];
}

Room* World::MoveNorth(){
    if(roomArray[iRow-1][jCol] == nullptr){
        return roomArray[iRow][jCol]; // if doesnt exist return the current room
    }else{
        iRow -= 1;
    }
    
    return roomArray[iRow][jCol];
}

Room* World::MoveSouth(){
    
    if(roomArray[iRow+1][jCol] == nullptr){
        return roomArray[iRow][jCol]; // if doesnt exist return the current room
    }else{
        iRow += 1;
    }
    return roomArray[iRow][jCol];
}

Room* World::MoveEast(){
    if(roomArray[iRow][jCol+1] == nullptr){
        return roomArray[iRow][jCol]; // if doesnt exist return the current room
    }else{
        jCol += 1;
    }
    return roomArray[iRow][jCol];
}

Room* World::MoveWest(){
    if(roomArray[iRow][jCol-1] == nullptr){
        return roomArray[iRow][jCol]; // if doesnt exist return the current room
    }else{
        jCol -= 1;
    }
    return roomArray[iRow][jCol];
}

void World::GenerateRooms(int row, int col, int roomChance) {
    if ((roomChance <= 0) || (row >= ROW_COUNT) || (col >= COL_COUNT)) { //Setting the bounds of the room generation
        return;
    }

    REGISTER int random = 0;
    if ((row+1 < ROW_COUNT) && this->roomArray[row+1][col] == nullptr) { //North
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row+1][col] = new Room();
            GenerateRooms(row+1, col, roomChance-CHANCE_DECREASE);
        }
    }

    if ((row-1 >= 0) && this->roomArray[row-1][col] == nullptr) { //South
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row-1][col] = new Room();
            GenerateRooms(row-1, col, roomChance-CHANCE_DECREASE);
        }
    }

    if ((col+1 < COL_COUNT) && this->roomArray[row][col+1] == nullptr) { //East
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row][col+1] = new Room();
            GenerateRooms(row, col+1, roomChance-CHANCE_DECREASE);
        }
    }
    
    if ((col-1 >= 0) && this->roomArray[row][col-1] == nullptr) { //West
        random = rand() % 100; //Gen number between 0 to 99
        if (random < roomChance) {
            this->roomArray[row][col-1] = new Room();
            GenerateRooms(row, col-1, roomChance-CHANCE_DECREASE);
        }
    }
}

void World::GenerateSpecialRoom(int row, int col){
    REGISTER int random = 0;
    random = rand() % 4;
    switch(random){
        case 0:
            for(int i = row-1; i < ROW_COUNT; i++){
                if(roomArray[row+i][col] == nullptr){
                    roomArray[row+i][col] = new SpecialRoom();
                    roomArray[row+i][col]->GetRoomItems().push_back(keyItem);
                    return;
                }
            }
            break;
        case 1:
            for(int i = row-1; i < ROW_COUNT; i++){
                if(roomArray[row + (row - i - 1)][col] == nullptr){
                    roomArray[row + (row - i - 1)][col] = new SpecialRoom();
                    roomArray[row + (row - i - 1)][col]->GetRoomItems().push_back(keyItem);
                    return;
                }       
            }
            break;
        case 2: 
            for(int j = col-1; j < COL_COUNT; j++){
                if(roomArray[row][col+j] == nullptr){
                    roomArray[row][col+j] = new SpecialRoom();
                    roomArray[row][col+j]->GetRoomItems().push_back(keyItem);
                    return;
                }
            }
            break;
        case 3:
            for(int j = col-1; j < COL_COUNT; j++){
                if(roomArray[row][col + (col - j - 1)] == nullptr){
                    roomArray[row][col + (col - j - 1)] = new SpecialRoom();
                    roomArray[row][col + (col - j - 1)]->GetRoomItems().push_back(keyItem);
                    return;
                }
            }
            break;
    }
}

void World::GenerateItems() { // call generateitems after generate rooms
    bool specialItemAdded = false;
    for (int row = 0; (row < ROW_COUNT) && !specialItemAdded; row++) {
        for (int col = 0; (col < COL_COUNT) && !specialItemAdded; col++) {
            Room* room = roomArray[row][col];
            if (room != nullptr) {
                if (room->GetRoomType() == Game::RoomType::Special) {
                    printf("Added Special Item\n");
                    room->AddItem(keyItem);
                    specialItemAdded = true;
                }
            }
        }
    }

    if (worldItems.empty()) {
        return;
    }

    uint32_t itemIndex = 0;
    while (itemIndex < worldItems.size()) {
        REGISTER int col = rand() % COL_COUNT; //Gen number between 0 to 99
        REGISTER int row = rand() % ROW_COUNT; //Gen number between 0 to 99

        Room* room = roomArray[row][col];
        if (room != nullptr) {
            if (room->GetRoomType() != Game::RoomType::Special) {
                room->AddItem(GetItem(itemIndex));
            }
   itemIndex++;
        }
    }
}

void World::Generate() {
    for (auto& array : roomArray) {
        array.fill(nullptr); //Set everything in 2D array to nullptr
    }

    this->roomArray[START_ROW][START_COL] = new Room(); //Generate starting room
    this->GenerateRooms(START_ROW, START_COL, BASE_ROOM_CHANCE); //Start in middle of array
    this->GenerateSpecialRoom(START_ROW, START_COL);
    this->GenerateItems();

    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COL_COUNT; j++) {
            printf("%X\t", roomArray[i][j]);
        }
        printf("\n");
    }   
    printf("\n");
}

} //namespace Game
