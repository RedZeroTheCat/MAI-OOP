#ifndef OOP_TRIANGLE_H
#define OOP_TRIANGLE_H

#include "figure.h"

template<numeric T>
class Triangle : public Figure<T>
{
public:
    Triangle();
    Triangle(const Point<T>&, const Point<T>&, const Point<T>&);
    Triangle(const Triangle<T>&);

    virtual Point<T> center() const override;
    virtual double area() const override;

    explicit virtual operator double() const override;

    Triangle& operator=(const Triangle<T>&);
    Triangle& operator=(Triangle&&);
    bool operator==(const Figure<T>&) const override;

    void print(std::ostream& out) const override
    {
        out << a << '\n';
        out << b << '\n';
        out << c << '\n';
    }

    friend std::ostream& operator<<(std::ostream& out, Triangle<T>& t) {
        t.print(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Triangle<T>& t) {
        in >> t.a >> t.b >> t.c;
        t.checkPoints(t.a, t.b, t.c);

        return in;
    }

    virtual ~Triangle() = default;

private:
    Point<T> a;
    Point<T> b;
    Point<T> c;

    void checkConstructor(const Figure<T>&) const override;
    void checkPoints(const Point<T>& a, const Point<T>& b, const Point<T>& c) const;
};

template<numeric T>
void Triangle<T>::checkConstructor(const Figure<T>& fig) const
{
    const Triangle<T>* temp = dynamic_cast<const Triangle<T>*>(&fig);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed cast");
    }

    std::vector<Point<T>> points(3);
    points[0] = temp->a;
    points[1] = temp->b;
    points[2] = temp->c;

    for (int i = 0; i < 2; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of triangle are the same");
        }
    }

    std::vector<double> sides(3);
    for (int i = 0; i < 3; ++i)
    {
        if (i < 2)
        {
            sides[i] = round(Point<T>::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of triangle are NOT the same");
        }
    }
}

template<numeric T>
void Triangle<T>::checkPoints(const Point<T>& a, const Point<T>& b, const Point<T>& c) const
{
    std::vector<Point<T>> points(3);
    points[0] = a;
    points[1] = b;
    points[2] = c;

    for (int i = 0; i < 2; ++i)
    {
        if (points[i] == points[i + 1])
        {
            throw std::logic_error("Some points of triangle are the same");
        }
    }
    std::vector<double> sides(3);
    for (int i = 0; i < 3; ++i)
    {
        if (i < 2)
        {
            sides[i] = round(Point<T>::distance(points[i], points[i + 1]) * 1000) / 1000;
            continue;
        }
        sides[i] = round(Point<T>::distance(points[i], points[0]) * 1000) / 1000;
    }
    for (int i = 0; i < 2; ++i)
    {
        if (sides[i] != sides[i + 1])
        {
            throw std::logic_error("Some sides of triangle are NOT the same");
        }
    }
}

template<numeric T>
Triangle<T>::Triangle() : Figure<T>("Triangle") {};

template<numeric T>
Triangle<T>::Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) : Figure<T>("Triangle") {
    this->a = a;
    this->b = b;
    this->c = c;
    checkConstructor(*this);
}

template<numeric T>
Triangle<T>::Triangle(const Triangle<T>& t) : Figure<T>("Triangle") {
    a = t.a;
    b = t.b;
    c = t.c;
}

template<numeric T>
Point<T> Triangle<T>::center() const
{
    T xCent = (a.getX() + b.getX() + c.getX()) / 3;
    T yCent = (a.getY() + b.getY() + c.getY()) / 3;
    Point center(xCent, yCent);
    return center;
}

template<numeric T>
double Triangle<T>::area() const
{
    double ab = Point<T>::distance(a, b);
    return ab * ab * 0.25 * std::sqrt(3);
}

template<numeric T>
Triangle<T>::operator double() const
{
    return this->area();
}

template<numeric T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T>& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

template<numeric T>
Triangle<T>& Triangle<T>::operator=(Triangle<T>&& t)
{
    if (this != &t)
    {
        a = t.a;
        b = t.b;
        c = t.c;
    }
    return *this;
}

template<numeric T>
bool Triangle<T>::operator==(const Figure<T>& f) const
{
    if (this->getName() != f.getName())
    {
        return false;
    }

    const Triangle* temp = dynamic_cast<const Triangle*>(&f);
    if (temp == nullptr)
    {
        throw std::logic_error("Failed to cast");
    }

    if (this->area() == temp->area())
    {
        return true;
    }

    return false;
}

#endif //OOP_TRIANGLE_H