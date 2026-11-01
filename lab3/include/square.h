#ifndef OOP_SQUARE_H
#define OOP_SQUARE_H

#include "figure.h"

class Square : public Figure
{
public:
    Square();
    Square(const Point&, const Point&, const Point&, const Point&);
    Square(const Square&);

    virtual Point center() const override;
    virtual double area() const override;

    explicit virtual operator double() const override;

    friend std::ostream& operator<<(std::ostream&, Square&);
    friend std::istream& operator>>(std::istream&, Square&);
    Square& operator=(const Square&);
    Square& operator=(Square&&);
    bool operator==(const Figure&) const override;

    virtual ~Square() = default;


private:
    Point a;
    Point b;
    Point c;
    Point d;

    void print(std::ostream&) override;
    void input(std::istream&) override;
    void checkConstructor(const Figure&) const override;
    void checkPoints(const Point&, const Point&, const Point&, const Point&);
};

#endif //OOP_SQUARE_H