#ifndef OOP_OBSERVERS_H
#define OOP_OBSERVERS_H

#include "npc.h"

class TextObserver : public IFightObserver
{
public:
    static std::shared_ptr<IFightObserver> get();
    void inFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool isWin);

private:
    TextObserver() {}
};

class FileObserver : public IFightObserver
{
public:
    static std::shared_ptr<IFightObserver> get();
    void inFight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool isWin);

private:
    FileObserver() {}

    std::string NPCgetType(const NpcType& type);
    std::ofstream file;
};

#endif //OOP_OBSERVERS_H