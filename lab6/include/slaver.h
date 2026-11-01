#ifndef OOP_SLAVER_H
#define OOP_SLAVER_H

#include "npc.h"

struct SlaverVisitor : public FightVisitor
{
    bool visit(const std::shared_ptr<Slaver>&) const override;
    bool visit(const std::shared_ptr<Druid>&) const override;
    bool visit(const std::shared_ptr<Orc>&) const override;
};

class Slaver : public NPC
{
public:
    Slaver();
    Slaver(const std::string& name, int, int);
    Slaver(std::istream&);

    void save(std::ostream&) override;
    bool accept(const std::shared_ptr<FightVisitor>&, const std::shared_ptr<NPC>&) const override;
    friend std::ostream& operator<<(std::ostream&, Slaver&);
    void print() override;

    ~Slaver() = default;
};

#endif //OOP_SLAVER_H