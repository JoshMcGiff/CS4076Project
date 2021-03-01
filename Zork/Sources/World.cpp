#include "World.hpp"
#define DEFAULT_DEPTH 6
#define SPECIAL_DEPTH 6
#define ROOM_CHANCE 50
#define ITEM_CHANCE 75

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

void World::GenerateRooms() {
    static uint32_t depthCount = 0;
    static int row = 5;
    static int col = 5;
    if (depthCount >= DEFAULT_DEPTH) {
        return;
    }

    GenerateItems();

    depthCount++;

    REGISTER int random = 0;

    if (this->roomArray[row+1][col] == nullptr) { //North
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomArray[row+1][col] = new Room();
            row++;
            GenerateRooms();
            row--;
        }
    }

    if (this->roomArray[row-1][col] == nullptr) { //South
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomArray[row-1][col] = new Room();
            row--;
            GenerateRooms();
            row++;
        }
    }

    if (this->roomArray[row][col+1] == nullptr) { //East
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomArray[row][col+1] = new Room();
            col++;
            GenerateRooms();
            col--;
        }
    }
    
    if (this->roomArray[row][col-1] == nullptr) { //West
        random = rand() % 100; //Gen number between 0 to 99
        if (random < ROOM_CHANCE) {
            this->roomArray[row][col-1] = new Room();
            col--;
            GenerateRooms();
            col++;
        }
    }
    depthCount--;
    row--;
    col--;
}

void World::GenerateSpecialRoom(){
    int random = rand() % 100;
    int row = roomArray.size() / 2;
    int col = roomArray[0].size() / 2;
    if(random < 25){
        if(roomArray[row+1][col] == nullptr){
            
        }
    }
}

void Room::GenerateItems() {
    Item item = GetItem(itemIndex);

    if (!item.IsSpecial()) {
        int random = rand() % 100; //Gen number between 0 to 99

        if (random >= ITEM_CHANCE)
            return;
    }

    this->roomItems.push_back(item);

    this->world->itemIndex++;
}

void World::Generate() {
    for (auto& array : roomArray) {
        array.fill(nullptr); //Set everything in 2D array to nullptr
    }


    this->GenerateRooms();
    
    //Do special rooms here
}