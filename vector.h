#pragma once

#include <stddef.h>
#include "iterator.h"
#include "reverse_iterator.h"
#include <iostream>
#include "allocator.h"

struct out_of_range
{

};

template <typename T, template <typename U> class MemStorage = DynamicStorage>
class Vector: private MemStorage<T>
{
private:
    T* data_ = NULL;
    size_t size_ = 0;
    size_t capacity_ = 0;
    //Allocator allocator_;
    //using allocator_ *this;

    int special_allocate_into(T** data, size_t size)
    {
        try{
            *data = MemStorage<T>::allocate(size);
        } 
        catch (const std::bad_alloc& e) {
            return -1;
        }
        return 0;
    }

    int special_allocate(size_t size)
    {
        return special_allocate_into(&data_, size);
    }

    int resize(size_t new_size)
    {
        if (new_size == 0)
        {
            if (capacity_ != 0)
                MemStorage<T>::deallocate(data_, capacity_);
            return 0;
        }

        T* new_vec = NULL;

        if (special_allocate_into(&new_vec, new_size) < 0)
        {
            return -1;
        }

        for (size_t i = 0; i < size_; i++)
        {
            new_vec[i] = data_[i];
        }
        
        if (capacity_ != 0)
            MemStorage<T>::deallocate(data_, capacity_);

        data_ = new_vec;
        capacity_ = new_size;

        return 0;
    }

public:
    size_t get_size() const {
        return size_;
    }
    size_t get_capacity() const {
        return capacity_;
    }

    Vector(): data_(NULL),
              size_(0),
              capacity_(0)
    {}

    Vector(const Vector& vec)
    {
        //std::cout << "came lvalue\n";
        size_t size = vec.get_size();

        if (special_allocate(size) < 0)
        {
            return;
        }
        else
        {
            for (size_t i = 0; i < size; i++)
            {
                data_[i] = vec[i];
            }
            
            capacity_ = size;
            size_ = size;
        }
    }

    Vector(Vector<T>&& arg)
    {
        //std::cout<<"rvalue came\n";
        std::swap(size_, arg.size_);
        std::swap(capacity_, arg.capacity_);
        std::swap(data_, arg.data_);
    }


    Vector(size_t size)
    {
        if (special_allocate(size) < 0)
        {
            return;
        }
        
        size_ = size;
        capacity_ = size_;
    } 

    Vector(std::initializer_list<T> init) 
    {
        //std::cout << "came lvalue\n";
        if (special_allocate(init.size()) < 0)
        {
            return;
        }

        std::copy(init.begin(), init.end(), data_);
        size_ = init.size();
        capacity_ = size_;
    }


    ~Vector()
    {
        if (capacity_ != 0)
        {
            MemStorage<T>::deallocate(data_, capacity_);
        }
    }


    const T* data() const
    {
        return data_;
    }

    T* data()
    {
        return data_;
    }

    void push_back(const T& value)
    {
        int res = 0;

        if (size_ == 0)
        {
            //std::cout<<"im here first size\n";
            res = resize(8);
        }
        else if (size_ == capacity_)
        {
            //std::cout<<"im here resize\n";
            res = resize(2 * size_);
        }
        //std::cout<<"im here\n";

        if (res < 0)
        {
            //std::cout<<"failure\n";
            return;
        }

        data_[size_] = value;
        size_++;
    }
    
    void pop_back()
    {
        int res = 0;

        if (size_ == 0)
        {
            return;
        }
        else if ((capacity_ % 2 == 0) && (size_ - capacity_ / 2 <= 0))
        {
            resize(capacity_ / 2);
        }

        if (res < 0)
        {
            return;
        }
        size_--;
    }

/*------ITERATOR--------*/

    typedef Iterator<T> iterator;
    typedef ReverseIterator<T> reverse_iterator;

	iterator begin()
    {
        return iterator(&data_[0]);
    }

	const iterator begin() const
    {
        return iterator(&data_[0]);
    }

	iterator end()
    {
        return iterator(&data_[size_]);
    }
	
	const iterator end() const
    {
        return iterator(&data_[size_]);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(&data_[size_ - 1]);
    }

    const reverse_iterator rbegin() const
    {
        return iterator(&data_[size_ - 1]);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(&data_[-1]);
    }

    const reverse_iterator rend() const
    {
        return reverse_iterator(&data_[-1]);
    }

	/*const iterator cbegin() const;

	const iterator cend() const;*/

/*-------ITERATOR_END-----*/
    
    // operators [] without checking bounds
    T& operator[](int i)
    {
        return data_[i];
    }

    const T& operator[](int i) const
    {
        return data_[i];
    }

    T& get_elem(size_t n) const
    {
        if (size_ <= n) throw out_of_range();

        return data_[n];
    }

	// Returns a reference to the first element
	T& front()
    {
        return data_[0];
    }

	// Returns a reference to the first element
	const T& front() const
    {
        return data_[0];
    }

	// Returns a reference to the last element
	T& back()
    {
        return data_[size_ - 1];
    }

	// Returns a reference to the last element
	const T& back() const
    {
        return data_[size_ - 1];
    }

    Vector& operator=(const Vector& arg)
    {
        if (this == &arg)
        {
            return *this;
        }

        resize(arg.capacity_);

        size_ = arg.size_;
        capacity_ = arg.capacity_;

        if (size_ != 0)//here we are working with dynamic memory
        {
            for (size_t i = 0; i < arg.size_; i++)
            {
                data_[i] = arg.data_[i];
            }
        }

        return *this;
    }


    Vector& operator=(Vector&& arg)
    {
        if (this == &arg)
        {
            return *this;
        }

        std::swap(size_, arg.size_);
        std::swap(capacity_, arg.capacity_);
        std::swap(data_, arg.data_);

        return *this;
    }

    
};

