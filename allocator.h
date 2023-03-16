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
    size_t N = 20;
    alignas(T) char m_data[20 * sizeof(T)];
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
    template <typename U>
    StaticStorage(const StaticStorage<U>& other) noexcept {}

    template <typename U>
    StaticStorage& operator=(const StaticStorage<U>& other) noexcept { return *this; }

    // Allocate and deallocate memory
    pointer allocate(size_type n) {
        if (n > N) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<pointer>(m_data);
    }

    void deallocate(pointer p, size_type n) {}

    // Get maximum number of elements that can be allocated
    size_type max_size() const noexcept { return N; }
};


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