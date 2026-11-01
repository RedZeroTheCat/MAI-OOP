#ifndef OOP_DRUID_H
#define OOP_DRUID_H

#include "npc.h"

struct DruidVisitor : public FightVisitor
{
    bool visit(const std::shared_ptr<Slaver>&) const override;
    bool visit(const std::shared_ptr<Druid>&) const override;
    bool visit(const std::shared_ptr<Orc>&) const override;
};

class Druid : public NPC
{
public:
    Druid();
    Druid(const std::string& name, int, int);
    Druid(std::istream&);

    void save(std::ostream&) override;
    bool accept(const std::shared_ptr<FightVisitor>&, const std::shared_ptr<NPC>&) const override;
    friend std::ostream& operator<<(std::ostream&, Druid&);
    void print() override;

    ~Druid() = default;
};

#endif //OOP_DRUID_H