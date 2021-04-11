#include "Npc.hpp"

namespace Game {
    Npc::Npc(const std::string& npcName, const std::string& npcQuestion, const std::string& npcResponseNo, const std::string& npcResponseYes, const Game::Item& keyItem, const NpcID npcID)
        : npcName(npcName), npcQuestion(npcQuestion), npcResponseNo(npcResponseNo), npcResponseYes(npcResponseYes), keyItem(keyItem), npcID(npcID)
    {

    }

    Npc::~Npc()
    {

    }

    std::string Npc::GetNpcName() const {
        return npcName;
    }

    std::string Npc::GetNpcQuestion() const {
        return npcQuestion;
    }

    std::string Npc::GetNpcResponseIncorrect() const {
        return npcResponseNo;
    }

    std::string Npc::GetNpcResponseCorrect() const {
        return npcResponseYes;
    }

    NpcID Npc::GetNpcID() const {
        return npcID;
    }

    Game::Item Npc::GetKeyItem() const {
        return keyItem;
    }
}
