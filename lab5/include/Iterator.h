#ifndef OOP_ITERATOR_H
#define OOP_ITERATOR_H

template<class ItemType, class ArrayType>
class Iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ItemType;
    using difference_type = std::ptrdiff_t;
    using pointer = ItemType*;
    using reference = ItemType&;

    Iterator() = default;
    Iterator(ArrayType*, size_t, size_t);

    ItemType& operator*();

    bool operator==(const Iterator<ItemType, ArrayType>&) const;
    bool operator!=(const Iterator<ItemType, ArrayType>&) const;

    Iterator<ItemType, ArrayType>& operator++();
    Iterator<ItemType, ArrayType>& operator+(size_t);

    ~Iterator() = default;

private:
    ArrayType* array;
    size_t size;
    size_t index;

    ArrayType* getArrayPtr() const;
};

template <class ItemType, class ArrayType>
ArrayType* Iterator<ItemType, ArrayType>::getArrayPtr() const
{
    return array;
}

template <class ItemType, class ArrayType>
Iterator<ItemType, ArrayType>::Iterator(ArrayType* array, size_t index, size_t size)
{
    this->array = array;
    this->index = index;
    this->size = size;
}

template <class ItemType, class ArrayType>
ItemType& Iterator<ItemType, ArrayType>::operator*()
{
    if (index > size)
    {
        throw std::invalid_argument("Iterator is out of bounds");
    }
    if (index == size)
    {
        return (*array)[index - 1];
    }
    return (*array)[index];
}

template <class ItemType, class ArrayType>
bool Iterator<ItemType, ArrayType>::operator==(const Iterator<ItemType, ArrayType>& other) const
{
    return (index == other.index) && (this->getArrayPtr() == other.getArrayPtr());
}

template <class ItemType, class ArrayType>
bool Iterator<ItemType, ArrayType>::operator!=(const Iterator<ItemType, ArrayType>& other) const
{
    return !(*this == other);
}

template <class ItemType, class ArrayType>
Iterator<ItemType, ArrayType>& Iterator<ItemType, ArrayType>::operator++()
{
    ++index;
    if (index > size)
    {
        throw std::invalid_argument("Iterator is out of bounds");
    }
    return *this;
}

template <class ItemType, class ArrayType>
Iterator<ItemType, ArrayType>& Iterator<ItemType, ArrayType>::operator+(size_t n)
{
    index += n;
    if (index > size)
    {
        throw std::invalid_argument("Iterator is out of bounds");
    }
    return *this;
}






#endif //OOP_ITERATOR_H