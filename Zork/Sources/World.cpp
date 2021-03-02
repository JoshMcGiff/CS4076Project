#include <cstdio>
#include <ctime>
#include "World.hpp"

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

World::World(const char* name, const char* desc) : worldName(name), worldDescription(desc) {
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

void World::GenerateRooms(int row, int col, int roomChance) {
    if ((roomChance <= 0) || (row >= ROW_COUNT) || (col >= COL_COUNT)) { //Setting the bounds of the room generation
        return;
    }

    GenerateItems();

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
    
    
}

void World::GenerateItems() { /*
    Item item = GetItem(itemIndex);

    if (!item.IsSpecial()) {
        int random = rand() % 100; //Gen number between 0 to 99

        if (random >= ITEM_CHANCE)
            return;
    }

    this->roomItems.push_back(item);

    this->world->itemIndex++; */
}

void World::Generate() {
    for (auto& array : roomArray) {
        array.fill(nullptr); //Set everything in 2D array to nullptr
    }

    srand(time(NULL));
    this->GenerateRooms(ROW_COUNT / 2, COL_COUNT / 2, BASE_ROOM_CHANCE); //Start in middle of array
    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COL_COUNT; j++) {
            if((roomArray[i][j] != nullptr) && roomArray[i][j]->GetRoomType() == RoomType::Special){ // Make sure to check for nullptr for element because it's being accessed not just printed
                printf("\t\t\t%X\t\t\t", roomArray[i][j]);
            }else{
                printf("%X\t", roomArray[i][j]);
            }
        }
        printf("\n");
    }
    //Do special rooms here
}

} //namespace Game
