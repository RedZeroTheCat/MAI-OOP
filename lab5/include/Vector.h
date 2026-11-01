#ifndef OOP_VECTOR_H
#define OOP_VECTOR_H

#include <initializer_list>

#include "Allocator.h"
#include "Iterator.h"
#include "ConstIterator.h"



template<class T, class Allocator = std::allocator<T>>
class Vector
{
public:
    Vector();
    Vector(size_t);
    Vector(size_t, const T&);
    Vector(const std::initializer_list<T>&);
    Vector(const Vector&);
    Vector(Vector&&);

    void push_back(const T&);
    void pop_back();
    void clear();
    void resize(size_t);

    size_t getSize();
    bool isEmpty();

    Iterator<T, Vector<T, Allocator>> begin();
    Iterator<T, Vector<T, Allocator>> end();

    ConstIterator<T, Vector<T, Allocator>> cbegin();
    ConstIterator<T, Vector<T, Allocator>> cend();

    Iterator<T, Vector<T, Allocator>> erase(Iterator<T, Vector<T, Allocator>>);
    ConstIterator<T, Vector<T, Allocator>> erase(ConstIterator<T, Vector<T, Allocator>>);
    Iterator<T, Vector<T, Allocator>> insert(ConstIterator<T, Vector<T, Allocator>>, const T&);

    T& operator[](size_t) const;

    ~Vector() = default;

private:
    T* data;
    size_t size;
    size_t capacity;
    Allocator alloc;

    void reallocate(size_t);
};

template<class T, class Allocator>
void Vector<T, Allocator>::reallocate(size_t newCapacity)
{
    if (data == nullptr)
    {
        return;
    }
    T temp[size];
    for (size_t i = 0; i < size; ++i)
    {
        temp[i] = data[i];
    }

    for (size_t i = 0; i < size; ++i)
    {
        alloc.destroy(&data[i]);
    }
    alloc.deallocate(data, size);

    capacity = newCapacity;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i)
    {
        if (i < size)
        {
            alloc.construct(&data[i], temp[i]);
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector()
{
    size = 0;
    capacity = 0;
    data = nullptr;
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t s)
{
    size = s;
    capacity = size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i)
    {
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t s, const T& value)
{
    size = s;
    capacity = size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i)
    {
        alloc.construct(&data[i], value);
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const std::initializer_list<T>& list)
{
    size = list.size();
    capacity = size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i)
    {
        if (i < size)
        {
            alloc.construct(&data[i], *(list.begin() + i));
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& other)
{
    size = other.size;
    capacity = size * 2;
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i)
    {
        if (i < size)
        {
            alloc.construct(&data[i], other[i]);
            continue;
        }
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& other)
{
    size = other.size;
    capacity = other.capacity;
    data = other.data;
    alloc = std::move(other.alloc);

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value)
{
    ++size;
    if (size < capacity || size == 1)
    {
        if (capacity == 0)
        {
            capacity = size * 2;
            data = alloc.allocate(capacity);
            alloc.construct(&data[size - 1], value);
            return;
        }
        data[size - 1] = value;
        return;
    }
    this->reallocate(capacity * 2);
    data[size - 1] = value;
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back()
{
    if (size == 0)
    {
        throw std::logic_error("Vector is empty");
    }
    --size;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear()
{
    size = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t newSize)
{
    size = newSize;
    if (newSize < capacity)
    {
        return;
    }
    capacity = size * 2;
    if (data != nullptr)
    {
        this->reallocate(capacity);
        return;
    }
    data = alloc.allocate(capacity);
    for (size_t i = 0; i < capacity; ++i)
    {
        alloc.construct(&data[i], T());
    }
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::getSize()
{
    return size;
}

template<class T, class Allocator>
bool Vector<T, Allocator>::isEmpty()
{
    return (size == 0);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::begin()
{
    return Iterator<T, Vector<T, Allocator>>(this, 0, size);
}

template<class T, class Allocator>
ConstIterator<T, Vector<T, Allocator>> Vector<T, Allocator>::cbegin()
{
    return ConstIterator<T, Vector<T, Allocator>>(this, 0, size);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::end()
{
    return Iterator<T, Vector<T, Allocator>>(this, size, size);
}

template<class T, class Allocator>
ConstIterator<T, Vector<T, Allocator>> Vector<T, Allocator>::cend()
{
    return ConstIterator<T, Vector<T, Allocator>>(this, size, size);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::erase(Iterator<T, Vector<T, Allocator>> it)
{
    if (it == this->end())
    {
        return (this->end());
    }
    size_t index = 0;
    for (auto iter = this->begin(); iter != this->end(); ++iter)
    {
        if (iter == it)
        {
            break;
        }
        ++index;
    }
    for (size_t i = index + 1; i < size; ++i)
    {
        data[i - 1] = data[i];
    }
    --size;
    return (this->begin() + index);
}

template<class T, class Allocator>
ConstIterator<T, Vector<T, Allocator>> Vector<T, Allocator>::erase(ConstIterator<T, Vector<T, Allocator>> it)
{
    if (it == this->cend())
    {
        return (this->cend());
    }
    size_t index = 0;
    for (auto iter = this->cbegin(); iter != this->cend(); ++iter)
    {
        if (iter == it)
        {
            break;
        }
        ++index;
    }
    for (size_t i = index + 1; i < size; ++i)
    {
        data[i - 1] = data[i];
    }
    --size;
    return (this->cbegin() + index);
}

template<class T, class Allocator>
Iterator<T, Vector<T, Allocator>> Vector<T, Allocator>::insert(ConstIterator<T, Vector<T, Allocator>> pos, const T& value)
{
    if (size == 0)
    {
        this->push_back(value);
        return (this->begin());
    }
    if (size + 1 == capacity)
    {
        this->reallocate(capacity * 2);
    }
    size_t index = 0;
    for (auto iter = this->cbegin(); iter != this->cend(); ++iter)
    {
        if (iter == pos) {
            break;
        }
        ++index;
    }
    for (size_t i = index; i < size; ++i)
    {
        data[i + 1] = data[i];
    }
    data[index] = value;
    ++size;
    return (this->begin() + index);
}

template<class T, class Allocator>
T& Vector<T, Allocator>::operator [] (size_t index) const
{
    if (index >= size) {
        throw std::invalid_argument("Index out of range");
    }
    return data[index];
}



#endif //OOP_VECTOR_H