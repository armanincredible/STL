#include "vector.h"
#include <iostream>
#include <gtest/gtest.h>
#include "allocator.h"

TEST(Allocator, ctor)
{
    Vector<int, Allocator<int, StaticStorage>> v({ 1, 2, 3, 4 });
    EXPECT_EQ(1, v.get_elem(0));
    EXPECT_EQ(2, v.get_elem(1));
    EXPECT_EQ(3, v.get_elem(2));
    EXPECT_EQ(4, v.get_elem(3));

}

// Constructors
TEST(Vector, ctor)
{
	Vector<int> v;

	// Check size = 0, capacity = 0, no elements
	EXPECT_EQ(0, v.get_size());
    EXPECT_EQ(0, v.get_capacity());
}

TEST(Vector, NullSize)
{
    Vector<int> v;
    Vector<int> v1;
    Vector<int> v2({ 1, 2, 3, 4 });
    v1 = v;
    v2 = v;
    //EXPECT_EQ(0, v1.get_size());
    //EXPECT_EQ(0, v1.get_capacity());
    //EXPECT_EQ(0, v2.get_size());
    //EXPECT_EQ(0, v2.get_capacity());

    //EXPECT_THROW(v2.get_elem(0), out_of_range);
}

TEST(Vector, CtorListInit)
{
    Vector<int> v({ 1, 2, 3, 4 });
    EXPECT_EQ(1, v.get_elem(0));
    EXPECT_EQ(2, v.get_elem(1));
    EXPECT_EQ(3, v.get_elem(2));
    EXPECT_EQ(4, v.get_elem(3));
}

TEST(Iterators, Begin)
{
    Vector<int> vec({ 1, 2, 3, 4 });
    EXPECT_EQ(1, *vec.begin());
}

TEST(Iterators, End)
{
    Vector<int> vec({ 1, 2, 3, 4 });
    EXPECT_EQ(vec.begin() + vec.get_size(), vec.end());
}

TEST(Iterators, Rbegin)
{
    Vector<int> vec({ 1, 2, 3, 4 });
    EXPECT_EQ(4, *(vec.rbegin()));
}

TEST(Iterators, Rend)
{
    Vector<int> vec({ 1, 2, 3, 4 });
    EXPECT_EQ(1, *(vec.rend() - 1));
}

TEST(Iterators, std_copy)
{
    Vector<int> vec({ 1, 2, 3, 4 });

    EXPECT_EQ(vec.begin() + vec.get_size(), vec.end());

    Vector<int> from_vector({ 1, 2, 3, 4 });
    Vector<int> to_vector(4);

    for (auto it = vec.end() - 1; it >= vec.begin(); it--) {
        //std::cout << *it << " " << std::endl;
    }

    try{
        std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
        //std::cout << "Copy completed successfully" << std::endl;
    }
    catch(const std::exception& e){
        //std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    EXPECT_EQ(from_vector.get_elem(0), to_vector.get_elem(0));
	EXPECT_EQ(from_vector.get_elem(1), to_vector.get_elem(1));
	EXPECT_EQ(from_vector.get_elem(2), to_vector.get_elem(2));
	EXPECT_EQ(from_vector.get_elem(3), to_vector.get_elem(3));
}

TEST(Vector, vectorCopyRvalueCtor)
{
	Vector<char> v;
	v.push_back('a');
	v.push_back('z');
	v.push_back('x');
	v.push_back('r');
	v.push_back('e');
    
    Vector<char> copy = v;
	Vector<char> copy_rvalue = std::move(v);

    EXPECT_EQ(0, v.get_size());
    EXPECT_THROW(v.get_elem(0), out_of_range);


	EXPECT_EQ(copy_rvalue.get_elem(0), copy.get_elem(0));
	EXPECT_EQ(copy_rvalue.get_elem(1), copy.get_elem(1));
	EXPECT_EQ(copy_rvalue.get_elem(2), copy.get_elem(2));
	EXPECT_EQ(copy_rvalue.get_elem(3), copy.get_elem(3));
	EXPECT_EQ(copy_rvalue.get_elem(4), copy.get_elem(4));
}

TEST(Vector, vectorCopyCtor)
{
	Vector<char> v;
	v.push_back('a');
	v.push_back('z');
	v.push_back('x');
	v.push_back('r');
	v.push_back('e');

	Vector<char> copy = v;

	EXPECT_EQ(v.get_elem(0), copy.get_elem(0));
	EXPECT_EQ(v.get_elem(1), copy.get_elem(1));
	EXPECT_EQ(v.get_elem(2), copy.get_elem(2));
	EXPECT_EQ(v.get_elem(3), copy.get_elem(3));
	EXPECT_EQ(v.get_elem(4), copy.get_elem(4));
}




// Capacity
TEST(Vector, size)
{
	Vector<double> v;

	// Size should be 0 upon creget_elemion
	EXPECT_EQ(0, v.get_size());

	v.push_back(3.14);
	EXPECT_EQ(1, v.get_size());

	v.push_back(0);
	EXPECT_EQ(2, v.get_size());
}

TEST(Vector, capacity)
{

}




// Modifiers
TEST(Vector, push_back_ints)
{
	Vector<int> v;

	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	for (int i = 0; i < 10; ++i)
		EXPECT_EQ(i, v[i]);

	v.push_back(1000);
	EXPECT_EQ(1000, v[v.get_size() - 1]);
}



// Accessors
TEST(Vector, accessget_elem)
{
	// Non-const vector
	Vector<int> v;

	EXPECT_THROW(v.get_elem(0), out_of_range);
	EXPECT_THROW(v.get_elem(-97), out_of_range);
	EXPECT_THROW(v.get_elem(1), out_of_range);

	v.push_back(4);
	v.push_back(8);
	v.push_back(10);
	v.push_back(-19);
	v.push_back(0);

	EXPECT_EQ(4, v.get_elem(0));
	EXPECT_EQ(8, v.get_elem(1));
	EXPECT_EQ(10, v.get_elem(2));
	EXPECT_EQ(-19, v.get_elem(3));
	EXPECT_EQ(0, v.get_elem(4));

	EXPECT_THROW(v.get_elem(-1), out_of_range);
	EXPECT_THROW(v.get_elem(5), out_of_range);


	// Const vector
	const Vector<int> cv = v;

	EXPECT_EQ(4, cv.get_elem(0));
	EXPECT_EQ(8, cv.get_elem(1));
	EXPECT_EQ(10, cv.get_elem(2));
	EXPECT_EQ(-19, cv.get_elem(3));
	EXPECT_EQ(0, cv.get_elem(4));

	EXPECT_THROW(cv.get_elem(-1), out_of_range);
	EXPECT_THROW(cv.get_elem(5), out_of_range);
	EXPECT_THROW(cv.get_elem(-2), out_of_range);
	EXPECT_THROW(cv.get_elem(8), out_of_range);
}

TEST(Vector, accessBrackets)
{
	const int NUM_ELEMENTS = 50;

	Vector<double> v;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
		v.push_back(i);

	for (int i = 0; i < NUM_ELEMENTS; ++i)
		EXPECT_EQ(i, v[i]);

	const Vector<double> cv = v;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
		EXPECT_EQ(i, cv[i]);
}

TEST(Vector, accessFront)
{
	Vector<int> v;

	v.push_back(9);
	EXPECT_EQ(9, v.front());

	v.push_back(4);
	EXPECT_EQ(9, v.front());
}

TEST(Vector, accessBack)
{
	Vector<int> v;

	v.push_back(9);
	EXPECT_EQ(9, v.back());

	v.push_back(4);
	EXPECT_EQ(4, v.back()); 
	
	v.push_back(1);
	EXPECT_EQ(1, v.back());
}

TEST(Vector, accessData)
{
	Vector<char> v;
	
	v.push_back('t');
	v.push_back('r');
	v.push_back('o');
	v.push_back('l');
	v.push_back('l');

	char* ptrCh = v.data();

	EXPECT_EQ(*ptrCh, v.front());
	EXPECT_EQ(*(ptrCh + 1), v.get_elem(1));
	EXPECT_EQ(*(ptrCh + 2), v.get_elem(2));
	EXPECT_EQ(*(ptrCh + 3), v.get_elem(3));
	EXPECT_EQ(*(ptrCh + 4), v.get_elem(4));
}


int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}