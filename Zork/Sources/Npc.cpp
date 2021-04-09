#include "Npc.hpp"

namespace Game {
    Npc::Npc(const std::string& npcName, const std::string& npcQuestion, const std::string& npcResponseNo, const std::string& npcResponseYes, const Game::Item& keyItem, const NpcID npcID)
        : npcName(npcName), npcQuestion(npcQuestion), npcResponseNo(npcResponseNo), npcResponseYes(npcResponseYes), keyItem(keyItem), npcID(npcID)
    {

    }

    Npc::~Npc()
    {

    }

    std::string Npc::GetNpcName() {
        return npcName;
    }

    std::string Npc::GetNpcQuestion() {
        return npcQuestion;
    }

    std::string Npc::GetNpcResponseIncorrect() {
        return npcResponseNo;
    }

    std::string Npc::GetNpcResponseCorrect() {
        return npcResponseYes;
    }

    NpcID Npc::GetNpcID() {
        return npcID;
    }

    Game::Item Npc::GetKeyItem() {
        return keyItem;
    }
}
