#include <cstdio>
#include <ctime>
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

World::World(const char* name, const char* desc) : worldName(name), worldDescription(desc), keyItem("Name", 0, "Desc", 0), iRow(START_ROW), jCol(START_COL) {
    this->Generate();
}

void World::SetItems(std::vector<Item>&& worldItems) {
    this->worldItems = worldItems;

    //TODO: randomise order
}

Item World::GetItem(int index) {
    //TODO: check index in bounds, make items shared pointer

    return worldItems[index];
}

Room* World::MoveNorth(){
    jCol += 1;
    return roomArray[iRow][jCol];
}

Room* World::MoveSouth(){
    jCol -= 1;
    return roomArray[iRow][jCol];
}

Room* World::MoveEast(){
    iRow += 1;
    return roomArray[iRow][jCol];
}

Room* World::MoveWest(){
    iRow -= 1;
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

    GenerateItems(row, col);
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

void World::GenerateItems(int row, int col) { 
    static uint32_t itemIndex = 0;

    if (itemIndex > worldItems.size()) {
        itemIndex = 0;
    }

    Room* room = roomArray[row][col];
    if (room != nullptr) {
        room->AddItem(GetItem(itemIndex));
        itemIndex++;
    }
}

void World::Generate() {
    for (auto& array : roomArray) {
        array.fill(nullptr); //Set everything in 2D array to nullptr
    }

    srand(time(NULL));
    this->GenerateRooms(START_ROW, START_COL, BASE_ROOM_CHANCE); //Start in middle of array
    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COL_COUNT; j++) {
            printf("%X\t", roomArray[i][j]);
        }
        printf("\n");
    }   
    this->GenerateSpecialRoom(START_ROW, START_COL);
    //Do special rooms here
}

} //namespace Game
