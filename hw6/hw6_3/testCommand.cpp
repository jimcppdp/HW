#include <string>
#include <iostream>
#include <vector>
#include <functional>
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

class MacroCommand : public Command
{
  private:
    std::vector <Command*> list;

  public:
    void push_back(Command* cmd)
    {
        std::cout << "MacroCommand::push_back() is called" << "\n";
        list.push_back(cmd);
    }

    virtual void execute()
    {
        std::cout << "MacroCommand::execute() is called" << "\n";
        for (int i = 0; i < list.size(); i++)
        {
          std::cout << "MacroCommand::execute for list is traveled" << "\n";
          list[i]->execute();
        }
    }
};


void divide(int var);
void add(int var);

int variableA (10);
int variableB (5);
TEST(testCommand, UseCase1)
{
  //int variableA (10);
  //int variableB (5);
  std::vector<Command*> commands;
  commands.emplace_back (new SimpleCommand(&variableA, std::bind (&divide, variableB)) );
  commands.emplace_back (new SimpleCommand(&variableA, std::bind (&add, variableB)) );
  EXPECT_EQ (variableA, 10);

  for (auto& c : commands)
    c->execute();

  EXPECT_EQ (variableA, 7);
}

TEST(testCommand, UseCase2)
{
  //int variableA (10);
  //int variableB (5);
  variableA = 10;
  variableB = 5;
  MacroCommand commands;
  commands.push_back (new SimpleCommand(&variableA, std::bind (&divide, variableB)) );
  commands.push_back (new SimpleCommand(&variableA, std::bind (&add, variableB)) );

  EXPECT_EQ (variableA, 10);
  commands.execute();
  EXPECT_EQ (variableA, 7);
}

void divide(int var)
{
  std::cout << "divide() is called" << "\n";
  std::cout << "var:" << var << "\n";
  variableA =  variableA / var;
}

void add(int var)
{
  std::cout << "add() is called" << "\n";
  std::cout << "var:" << var << "\n";
  variableA =  variableA + var;
}

