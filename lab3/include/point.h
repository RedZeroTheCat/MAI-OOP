#ifndef OOP_POINT_H
#define OOP_POINT_H

#include <iostream>
#include <string>
#include <algorithm>
#include <exception>
#include <cmath>

const double EPS = 0.01;

class Point
{
private:
    double x;
    double y;
public:
    Point();
    Point(double, double);
    Point(const Point&);
    ~Point() = default;

    double getX() const;
    double getY() const;

    void setX(double);
    void setY(double);

    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;
    Point& operator=(const Point&);
    Point& operator=(Point&&);

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

    static double distance(const Point&, const Point&);
};

#endif //OOP_POINT_H