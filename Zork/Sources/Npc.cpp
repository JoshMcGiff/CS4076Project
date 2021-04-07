#include "Npc.hpp"
namespace Game{
    Npc::Npc(const std::string& npcName, const std::string& npcQuestion, const std::string& npcResponseNo, const std::string& npcResponseYes, bool yesCorrect)
        : npcName(npcName), npcQuestion(npcQuestion), npcResponseNo(npcResponseNo), npcResponseYes(npcResponseYes), yesCorrect(yesCorrect)
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


    bool Npc::IsYesCorrect() {
        return yesCorrect;
    }

}
