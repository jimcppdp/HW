#include <string>
#include <iostream>
#include <memory>
#include <map>
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class Coffee
{
  private:
    int mCost;
    std::string mContent;
    
  public:
    Coffee(int cost, std::string content) { mCost = cost; mContent = std::string(content); }
    Coffee(Coffee* coffee) { mCost = coffee->mCost; mContent = coffee->mContent; } 
    virtual int get_cost() { return mCost; }
    virtual std::string get_content() { return mContent; }
};

class BlackCoffee : public Coffee
{
  public:
    BlackCoffee() : Coffee(10, "black coffee") {}
    virtual int get_cost() { return Coffee::get_cost(); }
    virtual std::string get_content() { return Coffee::get_content(); }
};


class Decorator : public Coffee
{
  public:
    Coffee* _coffee;
    
    Decorator(Coffee* coffee) : Coffee(coffee), _coffee(coffee) { }

    virtual int get_cost()
    {
      return _coffee->get_cost();
    }
    
    virtual std::string get_content()
    {
      return _coffee->get_content();
    }
};


class MilkDecorator : public Decorator
{
  public:
    MilkDecorator(Coffee* coffee) : Decorator(coffee) { }

    virtual int get_cost()
    {
      return Decorator::get_cost()+5;
    }
    
    virtual std::string get_content()
    {
      return  Decorator::get_content()+" with milk";
    }
};

class SugarDecorator : public Decorator
{
  public:
    SugarDecorator(Coffee* coffee) : Decorator(coffee) { }

    virtual int get_cost()
    {
      return Decorator::get_cost()+1;
    }
    
    virtual std::string get_content()
    {
      return Decorator::get_content()+" with sugar";
    }
};


TEST(testDecorator, UseCase1)
{
  Coffee* mycoffee = new BlackCoffee ;
  EXPECT_EQ(mycoffee->get_cost(), 10);
  EXPECT_EQ(mycoffee->get_content(), "black coffee");
  Coffee* Mycoffee = new MilkDecorator (mycoffee);
  EXPECT_EQ(Mycoffee->get_cost(), 15);
  EXPECT_EQ(Mycoffee->get_content(), "black coffee with milk");
  Mycoffee = new SugarDecorator (Mycoffee);
  EXPECT_EQ(Mycoffee->get_cost(), 16);
  EXPECT_EQ(Mycoffee->get_content(), "black coffee with milk with sugar");
}

TEST(testDecorator, UseCase2)
{
  Coffee* mycoffee = new BlackCoffee ;
  Coffee* Mycoffee = new SugarDecorator(mycoffee);
  EXPECT_EQ(Mycoffee->get_cost(), 11);
  EXPECT_EQ(Mycoffee->get_content(), "black coffee with sugar");
}

