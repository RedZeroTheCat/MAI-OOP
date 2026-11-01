#ifndef OOP_ORC_H
#define OOP_ORC_H

#include "npc.h"

struct OrcVisitor : public FightVisitor
{
    bool visit(const std::shared_ptr<Slaver>&) const override;
    bool visit(const std::shared_ptr<Druid>&) const override;
    bool visit(const std::shared_ptr<Orc>&) const override;
};

class Orc : public NPC
{
public:
    Orc();
    Orc(const std::string& name, int, int);
    Orc(std::istream&);

    void save(std::ostream&) override;
    bool accept(const std::shared_ptr<FightVisitor>&, const std::shared_ptr<NPC>&) const override;
    friend std::ostream& operator<<(std::ostream&, Orc&);
    void print() override;

    ~Orc() = default;
};

#endif //OOP_ORC_H