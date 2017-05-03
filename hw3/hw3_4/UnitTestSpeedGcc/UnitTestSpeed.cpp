// UnitTestComplex.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <queue>
#include <list>
#include <set>

#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

template<typename T, template<typename, typename...> class ContainerType, typename... Args>
class BackInserter
{
    ContainerType<T, Args...> container;

public:
    void insert(T e)
    {
#if 1
      auto it = container.begin();
      container.insert(it, e);
#else
      container.push_back(e);
#endif
    }

};


TEST(backinserter_test1, test_vector)
{
    BackInserter <int, std::vector> data; //noted the use of a template template parameter
    //std::vector<int> data; //noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
        //data.push_back(dis(gen));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
}

TEST(backinserter_test2, test_deque)
{
    BackInserter <int, std::deque> data; //noted the use of a template template parameter
    //std::vector<int> data; //noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
        //data.push_back(dis(gen));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
}

TEST(backinserter_test3, test_list)
{
    BackInserter <int, std::list> data; //noted the use of a template template parameter
    //std::vector<int> data; //noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
        //data.push_back(dis(gen));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
}

// TODO
// missing queue and set test in VS2013
// queue has no push_back or insert function, so it can not be implemented in generic way
#if 0
TEST(backinserter_test4, test_queue)
{
    BackInserter <int, std::queue> data; //noted the use of a template template parameter
    //std::vector<int> data; //noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
        //data.push_back(dis(gen));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
}
#endif

// set can be done in g++
#if 1
TEST(backinserter_test5, test_set)
{
    BackInserter <int, std::set> data; //noted the use of a template template parameter
    //std::vector<int> data; //noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    for (int i = 0; i<100000; ++i)
    {
        data.insert(dis(gen));
        //data.push_back(dis(gen));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
}
#endif
