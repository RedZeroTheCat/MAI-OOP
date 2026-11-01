#ifndef OOP_ARRAY_H
#define OOP_ARRAY_H

#include <memory>

#include "figure.h"

template<typename T>
class Array
{
public:
    Array();
    Array(size_t);

    void push_back(const T&);
    void pop_back();
    void erase(size_t);
    T operator[](size_t);

    auto figureCenter(size_t);
    double figureArea(size_t);
    double commonArea();

    size_t getSize() const;
    size_t getCapacity() const;

    ~Array() = default;

private:
    size_t size;
    size_t capacity;
    std::shared_ptr<T[]> data;

    void reallocate(size_t);
};

template <typename T>
Array<T>::Array()
{
    size = 0;
    capacity = 2;
    data = std::shared_ptr<T[]>(new T[capacity]);
}

template <typename T>
Array<T>::Array(size_t s)
{
    size = s;
    if (size > 0)
    {
        capacity = size * 2;
    }
    else
    {
        capacity = 2;
    }
    data = std::shared_ptr<T[]>(new T[capacity]);
}

template <typename T>
size_t Array<T>::getSize() const
{
    return size;
}

template <typename T>
size_t Array<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
void Array<T>::reallocate(size_t newCapacity)
{
    if (data == nullptr)
    {
        return;
    }
    std::shared_ptr<T[]> newData = std::shared_ptr<T[]>(new T[newCapacity]);

    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = data[i];
    }

    capacity = newCapacity;
    data = newData;
}

template <typename T>
void Array<T>::push_back(const T& elem)
{
    if (size < capacity)
    {
        if (size == 0)
        {
            data[size] = elem;
            size = 1;
            return;
        }
        data[size++] = elem;
        return;
    }
    this->reallocate(capacity * 2);
    data[size++] = elem;
}

template <typename T>
void Array<T>::pop_back()
{
    if (size == 0)
    {
        return;
    }
    size--;
}

template <typename T>
void Array<T>::erase(size_t index)
{
    if (index >= size)
    {
        return;
    }
    for (size_t i = index + 1; i < size; ++i)
    {
        data[i - 1] = data[i];
    }
    size--;
}

template <typename T>
T Array<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::logic_error("Index out of range");
    }
    return data[index];
}

template <typename T>
auto Array<T>::figureCenter(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[index]->center();
}

template <typename T>
double Array<T>::figureArea(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[index]->area();
}

template <typename T>
double Array<T>::commonArea()
{
    double sum = 0;

    for (size_t i = 0; i < size; ++i)
    {
        sum += data[i]->area();
    }

    return sum;
}

#endif //OOP_ARRAY_H