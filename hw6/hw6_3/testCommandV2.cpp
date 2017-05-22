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


class Command {
  public:
    virtual void execute() = 0;
};

class SimpleCommand : public Command
{
  public:
  std::function<void(int*)> _cb; // callback
  int* receiver;  // has_a instance

  SimpleCommand(int* rec, std::function<void(int*)> cb)
      : receiver(rec), _cb(cb)
  { }

  virtual void execute()
  {
    std::cout << "SimpleCommand::execute() is called" << "\n";
    std::cout << "SimpleCommand::receiver:" << *receiver << "\n";
    _cb(receiver); // don't know how to take receiver in callback
  }
  
};

void divide(int var, int* a);
void add(int var, int* a);

//int variableA (10);
//int variableB (5);
TEST(testCommand, UseCase1)
{
  int variableA (10);
  int variableB (5);
  std::vector<Command*> commands;
  commands.emplace_back (new SimpleCommand(&variableA, std::bind (&divide, variableB, &variableA)) );
  commands.emplace_back (new SimpleCommand(&variableA, std::bind (&add, variableB, &variableA)) );
  EXPECT_EQ (variableA, 10);

  for (auto& c : commands)
    c->execute();

  EXPECT_EQ (variableA, 7);
}


void divide(int var, int* a)
{
  std::cout << "divide() is called" << "\n";
  std::cout << "var:" << var << "\n";
  std::cout << "*a:" << *a << "\n";
  //variableA =  variableA / var;
  *a =  *a / var;
}


void add(int var, int* a)
{
  std::cout << "add() is called" << "\n";
  std::cout << "var:" << var << "\n";
  std::cout << "*a:" << *a << "\n";
  //variableA =  variableA + var;
  *a =  *a + var;
}

