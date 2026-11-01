#ifndef OOP_TRIANGLE_H
#define OOP_TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle();
    Triangle(const Point&, const Point&, const Point&);
    Triangle(const Triangle&);

    virtual Point center() const override;
    virtual double area() const override;

    explicit virtual operator double() const override;

    friend std::ostream& operator<<(std::ostream&, Triangle&);
    friend std::istream& operator>>(std::istream&, Triangle&);
    Triangle& operator=(const Triangle&);
    Triangle& operator=(Triangle&&);
    bool operator==(const Figure&) const override;

    virtual ~Triangle() = default;


private:
    Point a;
    Point b;
    Point c;

    void print(std::ostream&) override;
    void input(std::istream&) override;
    void checkConstructor(const Figure&) const override;
    void checkPoints(const Point&, const Point&, const Point&);
};

#endif //OOP_TRIANGLE_H