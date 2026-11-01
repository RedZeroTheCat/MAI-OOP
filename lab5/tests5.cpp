#include <gtest/gtest.h>

#include "Allocator.h"
#include "Iterator.h"
#include "ConstIterator.h"
#include "Vector.h"

TEST(Allocator_tests, allocate_deallocate_methods) {
    Allocator<float, 1500> alloc;
    float* data = alloc.allocate(1000);
    alloc.deallocate(data, 594);
    alloc.~Allocator();
    ASSERT_TRUE(1);
}

TEST(Allocator_tests, construct_destroy_methods) {
    Allocator<std::string, 1500> alloc;
    std::string* data = alloc.allocate(1000);
    for (size_t i = 0; i < 1000; ++i) {
        alloc.construct(&data[i], std::string());
    }
    for (size_t i = 0; i < 1000; ++i) {
        alloc.destroy(&data[i]);
    }
    alloc.deallocate(data, 1000);
    alloc.~Allocator();
    ASSERT_TRUE(1);
}

TEST(Allocator_tests_throws, allocate_method) {
    Allocator<float, 500> alloc;
    ASSERT_ANY_THROW(alloc.allocate(1000000));
}

TEST(Allocator_tests_throws, deallocate_method_1) {
    Allocator<std::string, 400> alloc;
    ASSERT_ANY_THROW(alloc.deallocate(nullptr, 100000));
}

TEST(Allocator_tests_throws, deallocate_method_2) {
    Allocator<std::string, 400> alloc;
    std::string* data = alloc.allocate(100);
    ASSERT_ANY_THROW(alloc.deallocate(data + 1000, 100));
}

TEST(Iterator_tests, constructor_and_dereference_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    ASSERT_TRUE(*(vec.begin()) == *it);
}

TEST(Iterator_tests, equality_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    ASSERT_TRUE(vec.begin() == it);
}

TEST(Iterator_tests, inequality_operator_1) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    ASSERT_FALSE(vec.begin() != it);
}

TEST(Iterator_tests, inequality_operator_2) {
    Vector<int, Allocator<int, 100>> vec1;
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    Vector<int, Allocator<int, 100>> vec2;
    vec2.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it1(&vec1, 0, vec1.getSize());
    Iterator<int, Vector<int, Allocator<int, 100>>> it2(&vec2, 0, vec2.getSize());
    ASSERT_TRUE(it1 != it2);
}

TEST(Iterator_tests, increment_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ASSERT_TRUE(*(++vec.begin()) == 4);
}

TEST(Iterator_tests, plus_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ASSERT_TRUE(*(vec.begin() + 2) == 5);
}

TEST(Iterator_tests, dectructor) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    vec.~Vector();
    it.~Iterator();
    ASSERT_TRUE(1);
}

TEST(Iterator_throws, dereference_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 1000, vec.getSize());
    ASSERT_ANY_THROW(*it);
}

TEST(Iterator_throws, increment_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it = vec.end();
    ASSERT_ANY_THROW(++it);
}

TEST(Iterator_throws, plus_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    Iterator<int, Vector<int, Allocator<int, 100>>> it = vec.begin();
    ASSERT_ANY_THROW(it + 100);
}

TEST(ConstIterator_tests, constructor_and_dereference_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    ASSERT_TRUE(*(vec.cbegin()) == *it);
}

TEST(ConstIterator_tests, equality_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    ASSERT_TRUE(vec.cbegin() == it);
}

TEST(ConstIterator_tests, inequality_operator_1) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    ASSERT_FALSE(vec.cbegin() != it);
}

TEST(ConstIterator_tests, inequality_operator_2) {
    Vector<int, Allocator<int, 100>> vec1;
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    Vector<int, Allocator<int, 100>> vec2;
    vec2.push_back(3);
    vec2.push_back(4);
    vec2.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it1(&vec1, 0, vec1.getSize());
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it2(&vec2, 0, vec2.getSize());
    ASSERT_FALSE(it1 == it2);
}

TEST(ConstIterator_tests, increment_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ASSERT_TRUE(*(++vec.cbegin()) == 4);
}

TEST(ConstIterator_tests, plus_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ASSERT_TRUE(*(vec.cbegin() + 2) == 5);
}

TEST(ConstIterator_tests, destructor) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 0, vec.getSize());
    vec.~Vector();
    it.~ConstIterator();
    ASSERT_TRUE(1);
}

TEST(ConstIterator_throws, dereference_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it(&vec, 1000, vec.getSize());
    ASSERT_ANY_THROW(*it);
}

TEST(ConstIterator_throws, increment_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it = vec.cend();
    ASSERT_ANY_THROW(++it);
}

TEST(ConstIterator_throws, plus_operator) {
    Vector<int, Allocator<int, 100>> vec;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    ConstIterator<int, Vector<int, Allocator<int, 100>>> it = vec.cbegin();
    ASSERT_ANY_THROW(it + 100);
}

TEST(Vector_tests, defaul_constructor_and_destructor) {
    Vector<int, Allocator<int, 100>> vec;
    vec.~Vector();
    ASSERT_TRUE(1);
}

TEST(Vector_tests, size_constructor) {
    Vector<int, Allocator<int, 200>> vec(2);
    ASSERT_TRUE(vec[0] == 0 && vec[1] == 0);
}

TEST(Vector_tests, size_and_value_constructor) {
    Vector<std::string, Allocator<std::string, 300>> vec(2, "testing");
    ASSERT_TRUE(vec[0] == "testing" && vec[1] == "testing");
}

TEST(Vector_tests, init_list_constructor) {
    Vector<std::string, Allocator<std::string, 432>> vec({"one", "two", "three"});
    ASSERT_TRUE(vec[0] == "one" && vec[1] == "two" && vec[2] == "three");
}

TEST(Vector_tests, copy_constructor) {
    Vector<std::string, Allocator<std::string, 1000>> vec1({"one", "two", "three"});
    Vector<std::string, Allocator<std::string, 1000>> vec2(vec1);
    ASSERT_TRUE(vec2[0] == "one" && vec2[1] == "two" && vec2[2] == "three");
}

TEST(Vector_tests, move_constructor) {
    Vector<std::string, Allocator<std::string, 1000>> vec1({"one", "two", "three"});
    Vector<std::string, Allocator<std::string, 1000>> vec2(std::move(vec1));
    ASSERT_TRUE(vec2[0] == "one" && vec2[1] == "two" && vec2[2] == "three");
}

TEST(Vector_tests, size_method) {
    Vector<int, Allocator<int, 2000>> vec({1,2,3,4,5});
    ASSERT_TRUE(vec.getSize() == 5);
}

TEST(Vector_tests, push_back_method) {
    Vector<int, Allocator<int, 2000>> vec({1,2,3,4,5});
    vec.push_back(234);
    ASSERT_TRUE(vec[vec.getSize() - 1] == 234);
}

TEST(Vector_tests, pop_back_method) {
    Vector<int, Allocator<int, 2000>> vec({1,2,3,4,5});
    vec.pop_back();
    ASSERT_TRUE(vec.getSize() == 4);
}

TEST(Vector_tests_throws, pop_back_method) {
    Vector<float, Allocator<float, 300>> vec;
    ASSERT_ANY_THROW(vec.pop_back());
}

TEST(Vector_tests, clear_method) {
    Vector<int, Allocator<int, 2000>> vec({1,2,3,4,5});
    vec.clear();
    ASSERT_TRUE(vec.getSize() == 0);
}

TEST(Vector_tests, resize_method) {
    Vector<std::string, Allocator<std::string, 1000>> vec;
    vec.resize(3);
    ASSERT_TRUE(vec.getSize() == 3 && vec[0] == "" && vec[1] == "" && vec[2] == "");
}

TEST(Vector_tests, empty_method) {
    Vector<std::string, Allocator<std::string, 1000>> vec;
    ASSERT_TRUE(vec.isEmpty());
}

TEST(Vector_tests, begin_method) {
    Vector<std::string, Allocator<std::string, 1000>> vec(3, "testing");
    ASSERT_TRUE(*vec.begin() == "testing");
}

TEST(Vector_tests, cbegin_method) {
    Vector<std::string, Allocator<std::string, 1000>> vec(3, "testing");
    ASSERT_TRUE(*vec.cbegin() == "testing");
}

TEST(Vector_tests, end_method) {
    Vector<std::string, Allocator<std::string, 200>> vec(3, "testing");
    auto it = vec.end();
    ASSERT_TRUE(*it == "testing");
}

TEST(Vector_tests, cend_method) {
    Vector<std::string, Allocator<std::string, 200>> vec;
    auto it = vec.end();
    ASSERT_ANY_THROW(*it);
}

TEST(Vector_tests, erase_method_1) {
    Vector<int, Allocator<int, 200>> vec({1,2,3,4,5});
    auto it = vec.erase(vec.begin() + 2);
    ASSERT_TRUE(vec[2] == 4 && it == vec.begin() + 2 && vec.getSize() == 4 && *it == 4);
}

TEST(Vector_tests, erase_method_2) {
    Vector<std::string, Allocator<std::string, 200>> vec({"one", "two", "three"});
    auto it = vec.erase(vec.begin() + 2);
    ASSERT_TRUE(it == vec.end() && vec.getSize() == 2);
}

TEST(Vector_tests, erase_method_3) {
    Vector<int, Allocator<int, 200>> vec({1,2,3,4,5});
    auto it = vec.erase(vec.cbegin() + 2);
    ASSERT_TRUE(vec[2] == 4 && it == vec.cbegin() + 2 && vec.getSize() == 4 && *it == 4);
}

TEST(Vector_tests, erase_method_4) {
    Vector<std::string, Allocator<std::string, 200>> vec({"one", "two", "three"});
    auto it = vec.erase(vec.cbegin() + 2);
    ASSERT_TRUE(it == vec.cend() && vec.getSize() == 2);
}

TEST(Vector_tests, insert_method_1) {
    Vector<int, Allocator<int, 400>> vec({1,2,3});
    auto it = vec.insert(vec.cbegin() + 2, 325);
    ASSERT_TRUE(it == vec.begin() + 2 && vec.getSize() == 4 && *it == 325);
}

TEST(Vector_test, insert_method_2) {
    Vector<int, Allocator<int, 400>> vec;
    auto it = vec.insert(vec.cend(), 300);
    ASSERT_TRUE(*it == 300 && vec.getSize() == 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}