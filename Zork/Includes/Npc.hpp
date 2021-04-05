#ifndef NPC_HPP
#define NPC_HPP

#include <string>

namespace Game {
class Npc
{
private:
    std::string npcName;
    std::string npcDescription;
public:
    Npc(std::string npcName, std::string npcDescription);
    ~Npc();
};



}
#endif