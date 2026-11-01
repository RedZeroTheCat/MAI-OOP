#ifndef OOP_OCTAGON_H
#define OOP_OCTAGON_H

#include "figure.h"

const double SIDE_TO_DIAM_MODIFIER = 2 / std::sqrt(2 - std::sqrt(2)); // trigonometry

class Octagon : public Figure
{
public:
    Octagon();
    Octagon(const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&);
    Octagon(const Octagon&);

    virtual Point center() const override;
    virtual double area() const override;

    explicit virtual operator double() const override;

    friend std::ostream& operator<<(std::ostream&, Octagon&);
    friend std::istream& operator>>(std::istream&, Octagon&);
    Octagon& operator=(const Octagon&);
    Octagon& operator=(Octagon&&);
    bool operator==(const Figure&) const override;

    virtual ~Octagon() = default;


private:
    Point a;
    Point b;
    Point c;
    Point d;
    Point e;
    Point f;
    Point g;
    Point h;

    void print(std::ostream&) override;
    void input(std::istream&) override;
    void checkConstructor(const Figure&) const override;
    void checkPoints(const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&, const Point&);
};

#endif //OOP_OCTAGON_H