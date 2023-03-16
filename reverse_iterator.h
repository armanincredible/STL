#pragma once
template<class T> 
class ReverseIterator
{
public:
	ReverseIterator()
		:ptr_(NULL)
	{}
	ReverseIterator(T* p)
		:ptr_(p)
	{}
	ReverseIterator(const ReverseIterator& other)
		:ptr_(other.ptr_)
	{}
 
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using ReverseIterator_category = std::random_access_iterator_tag;

    //typedef std::bidirectional_ReverseIterator_tag ReverseIterator_category;

    template<typename OtherIter>
    ReverseIterator(const ReverseIterator<OtherIter>& other) : ptr_(other.base()) {}

    value_type base() const {
        return ptr_;
    }

	ReverseIterator& operator++()
	{
		ptr_--;
		return *this;
	}

    ReverseIterator operator++(int) 
    {
        ReverseIterator tmp(*this);
        --(*this);
        return tmp;
    }

    ReverseIterator operator+(difference_type i)
	{
		return ReverseIterator(ptr_ - i);
	}

    ReverseIterator operator-(difference_type i)
	{
		return ReverseIterator(ptr_ + i);
	}

    difference_type operator-(const ReverseIterator& other) const {
        return ptr_ - other.ptr_;
    }

    reference operator*() const {
        return *ptr_;
    }

	ReverseIterator& operator--()
	{
		ptr_--;
		return *this;
	}

    ReverseIterator operator--(int) 
    {
        ReverseIterator tmp(*this);
        ++(*this);
        return tmp;
    }

	T& operator*()
	{
		return *ptr_;
	}

    ReverseIterator& operator+=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    ReverseIterator& operator-=(difference_type n) {
        ptr_ += n;
        return *this;
    }

	bool operator==(const ReverseIterator& b) const
	{
		return ptr_ == b.ptr_;
	}

	bool operator!=(const ReverseIterator& b) const
	{
		return ptr_ != b.ptr_;
	}

    bool operator<(const ReverseIterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator>(const ReverseIterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator<=(const ReverseIterator& other) const {
        return ptr_ >= other.ptr_;
    }

    bool operator>=(const ReverseIterator& other) const {
        return ptr_ <= other.ptr_;
    }

private:
	T* ptr_ = NULL;
};
