// pimpl.cpp
// below can be run on Linux/MacOS to detect c/c++ memory leak
// valgrind --leak-check=full ./pimpl

#include "api.h"
#include <memory>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class Api::Impl
{
  public:
    std::string mName;
};

std::ostream& operator<<(std::ostream& os, Api& api)
{
  return os
  << "Api Name=" << api.getName();
}

//Api::Api(const std::string& name) : pImpl(new Api::Impl())
//Api::Api(const std::string& name) : pImpl(std::make_shared<Api::Impl>())
Api::Api(const std::string& name) : pImpl(std::make_unique<Api::Impl>())
{
  std::cout << "Api constructor called\n";
  pImpl->mName = name;
}

Api::~Api()
{
  std::cout << "Api destructor called\n";
  //delete pImpl;
}

std::string Api::getName()
{
  return   pImpl->mName;
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

    Api api("myapi");
    std::cout << api << "\n";    

    BackInserter <int, std::vector> data; //noted the use of a template template parameter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 65535);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    //for (int i = 0; i<100000; ++i)
    for (int i = 0; i<100; ++i)
    {
        data.insert(dis(gen));
        //data.push_back(dis(gen));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed : " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
}

