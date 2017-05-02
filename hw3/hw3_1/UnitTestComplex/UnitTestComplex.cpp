// UnitTestComplex.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "gtest/gtest.h"
#include "../Complex.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(ComplexMultiUnitTests, testAddition)
{
    Complex x1(10, 9); //10+9i
    Complex x2(5, 4); //5+4i
    Complex y(15, 13); //15+13i
    EXPECT_EQ(x1+x2, y);
}

TEST(ComplexMultiUnitTests, testMultiply)
{
    Complex x1(10, 9); //10+9i
    Complex x2(5, 4); //5+4i
    Complex y(14, 85); //14+85i
    EXPECT_EQ(x1*x2, y);
}

