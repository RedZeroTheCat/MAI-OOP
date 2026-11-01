#ifndef OOP_NPC_H
#define OOP_NPC_H

#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <ctime>
#include <unordered_map>

struct NPC;
struct Slaver;
struct Druid;
struct Orc;

enum NpcType
{
    SlaverType,
    DruidType,
    OrcType
};

const int NPC_TYPES = 3;

struct IFightObserver
{
    virtual void inFight(const std::shared_ptr<NPC>&, const std::shared_ptr<NPC>&, bool) = 0;
};

struct FightVisitor
{
    virtual bool visit(const std::shared_ptr<Slaver>&) const = 0;
    virtual bool visit(const std::shared_ptr<Druid>&) const = 0;
    virtual bool visit(const std::shared_ptr<Orc>&) const = 0;
};

class NPC : public std::enable_shared_from_this<NPC>
{
public:
    NPC(NpcType, const std::string&, int, int);
    NPC(NpcType, std::istream&);

    NpcType& getType();
    std::string getName();
    int getX() const;
    int getY() const;

    void subscribe(const std::shared_ptr<IFightObserver>&);
    void fightNotify(const std::shared_ptr<NPC>&, bool);

    bool inRange(const std::shared_ptr<NPC>&, size_t) const;

    virtual bool accept(const std::shared_ptr<FightVisitor>&, const std::shared_ptr<NPC>&) const = 0;
    virtual void save(std::ostream&);
    virtual void print() = 0;

    friend std::ostream& operator<<(std::ostream&, NPC&);

    ~NPC() = default;

protected:
    NpcType type;
    std::string name;
    int x;
    int y;
    std::vector<std::shared_ptr<IFightObserver>> observers;
};

#endif //OOP_NPC_H