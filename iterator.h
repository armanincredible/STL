#pragma once

#include <iostream>
#include <iterator>

template<class T> 
class Iterator
{
public:
	Iterator()
		:ptr_(NULL)
	{}
	Iterator(T* p)
		:ptr_(p)
	{}
	Iterator(const Iterator& other)
		:ptr_(other.ptr_)
	{}
 
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

    //typedef std::bidirectional_iterator_tag iterator_category;

    template<typename OtherIter>
    Iterator(const Iterator<OtherIter>& other) : ptr_(other.base()) {}

    value_type base() const {
        return ptr_;
    }

	Iterator& operator++()
	{
		ptr_++;
		return *this;
	}

    Iterator operator++(int) 
    {
        Iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    Iterator operator+(difference_type i)
	{
		return Iterator(ptr_ + i);
	}

    Iterator operator-(difference_type i)
	{
		return Iterator(ptr_ - i);
	}

    difference_type operator-(const Iterator& other) const {
        return ptr_ - other.ptr_;
    }

    reference operator*() const {
        return *ptr_;
    }

	Iterator& operator--()
	{
		ptr_--;
		return *this;
	}

    Iterator operator--(int) 
    {
        Iterator tmp(*this);
        --(*this);
        return tmp;
    }

	T& operator*()
	{
		return *ptr_;
	}

    Iterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }

    Iterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

	bool operator==(const Iterator& b) const
	{
		return ptr_ == b.ptr_;
	}

	bool operator!=(const Iterator& b) const
	{
		return ptr_ != b.ptr_;
	}

    bool operator<(const Iterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator>(const Iterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator<=(const Iterator& other) const {
        return ptr_ <= other.ptr_;
    }

    bool operator>=(const Iterator& other) const {
        return ptr_ >= other.ptr_;
    }

private:
	T* ptr_ = NULL;
};
/*
namespace std {
    template<typename T>
    struct iterator_traits<Iterator<T>> {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;
    };
}*/

/*
struct std::iterator_traits<Iterator<int>>
{
    typedef std::bidirectional_iterator_tag iterator_category;
};*/

