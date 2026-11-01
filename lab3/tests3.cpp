#include <gtest/gtest.h>
#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"
#include "array.h"

TEST(Point_class, default_constructor) {
    Point p;
    ASSERT_TRUE(p.getX() == 0 && p.getY() == 0);
}

TEST(Point_class, values_constructor) {
    Point p(3.2, 1);
    ASSERT_TRUE(p.getX() == 3.2 && p.getY() == 1);
}

TEST(Point_class, copy_constructor) {
    Point a(4.4, 3.545);
    Point b(a);
    ASSERT_TRUE(b.getX() == 4.4 && b.getY() == 3.545);
}

TEST(Point_class, equality_operator_1) {
    Point a(4.4, 3.545);
    Point b(a);
    ASSERT_TRUE(a == b);
}

TEST(Point_class, equality_operator_2) {
    Point a(2, 5);
    Point b(3.4, 2);
    ASSERT_FALSE(a == b);
}

TEST(Point_class, lvalue_copy) {
    Point a(3.45, 2);
    Point b = a;
    ASSERT_TRUE(b.getX() == 3.45 && b.getY() == 2);
}

TEST(Point_class, rvalue_copy) {
    Point a(3.45, 2);
    Point b;
    b = std::move(a);
    ASSERT_TRUE(b.getX() == 3.45 && b.getY() == 2 && a.getX() == 0 && a.getY() == 0);
}

TEST(Point_class, distance_1) {
    Point a(0,3);
    Point b(4,0);
    ASSERT_TRUE(Point::distance(a, b) == 5);
}

TEST(Point_class, distance_2) {
    Point a(1,1);
    Point b(1,1);
    ASSERT_TRUE(Point::distance(a, b) == 0);
}

TEST(Triangle_class, default_constructor) {
    Triangle t;
    ASSERT_TRUE(t.getName() == "Triangle");
}

TEST(Triangle_class, points_constructor_1) {
    ASSERT_ANY_THROW(Triangle t(Point(0, 0), Point(0,3), Point(0, 4)));
}

TEST(Triangle_class, points_constructor_2) {
    ASSERT_ANY_THROW(Triangle t(Point(0,0), Point(0, 0), Point(0, 4)));
}

TEST(Triangle_class, copy_constructor) {
    const Point a(0, 0);
    const Point b(1, sqrt(3));
    const Point c(-1, sqrt(3));
    Triangle t(a, b, c);
    Triangle New(t);
    ASSERT_TRUE(New == t);
}

TEST(Triangle_class, destructor_and_points_constructor) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    t.~Triangle();
}

TEST(Triangle_methods, center_method_1) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Point center = t.center();
    ASSERT_TRUE(center.getX() <= EPS && center.getY() - 2.309 <= EPS);
}

TEST(Triangle_methods, center_method_2) {
    Triangle t(Point(0,0), Point(1,sqrt(3)), Point(-1,sqrt(3)));
    Point center = t.center();
    ASSERT_TRUE(center.getX() <= EPS && center.getY() - 1.155 <= EPS);
}

TEST(Triangle_methods, area_method_1) {
    Triangle t(Point(0,0), Point(1,sqrt(3)), Point(-1,sqrt(3)));
    double area = round(t.area()*1000)/1000;
    ASSERT_TRUE(area == round(sqrt(3)*1000)/1000);
}

TEST(Triangle_methods, area_method_2) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    double area = t.area();
    ASSERT_TRUE(area == sqrt(3));
}

TEST(Triangle_methods, double_cast_method_1) {
    Triangle t(Point(0,0), Point(1,sqrt(3)), Point(-1,sqrt(3)));
    double temp = round(double(t) * 1000) / 1000;
    ASSERT_TRUE(temp == round(sqrt(3)*1000)/1000);
}

TEST(Triangle_methods, double_cast_method_2) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    double temp = double(t);
    ASSERT_TRUE(temp == sqrt(3));
}

TEST(Triangle_operators, equality_operator) {
    Triangle t1(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Triangle t2(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    ASSERT_TRUE(t1 == t2);
}

TEST(Triangle_operators, lvalue_copy_1) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Triangle New;
    New = t;
    ASSERT_TRUE(New == t);
}

TEST(Triangle_operators, rvalue_copy_1) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Triangle New1 = t;
    Triangle New2 = std::move(t);
    ASSERT_TRUE(New1 == New2);
}

TEST(Square_constructors, default_constructor) {
    Square s;
    ASSERT_TRUE(s.getName() == "Square");
}

TEST(Square_constructors, points_constructor_1) {
    ASSERT_ANY_THROW(Square s(Point(0, 0), Point(0,0), Point(1,1), Point(2,2)));
}

TEST(Square_constructos, points_constructor_2) {
    ASSERT_ANY_THROW(Square s(Point(1, 1), Point(2, 2), Point(3, 3), Point(4, 4)));
}

TEST(Square_construcors, points_constructor_3) {
    Square s(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
}

TEST(Square_methods, center_method_1) {
    Square s(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
    Point center = s.center();
    ASSERT_TRUE(center.getX() <= EPS && center.getY() <= EPS);
}

TEST(Square_methods, center_method_2) {
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Point center = s.center();
    ASSERT_TRUE(center.getX() - 2 <= EPS && center.getY() - 2 <= EPS);
}

TEST(Square_methods, area_method_1) {
    Square s(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
    double area = s.area();
    ASSERT_TRUE(area == 16);
}

TEST(Square_methods, area_method_2) {
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    double area = s.area();
    ASSERT_TRUE(area == 16);
}

TEST(Square_operators, double_cast_operator) {
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    double temp = double(s);
    ASSERT_TRUE(temp == 16);
}

TEST(Square_operators, equality_operator) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_operators, lvalue_copy_1) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2;
    s2 = s1;
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_operators, lvalue_copy_2) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2;
    s1 = s2;
    ASSERT_TRUE(s1 == s2 && s1.getName() == "Square");
}

TEST(Square_operators, rvalue_copy) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2;
    Square s3;
    s3 = s1;
    s2 = std::move(s1);
    ASSERT_TRUE(s2 == s3);
}

TEST(Octagon_class, default_constructor) {
    Octagon o;
    ASSERT_TRUE(o.getName() == "Octagon");
}

TEST(Octagon_class, points_constructor_1) {
    ASSERT_ANY_THROW(Octagon o(Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)));
}

TEST(Octagon_class, points_constructor_2) {
    ASSERT_ANY_THROW(Octagon o(Point(1, 1), Point(0, 0), Point(2, 2), Point(3, 3), Point(4, 4), Point(5, 5), Point(6, 6), Point(7, 7)));
}

TEST(Octagon_class, points_constructor_3) {
    Octagon o(Point(0, -2 * sqrt(2)), Point(2, -2), Point(2 * sqrt(2), 0), Point(2, 2), Point(0, 2 * sqrt(2)), Point(-2, 2), Point(-2 * sqrt(2), 0), Point(-2, -2));
    o.~Octagon();
}

TEST(Octagon_class, points_constructor_4) {
    Octagon o(Point(3, -2 * sqrt(2)), Point(5, -2), Point(3 + 2 * sqrt(2), 0), Point(5, 2), Point(3, 2 * sqrt(2)), Point(1, 2), Point(3 - 2 * sqrt(2), 0), Point(1, -2));
    o.~Octagon();
}

TEST(Octagon_methods, center_method_1) {
    Octagon o(Point(0, -2 * sqrt(2)), Point(2, -2), Point(2 * sqrt(2), 0), Point(2, 2), Point(0, 2 * sqrt(2)), Point(-2, 2), Point(-2 * sqrt(2), 0), Point(-2, -2));
    Point center = o.center();
    ASSERT_TRUE(fabs(center.getX()) <= EPS && fabs(center.getY()) <= EPS);
}

TEST(Octagon_methods, center_method_2) {
    Octagon o(Point(3, -2 * sqrt(2)), Point(5, -2), Point(3 + 2 * sqrt(2), 0), Point(5, 2), Point(3, 2 * sqrt(2)), Point(1, 2), Point(3 - 2 * sqrt(2), 0), Point(1, -2));
    Point center = o.center();
    ASSERT_TRUE(fabs(center.getX()) - 3 <= EPS && fabs(center.getY()) <= EPS);
}

TEST(Octagon_methods, area_method_1) {
    Octagon o(Point(3, -2 * sqrt(2)), Point(5, -2), Point(3 + 2 * sqrt(2), 0), Point(5, 2), Point(3, 2 * sqrt(2)), Point(1, 2), Point(3 - 2 * sqrt(2), 0), Point(1, -2));
    double area = o.area();
    EXPECT_NEAR(area, 22.6274, EPS);
}

TEST(Octagon_methods, area_method_2) {
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    double area = o.area();
    EXPECT_NEAR(area, 5.65685, EPS);
}

TEST(Octagon_methods, double_cast_method) {
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    double temp = double(o);
    EXPECT_NEAR(temp, 5.65685, EPS);
}

TEST(Octagon_operators, equality_operator) {
    Octagon o1(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Octagon o2(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    ASSERT_TRUE(o1 == o2);
}

TEST(Octagon_operators, lvalue_copy_1) {
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Octagon temp;
    temp = o;
    ASSERT_TRUE(temp == o);
}

TEST(Octagon_operators, lvalue_copy_2) {
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Octagon temp;
    o = temp;
    ASSERT_TRUE(temp == o);
}

TEST(Octagon_operators, rvalue_copy) {
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Octagon temp;
    Octagon oct;
    oct = o;
    temp = std::move(o);
    ASSERT_TRUE(temp == oct);
}

TEST(Array_constructors, default_constructor) {
    Array arr;
    ASSERT_TRUE(arr.getCapacity() == 2 && arr.getSize() == 0);
}

TEST(Array_constructors, default_constructor_destructor) {
    Array arr;
    arr.~Array();
}

TEST(Array_constructors, size_constructor_1) {
    Array arr(0);
    ASSERT_TRUE(arr.getCapacity() == 2 && arr.getSize() == 0);
}

TEST(Array_constructors, size_constructor_2) {
    Array arr(3);
    ASSERT_TRUE(arr.getCapacity() == 6 && arr.getSize() == 3);
}

TEST(Array_methods, push_back_method) {
    Array arr(0);
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    arr.push_back(&s1);
    ASSERT_TRUE(arr.getSize() == 1);
}

TEST(Array_methods, pop_back_method) {
    Array arr(1);
    arr.pop_back();
    ASSERT_TRUE(arr.getSize() == 0);
}

TEST(Array_methods, erase_method) {
    Array arr(0);
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    arr.push_back(&s1);
    arr.push_back(&o);
    arr.push_back(&t);
    arr.erase(1);
    ASSERT_TRUE(arr.getSize() == 2 && *(arr[0]) == s1 && *(arr[1]) == t);
}

TEST(Array_methods, methods_thows_1) {
    Array arr(0);
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    arr.push_back(&s1);
    arr.push_back(&o);
    arr.push_back(&t);
    ASSERT_ANY_THROW(arr.figureCenter(10));
}

TEST(Array_methods, methods_thows_2) {
    Array arr;
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    arr.push_back(&s1);
    arr.push_back(&o);
    arr.push_back(&t);
    ASSERT_ANY_THROW(arr.figureArea(10));
}

TEST(Array_methods, methods_throws_3) {
    Array arr;
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Octagon o(Point(0, -sqrt(2)), Point(1, -1), Point(sqrt(2), 0), Point(1, 1), Point(0, sqrt(2)), Point(-1, 1), Point(-sqrt(2), 0), Point(-1, -1));
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    arr.push_back(&s1);
    arr.push_back(&o);
    arr.push_back(&t);
    ASSERT_ANY_THROW(arr[10]);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}