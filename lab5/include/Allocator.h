#ifndef OOP_ALLOCATOR_H
#define OOP_ALLOCATOR_H

#include <iostream>
#include <array>
#include <exception>

template<class T, size_t N>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Allocator();

    T* allocate(size_t n);
    void deallocate(T* ptr, size_t n);

    template<class U>
    struct rebind
    {
        using other = Allocator<U, N>;
    };

    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args);

    void destroy(T* ptr);

    ~Allocator() = default;

private:
    std::array<T, N> _used_blocks;
    std::array<T*, N> _free_blocks;
    long long _free_count = N;
};

template<class T, size_t N>
Allocator<T, N>::Allocator()
{
    _free_count = N;
    for (size_t i = 0; i < N; ++i)
    {
        _free_blocks[i] = &_used_blocks[i];
    }
}

template <class T, size_t N>
T* Allocator<T, N>::allocate(size_t n)
{
    T* result = nullptr;

    if (_free_count - int(n) < 0)
    {
        throw std::invalid_argument("Not enough memory to allocate");
    }

    if (_free_count > 0 && n != 0)
    {
        result = _free_blocks[_free_count - n];
        _free_count -= n;
    }

    return result;
}

template <class T, size_t N>
void Allocator<T, N>::deallocate(T* ptr, size_t n)
{
    if (_free_count + n > N)
    {
        throw std::invalid_argument("Too much memory to deallocate");
    }

    if (ptr < &_used_blocks[0] || ptr > &_used_blocks[0] + N)
    {
        throw std::invalid_argument("Allocator out of bounds");
    }

    for (size_t i = 0; i < n; ++i)
    {
        _free_blocks[_free_count++] = ptr + i;
    }
}

template <class T, size_t N>
template <typename U, typename... Args>
void Allocator<T, N>::construct(U* ptr, Args&&... args)
{
    new (ptr) U(std::forward<Args>(args)...);
}

template <class T, size_t N>
void Allocator<T, N>::destroy(T* ptr)
{
    ptr->~T();
}

#endif //OOP_ALLOCATOR_H