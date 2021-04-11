#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include "Item.hpp"

enum class NpcID {
    Nicki = 1,
    Bandit = 2,
    Twitter = 3,
    Gamer = 4,
    Code = 5
};

namespace Game {
class Npc
{
private:
    std::string npcName;
    std::string npcQuestion;
    std::string npcResponseNo;
    std::string npcResponseYes;
    Game::Item keyItem;
    NpcID npcID;

public:
    Npc(const std::string& npcName, const std::string& npcQuestion, const std::string& npcResponseNo, const std::string& npcResponseYes, const Game::Item& keyItem, const NpcID npcID);
    ~Npc();
    std::string GetNpcName() const;
    std::string GetNpcQuestion() const;
    std::string GetNpcResponseIncorrect() const; //No
    std::string GetNpcResponseCorrect() const; //Yes
    Game::Item GetKeyItem() const;
    NpcID GetNpcID() const;
};

}
#endif