// Non GoogleTest Version https://repl.it/IR7X/4
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class Employee // composite
{
  public:
    std::vector<Employee*> eList;
  
    virtual void manage(Employee* e) = 0;
    virtual std::string who() = 0;

};

class Worker : public Employee // leaf
{
  private:
    std::string _name;
    
  public:
    Worker(std::string n) : _name(n) { }
    
    virtual void manage(Employee* e) { }
    
    virtual std::string who() { 
      return _name + " "; 
    }
};

class Manager : public Employee // container 1
{

  private:
    std::string _name;
    std::string local_result;
    
  public:
    Manager(std::string n) : _name(n) { }
    
    virtual void manage(Employee* e)
    {
      eList.push_back(e);
    }
  
    virtual std::string who() { 
      local_result = _name + " ";
      
      for(auto& func: eList)
      {
        local_result = local_result + func->who();
      }      
      
      return local_result;
    }
};    


class Director : public Employee // container 2
{
  private:
    std::string _name;
    std::string local_result;
    
  public:
    Director(std::string n) : _name(n) { }
  
    virtual void manage(Employee* e)
    {
      eList.push_back(e);
    }
    
    virtual std::string who()
    {
      local_result = _name + " ";

      for(auto& func: eList)
      {
        local_result = local_result + func->who();
      }

      return local_result;
    }
};

// TODO: valgrind still complain memory leak, is it true? 
TEST(testComposite, UseCase1)
{

  Employee* A = new Worker("Mary");
  Employee* B = new Worker("Jean");
  Employee* C = new Manager("John Doe");
  Employee* D = new Director("Gin");
  C->manage(A);
  C->manage(B);
  D->manage(C);
  EXPECT_EQ( "Gin John Doe Mary Jean ", D->who() );

  delete A;
  delete B;
  delete C;
  delete D;

}


