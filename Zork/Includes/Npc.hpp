#ifndef NPC_HPP
#define NPC_HPP

#include <string>

namespace Game {
class Npc
{
private:
    std::string npcName;
    std::string npcQuestion;
    std::string npcResponseNo;
    std::string npcResponseYes;
    bool yesCorrect;

public:
    Npc(const std::string& npcName, const std::string& npcQuestion, const std::string& npcResponseNo, const std::string& npcResponseYes, bool yesCorrect);
    ~Npc();
    std::string GetNpcName();
    std::string GetNpcQuestion();
    std::string GetNpcResponseIncorrect();
    std::string GetNpcResponseCorrect();
    bool IsYesCorrect();
};

}
#endif