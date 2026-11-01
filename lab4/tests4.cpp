#include <gtest/gtest.h>

#include "array.h"
#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"

TEST(Point_class, default_constructor) {
    Point<int> p;
    ASSERT_TRUE(p.getX() == 0 && p.getY() == 0);
}

TEST(Point_class, values_constructor) {
    Point<double> p(3.2, 1);
    ASSERT_TRUE(p.getX() == 3.2 && p.getY() == 1);
}

TEST(Point_class, copy_constructor) {
    Point<double> a(4.4, 3.545);
    Point b(a);
    ASSERT_TRUE(b.getX() == 4.4 && b.getY() == 3.545);
}

TEST(Point_class, equality_operator_1) {
    Point<float> a(4.4, 3.545);
    Point b(a);
    ASSERT_TRUE(a == b);
}

TEST(Point_class, equality_operator_2) {
    Point<long double> a(2, 5);
    Point<long double> b(3.4, 2);
    ASSERT_FALSE(a == b);
}

TEST(Point_class, lvalue_copy) {
    Point<double> a(3.45, 2);
    Point<double> b = a;
    ASSERT_TRUE(b.getX() == 3.45 && b.getY() == 2);
}

TEST(Point_class, rvalue_copy) {
    Point<float> a(3.45, 2);
    Point<float> b;
    b = std::move(a);
    ASSERT_TRUE(b.getX() - 3.45 <= EPS && b.getY() - 2 <= EPS && a.getX() <= EPS && a.getY() <= EPS);
}

TEST(Point_class, distance_1) {
    Point<long> a(0,3);
    Point<long> b(4,0);
    ASSERT_TRUE(Point<long>::distance(a, b) == 5);
}

TEST(Point_class, distance_2) {
    Point<int> a(1,1);
    Point<int> b(1,1);
    ASSERT_TRUE(Point<int>::distance(a, b) == 0);
}

TEST(Triangle_class, default_constructor) {
    Triangle<long double> t;
    ASSERT_TRUE(t.getName() == "Triangle");
}

TEST(Triangle_class, points_constructor_1) {
    ASSERT_ANY_THROW(Triangle<int> t(Point<int>(0, 0), Point<int>(0,3), Point<int>(0, 4)));
}

TEST(Triangle_class, points_constructor_2) {
    ASSERT_ANY_THROW(Triangle<long> t(Point<long>(0,0), Point<long>(0, 0), Point<long>(0, 4)));
}

TEST(Triangle_class, copy_constructor) {
    const Point<float> a(0, 0);
    const Point<float> b(1, sqrt(3));
    const Point<float> c(-1, sqrt(3));
    Triangle<float> t(a, b, c);
    Triangle<float> New(t);
    ASSERT_TRUE(New == t);
}

TEST(Triangle_class, destructor_and_points_constructor) {
    Triangle<double> t(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    t.~Triangle();
}

TEST(Triangle_methods, center_method_1) {
    Triangle t(Point<long double>(1,sqrt(3)), Point<long double>(-1,sqrt(3)), Point<long double>(0,2*sqrt(3)));
    Point<long double> center = t.center();
    ASSERT_TRUE(center.getX() <= EPS && center.getY() - 2.309 <= EPS);
}

TEST(Triangle_methods, center_method_2) {
    Triangle<float> t(Point<float>(0,0), Point<float>(1,sqrt(3)), Point<float>(-1,sqrt(3)));
    Point<float> center = t.center();
    ASSERT_TRUE(center.getX() <= EPS && center.getY() - 1.155 <= EPS);
}

TEST(Triangle_methods, area_method_1) {
    Triangle<double> t(Point<double>(0,0), Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)));
    double area = round(t.area()*1000)/1000;
    ASSERT_TRUE(area == round(sqrt(3)*1000)/1000);
}

TEST(Triangle_methods, area_method_2) {
    Triangle<long double> t(Point<long double>(1,sqrt(3)), Point<long double>(-1,sqrt(3)), Point<long double>(0,2*sqrt(3)));
    double area = t.area();
    ASSERT_TRUE(area == sqrt(3));
}

TEST(Triangle_methods, double_cast_method_1) {
    Triangle<float> t(Point<float>(0,0), Point<float>(1,sqrt(3)), Point<float>(-1,sqrt(3)));
    double temp = round(double(t) * 1000) / 1000;
    ASSERT_TRUE(temp == round(sqrt(3)*1000)/1000);
}

TEST(Triangle_methods, double_cast_method_2) {
    Triangle<double> t(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    double temp = double(t);
    ASSERT_TRUE(temp == sqrt(3));
}

TEST(Triangle_operators, equality_operator) {
    Triangle<double> t1(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    Triangle<double> t2(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    ASSERT_TRUE(t1 == t2);
}

TEST(Triangle_operators, lvalue_copy_1) {
    Triangle<double> t(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    Triangle<double> New;
    New = t;
    ASSERT_TRUE(New == t);
}

TEST(Triangle_operators, rvalue_copy_1) {
    Triangle<float> t(Point<float>(1,sqrt(3)), Point<float>(-1,sqrt(3)), Point<float>(0,2*sqrt(3)));
    Triangle<float> New1 = t;
    Triangle<float> New2 = std::move(t);
    ASSERT_TRUE(New1 == New2);
}

TEST(Square_constructors, default_constructor) {
    Square<int> s;
    ASSERT_TRUE(s.getName() == "Square");
}

TEST(Square_constructors, points_constructor_1) {
    ASSERT_ANY_THROW(Square<float> s(Point<float>(0, 0), Point<float>(0,0), Point<float>(1,1), Point<float>(2,2)));
}

TEST(Square_constructos, points_constructor_2) {
    ASSERT_ANY_THROW(Square<double> s(Point<double>(1, 1), Point<double>(2, 2), Point<double>(3, 3), Point<double>(4, 4)));
}

TEST(Square_construcors, points_constructor_3) {
    Square<long> s(Point<long>(-2, -2), Point<long>(-2, 2), Point<long>(2, 2), Point<long>(2, -2));
}

TEST(Square_methods, center_method_1) {
    Square<long double> s(Point<long double>(-2, -2), Point<long double>(-2, 2), Point<long double>(2, 2), Point<long double>(2, -2));
    Point<long double> center = s.center();
    ASSERT_TRUE(center.getX() <= EPS && center.getY() <= EPS);
}

TEST(Square_methods, center_method_2) {
    Square<int> s(Point<int>(0,0), Point<int>(0,4), Point<int>(4,4), Point<int>(4,0));
    Point<int> center = s.center();
    ASSERT_TRUE(center.getX() - 2 <= EPS && center.getY() - 2 <= EPS);
}

TEST(Square_methods, area_method_1) {
    Square<float> s(Point<float>(-2, -2), Point<float>(-2, 2), Point<float>(2, 2), Point<float>(2, -2));
    double area = s.area();
    ASSERT_TRUE(area == 16);
}

TEST(Square_methods, area_method_2) {
    Square<int> s(Point<int>(0,0), Point<int>(0,4), Point<int>(4,4), Point<int>(4,0));
    double area = s.area();
    ASSERT_TRUE(area == 16);
}

TEST(Square_operators, double_cast_operator) {
    Square<int> s(Point<int>(0,0), Point<int>(0,4), Point<int>(4,4), Point<int>(4,0));
    double temp = double(s);
    ASSERT_TRUE(temp == 16);
}

TEST(Square_operators, equality_operator) {
    Square<int> s1(Point<int>(0,0), Point<int>(0,4), Point<int>(4,4), Point<int>(4,0));
    Square<int> s2(Point<int>(0,0), Point<int>(0,4), Point<int>(4,4), Point<int>(4,0));
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_operators, lvalue_copy_1) {
    Square<float> s1(Point<float>(0,0), Point<float>(0,4), Point<float>(4,4), Point<float>(4,0));
    Square<float> s2;
    s2 = s1;
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_operators, lvalue_copy_2) {
    Square<float> s1(Point<float>(0,0), Point<float>(0,4), Point<float>(4,4), Point<float>(4,0));
    Square<float> s2;
    s1 = s2;
    ASSERT_TRUE(s1 == s2 && s1.getName() == "Square");
}

TEST(Square_operators, rvalue_copy) {
    Square<int> s1(Point<int>(0,0), Point<int>(0,4), Point<int>(4,4), Point<int>(4,0));
    Square<int> s2;
    Square<int> s3;
    s3 = s1;
    s2 = std::move(s1);
    ASSERT_TRUE(s2 == s3);
}

TEST(Octagon_class, default_constructor) {
    Octagon<long double> o;
    ASSERT_TRUE(o.getName() == "Octagon");
}

TEST(Octagon_class, points_constructor_1) {
    ASSERT_ANY_THROW(Octagon<int> o(Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0), Point<int>(0, 0)));
}

TEST(Octagon_class, points_constructor_2) {
    ASSERT_ANY_THROW(Octagon<long> o(Point<long>(1, 1), Point<long>(0, 0), Point<long>(2, 2), Point<long>(3, 3), Point<long>(4, 4), Point<long>(5, 5), Point<long>(6, 6), Point<long>(7, 7)));
}

TEST(Octagon_class, points_constructor_3) {
    Octagon<float> o(Point<float>(0, -2 * sqrt(2)), Point<float>(2, -2), Point<float>(2 * sqrt(2), 0), Point<float>(2, 2), Point<float>(0, 2 * sqrt(2)), Point<float>(-2, 2), Point<float>(-2 * sqrt(2), 0), Point<float>(-2, -2));
    o.~Octagon();
}

TEST(Octagon_class, points_constructor_4) {
    Octagon<long double> o(Point<long double>(3, -2 * sqrt(2)), Point<long double>(5, -2), Point<long double>(3 + 2 * sqrt(2), 0), Point<long double>(5, 2), Point<long double>(3, 2 * sqrt(2)), Point<long double>(1, 2), Point<long double>(3 - 2 * sqrt(2), 0), Point<long double>(1, -2));
    o.~Octagon();
}

TEST(Octagon_methods, center_method_1) {
    Octagon<float> o(Point<float>(0, -2 * sqrt(2)), Point<float>(2, -2), Point<float>(2 * sqrt(2), 0), Point<float>(2, 2), Point<float>(0, 2 * sqrt(2)), Point<float>(-2, 2), Point<float>(-2 * sqrt(2), 0), Point<float>(-2, -2));
    Point<float> center = o.center();
    ASSERT_TRUE(fabs(center.getX()) <= EPS && fabs(center.getY()) <= EPS);
}

TEST(Octagon_methods, center_method_2) {
    Octagon<long double> o(Point<long double>(3, -2 * sqrt(2)), Point<long double>(5, -2), Point<long double>(3 + 2 * sqrt(2), 0), Point<long double>(5, 2), Point<long double>(3, 2 * sqrt(2)), Point<long double>(1, 2), Point<long double>(3 - 2 * sqrt(2), 0), Point<long double>(1, -2));
    Point<long double> center = o.center();
    ASSERT_TRUE(fabs(center.getX()) - 3 <= EPS && fabs(center.getY()) <= EPS);
}

TEST(Octagon_methods, area_method_1) {
    Octagon<long double> o(Point<long double>(3, -2 * sqrt(2)), Point<long double>(5, -2), Point<long double>(3 + 2 * sqrt(2), 0), Point<long double>(5, 2), Point<long double>(3, 2 * sqrt(2)), Point<long double>(1, 2), Point<long double>(3 - 2 * sqrt(2), 0), Point<long double>(1, -2));
    double area = o.area();
    ASSERT_TRUE(area = 24.1421);
}

TEST(Octagon_methods, area_method_2) {
    Octagon<float> o(Point<float>(0, -sqrt(2)), Point<float>(1, -1), Point<float>(sqrt(2), 0), Point<float>(1, 1), Point<float>(0, sqrt(2)), Point<float>(-1, 1), Point<float>(-sqrt(2), 0), Point<float>(-1, -1));
    double area = o.area();
    ASSERT_TRUE(area = 6.03553);
}

TEST(Octagon_methods, double_cast_method) {
    Octagon<float> o(Point<float>(0, -sqrt(2)), Point<float>(1, -1), Point<float>(sqrt(2), 0), Point<float>(1, 1), Point<float>(0, sqrt(2)), Point<float>(-1, 1), Point<float>(-sqrt(2), 0), Point<float>(-1, -1));
    double temp = double(o);
    ASSERT_TRUE(temp = 6.03553);
}

TEST(Octagon_operators, equality_operator) {
    Octagon<float> o1(Point<float>(0, -sqrt(2)), Point<float>(1, -1), Point<float>(sqrt(2), 0), Point<float>(1, 1), Point<float>(0, sqrt(2)), Point<float>(-1, 1), Point<float>(-sqrt(2), 0), Point<float>(-1, -1));
    Octagon<float> o2(Point<float>(0, -sqrt(2)), Point<float>(1, -1), Point<float>(sqrt(2), 0), Point<float>(1, 1), Point<float>(0, sqrt(2)), Point<float>(-1, 1), Point<float>(-sqrt(2), 0), Point<float>(-1, -1));
    ASSERT_TRUE(o1 == o2);
}

TEST(Octagon_operators, lvalue_copy_1) {
    Octagon<double> o(Point<double>(0, -sqrt(2)), Point<double>(1, -1), Point<double>(sqrt(2), 0), Point<double>(1, 1), Point<double>(0, sqrt(2)), Point<double>(-1, 1), Point<double>(-sqrt(2), 0), Point<double>(-1, -1));
    Octagon<double> temp;
    temp = o;
    ASSERT_TRUE(temp == o);
}

TEST(Octagon_operators, lvalue_copy_2) {
    Octagon<float> o(Point<float>(0, -sqrt(2)), Point<float>(1, -1), Point<float>(sqrt(2), 0), Point<float>(1, 1), Point<float>(0, sqrt(2)), Point<float>(-1, 1), Point<float>(-sqrt(2), 0), Point<float>(-1, -1));
    Octagon<float> temp;
    o = temp;
    ASSERT_TRUE(temp == o);
}

TEST(Octagon_operators, rvalue_copy) {
    Octagon<float> o(Point<float>(0, -sqrt(2)), Point<float>(1, -1), Point<float>(sqrt(2), 0), Point<float>(1, 1), Point<float>(0, sqrt(2)), Point<float>(-1, 1), Point<float>(-sqrt(2), 0), Point<float>(-1, -1));
    Octagon<float> temp;
    Octagon<float> oct;
    oct = o;
    temp = std::move(o);
    ASSERT_TRUE(temp == oct);
}

TEST(Array_constructors, default_constructor) {
    Array<Figure<int>*> arr;
    ASSERT_TRUE(arr.getCapacity() == 2 && arr.getSize() == 0);
}

TEST(Array_constructors, default_constructor_destructor) {
    Array<Figure<double>*> arr;
}

TEST(Array_constructors, size_constructor_1) {
    Array<Figure<double>*> arr(0);
    ASSERT_TRUE(arr.getCapacity() == 2 && arr.getSize() == 0);
}

TEST(Array_constructors, size_constructor_2) {
    Array<Figure<long>*> arr(3);
    ASSERT_TRUE(arr.getCapacity() == 6 && arr.getSize() == 3);
}

TEST(Array_methods, push_back_method) {
    Array<Figure<long>*> arr(0);
    Square<long> s1(Point<long>(0,0), Point<long>(0,4), Point<long>(4,4), Point<long>(4,0));
    arr.push_back(&s1);
    ASSERT_TRUE(arr.getSize() == 1);
}

TEST(Array_methods, pop_back_method) {
    Array<Figure<float>*> arr(1);
    arr.pop_back();
    ASSERT_TRUE(arr.getSize() == 0);
}

TEST(Array_methods, erase_method) {
    Array<Figure<double>*> arr(0);
    Square<double> s1(Point<double>(0,0), Point<double>(0,4), Point<double>(4,4), Point<double>(4,0));
    Octagon<double> o(Point<double>(0, -sqrt(2)), Point<double>(1, -1), Point<double>(sqrt(2), 0), Point<double>(1, 1), Point<double>(0, sqrt(2)), Point<double>(-1, 1), Point<double>(-sqrt(2), 0), Point<double>(-1, -1));
    Triangle<double> t(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    arr.push_back(&s1);
    arr.push_back(&o);
    arr.push_back(&t);
    arr.erase(1);
    ASSERT_TRUE(arr.getSize() == 2 && *(arr[0]) == s1 && *(arr[1]) == t);
}

TEST(Array_methods, methods_throws_3) {
    Array<Figure<double>*> arr(0);
    Square<double> s1(Point<double>(0,0), Point<double>(0,4), Point<double>(4,4), Point<double>(4,0));
    Octagon<double> o(Point<double>(0, -sqrt(2)), Point<double>(1, -1), Point<double>(sqrt(2), 0), Point<double>(1, 1), Point<double>(0, sqrt(2)), Point<double>(-1, 1), Point<double>(-sqrt(2), 0), Point<double>(-1, -1));
    Triangle<double> t(Point<double>(1,sqrt(3)), Point<double>(-1,sqrt(3)), Point<double>(0,2*sqrt(3)));
    arr.push_back(&s1);
    arr.push_back(&o);
    arr.push_back(&t);
    ASSERT_ANY_THROW(arr[10]);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}