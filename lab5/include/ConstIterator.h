#ifndef OOP_CONST_ITERATOR_H
#define OOP_CONST_ITERATOR_H

template<class ItemType, class ArrayType>
class ConstIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ItemType;
    using difference_type = std::ptrdiff_t;
    using pointer = ItemType*;
    using reference = ItemType&;

    ConstIterator() = default;
    ConstIterator(const ArrayType*, size_t, size_t);

    const ItemType& operator*();

    bool operator==(const ConstIterator<ItemType, ArrayType>&) const;
    bool operator!=(const ConstIterator<ItemType, ArrayType>&) const;

    ConstIterator<ItemType, ArrayType>& operator++();
    ConstIterator<ItemType, ArrayType>& operator+(size_t);

    ~ConstIterator() = default;

private:
    const ArrayType* array;
    size_t size;
    size_t index;

    const ArrayType* getArrayPtr() const;
};

template <class ItemType, class ArrayType>
const ArrayType* ConstIterator<ItemType, ArrayType>::getArrayPtr() const
{
    return array;
}

template<class ItemType, class ArrayType>
ConstIterator<ItemType, ArrayType>::ConstIterator(const ArrayType* array, size_t index, size_t size)
{
    this->array = array;
    this->index = index;
    this->size = size;
}

template<class ItemType, class ArrayType>
const ItemType& ConstIterator<ItemType, ArrayType>::operator*()
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

template<class ItemType, class ArrayType>
bool ConstIterator<ItemType, ArrayType>::operator==(const ConstIterator<ItemType, ArrayType>& other) const
{
    return (index == other.index) && (this->getArrayPtr() == other.getArrayPtr());
}

template<class ItemType, class ArrayType>
bool ConstIterator<ItemType, ArrayType>::operator!=(const ConstIterator<ItemType, ArrayType>& other) const
{
    return !(*this == other);
}

template <class ItemType, class ArrayType>
ConstIterator<ItemType, ArrayType>& ConstIterator<ItemType, ArrayType>::operator++()
{
    ++index;
    if (index > size)
    {
        throw std::invalid_argument("Iterator is out of bounds");
    }
    return *this;
}

template <class ItemType, class ArrayType>
ConstIterator<ItemType, ArrayType>& ConstIterator<ItemType, ArrayType>::operator+(size_t n)
{
    index += n;
    if (index > size)
    {
        throw std::invalid_argument("Iterator is out of bounds");
    }
    return *this;
}


#endif //OOP_CONST_ITERATOR_H