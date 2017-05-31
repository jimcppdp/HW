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

/*

vector<composite*> nodes(10);
Nodes[0] = new container;

Class composite
{
  Virtual void traverse() = 0;

};

Class leaf: composite
{
  Virtual void traverse()
  {
    Cout << “I am a leaf”
  }

}

Class container: composite
{
  Vector <composite*> childs;
  Void traverse()
  {
    Cout << “I am a folder”
    for(auto& c: childs)
    {
      c->traverse()
    }
}

main()
{
  vector<composite*> all_nodes(4);
  All_node[0] = new leaf;
  All_node[1] = new leaf;
  All_node[2] = new container(all_node);
   all_node[3]->traverse;
      // I am a folder
      // I am a leaf
}

*/

// make global result to local in class
//std::string result;

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
      //result = result + _name + " ";
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
      //result = result + _name + " ";
      local_result = _name + " ";
      
      //for_each(eList.begin(), eList.end(), std::mem_fun(&Employee::who));
      for(auto& func: eList)
      {
        //std::cout << func->who();
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
      //result = _name + " ";
      local_result = _name + " ";

      //for_each(eList.begin(), eList.end(), std::mem_fun(&Employee::who));
      for(auto& func: eList)
      {
        //std::cout << func->who();
        local_result = local_result + func->who();
      }

      return local_result;
    }
};


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
}


