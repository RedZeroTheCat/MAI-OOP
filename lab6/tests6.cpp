#include "npc.h"
#include "slaver.h"
#include "druid.h"
#include "orc.h"
#include "utils.h"
#include "factory.h"
#include "observers.h"
#include "data_methods.h"

#include <gtest/gtest.h>

TEST(NPC_class_tests, getters) {
    std::shared_ptr<NPC> ptr = std::make_shared<Slaver>("Slavic", 2, 2);
    ASSERT_TRUE(ptr->getType() == 0 && ptr->getX() == 2 && ptr->getY() == 2);
}

TEST(NPC_class_tests, is_close_method_1) {
    std::shared_ptr<NPC> ptr1 = std::make_shared<Orc>("Bob", 0, 0);
    std::shared_ptr<NPC> ptr2 = std::make_shared<Druid>("John", 10, 10);
    ASSERT_TRUE(ptr1->inRange(ptr2, 20));
}

TEST(NPC_class_tests, is_close_method_2) {
    std::shared_ptr<NPC> ptr1 = std::make_shared<Orc>("Bob", 0,0);
    std::shared_ptr<NPC> ptr2 = std::make_shared<Druid>("John", 10, 10);
    ASSERT_FALSE(ptr1->inRange(ptr2, 2));
}

TEST(Slaver_tests, slaver_visitor_test_1) {
    SlaverVisitor visitor;
    std::shared_ptr<Slaver> ptr = std::make_shared<Slaver>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Slaver_tests, slaver_visitor_test_2) {
    SlaverVisitor visitor;
    std::shared_ptr<Druid> ptr = std::make_shared<Druid>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Slaver_tests, slaver_visitor_test_3) {
    SlaverVisitor visitor;
    std::shared_ptr<Orc> ptr = std::make_shared<Orc>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Slaver_class_tests, default_constructor_and_destructor) {
    Slaver s;
    s.~Slaver();
}

TEST(Slaver_class_tests, int_constructor) {
    Slaver s("Slavic", 2, 2);
    ASSERT_TRUE(s.getType() == 0 && s.getX() == 2 && s.getY() == 2);
}

TEST(Slaver_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>("Slavic", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>("Bob", 3, 3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<OrcVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Slaver_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>("Slavic I", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>("Slavic II", 3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<SlaverVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Slaver_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Slaver>("Slavic", 2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>("John", 3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<DruidVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Druid_tests, druid_visitor_test_1) {
    DruidVisitor visitor;
    std::shared_ptr<Slaver> ptr = std::make_shared<Slaver>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Druid_tests, druid_visitor_test_2) {
    DruidVisitor visitor;
    std::shared_ptr<Druid> ptr = std::make_shared<Druid>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Druid_tests, druid_visitor_test_3) {
    DruidVisitor visitor;
    std::shared_ptr<Orc> ptr = std::make_shared<Orc>();
    ASSERT_FALSE(visitor.visit(ptr));
}

TEST(Druid_class_tests, default_constructor_and_destructor) {
    Druid d;
    d.~Druid();
}

TEST(Druid_class_tests, int_constructor) {
    Druid d("John", 2, 2);
    ASSERT_TRUE(d.getType() == 1 && d.getX() == 2 && d.getY() == 2);
}

TEST(Druid_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>("John", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>("Bob", 3, 3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<OrcVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Druid_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>("John", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>("Slavic", 3, 3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<SlaverVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Druid_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Druid>("John I", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>("John II", 3, 3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<DruidVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Orc_tests, orc_visitor_test_1) {
    OrcVisitor visitor;
    std::shared_ptr<Slaver> ptr = std::make_shared<Slaver>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Orc_tests, orc_visitor_test_2) {
    OrcVisitor visitor;
    std::shared_ptr<Druid> ptr = std::make_shared<Druid>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Orc_tests, orc_visitor_test_3) {
    OrcVisitor visitor;
    std::shared_ptr<Orc> ptr = std::make_shared<Orc>();
    ASSERT_TRUE(visitor.visit(ptr));
}

TEST(Orc_class_tests, default_constructor_and_destructor) {
    Orc o;
    o.~Orc();
}

TEST(Orc_class_tests, int_constructor) {
    Orc o("Bob", 2, 2);
    ASSERT_TRUE(o.getType() == 2 && o.getX() == 2 && o.getY() == 2);
}

TEST(Orc_class_tests, accept_method_1) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>("Bob", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Slaver>("Slavic", 3, 3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<SlaverVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Orc_class_tests, accept_method_2) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>("Bob", 2,2);
    std::shared_ptr<NPC> attacker = std::make_shared<Druid>("John", 3,3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<DruidVisitor>();
    ASSERT_FALSE(defender->accept(visitor_ptr, attacker));
}

TEST(Orc_class_tests, accept_method_3) {
    std::shared_ptr<NPC> defender = std::make_shared<Orc>("Bob I", 2, 2);
    std::shared_ptr<NPC> attacker = std::make_shared<Orc>("Bob II", 3, 3);
    std::shared_ptr<FightVisitor> visitor_ptr = std::make_shared<OrcVisitor>();
    ASSERT_TRUE(defender->accept(visitor_ptr, attacker));
}

TEST(Factory_tests, create_1) {
    std::shared_ptr<NPC> ptr = Factory::create(SlaverType, "Slavic", 1, 1);
    ASSERT_TRUE(ptr->getType() == 0 && ptr->getX() == 1 && ptr->getY() == 1);
}

TEST(Factory_tests, create_2) {
    std::shared_ptr<NPC> ptr = Factory::create(OrcType, "Bob", 1, 1);
    ASSERT_TRUE(ptr->getType() == 2 && ptr->getX() == 1 && ptr->getY() == 1);
}

TEST(Factory_tests, create_3) {
    std::shared_ptr<NPC> ptr = Factory::create(DruidType, "John", 1, 1);
    ASSERT_TRUE(ptr->getType() == 1 && ptr->getX() == 1 && ptr->getY() == 1);
}

TEST(Factory_tests, create_throw) {
    std::shared_ptr<NPC> ptr;
    ASSERT_ANY_THROW(ptr = Factory::create(NpcType(534), "Stas", 2, 2));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}