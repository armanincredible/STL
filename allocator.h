#pragma once

#include <stdlib.h>

template <typename T>
class DynamicStorage 
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    DynamicStorage () noexcept {}
    ~DynamicStorage () noexcept {}

    pointer allocate(size_type n) {
        T* ptr = (pointer) calloc (n, sizeof(value_type));
        if (ptr == NULL)
        {
            throw std::bad_alloc();
        }
        
        return ptr;
    }

    void deallocate(pointer p, size_type n){
        free(p);
    }
};

template <typename T>
class StaticStorage 
{
private:
    #define SIZE 1000
    alignas(T) char m_data[SIZE * sizeof(T)];
    size_t offset = 0;
public:
    // Type definitions
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    // Constructor and destructor
    StaticStorage () noexcept {}
    ~StaticStorage () noexcept {}

    // Copy constructor and assignment operator
    StaticStorage(const StaticStorage& other) noexcept {}

    StaticStorage& operator=(const StaticStorage& other) noexcept { return *this; }

    // Allocate and deallocate memory
    pointer allocate(size_type n) {
        if (n > SIZE - offset) {
            throw std::bad_alloc();
        }
        offset += n;
        return reinterpret_cast<pointer>(m_data + offset - n);
    }

    void deallocate(pointer p, size_type n) {}

    // Get maximum number of elements that can be allocated
    size_type max_size() const noexcept { return SIZE; }
};

/*
template <typename T, template <typename U> class MemStorage = DynamicStorage>
class Allocator : public MemStorage<T>
{
public:
    // Type definitions
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    // Constructor and destructor
    Allocator() noexcept {}
    ~Allocator() noexcept {}
};
*/
